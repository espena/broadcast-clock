#include "lea_m8t.hpp"
#include "configuration.hpp"
#include "ubx_types.hpp"
#include "../utils/fletcher8.hpp"
#include "../utils/hexdump.hpp"
#include <string>
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portmacro.h>
#include <freertos/timers.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <driver/i2c_master.h>
#include <esp_timer.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::lea_m8t::m_component_name = "lea_m8t";

int64_t broadcast_clock::lea_m8t::m_ns_timepulse = 0;
int64_t broadcast_clock::lea_m8t::m_ns_mismatch = 0;

broadcast_clock::lea_m8t::
lea_m8t() : m_i2c_bus( nullptr ),
            m_i2c_dev( nullptr ) {

  spinlock_initialize( &m_spinlock );

  memset( &m_cfg_prt_ddc, 0x00, sizeof( ubx::cfg_prt_ddc_t ) );
  memset( &m_cfg_tmode2, 0x00, sizeof( ubx::cfg_tmode2_t ) );
  memset( &m_cfg_gnss, 0x00, sizeof( ubx::cfg_gnss_t ) );
  memset( &m_cfg_ant, 0x00, sizeof( ubx::cfg_ant_t ) );
  
  memset( &m_nav_sat, 0x00, sizeof( ubx::nav_sat_t ) );  

  m_task_queue = xQueueCreate( 8192, sizeof( lea_m8t_task_queue_item_t ) );
  m_egress_queue = xQueueCreate( 4096, sizeof( lea_m8t_egress_queue_item_t ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &lea_m8t::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     2,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer );

  esp_timer_create_args_t timer_args;
  memset( &timer_args, 0x00, sizeof( esp_timer_create_args_t ) );
  timer_args.callback = &on_poll_timer;
  timer_args.arg = this;
  timer_args.name = "poll_timer";

  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &m_poll_timer ) );
  ESP_ERROR_CHECK( esp_timer_start_periodic( m_poll_timer, 250000 ) );
}

broadcast_clock::lea_m8t::
~lea_m8t() {

}

void broadcast_clock::lea_m8t::
task_loop( void *arg ) {
  lea_m8t_task_params *params = static_cast<lea_m8t_task_params *>( arg );
  lea_m8t *inst = params->instance;
  lea_m8t_task_queue_item_t item;
  memset( &item, 0x00, sizeof( lea_m8t_task_queue_item_t ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, -1 ) ) {
      inst->on_task_message( item.message, item.arg );
    }
  }
}

void broadcast_clock::lea_m8t::
on_poll_timer( void *arg ) {
  lea_m8t *inst = static_cast<lea_m8t *>( arg );
  if( inst ) {
    if( inst->m_i2c_dev != nullptr ) {
      lea_m8t_task_queue_item_t item = { lea_m8t_task_message::poll, nullptr };
      xQueueSend( inst->m_task_queue, &item, 0 );
    }
  }
}

uint16_t broadcast_clock::lea_m8t::
get_bytes_available() {

  uint8_t cmd_rx_buf[ 2 ] = { 0x00, 0x01 };
  uint8_t addr = 0xfd;
  
  if( m_i2c_dev != nullptr ) {

    esp_err_t res = -1;
    uint8_t retries = 0;
    
    while( res != ESP_OK && retries++ < 10 ) {
      
      i2c_master_bus_wait_all_done( m_i2c_bus, -1 );

      res = i2c_master_transmit_receive( m_i2c_dev,
                                         &addr,
                                         1,
                                         cmd_rx_buf,
                                         2,
                                         1000 );
    }

    if( res != ESP_OK ) {
      ESP_LOGE( m_component_name, "Failed to read bytes available" );
    }
  }
  return ( cmd_rx_buf[ 0 ] << 8 & 0xff00 ) | ( cmd_rx_buf[ 1 ] & 0x00ff );
}

void broadcast_clock::lea_m8t::
read() {

  if( m_i2c_dev == nullptr ) {
    return;
  }

  uint16_t bytes_available = get_bytes_available();
  if( bytes_available == 0 ) {
    return;
  }

  ESP_LOGI( m_component_name, "Bytes available: %d", bytes_available );

  uint8_t *cmd_rx_buf = new uint8_t[ bytes_available ];
  uint8_t addr = 0xff;
  uint16_t offset = 0;

  esp_err_t res = -1;
  uint8_t retries = 0;
  
  while( res != ESP_OK && retries++ < 10 ) {

    i2c_master_bus_wait_all_done( m_i2c_bus, -1 );
    
    res = i2c_master_transmit_receive( m_i2c_dev,
                                       &addr,
                                       1,
                                       cmd_rx_buf,
                                       bytes_available,
                                       1000 );
  }

  if( res != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to read bytes available" );
  }
  else if( retries > 1 ) {
    ESP_LOGW( m_component_name, "Read operation succeeded after %d attempts", retries );
  }
  else {
    ESP_LOGI( m_component_name, "Read operation succeeded on first attempt" );
  }

  utils::hexdump( cmd_rx_buf, bytes_available );
  ESP_LOGI( m_component_name, "String repr.: %s", cmd_rx_buf );
  
  while( offset < ( bytes_available - 8 ) && cmd_rx_buf[ offset ] != 0xb5 && cmd_rx_buf[ offset + 1 ] != 0x62 ) {
    offset++; // Fast forward to first UBX message
  }

  while( offset < ( bytes_available - 8 ) &&
          cmd_rx_buf[ offset ] == 0xb5 &&
          cmd_rx_buf[ offset + 1 ] == 0x62 )
  {
    const uint8_t msg_class = cmd_rx_buf[ offset + 2 ];
    const uint8_t msg_id = cmd_rx_buf[ offset + 3 ];
    const uint16_t len = ( cmd_rx_buf[ offset + 5 ] << 8 & 0xff00 ) | ( cmd_rx_buf[ offset + 4 ] & 0x00ff );

    if( offset + len + 8 > bytes_available ) {
      ESP_LOGE( m_component_name, "Message length exceeds buffer length for cls %d id %d", msg_class, msg_id );
      break;
    } 

    const uint8_t fletcher_a = cmd_rx_buf[ offset + len + 6 ];
    const uint8_t fletcher_b = cmd_rx_buf[ offset + len + 7 ];
    utils::fletcher8( &cmd_rx_buf[ offset + 2 ], len + 4, &cmd_rx_buf[ offset + len + 6 ] );
    if( fletcher_a != cmd_rx_buf[ offset + len + 6 ] || fletcher_b != cmd_rx_buf[ offset + len + 7 ] ) {
      ESP_LOGE( m_component_name, "Fletcher checksum failed for cls %d id %d", msg_class, msg_id );
      offset += len + 8;
      continue;
    }

    if( msg_class == ubx::message::ack::cls ) {
      m_ack = msg_id; // Resume writing messages after receiving ACK
    }
    
    utils::hexdump( &cmd_rx_buf[ offset ], len + 8 );
    on_ubx_message( msg_class, msg_id, len > 0 ? &cmd_rx_buf[ offset + 6 ] : nullptr, len );

    offset += len + 8;
  }
  delete [] cmd_rx_buf;

}

void broadcast_clock::lea_m8t::
write() {
  lea_m8t_egress_queue_item_t item;
  if( m_i2c_dev != nullptr ) {
    while( m_ack != 0xff && xQueueReceive( m_egress_queue, &item, 0 ) ) {
      ESP_LOGI( m_component_name, "Writing message: class: 0x%02x, id: 0x%02x", item.message.cls, item.message.id );
      uint16_t buflen = 8 + item.len;
      uint8_t *msg = new uint8_t[ buflen ];
      int i = 0;
      msg[ i++ ] = 0xb5;
      msg[ i++ ] = 0x62;
      msg[ i++ ] = item.message.cls;
      msg[ i++ ] = item.message.id;
      msg[ i++ ] = item.len & 0x00ff;
      msg[ i++ ] = ( item.len >> 8 ) & 0x00ff;
      if( item.acked ) {
        m_ack = 0xff; // Stop writing subsequent messages until next ack is received
      }
      if( item.len > 0 ) {
        memcpy( &msg[ i ], item.deletable_payload, item.len );
        i += item.len;
      }
      utils::fletcher8( &msg[ 2 ], i - 2, &msg[ i ] );
      
      printf( "Writing message\n" );
      printf( "***************************************************\n" );
      utils::hexdump( msg, buflen );
      
      i2c_master_bus_wait_all_done( m_i2c_bus, -1 );
      //i2c_master_bus_reset( m_i2c_bus );

      i2c_master_transmit( m_i2c_dev,
                           msg,
                           buflen,
                           1000 );
      delete [] msg;
      delete [] item.deletable_payload;
    }
  }
}

void broadcast_clock::lea_m8t::
on_task_message( lea_m8t_task_message msg, void *arg ) {
  switch( msg ) {
    case lea_m8t_task_message::init:
      on_init( static_cast<i2c_master_bus_handle_t>( arg ) );
      break;
    case lea_m8t_task_message::poll:
      read();
      write();
      break;
    case lea_m8t_task_message::timepulse:
      on_timepulse();
      break;
  }
}

void broadcast_clock::lea_m8t::
on_ubx_message( const uint8_t msg_class,
                const uint8_t msg_id,
                void *payload,
                const uint16_t len ) {

  ESP_LOGI( m_component_name, "UBX message: class: 0x%02x, id: 0x%02x", msg_class, msg_id );

  switch( msg_class ) {
    case ubx::message::cfg::cls:
      switch( msg_id ) {
        case ubx::message::cfg::prt:
          if( payload != nullptr ) {
            const uint8_t port_id = *static_cast<uint8_t *>( payload );
            switch( port_id ) {
              case 0x00:
                on_ubx_cfg_prt( static_cast<ubx::cfg_prt_ddc_t *>( payload ) );
                break;
            }
          }
          break;
        case ubx::message::cfg::tmode2:
          if( payload != nullptr ) {
            on_ubx_cfg_tmode2( static_cast<ubx::cfg_tmode2_t *>( payload ) );
          }
          break;
        case ubx::message::cfg::gnss:
          if( payload != nullptr ) {
            on_ubx_cfg_gnss( static_cast<ubx::cfg_gnss_t *>( payload ) );
          }
          break;
        case ubx::message::cfg::ant:
          if( payload != nullptr ) {
            on_ubx_cfg_ant( static_cast<ubx::cfg_ant_t *>( payload ) );
          }
          break;
      }
      break;
    case ubx::message::mon::cls:
      switch( msg_id ) {
        case ubx::message::mon::hw:
          on_ubx_mon_hw( static_cast<ubx::mon_hw_t *>( payload ) );
          break;
      }
      break;
    case ubx::message::nav::cls:
      switch( msg_id ) {
        case ubx::message::nav::sat:
          on_ubx_nav_sat( static_cast<ubx::nav_sat_t *>( payload ) );
          break;
        case ubx::message::nav::timeutc:
          on_ubx_nav_timeutc( static_cast<ubx::nav_timeutc_t *>( payload ) );
          break;
      }
      break;
    case ubx::message::ack::cls:
      switch( msg_id ) {
        case ubx::message::ack::ack: // fallthru
        case ubx::message::ack::nak:
          ESP_LOGI( m_component_name, "UBX_ACK: 0x%02x", msg_id );
          break;
      }
      break;
  }

}

void broadcast_clock::lea_m8t::
on_ubx_cfg_ant( ubx::cfg_ant_t *ant ) {
  ESP_LOGI( m_component_name, "UBX_CFG_ANT" );
  memcpy( &m_cfg_ant, ant, sizeof( ubx::cfg_ant_t ) );
  ESP_LOGI( m_component_name, "Antenna supply voltage control enabled: 0x%02x", ant->flags.svcs );
  ESP_LOGI( m_component_name, "Antenna short circuit detection enabled: 0x%02x", ant->flags.scd );
  ESP_LOGI( m_component_name, "Antenna open circuit detection enabled: 0x%02x", ant->flags.ocd );
  ESP_LOGI( m_component_name, "Power down antenna supply on short circuit: 0x%02x", ant->flags.pdwn_on_scd );
  ESP_LOGI( m_component_name, "Enable automatic recovery from short circuit: 0x%02x", ant->flags.recovery );
  ESP_LOGI( m_component_name, "PIO pin used for switching antenna supply: %d", ant->pins.pin_switch );
  ESP_LOGI( m_component_name, "PIO pin used for detecting short circuit: %d", ant->pins.pin_scd );
  ESP_LOGI( m_component_name, "PIO pin used for detecting open or not connected: %d", ant->pins.pin_ocd );
  ESP_LOGI( m_component_name, "Reconfiguring: 0x%02x", ant->pins.reconfig );
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_prt( ubx::cfg_prt_ddc_t *prt ) {
  ESP_LOGI( m_component_name, "UBX_CFG_PRT" );
  memcpy( &m_cfg_prt_ddc, prt, sizeof( ubx::cfg_prt_ddc_t ) );
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_tmode2( ubx::cfg_tmode2_t *tmode2 ) {
  ESP_LOGI( m_component_name, "UBX_CFG_TMODE2" );
  memcpy( &m_cfg_tmode2, tmode2, sizeof( ubx::cfg_tmode2_t ) );
  const char *loc_fmt = tmode2->flags.lla == 0 ? "ECEF" : "LAT/LON";
  ESP_LOGI( m_component_name, "Time mode: %s", tmode2->time_mode == 0 ? "Disabled" : ( tmode2->time_mode == 1 ? "Survey-in" : "Fixed mode" ) );
  ESP_LOGI( m_component_name, "Location format: %s", loc_fmt );
  ESP_LOGI( m_component_name, "Altitude valid: %s", tmode2->flags.alt_inv == 0 ? "No" : "Yes" );
  ESP_LOGI( m_component_name, "%s X: %lu", loc_fmt, tmode2->ecef_x_or_lat );
  ESP_LOGI( m_component_name, "%s Y: %lu", loc_fmt, tmode2->ecef_y_or_lon );
  ESP_LOGI( m_component_name, "%s Z: %lu", loc_fmt, tmode2->ecef_z_or_alt );
  ESP_LOGI( m_component_name, "Fixed pos. accuracy (mm): %lu", tmode2->fixed_pos_acc );
  ESP_LOGI( m_component_name, "Survey-in minimum duration: %lu", tmode2->svin_min_dur );
  ESP_LOGI( m_component_name, "Survey-in position accuracy limit: %lu", tmode2->svin_acc_limit );
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_gnss( ubx::cfg_gnss_t *gnss ) {
  memcpy( &m_cfg_gnss, gnss, sizeof( ubx::cfg_gnss_t ) );
}

void broadcast_clock::lea_m8t::
on_ubx_mon_hw( ubx::mon_hw_t *hw ) {
  ESP_LOGI( m_component_name, "UBX_MON_HW" );
  uint8_t safeboot_active = ( hw->flags & 0b00000010 ) >> 1;
  ESP_LOGI( m_component_name, "Safeboot active: %d", safeboot_active );
  if( safeboot_active ) {
    ESP_LOGI( m_component_name, "Initializing safe boot" );
    init_ubx_safeboot();
  }
  else {
    ESP_LOGI( m_component_name, "Initializing normal boot" );
    init_ubx_normalboot();
  }
}

void broadcast_clock::lea_m8t::
on_ubx_nav_sat( ubx::nav_sat_t *sat ) {
  ESP_LOGI( m_component_name, "UBX_NAV_SAT" );
  ESP_LOGI( m_component_name, "Number of satellites: %d", sat->num_svs );
  memcpy( &m_nav_sat, sat, sizeof( ubx::nav_sat_t ) );
}

void broadcast_clock::lea_m8t::
on_ubx_nav_timeutc( ubx::nav_timeutc_t *timeutc ) {

  if( m_ns_timepulse > 0 ) {

    struct tm now_tm;
    memset( &now_tm, 0x00, sizeof( struct tm ) );
    
    now_tm.tm_year = timeutc->year - 1900; // tm_year is years since 1900
    now_tm.tm_mon = timeutc->month - 1;    // tm_mon is 0-based
    now_tm.tm_mday = timeutc->day;
    now_tm.tm_hour = timeutc->hour;
    now_tm.tm_min = timeutc->min;
    now_tm.tm_sec = timeutc->sec;
    now_tm.tm_isdst = -1;

    char *tz = getenv( "TZ" );
    if( tz != nullptr ) {
      tz = strdup( tz );
    } 
    setenv( "TZ", "UTC0", 1 );
    tzset();
    time_t now_time = mktime( &now_tm );
    if( tz != nullptr ) {
      setenv( "TZ", tz, 1 );
      free( tz );
    }

    taskENTER_CRITICAL( &m_spinlock );

    struct timespec now_spec;
    clock_gettime( CLOCK_REALTIME, &now_spec );

    int64_t now_ns = now_spec.tv_sec * 1000000000 + now_spec.tv_nsec;
    int64_t ns_since_timepulse = now_ns - m_ns_timepulse;

    if( ns_since_timepulse < 1000000000 ) {
      if( now_time != -1 ) {

        const int adj_ns = 34000;

        now_spec.tv_sec = now_time;
        now_spec.tv_nsec = ns_since_timepulse + adj_ns;
        clock_settime( CLOCK_REALTIME, &now_spec );
      }
    }

    m_ns_timepulse = 0;
    
    taskEXIT_CRITICAL( &m_spinlock );
  }
}

void broadcast_clock::lea_m8t::
timepulse_handler( void *arg ) {

  UBaseType_t critical_section = taskENTER_CRITICAL_FROM_ISR();
  {
    struct timespec now;
    clock_gettime( CLOCK_REALTIME, &now );
    m_ns_timepulse = now.tv_sec * 1000000000 + now.tv_nsec;
    m_ns_mismatch = now.tv_nsec; //< Should be as close to zero as possible
  }
  taskEXIT_CRITICAL_FROM_ISR( critical_section );

  lea_m8t *inst = static_cast<lea_m8t *>( arg );
  lea_m8t::lea_m8t_task_queue_item_t item = { lea_m8t::lea_m8t_task_message::timepulse, nullptr };
  xQueueSendFromISR( inst->m_task_queue, &item, nullptr );

}

void broadcast_clock::lea_m8t::
on_timepulse() {
  ESP_LOGW( m_component_name, "Timepulse offset from system clock: %lli ns", m_ns_mismatch );
}

bool broadcast_clock::lea_m8t::
is_present() {
  return i2c_master_probe( m_i2c_bus, m_i2c_address, 1000 ) == ESP_OK;
}

void broadcast_clock::lea_m8t::
init_isr_timepulse() {
  ESP_LOGI( m_component_name, "Configure timpulse interrupt" );
  ESP_ERROR_CHECK( gpio_install_isr_service( 0 ) );
  ESP_ERROR_CHECK( gpio_set_direction( LEA_M8T_TIMEPULSE, GPIO_MODE_INPUT ) );
  ESP_ERROR_CHECK( gpio_set_intr_type( LEA_M8T_TIMEPULSE, GPIO_INTR_POSEDGE ) );
  ESP_ERROR_CHECK( gpio_isr_handler_add( LEA_M8T_TIMEPULSE, &timepulse_handler, this ) );
}

void broadcast_clock::lea_m8t::
init_i2c_device() {
  ESP_LOGI( m_component_name, "Initializing i2c device" );
  i2c_device_config_t dev_cfg;
  memset( &dev_cfg, 0x00, sizeof( i2c_device_config_t ) );
  dev_cfg.dev_addr_length = I2C_ADDR_BIT_LEN_7;
  dev_cfg.device_address = m_i2c_address;
  dev_cfg.scl_speed_hz = 5000; // 5 kHz was as fast as I could get it to work...
  dev_cfg.flags.disable_ack_check = 0; // < Must be 0 to work with u-blox module
  dev_cfg.scl_wait_us = 10000000;
  ESP_LOGI( m_component_name, "Adding device to i2c bus" );
  ESP_ERROR_CHECK( i2c_master_bus_add_device( m_i2c_bus, &dev_cfg, &m_i2c_dev ) );
  ESP_LOGI( m_component_name, "Device added, OK!" );
}

void broadcast_clock::lea_m8t::
init_ubx_normalboot() {

  { // Set port configuration
    ubx::cfg_prt_ddc_t *payload = new ubx::cfg_prt_ddc_t;
    memset( payload, 0x00, sizeof( ubx::cfg_prt_ddc_t ));
    payload->port_id = 0x00; // DDC
    payload->tx_ready = 0x0000; // Disable tx_ready pin
    payload->mode = ( m_i2c_address << 1 );
    payload->in_proto_mask |= 0x0001; // UBX
    payload->out_proto_mask |= 0x0001; // UBX
    payload->flags = 0x0000;
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { sizeof( ubx::cfg_prt_ddc_t ), { ubx::message::cfg::cls, ubx::message::cfg::prt }, reinterpret_cast<uint8_t *>( payload ), false };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 0 );
  }

  { // Disable all NMEA messages

    const uint8_t messages[][2] = {
      {0xF0, 0x0A}, // DTM
      {0xF0, 0x44}, // GBQ
      {0xF0, 0x09}, // GBS
      {0xF0, 0x00}, // GGA
      {0xF0, 0x01}, // GLL
      {0xF0, 0x43}, // GLQ
      {0xF0, 0x42}, // GNQ
      {0xF0, 0x0D}, // GNS
      {0xF0, 0x40}, // GPQ
      {0xF0, 0x06}, // GRS
      {0xF0, 0x02}, // GSA
      {0xF0, 0x07}, // GST
      {0xF0, 0x03}, // GSV
      {0xF0, 0x04}, // RMC
      {0xF0, 0x0E}, // THS
      {0xF0, 0x41}, // TXT
      {0xF0, 0x0F}, // VLW
      {0xF0, 0x05}, // VTG
      {0xF0, 0x08}  // ZDA
    };

    for( size_t i = 0; i < sizeof( messages ) / sizeof( messages[ 0 ] ); ++i ) {
        uint8_t *payload = new uint8_t[3];
        payload[0] = messages[i][0]; // Message class
        payload[1] = messages[i][1]; // Message ID
        payload[2] = 0x00;           // Rate: disable message
        lea_m8t_egress_queue_item_t ubx_cfg_msg = {3, {ubx::message::cfg::cls, ubx::message::cfg::msg}, payload, false};
        xQueueSend(m_egress_queue, &ubx_cfg_msg, 10);
    }

  }

  { // Set message rate
    ubx::cfg_rate_t *payload = new ubx::cfg_rate_t;
    payload->meas_rate = 500;
    payload->nav_rate = 32;
    payload->time_ref = 1;
    lea_m8t_egress_queue_item_t ubx_cfg_rate = { sizeof( ubx::cfg_rate_t ), { ubx::message::cfg::cls, ubx::message::cfg::rate }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_rate, 0 );
  }

  { // Poll UBX-NAV-TIMEUTC
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::timeutc;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }


}

void broadcast_clock::lea_m8t::
init_ubx_safeboot() {

  { // Set port configuration
    ubx::cfg_prt_ddc_t *payload = new ubx::cfg_prt_ddc_t;
    memset( payload, 0x00, sizeof( ubx::cfg_prt_ddc_t ));
    payload->port_id = 0x00; // DDC
    payload->tx_ready = 0x0000; // Disable tx_ready pin
    payload->mode = ( m_i2c_address << 1 );
    payload->in_proto_mask |= 0x0001; // UBX
    payload->out_proto_mask |= 0x0001; // UBX
    payload->flags = 0x0000;
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { sizeof( ubx::cfg_prt_ddc_t ), { ubx::message::cfg::cls, ubx::message::cfg::prt }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 0 );
  }

  { // Set message rate
    ubx::cfg_rate_t *payload = new ubx::cfg_rate_t;
    payload->meas_rate = 500;
    payload->nav_rate = 1;
    payload->time_ref = 1;
    lea_m8t_egress_queue_item_t ubx_cfg_rate = { sizeof( ubx::cfg_rate_t ), { ubx::message::cfg::cls, ubx::message::cfg::rate }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_rate, 0 );
  }

  { // Disable all messages


    const uint8_t messages[][2] = {
      {0x01, 0x07}, // NAV-PVT
      {0x01, 0x35}, // NAV-SAT
      {0x01, 0x03}, // NAV-STATUS
      {0x01, 0x06}, // NAV-SOL
      {0x01, 0x02}, // NAV-POSLLH
      {0x01, 0x12}, // NAV-VELNED
      {0x01, 0x21}, // NAV-TIMEUTC
      {0x02, 0x13}, // RXM-RAWX
      {0x02, 0x15}, // RXM-SFRBX
      {0x0A, 0x04}, // MON-VER
      {0x0A, 0x09}, // MON-HW
      {0x0A, 0x06}, // MON-MSGPP
      {0x0A, 0x07}, // MON-RXBUF
      {0x0A, 0x08}, // MON-TXBUF
      {0x0A, 0x21}, // MON-RF
      // NMEA
      {0xF0, 0x0A}, // DTM
      {0xF0, 0x44}, // GBQ
      {0xF0, 0x09}, // GBS
      {0xF0, 0x00}, // GGA
      {0xF0, 0x01}, // GLL
      {0xF0, 0x43}, // GLQ
      {0xF0, 0x42}, // GNQ
      {0xF0, 0x0D}, // GNS
      {0xF0, 0x40}, // GPQ
      {0xF0, 0x06}, // GRS
      {0xF0, 0x02}, // GSA
      {0xF0, 0x07}, // GST
      {0xF0, 0x03}, // GSV
      {0xF0, 0x04}, // RMC
      {0xF0, 0x0E}, // THS
      {0xF0, 0x41}, // TXT
      {0xF0, 0x0F}, // VLW
      {0xF0, 0x05}, // VTG
      {0xF0, 0x08}  // ZDA
    };

    for( size_t i = 0; i < sizeof( messages ) / sizeof( messages[ 0 ] ); ++i ) {
        uint8_t *payload = new uint8_t[ 3 ];
        payload[0] = messages[i][0]; // Message class
        payload[1] = messages[i][1]; // Message ID
        payload[2] = 0x00;           // Rate: disable message
        lea_m8t_egress_queue_item_t ubx_cfg_msg = {3, {ubx::message::cfg::cls, ubx::message::cfg::msg}, payload, true};
        xQueueSend(m_egress_queue, &ubx_cfg_msg, 10);
    }

  }

  { // Save configuration
    uint8_t *payload = new uint8_t[ 13 ];

    payload[ 0 ] = 0b00000000;
    payload[ 1 ] = 0b00000000;
    payload[ 2 ] = 0b00000000;
    payload[ 3 ] = 0b00000000;

    payload[ 4 ] = 0b00001011; // Save PRT, MSG and NAV
    payload[ 5 ] = 0b00000000;
    payload[ 6 ] = 0b00000000;
    payload[ 7 ] = 0b00000000;

    payload[ 8 ] = 0b00000000;
    payload[ 9 ] = 0b00000000;
    payload[ 10 ] = 0b00000000;
    payload[ 11 ] = 0b00000000;

    payload[ 13 ] = 0b00000001; // Write to EEPROM

    lea_m8t_egress_queue_item_t ubx_cfg_cfg = { 13, { ubx::message::cfg::cls, ubx::message::cfg::cfg }, payload, false };
    xQueueSend( m_egress_queue, &ubx_cfg_cfg, 0 );
  }

}

void broadcast_clock::lea_m8t::
init_ubx() {

  init_ubx_normalboot();
  

  /*

  { // Poll UBX-MON-HW
    lea_m8t_egress_queue_item_t ubx_mon_hw = { 0, { ubx::message::mon::cls, ubx::message::mon::hw }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_hw, 0 );
  }

  { // Poll UBX-NAV-SAT
    lea_m8t_egress_queue_item_t ubx_nav_sat = { 0, { ubx::message::nav::cls, ubx::message::nav::sat }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_nav_sat, 0 );
  }

  { // Poll UBX-NAV-SAT
    lea_m8t_egress_queue_item_t ubx_nav_sat = { 0, { ubx::message::nav::cls, ubx::message::nav::sat }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_nav_sat, 0 );
  }


  { // Poll UBX-NAV-SAT
    lea_m8t_egress_queue_item_t ubx_nav_sat = { 0, { ubx::message::nav::cls, ubx::message::nav::sat }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_nav_sat, 0 );
  }


  { // Set port configuration
    ubx::cfg_prt_ddc_t *payload = new ubx::cfg_prt_ddc_t;
    memset( payload, 0x00, sizeof( ubx::cfg_prt_ddc_t ));
    payload->port_id = 0x00; // DDC
    payload->tx_ready = 0x0000; // Disable tx_ready pin
    payload->mode = ( m_i2c_address << 1 );
    payload->in_proto_mask |= 0x0001; // UBX
    payload->out_proto_mask |= 0x0001; // UBX
    payload->flags = 0x0000;
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { sizeof( ubx::cfg_prt_ddc_t ), { ubx::message::cfg::cls, ubx::message::cfg::prt }, reinterpret_cast<uint8_t *>( payload ), false };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 0 );
  }

  { // Get software and hardware versions
    lea_m8t_egress_queue_item_t ubx_mon_ver = { 0, { ubx::message::mon::cls, ubx::message::mon::ver }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_ver, 10 );
  }

  { // Get port configuration
    uint8_t *payload = new uint8_t;
    *payload = 0x00; // Port ID (DDC)
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { 1, { ubx::message::cfg::cls, ubx::message::cfg::prt }, payload, false };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 0 );
  }



  { // Poll UBX-NAV-TIMEGPS
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::timegps;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }

  { // Set message rate
    ubx::cfg_rate_t *payload = new ubx::cfg_rate_t;
    payload->meas_rate = 50;
    payload->nav_rate = 1;
    payload->time_ref = 1;
    lea_m8t_egress_queue_item_t ubx_cfg_rate = { sizeof( ubx::cfg_rate_t ), { ubx::message::cfg::cls, ubx::message::cfg::rate }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_rate, 0 );
  }

  { // Poll UBX-NAV-TIMEGPS
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::timegps;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }

  { // Poll UBX-NAV-SAT
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::sat;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }


  { // Poll UBX-NAV-SAT
    lea_m8t_egress_queue_item_t ubx_nav_sat = { 0, { ubx::message::nav::cls, ubx::message::nav::sat }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_nav_sat, 0 );
  }


  
  { // Get software and hardware versions
    lea_m8t_egress_queue_item_t ubx_mon_ver = { 0, { ubx::message::mon::cls, ubx::message::mon::ver }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_ver, 10 );
  }


  { // Get software and hardware versions
    lea_m8t_egress_queue_item_t ubx_mon_ver = { 0, { ubx::message::mon::cls, ubx::message::mon::ver }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_ver, 10 );
  }



  ESP_LOGI( m_component_name, "Initializing UBX" );

  { // Hardware status
    lea_m8t_egress_queue_item_t ubx_mon_hw = { 0, { ubx::message::mon::cls, ubx::message::mon::hw }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_hw, 10 );
  }




  { // Set port configuration
    ubx::cfg_prt_ddc_t *payload = new ubx::cfg_prt_ddc_t;
    memset( payload, 0x00, sizeof( ubx::cfg_prt_ddc_t ));
    payload->port_id = 0x00; // DDC
    payload->tx_ready.enable = 0;
    payload->mode.slave_addr = 66;
    payload->in_proto_mask.ubx = 1;
    payload->out_proto_mask.ubx = 1;
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { sizeof( ubx::cfg_prt_ddc_t ), { ubx::message::cfg::cls, ubx::message::cfg::prt }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 10 );
  }

  { // Get antenna settings
    lea_m8t_egress_queue_item_t ubx_cfg_ant = { 0, { ubx::message::cfg::cls, ubx::message::cfg::ant }, nullptr, true };
    xQueueSend( m_egress_queue, &ubx_cfg_ant, 0 );
  }

  { // Set antenna settings
    ubx::cfg_ant_t *payload = new ubx::cfg_ant_t;
    memcpy( payload, &m_cfg_ant, sizeof( ubx::cfg_ant_t ) );
    payload->flags.svcs = 0x00;
    payload->flags.scd = 0x00;
    payload->flags.ocd = 0x00;
    payload->flags.pdwn_on_scd = 0x00;
    payload->flags.recovery = 0x00;
    lea_m8t_egress_queue_item_t ubx_cfg_ant = { sizeof( ubx::cfg_ant_t ), { ubx::message::cfg::cls, ubx::message::cfg::ant }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_ant, 10 );
  }

  { // Get antenna settings
    lea_m8t_egress_queue_item_t ubx_cfg_ant = { 0, { ubx::message::cfg::cls, ubx::message::cfg::ant }, nullptr, true };
    xQueueSend( m_egress_queue, &ubx_cfg_ant, 0 );
  }

  { // Hardware status
    lea_m8t_egress_queue_item_t ubx_mon_hw = { 0, { ubx::message::mon::cls, ubx::message::mon::hw }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_hw, 10 );
  }

  { // Poll UBX-NAV-SAT
    lea_m8t_egress_queue_item_t ubx_nav_sat = { 0, { ubx::message::nav::cls, ubx::message::nav::sat }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_nav_sat, 0 );
  }



  */



  /*
  { // Set message rate
    ubx::cfg_rate_t *payload = new ubx::cfg_rate_t;
    payload->meas_rate = 1000;
    payload->nav_rate = 10;
    payload->time_ref = 0;
    lea_m8t_egress_queue_item_t ubx_cfg_rate = { sizeof( ubx::cfg_rate_t ), { ubx::message::cfg::cls, ubx::message::cfg::rate }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_rate, 0 );
  }

  { // Get software and hardware versions
    lea_m8t_egress_queue_item_t ubx_mon_ver = { 0, { ubx::message::mon::cls, ubx::message::mon::ver }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_ver, 10 );
  }

  {
    // Get time mode
    lea_m8t_egress_queue_item_t ubx_cfg_tmode2 = { 0, { ubx::message::cfg::cls, ubx::message::cfg::tmode3 }, nullptr, true };
    ubx::cfg_tmode2_t *tmode2 = new ubx::cfg_tmode2_t;
    memset( tmode2, 0x00, sizeof( ubx::cfg_tmode2_t ) );
    tmode2->time_mode = 1; // Survey-in
    tmode2->flags.lla = 1;
    tmode2->flags.alt_inv = 1;
    tmode2->ecef_x_or_lat = 0;
    tmode2->ecef_y_or_lon = 0;
    tmode2->ecef_z_or_alt = 0;
    tmode2->fixed_pos_acc = 10000;
    tmode2->svin_min_dur = 60;
    tmode2->svin_acc_limit = 10000;
    ubx_cfg_tmode2.len = sizeof( ubx::cfg_tmode2_t );
    ubx_cfg_tmode2.deletable_payload = reinterpret_cast<uint8_t *>( tmode2 );
    ubx_cfg_tmode2.acked = true;
    xQueueSend( m_egress_queue, &ubx_cfg_tmode2, 10 );
  }
  */

  /*
  { // Start GNSS
    ubx::cfg_rst_t *payload = new ubx::cfg_rst_t; // Reset
    memset( payload, 0x00, sizeof( ubx::cfg_rst_t ) );
    payload->nav_bbr_mask = 0x0000; // Warm start
    payload->reset_mode = 0x09; // Controlled GNSS start
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { sizeof( ubx::cfg_rst_t ), { ubx::message::cfg::cls, ubx::message::cfg::rst }, reinterpret_cast<uint8_t *>( payload ), false };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 10 );
  }

  {
    // Get GNSS
    lea_m8t_egress_queue_item_t ubx_cfg_gnss = { 0, { ubx::message::cfg::cls, ubx::message::cfg::gnss }, nullptr, true };
    xQueueSend( m_egress_queue, &ubx_cfg_gnss, 10 );
  }

  */

  /*

  { // Set port configuration
    ubx::cfg_prt_ddc_t *payload = new ubx::cfg_prt_ddc_t;
    memset( payload, 0x00, sizeof( ubx::cfg_prt_ddc_t ));
    payload->port_id = 0x00; // DDC
    payload->tx_ready.enable = 0;
    payload->mode.slave_addr = 66;
    payload->in_proto_mask.ubx = 1;
    payload->out_proto_mask.ubx = 1;
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { sizeof( ubx::cfg_prt_ddc_t ), { ubx::message::cfg::cls, ubx::message::cfg::prt }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 10 );
  }


  { // Enable UBX-NAV-SAT
    uint8_t *payload = new uint8_t[ 3 ];
    //payload[ 0 ] = 0x0a;
    //payload[ 1 ] = 0x06;
    //payload[ 2 ] = 0x01;
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::sat;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }

  { // Poll UBX-NAV-SAT
    lea_m8t_egress_queue_item_t ubx_nav_sat = { 0, { ubx::message::nav::cls, ubx::message::nav::sat }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_nav_sat, 0 );
  }

  



  */


  /*

  {
    ubx::cfg_tmode2_t *payload = new ubx::cfg_tmode2_t;
    memset( payload, 0x00, sizeof( ubx::cfg_tmode2_t ));
    payload->time_mode = 2; // Survey-in mode
    payload->flags.lla = 1;
    payload->flags.alt_inv = 1;
    payload->ecef_x_or_lat = 102931153; // Example fixed position latitude
    payload->ecef_y_or_lon = 600942397; // Example fixed position longitude
    payload->ecef_z_or_alt = 0; // Example fixed position altitude
    payload->fixed_pos_acc = 10000; // Fixed position accuracy
    payload->svin_min_dur = 60; // Survey-in minimum duration
    payload->svin_acc_limit = 10000; // Survey-in accuracy limit
    lea_m8t_egress_queue_item_t ubx_cfg_tmode2 = {
        sizeof(ubx::cfg_tmode2_t),
        {
            ubx::message::cfg::cls,
            ubx::message::cfg::tmode2
        },
        reinterpret_cast<uint8_t *>(payload),
        true
    };
  }


  {
    ubx::cfg_tmode2_t *payload = new ubx::cfg_tmode2_t;
    memset( payload, 0x00, sizeof( ubx::cfg_tmode2_t ));
    payload->time_mode = 1; // Survey-in mode
    payload->flags.lla = 1;
    payload->flags.alt_inv = 1;
    payload->ecef_x_or_lat = 102931153; // Example fixed position latitude
    payload->ecef_y_or_lon = 600942397; // Example fixed position longitude
    payload->ecef_z_or_alt = 0; // Example fixed position altitude
    payload->fixed_pos_acc = 10000; // Fixed position accuracy
    payload->svin_min_dur = 60; // Survey-in minimum duration
    payload->svin_acc_limit = 10000; // Survey-in accuracy limit
    lea_m8t_egress_queue_item_t ubx_cfg_tmode2 = {
        sizeof(ubx::cfg_tmode2_t),
        {
            ubx::message::cfg::cls,
            ubx::message::cfg::tmode2
        },
        reinterpret_cast<uint8_t *>(payload),
        true
    };
  }
  

  { // Survey-in data
    lea_m8t_egress_queue_item_t ubx_tim_svin = { 0, { ubx::message::tim::cls, ubx::message::tim::svin }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_tim_svin, 10 );
  }

  { // Enable
    uint8_t *payload = new uint8_t[ 3 ];
    //payload[ 0 ] = 0x0a;
    //payload[ 1 ] = 0x06;
    //payload[ 2 ] = 0x01;
    payload[ 0 ] = 0x01;
    payload[ 1 ] = 0x22;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }
  { // Get port configuration
    uint8_t *payload = new uint8_t[ 1 ];
    *payload = 0x00;
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { 1, { ubx::message::cfg::cls, ubx::message::cfg::prt }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 10 );
  }
  */

  /*
  { // Enable
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::cfg::cls;
    payload[ 1 ] = ubx::message::cfg::prt;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }
  */

  /*
  { // Poll
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 0, { ubx::message::cfg::cls, ubx::message::cfg::prt }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 10 );
  }

  { // Enable UBX_TIM_SVIN messages
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::tim::cls;
    payload[ 1 ] = ubx::message::tim::svin;
    payload[ 2 ] = 0x01;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 10 );
  }

  { // Set message rate
    ubx::cfg_rate_t *payload = new ubx::cfg_rate_t;
    payload->meas_rate = 200;
    payload->nav_rate = 10;
    payload->time_ref = 0;
    lea_m8t_egress_queue_item_t ubx_cfg_rate = { sizeof( ubx::cfg_rate_t ), { ubx::message::cfg::cls, ubx::message::cfg::rate }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_rate, 0 );
  }
  */



  /*
  { // Enable UBX_NAV_SAT messages
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::sat;
    payload[ 2 ] = 0x10;
    payload[ 3 ] = 0x10;
    payload[ 4 ] = 0x10;
    payload[ 5 ] = 0x10;
    payload[ 6 ] = 0x10;
    payload[ 7 ] = 0x10;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 8, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 10 );
  }
  */

  /*
  { // Enable UBX_NAV_STATUS messages
    uint8_t *payload = new uint8_t[ 3 ];
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::status;
    payload[ 2 ] = 0x10;
    payload[ 3 ] = 0x10;
    payload[ 4 ] = 0x10;
    payload[ 5 ] = 0x10;
    payload[ 6 ] = 0x10;
    payload[ 7 ] = 0x10;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 8, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 10 );
  }
  */


  /*
  { // Get port configuration
    uint8_t *payload = new uint8_t[ 1 ];
    *payload = 0x00;
    lea_m8t_egress_queue_item_t ubx_cfg_prt = { 1, { ubx::message::cfg::cls, ubx::message::cfg::prt }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_prt, 10 );
  }
  */


}

void broadcast_clock::lea_m8t::
on_init( i2c_master_bus_handle_t i2c_bus ) {
  ESP_LOGI( m_component_name, "Initializing" );
  m_i2c_bus = i2c_bus;
  if( is_present() ) {
    ESP_LOGI( m_component_name, "LEA M8T found on i2c bus" );
    init_isr_timepulse();
    init_i2c_device();
    vTaskDelay( 500 / portTICK_PERIOD_MS );
    init_ubx();
  }
  else {
    ESP_LOGE( m_component_name, "Not found on i2c bus" );
  }
}

void broadcast_clock::lea_m8t::
init( i2c_master_bus_handle_t i2c_bus ) {
  vTaskDelay( 2000 / portTICK_PERIOD_MS );
  lea_m8t_task_queue_item_t item = { lea_m8t_task_message::init, i2c_bus };
  xQueueSend( m_task_queue, &item, 0 );
}
