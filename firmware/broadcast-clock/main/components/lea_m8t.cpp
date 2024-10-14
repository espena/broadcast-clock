#include "lea_m8t.hpp"
#include "configuration.hpp"
#include "ubx_types.hpp"
#include "../semaphores/mutex.hpp"
#include "../utils/fletcher8.hpp"
#include "../utils/hexdump.hpp"
#include <string>
#include <queue>
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/portmacro.h>
#include <freertos/timers.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <esp_timer.h>
#include <esp32/rom/ets_sys.h>
#include <esp_log.h>
#include <esp_heap_caps.h>

using namespace espena;

const char *broadcast_clock::lea_m8t::m_component_name = "lea_m8t";
const char *broadcast_clock::lea_m8t::m_event_base = "broadcast_clock_lea_m8t_event";

broadcast_clock::lea_m8t::
lea_m8t() : m_event_loop_handle( nullptr ) {

  spinlock_initialize( &m_spinlock1 );
  spinlock_initialize( &m_spinlock2 );

  memset( &m_cfg_prt_ddc, 0x00, sizeof( ubx::cfg_prt_ddc_t ) );
  memset( &m_cfg_tmode2, 0x00, sizeof( ubx::cfg_tmode2_t ) );
  memset( &m_cfg_gnss, 0x00, sizeof( ubx::cfg_gnss_t ) );
  memset( &m_cfg_ant, 0x00, sizeof( ubx::cfg_ant_t ) );
  
  memset( &m_mon_ver, 0x00, sizeof( ubx::mon_ver_t ) );
  
  memset( &m_nav_timeutc, 0x00, sizeof( ubx::nav_timeutc_t ) );
  memset( &m_nav_sat, 0x00, sizeof( ubx::nav_sat_t ) );  

  memset( &m_tim_svin, 0x00, sizeof( ubx::tim_svin_t ) );

  m_task_queue = xQueueCreate( 1024, sizeof( lea_m8t_task_queue_item_t ) );
  m_egress_queue = xQueueCreate( 1024, sizeof( lea_m8t_egress_queue_item_t ) );
  m_timepulse_queue = xQueueCreate( 10, sizeof( lea_m8t_timepulse_queue_item_t ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &lea_m8t::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     configMAX_PRIORITIES - 3,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer );

  m_lea_m8t_tp_loop_params.instance = this;
  m_lea_m8t_tp_loop_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_timepulse_loop_stack_size,
                                                                              MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &lea_m8t::timepulse_loop,
                     m_component_name,
                     m_timepulse_loop_stack_size,
                     &m_lea_m8t_tp_loop_params,
                     configMAX_PRIORITIES - 1,
                     m_lea_m8t_tp_loop_params.stack_buffer,
                     &m_lea_m8t_tp_loop_params.task_buffer );

  esp_timer_create_args_t timer_args;
  memset( &timer_args, 0x00, sizeof( esp_timer_create_args_t ) );
  timer_args.callback = &on_poll_timer;
  timer_args.arg = this;
  timer_args.name = "poll_timer";

  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &m_poll_timer ) );
  ESP_ERROR_CHECK( esp_timer_start_periodic( m_poll_timer, 5000 ) );
}

broadcast_clock::lea_m8t::
~lea_m8t() {

}

void broadcast_clock::lea_m8t::
set_event_loop_handle( esp_event_loop_handle_t h ) {
  m_event_loop_handle = h;
  if( m_event_loop_handle ) {
    esp_event_handler_register_with( m_event_loop_handle,
                                     configuration::m_event_base,
                                     configuration::CONFIGURATION_UPDATED,
                                     event_handler,
                                     this );
  }
}

void broadcast_clock::lea_m8t::
event_handler( void *handler_arg,
               esp_event_base_t event_base,
               int32_t event_id,
               void *event_params ) {

  std::string source = ( char * ) event_base;
  if( source == configuration::m_event_base ) {
    lea_m8t *instance = static_cast<lea_m8t *>( handler_arg );
    if( instance ) {
      switch( event_id ) {
        case configuration::CONFIGURATION_UPDATED:
          instance->m_configuration_updated = true;
          break;
      }
    }
  }
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
timepulse_loop( void *arg ) {
  lea_m8t_task_params *params = static_cast<lea_m8t_task_params *>( arg );
  lea_m8t *inst = params->instance;
  lea_m8t_timepulse_queue_item_t item;
  memset( &item, 0x00, sizeof( lea_m8t_timepulse_queue_item_t ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_timepulse_queue, &item, -1 ) ) {
      inst->on_timepulse_loop_message( item.message, item.arg );
    }
  }
}

void broadcast_clock::lea_m8t::
on_poll_timer( void *arg ) {
  lea_m8t *inst = static_cast<lea_m8t *>( arg );
  if( inst ) {
    lea_m8t_task_queue_item_t item = { lea_m8t_task_message::poll, nullptr };
    xQueueSend( inst->m_task_queue, &item, 0 );
  }
}

uint16_t broadcast_clock::lea_m8t::
get_bytes_available() {

  uint8_t cmd_rx_buf[ 2 ] = { 0x01, 0x01 };
  const uint8_t addr = 0xfd;
  
  esp_err_t res = -1;
  uint8_t retries = 0;
  
  while( res != ESP_OK && retries++ < 10 ) {
    res = i2c_master_write_read_device( I2C_NUM_0,
                                        m_i2c_address,
                                        &addr,
                                        1,
                                        cmd_rx_buf,
                                        2,
                                        -1 );
  }

  if( res != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to read bytes available" );
  }
  return ( cmd_rx_buf[ 0 ] << 8 & 0xff00 ) | ( cmd_rx_buf[ 1 ] & 0x00ff );
}

void broadcast_clock::lea_m8t::
read() {

  uint16_t bytes_available = get_bytes_available();
  if( bytes_available == 0 ) {
    return;
  }

  ESP_LOGI( m_component_name, "Bytes available: %d", bytes_available );

  uint8_t *cmd_rx_buf = static_cast<uint8_t *>( heap_caps_malloc( bytes_available, MALLOC_CAP_SPIRAM ) );
  //uint8_t *cmd_rx_buf = new uint8_t[ bytes_available ];
  uint8_t addr = 0xff;
  uint16_t offset = 0;

  i2c_master_write_read_device( I2C_NUM_0,
                                m_i2c_address,
                                &addr,
                                1,
                                cmd_rx_buf,
                                bytes_available,
                                -1 );

  while( offset < ( bytes_available - 8 ) && cmd_rx_buf[ offset ] != 0xb5 && cmd_rx_buf[ offset + 1 ] != 0x62 ) {
    offset++; // Fast forward to first UBX message
  }

  while( offset < ( bytes_available - 8 ) &&
          cmd_rx_buf[ offset ] == 0xb5 &&
          cmd_rx_buf[ offset + 1 ] == 0x62 )
  {
    const uint8_t msg_class = cmd_rx_buf[ offset + 2 ];
    const uint8_t msg_id = cmd_rx_buf[ offset + 3 ];
    
    ESP_LOGI( m_component_name, "Message length taken from offset %d", offset + 4 );

    const uint16_t len = ( ( cmd_rx_buf[ offset + 5 ] << 8 ) & 0xff00 ) | ( cmd_rx_buf[ offset + 4 ] & 0x00ff );


    ESP_LOGI( m_component_name, "Message length LSB %02x MSB %02x = %d", cmd_rx_buf[ offset + 4 ], cmd_rx_buf[ offset + 5 ], len );
    
    

    if( offset + len + 8 > bytes_available ) {
      ESP_LOGE( m_component_name, "Message length exceeds buffer length for cls %02x id %02x", msg_class, msg_id );
      break;
    } 

    uint8_t fletcher_sum[ 2 ] = { 0x00, 0x00 };
    const uint8_t fletcher_a = cmd_rx_buf[ offset + len + 6 ];
    const uint8_t fletcher_b = cmd_rx_buf[ offset + len + 7 ];
    utils::fletcher8( &cmd_rx_buf[ offset + 2 ], len + 4, fletcher_sum );

    if( fletcher_sum[ 0 ] != fletcher_a || fletcher_sum[ 1 ] != fletcher_b ) {
      ESP_LOGE( m_component_name, "Fletcher checksum failed for cls 0x%02x id 0x%02x", msg_class, msg_id );
      ESP_LOGE( m_component_name, "LEA M8T passed 0x%02x 0x%02x while 0x%02x 0x%02x was expected", fletcher_a, fletcher_b, fletcher_sum[ 0 ], fletcher_sum[ 1 ] );
      utils::hexdump( &cmd_rx_buf[ offset ], len + 8 );
      offset += len + 8;
      continue;
    }

    if( msg_class == ubx::message::ack::cls ) {
      m_ack = msg_id; // Resume writing messages after receiving ACK
    }
    
    utils::hexdump( &cmd_rx_buf[ offset ], len + 8 );
    on_ubx_message( msg_class, msg_id, len > 0 ? &cmd_rx_buf[ offset + 6 ] : nullptr, len ); // DEBUG 3

    offset += len + 8;
  }

  //delete [] cmd_rx_buf;
  if( cmd_rx_buf != nullptr ) {
    heap_caps_free( cmd_rx_buf );
  }

}

void broadcast_clock::lea_m8t::
write() {
  lea_m8t_egress_queue_item_t item;
  while( m_ack != 0xff && xQueueReceive( m_egress_queue, &item, 0 ) ) {
    ESP_LOGI( m_component_name, "Writing message: class: 0x%02x, id: 0x%02x", item.message.cls, item.message.id );
    uint16_t buflen = 8 + item.len;
    ESP_LOGI( m_component_name, "Write message length: %d", buflen );
    //uint8_t *msg = new uint8_t[ buflen ];
    uint8_t *msg = static_cast<uint8_t *>( heap_caps_malloc( buflen, MALLOC_CAP_SPIRAM ) );
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
    utils::hexdump( msg, buflen );
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start( cmd );
    i2c_master_write_byte( cmd, ( m_i2c_address << 1 ) | I2C_MASTER_WRITE, true );
    i2c_master_write( cmd, msg, buflen, true );
    i2c_master_stop( cmd );
    esp_err_t res = i2c_master_cmd_begin( I2C_NUM_0, cmd, 1000 );
    i2c_cmd_link_delete( cmd );

    if( res != ESP_OK ) {
      ESP_LOGE( m_component_name, "Failed to write message" );
    }
    else {
      ESP_LOGI( m_component_name, "Message written!" );
    }

    //delete [] msg;
    if( msg != nullptr ) {
      heap_caps_free( msg );
    }    
    //delete [] item.deletable_payload;
    if( item.deletable_payload != nullptr ) {
      heap_caps_free( item.deletable_payload );
      item.deletable_payload = nullptr;
    }
  }
}

void broadcast_clock::lea_m8t::
update_status() {
  if( m_configuration_updated ) {
    m_configuration_updated = false;
    configuration *cnf = configuration::get_instance();
    if( cnf ) {
      if( cnf->get_str( "time_mode_enable" ) == "on" ) {
        ESP_LOGI( m_component_name, "Time mode enabled" );
        set_time_mode( true );
      }
      else {
        ESP_LOGI( m_component_name, "Time mode disabled" );
        set_time_mode( false );
      }
      // Poll UBX-CFG-TMODE2
      lea_m8t_egress_queue_item_t ubx_cfg_tmode2 = { 0, { ubx::message::cfg::cls, ubx::message::cfg::tmode2 }, nullptr, true };
      xQueueSend( m_egress_queue, &ubx_cfg_tmode2, 0 );
    }
  }
  if( m_event_loop_handle ) {
    if( m_timepulse_cc > 0 ) {
      uint32_t cc_tp = m_timepulse_cc;
      uint32_t cc_now = xthal_get_ccount();
      uint32_t cc_diff = cc_now - cc_tp;
      uint32_t diff_msec = ( cc_diff * 1000 ) / 240000000;
      if( diff_msec > 2000 ) {
        m_timepulse_cc = 0;
        ESP_LOGE( m_component_name, "Timepulse ABSENT" );
        esp_event_post_to( m_event_loop_handle,
                          m_event_base,
                          TIMEPULSE_ABSENT,
                          "",
                          0,
                          portMAX_DELAY );
      }
    }
  }
}

void broadcast_clock::lea_m8t::
on_timepulse_loop_message( lea_m8t_timepulse_message msg, void *arg ) {

  // High priority handling of timepulse
  struct timespec now;
  int32_t now_ns = 0;
  uint32_t now_cc = 0;
  uint32_t tp_cc = 0;
  uint32_t tp_ns = 0;

  if( xSemaphoreTake( semaphores::mutex::system_clock, portMAX_DELAY ) ) {
    taskENTER_CRITICAL( &m_spinlock1 );
    clock_gettime( CLOCK_REALTIME, &now );
    xSemaphoreGive( semaphores::mutex::system_clock );
    now.tv_sec = ( now.tv_nsec > 500000000 ? now.tv_sec + 1 : now.tv_sec );
    now_ns = now.tv_nsec;
    now_cc = xthal_get_ccount();
    tp_cc = now_cc - m_timepulse_cc;
    tp_ns = ( tp_cc * 1000000 ) / 240000000;
    now.tv_nsec = tp_ns + 52000; // Adjust for code execution time
    clock_settime( CLOCK_REALTIME, &now );
    now_ns -= ( tp_ns );
    taskEXIT_CRITICAL( &m_spinlock1 );
    xSemaphoreGive( semaphores::mutex::system_clock );
  }

  // Forward timepulse message to regular task loop
  lea_m8t_task_queue_item_t ts_item = { lea_m8t_task_message::timepulse, nullptr };
  xQueueSendToFront( m_task_queue, &ts_item, -1 );

  // Output timepulse offset
  m_tp_offset_us = ( now_ns >= 500000000 ? now_ns -= 1000000000 : now_ns ) / 1000;
  ESP_LOGI( m_component_name, "Timepulse offset: %li us", m_tp_offset_us );

  // Fire time pulse offset reporting event
  const uint32_t event_id = m_tp_offset_us >= -m_time_pulse_offset_threshold_us &&
                            m_tp_offset_us <= m_time_pulse_offset_threshold_us
                          ? HIGH_ACCURACY
                          : LOWER_ACCURACY;  

  esp_event_post_to( m_event_loop_handle,
                    m_event_base,
                    event_id,
                    &m_tp_offset_us,
                    sizeof( int32_t ),
                    portMAX_DELAY );

}

void broadcast_clock::lea_m8t::
on_task_message( lea_m8t_task_message msg, void *arg ) {
  switch( msg ) {
    case lea_m8t_task_message::init:
      on_init();
      break;
    case lea_m8t_task_message::soft_init:
      init_ubx_normalboot();
      break;
    case lea_m8t_task_message::poll:
      if( m_i2c_installed ) {
        read();
        write();
        update_status();
      }
      break;
    case lea_m8t_task_message::start_time_mode:
      // Moved to on_update function
      break;
    case lea_m8t_task_message::stop_time_mode:
      // Moved to on_update function
      break;
    case lea_m8t_task_message::timepulse:
      on_timepulse();
      break;
  }
}

void broadcast_clock::lea_m8t::
reset() {
  ESP_LOGI( m_component_name, "Resetting device..." );
  { // Reset device
    //uint8_t *payload = new uint8_t[ 4 ];
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 4, MALLOC_CAP_SPIRAM ) );
    memset( payload, 0x00, 4 );
    lea_m8t_egress_queue_item_t ubx_cfg_rst = { 4, { ubx::message::cfg::cls, ubx::message::cfg::rst }, payload, false };
    xQueueSend( m_egress_queue, &ubx_cfg_rst, 0 );
  }
}

void broadcast_clock::lea_m8t::
set_time_mode( bool enable ) {

  { // Set time mode
    //ubx::cfg_tmode2_t *payload = reinterpret_cast<ubx::cfg_tmode2_t *>( new uint8_t[ sizeof( ubx::cfg_tmode2_t ) ] );
    ubx::cfg_tmode2_t *payload = static_cast<ubx::cfg_tmode2_t *>( heap_caps_malloc( sizeof( ubx::cfg_tmode2_t ), MALLOC_CAP_SPIRAM ) );

    memset( payload, 0x00, sizeof( ubx::cfg_tmode2_t ) );
    payload->time_mode = enable ? 0x01 : 0x00; // < survey-in if enabled
    payload->svin_min_dur = 3600;
    payload->svin_acc_limit = 3000;
    payload->fixed_pos_acc = 1000;
    lea_m8t_egress_queue_item_t ubx_cfg_tmode2 = { sizeof( ubx::cfg_tmode2_t ), { ubx::message::cfg::cls, ubx::message::cfg::tmode2 }, reinterpret_cast<uint8_t *>( payload ), true };
    ESP_LOGI( m_component_name, "Setting time mode to %s", enable ? "on" : "off" );
    xQueueSend( m_egress_queue, &ubx_cfg_tmode2, 0 );
  }
  if( enable ) {
    // Start polling UBX_TIM_SVIN more frequently
    //uint8_t *payload = new uint8_t[ 3 ];
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
    payload[ 0 ] = ubx::message::tim::cls;
    payload[ 1 ] = ubx::message::tim::svin;
    payload[ 2 ] = 0x10;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }
  else {
    // Lower UBX_TIM_SVIN poll frequency
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
    payload[ 0 ] = ubx::message::tim::cls;
    payload[ 1 ] = ubx::message::tim::svin;
    payload[ 2 ] = 0x30;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
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
        case ubx::message::mon::ver:
          on_ubx_mon_ver( static_cast<ubx::mon_ver_t *>( payload ) );
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
    case ubx::message::tim::cls:
      switch( msg_id ) {
        case ubx::message::tim::svin:
          on_ubx_tim_svin( static_cast<ubx::tim_svin_t *>( payload ) );
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
  if( m_cfg_tmode2.time_mode == 0x01 ) {
    // Start polling UBX_TIM_SVIN
    //uint8_t *payload = new uint8_t[ 3 ];
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
    payload[ 0 ] = ubx::message::tim::cls;
    payload[ 1 ] = ubx::message::tim::svin;
    payload[ 2 ] = 0x10;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }
  else {
    // Stop polling UBX_TIM_SVIN
    //uint8_t *payload = new uint8_t[ 3 ];
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
    payload[ 0 ] = ubx::message::tim::cls;
    payload[ 1 ] = ubx::message::tim::svin;
    payload[ 2 ] = 0x00;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        UBX_CFG_TMODE2,
                        &m_cfg_tmode2,
                        sizeof( ubx::cfg_tmode2_t ),
                        portMAX_DELAY );
  }
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_gnss( ubx::cfg_gnss_t *gnss ) {
  memcpy( &m_cfg_gnss, gnss, sizeof( ubx::cfg_gnss_t ) );
}

void broadcast_clock::lea_m8t::
on_ubx_mon_hw( ubx::mon_hw_t *hw ) {
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
on_ubx_mon_ver( ubx::mon_ver_t *ver ) {
  ESP_LOGI( m_component_name, "UBX_MON_VER" );
  memcpy( &m_mon_ver, ver, sizeof( ubx::mon_ver_t ) );
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        UBX_MON_VER,
                        &m_mon_ver,
                        sizeof( ubx::mon_ver_t ),
                        portMAX_DELAY );
  }
}

void broadcast_clock::lea_m8t::
on_ubx_nav_sat( ubx::nav_sat_t *sat ) {
  ESP_LOGI( m_component_name, "UBX_NAV_SAT" );
  ESP_LOGI( m_component_name, "Number of satellites: %d", sat->num_svs );
  memcpy( &m_nav_sat, sat, sizeof( ubx::nav_sat_t ) );
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        UBX_NAV_SAT,
                        &m_nav_sat,
                        sizeof( ubx::nav_sat_t ),
                        portMAX_DELAY );
  }
}

void broadcast_clock::lea_m8t::
on_ubx_tim_svin( ubx::tim_svin_t *payload ) {
  ESP_LOGI( m_component_name, "UBX_TIM_SVIN enter event handler" );
  memcpy( &m_tim_svin, payload, sizeof( ubx::tim_svin_t ) );
  ESP_LOGI( m_component_name, "UBX_TIM_SVIN memcpy OK" );
  if( m_event_loop_handle ) {
    ESP_LOGI( m_component_name, "UBX_TIM_SVIN prepare event" );
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        UBX_TIM_SVIN,
                        &m_tim_svin,
                        sizeof( ubx::tim_svin_t ),
                        portMAX_DELAY );
    ESP_LOGI( m_component_name, "UBX_TIM_SVIN event sent" );
  }
}

void broadcast_clock::lea_m8t::
on_ubx_nav_timeutc( ubx::nav_timeutc_t *timeutc ) {

  bool is_time_set = false;
  struct timespec now_spec;
  time_t now_time = -1;

  struct tm now_tm;
  memset( &now_tm, 0x00, sizeof( struct tm ) );
  
  now_tm.tm_year = timeutc->year - 1900; // tm_year is years since 1900
  now_tm.tm_mon = timeutc->month - 1;    // tm_mon is 0-based
  now_tm.tm_mday = timeutc->day;
  now_tm.tm_hour = timeutc->hour;
  now_tm.tm_min = timeutc->min;
  now_tm.tm_sec = timeutc->sec;
  now_tm.tm_isdst = -1;

  if( xSemaphoreTake( semaphores::mutex::system_clock, portMAX_DELAY ) ) {

    char *tz = getenv( "TZ" );
    if( tz != nullptr ) {
      tz = strdup( tz );
    } 
    setenv( "TZ", "UTC0", 1 );
    tzset();
    now_time = mktime( &now_tm );
    if( tz != nullptr ) {
      setenv( "TZ", tz, 1 );
      free( tz );
    }

    if( now_time != -1 ) {

      clock_gettime( CLOCK_REALTIME, &now_spec );

      //const uint32_t cc_now = xthal_get_ccount();
      //const uint32_t cc_diff = cc_now - m_timepulse_cc;
      //const int32_t ns_diff = ( ( cc_diff * 1000000000 ) / 240000000 ) + 20000; // Adjust for code execution time

      now_spec.tv_sec = now_time;
      now_spec.tv_nsec = timeutc->nano;

      clock_settime( CLOCK_REALTIME, &now_spec );

      ESP_LOGI( m_component_name, "Time set to %s", ctime( &now_time ) );
      is_time_set = true;
    }

    xSemaphoreGive( semaphores::mutex::system_clock );
  }

  if( is_time_set && m_event_loop_handle ) {
    m_seconds_with_no_timesync_data = 0;
    memcpy( &m_nav_timeutc, timeutc, sizeof( ubx::nav_timeutc_t ) );
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        UBX_NAV_TIMEUTC,
                        &m_nav_timeutc,
                        sizeof( ubx::nav_timeutc_t ),
                        portMAX_DELAY );
  }
}

void broadcast_clock::lea_m8t::
isr_timepulse_handler( void *arg ) {
  UBaseType_t intstat = taskENTER_CRITICAL_FROM_ISR();
  lea_m8t *inst = static_cast<lea_m8t *>( arg );
  inst->m_timepulse_cc = xthal_get_ccount();
  taskEXIT_CRITICAL_FROM_ISR( intstat );
  lea_m8t_timepulse_queue_item_t tp_item = { lea_m8t_timepulse_message::timepulse, nullptr };
  xQueueSendFromISR( inst->m_timepulse_queue, &tp_item, nullptr );
}

void broadcast_clock::lea_m8t::
on_timepulse() {

  if( m_timepulse_cc > 0 ) {

    if( m_event_loop_handle ) {
      esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        TIMEPULSE_PRESENT,
                        nullptr,
                        0,
                        portMAX_DELAY );
    }
  }

  if( ++m_seconds_with_no_timesync_data > 60 ) {
    esp_event_post_to( m_event_loop_handle,
                       m_event_base,
                       NO_TIME_SYNC,
                       nullptr,
                       0,
                       portMAX_DELAY );
    
  }    
}

bool broadcast_clock::lea_m8t::
is_present() {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start( cmd );
  i2c_master_write_byte( cmd, ( m_i2c_address << 1 ) | I2C_MASTER_WRITE, true );
  i2c_master_stop( cmd );
  esp_err_t res = i2c_master_cmd_begin( I2C_NUM_0, cmd, 1000 );
  i2c_cmd_link_delete( cmd );  
  bool presence = ( res == ESP_OK );
  if( presence ) {
    esp_event_post_to( m_event_loop_handle,
                       m_event_base,
                       GNSS_INSTALLED,
                       nullptr,
                       0,
                       portMAX_DELAY );
  }
  return presence;
}

void broadcast_clock::lea_m8t::
init_isr_timepulse() {
  ESP_LOGI( m_component_name, "Configure timepulse interrupt" );
  ESP_ERROR_CHECK( gpio_install_isr_service( 0 ) );
  ESP_ERROR_CHECK( gpio_set_direction( LEA_M8T_TIMEPULSE, GPIO_MODE_INPUT ) );
  ESP_ERROR_CHECK( gpio_set_intr_type( LEA_M8T_TIMEPULSE, GPIO_INTR_POSEDGE ) );
  ESP_ERROR_CHECK( gpio_isr_handler_add( LEA_M8T_TIMEPULSE, &isr_timepulse_handler, this ) );
}

void broadcast_clock::lea_m8t::
init_ubx_normalboot() {

  { // Set port configuration
    //ubx::cfg_prt_ddc_t *payload = reinterpret_cast<ubx::cfg_prt_ddc_t *>( new uint8_t[ sizeof( ubx::cfg_prt_ddc_t ) ] );
    ubx::cfg_prt_ddc_t *payload = static_cast<ubx::cfg_prt_ddc_t *>( heap_caps_malloc( sizeof( ubx::cfg_prt_ddc_t ), MALLOC_CAP_SPIRAM ) );
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
        //uint8_t *payload = new uint8_t[3];
        uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
        payload[0] = messages[i][0]; // Message class
        payload[1] = messages[i][1]; // Message ID
        payload[2] = 0x00;           // Rate: disable message
        lea_m8t_egress_queue_item_t ubx_cfg_msg = {3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
        xQueueSend(m_egress_queue, &ubx_cfg_msg, 10);
    }

  }

  { // Set message rate
    //ubx::cfg_rate_t *payload = reinterpret_cast<ubx::cfg_rate_t *>( new uint8_t[ sizeof( ubx::cfg_rate_t ) ] );
    ubx::cfg_rate_t *payload = static_cast<ubx::cfg_rate_t *>( heap_caps_malloc( sizeof( ubx::cfg_rate_t ), MALLOC_CAP_SPIRAM ) );
    payload->meas_rate = 100;
    payload->nav_rate = 8;
    payload->time_ref = 1;
    lea_m8t_egress_queue_item_t ubx_cfg_rate = { sizeof( ubx::cfg_rate_t ), { ubx::message::cfg::cls, ubx::message::cfg::rate }, reinterpret_cast<uint8_t *>( payload ), true };
    xQueueSend( m_egress_queue, &ubx_cfg_rate, 0 );
  }

  { // Poll periodic UBX-NAV-TIMEUTC
    //uint8_t *payload = new uint8_t[ 3 ];
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::timeutc;
    payload[ 2 ] = 0x4c; // Update every minute
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }

  { // Poll periodic UBX-NAV-SAT
    //uint8_t *payload = new uint8_t[ 3 ];
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
    payload[ 0 ] = ubx::message::nav::cls;
    payload[ 1 ] = ubx::message::nav::sat;
    payload[ 2 ] = 0x20;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }

  { // Poll periodic UBX-TIM-SVIN
    //uint8_t *payload = new uint8_t[ 3 ];
    uint8_t *payload = static_cast<uint8_t *>( heap_caps_malloc( 3, MALLOC_CAP_SPIRAM ) );
    payload[ 0 ] = ubx::message::tim::cls;
    payload[ 1 ] = ubx::message::tim::svin;
    payload[ 2 ] = 0x10;
    lea_m8t_egress_queue_item_t ubx_cfg_msg = { 3, { ubx::message::cfg::cls, ubx::message::cfg::msg }, payload, true };
    xQueueSend( m_egress_queue, &ubx_cfg_msg, 0 );
  }

  { // Poll UBX-CFG-TMODE2
    lea_m8t_egress_queue_item_t ubx_cfg_tmode2 = { 0, { ubx::message::cfg::cls, ubx::message::cfg::tmode2 }, nullptr, true };
    xQueueSend( m_egress_queue, &ubx_cfg_tmode2, 0 );
  }

  { // Poll UBX-MON-VER to populate JSON feed to web interface
    lea_m8t_egress_queue_item_t ubx_mon_ver = { 0, { ubx::message::mon::cls, ubx::message::mon::ver }, nullptr, false };
    xQueueSend( m_egress_queue, &ubx_mon_ver, 0 );
  }

}

void broadcast_clock::lea_m8t::
init_ubx_safeboot() {

}

void broadcast_clock::lea_m8t::
init_ubx() {
  init_ubx_normalboot();
}

void broadcast_clock::lea_m8t::
on_init() {
  ESP_LOGI( "application", "Initializing i2c" );
  vTaskDelay( 2000 / portTICK_PERIOD_MS );

  m_i2c_installed = true;

  if( is_present() ) {
    ESP_LOGI( m_component_name, "LEA M8T found on i2c bus" );
    init_isr_timepulse();
    vTaskDelay( 500 / portTICK_PERIOD_MS );
    init_ubx();
  }
  else {
    ESP_LOGE( m_component_name, "Not found on i2c bus" );
  }
}

void broadcast_clock::lea_m8t::
init() {
  lea_m8t_task_queue_item_t item = { lea_m8t_task_message::init, nullptr };
  xQueueSend( m_task_queue, &item, 0 );
}

void broadcast_clock::lea_m8t::
soft_init() {
  lea_m8t_task_queue_item_t item = { lea_m8t_task_message::soft_init, nullptr };
  xQueueSend( m_task_queue, &item, 0 );
}

void broadcast_clock::lea_m8t::
start_time_mode() {
  lea_m8t_task_queue_item_t item = { lea_m8t_task_message::start_time_mode, nullptr };
  xQueueSend( m_task_queue, &item, 0 );
}

void broadcast_clock::lea_m8t::
stop_time_mode() {
  lea_m8t_task_queue_item_t item = { lea_m8t_task_message::stop_time_mode, nullptr };
  xQueueSend( m_task_queue, &item, 0 );
}
