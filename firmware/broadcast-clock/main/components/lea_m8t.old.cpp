#include "lea_m8t.hpp"
#include "ubx_types.hpp"
#include "../utils/fletcher8.hpp"
#include "../utils/hexdump.hpp"
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
//#include <driver/i2c.h>
#include <driver/i2c_master.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::lea_m8t::m_component_name = "lea_m8t";

broadcast_clock::lea_m8t::
lea_m8t() : m_i2c_bus( nullptr ),
            m_i2c_dev( nullptr ) {

  m_task_queue = xQueueCreate( 1, sizeof( lea_m8t_task_queue_item ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &lea_m8t::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     8,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer );
}

broadcast_clock::lea_m8t::
~lea_m8t() {

}

void broadcast_clock::lea_m8t::
task_loop( void *arg ) {
  lea_m8t_task_params *params = static_cast<lea_m8t_task_params *>( arg );
  lea_m8t *inst = params->instance;
  lea_m8t_task_queue_item item;
  memset( &item, 0x00, sizeof( lea_m8t_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 1 ) ) {
      inst->on_message( item.message, item.arg );
    }
    if( inst->m_i2c_dev != nullptr ) {
      inst->poll();
    }
  }
}

uint16_t broadcast_clock::lea_m8t::
get_bytes_available() {

  uint8_t cmd_rx_buf[ 8 ] = { 0x00 };
  uint8_t addr = 0xfd;

  i2c_master_transmit_receive( m_i2c_dev,
                               &addr,
                               1,
                               cmd_rx_buf,
                               4,
                               -1 );

  return ( cmd_rx_buf[ 0 ] << 8 & 0xff00 ) | ( cmd_rx_buf[ 1 ] & 0x00ff );
}

void broadcast_clock::lea_m8t::
poll() {
  uint8_t cmd_rx_buf[ 2048 ];
  uint16_t bytes_available = get_bytes_available();
  //if( bytes_available > 0 && bytes_available < sizeof( cmd_rx_buf ) ) {

    //ESP_LOGE( m_component_name, "Bytes available: %d", bytes_available );
    
    uint8_t addr = 0xfd;
    i2c_master_transmit_receive( m_i2c_dev,
                                &addr,
                                1,
                                cmd_rx_buf,
                                sizeof( cmd_rx_buf ),
                                -1 );

    bytes_available = ( cmd_rx_buf[ 0 ] << 8 & 0xff00 ) | ( cmd_rx_buf[ 1 ] & 0x00ff );
    utils::hexdump( cmd_rx_buf, bytes_available );
    
    uint16_t offset = 2;

    while( offset < ( bytes_available ) ) {

      const uint8_t msg_class = cmd_rx_buf[ offset ];
      const uint8_t msg_id = cmd_rx_buf[ offset + 1 ];
      const uint16_t len = ( cmd_rx_buf[ offset + 3 ] << 8 & 0xff00 ) | ( cmd_rx_buf[ offset + 2 ] & 0x00ff );

      on_ubx_message( msg_class, msg_id, len > 0 ? &cmd_rx_buf[ offset + 4 ] : nullptr, len );

      if( cmd_rx_buf[ offset + 4 + len + 2 ] != 0xb5 || cmd_rx_buf[ offset + 4 + len + 3 ] != 0x62 ) {
        ESP_LOGI( m_component_name, "No more messages from %d and on", offset );
        break;
      }
      else {
        offset += ( 4 + len + 4 );
      }

    }

  //}
}

void broadcast_clock::lea_m8t::
on_ubx_message( const uint8_t msg_class,
                const uint8_t msg_id,
                void *payload,
                const uint16_t len ) {

  ESP_LOGI( m_component_name, "UBX message: class: 0x%02x, id: 0x%02x", msg_class, msg_id );

  switch( msg_class ) {
    case ubx::message::ack::cls:
      m_ack = msg_id;
      switch( msg_id ) {
        case ubx::message::ack::ack:
          on_ubx_ack_ack( static_cast<uint8_t *>( payload )[ 0 ] );
          break;
        case ubx::message::ack::nak:
          on_ubx_ack_nak( static_cast<uint8_t *>( payload )[ 0 ],
                          static_cast<uint8_t *>( payload )[ 1 ] );
          break;
      }
      break;
    case ubx::message::mon::cls:
      switch( msg_id ) {
        case ubx::message::mon::ver:
          on_ubx_mon_ver( static_cast<ubx::mon_ver_t *>( payload ) );
          break;
        case ubx::message::mon::hw:
          on_ubx_mon_hw( static_cast<ubx::mon_hw_t *>( payload ) );
          break;
      }
      break;
    case ubx::message::cfg::cls:
      switch( msg_id ) {
        case ubx::message::cfg::prt:
          switch( static_cast<uint8_t *>( payload )[ 0 ] ) { // port_id
            case 0x00:
              on_ubx_cfg_prt_ddc( static_cast<ubx::cfg_prt_ddc_t *>( payload ) );
              break;
          }
          break;
        case ubx::message::cfg::gnss:
          on_ubx_cfg_gnss( static_cast<ubx::cfg_gnss_t *>( payload ) );
          break;
        case ubx::message::cfg::tp5:
          on_ubx_cfg_tp5( static_cast<ubx::cfg_tp5_t *>( payload ) );
          break;
        case ubx::message::cfg::tmode2:
          on_ubx_cfg_tmode2( static_cast<ubx::cfg_tmode2_t *>( payload ) );
          break;
        case ubx::message::cfg::tmode3:
          on_ubx_cfg_tmode3( static_cast<ubx::cfg_tmode3_t *>( payload ) );
          break;
      }
      break;
    case ubx::message::nav::cls:
      switch( msg_id ) {
        case ubx::message::nav::clock:
          on_ubx_nav_clock( static_cast<ubx::nav_clock_t *>( payload ) );
          break;
        case ubx::message::nav::sat:
          on_ubx_nav_sat( static_cast<ubx::nav_sat_t *>( payload ) );
          break;
        case ubx::message::nav::svin:
          on_ubx_nav_svin( static_cast<ubx::nav_svin_t *>( payload ) );
          break;
        case ubx::message::nav::timegps:
          on_ubx_nav_timegps( static_cast<ubx::nav_timegps_t *>( payload ) );
          break;
      }
      break;
    case ubx::message::tim::cls:
      switch( msg_id ) {
        case ubx::message::tim::tm2:
          on_ubx_tim_tm2( static_cast<ubx::tim_tm2_t *>( payload ) );
          break;
        case ubx::message::tim::svin:
          on_ubx_tim_svin( static_cast<ubx::tim_svin_t *>( payload ) );
          break;
      }
      break;
  }

}

void broadcast_clock::lea_m8t::
on_ubx_ack_ack( uint8_t port_id ) {
  ESP_LOGI( m_component_name, "UBX_ACK_ACK" );
}

void broadcast_clock::lea_m8t::
on_ubx_ack_nak( uint8_t msg_cls, uint8_t msg_id ) {
  ESP_LOGI( m_component_name, "UBX_ACK_NAK" );
  ESP_LOGW( m_component_name, "Message 0x%02x 0x%02x not acknowledged", msg_cls, msg_id );
}

void broadcast_clock::lea_m8t::
on_ubx_mon_ver( ubx::mon_ver_t *ver ) {
  ESP_LOGI( m_component_name, "UBX_MON_VER" );
  memcpy( m_software_version, ver->sw_version, sizeof( m_software_version ) );
  memcpy( m_hardware_version, ver->hw_version, sizeof( m_hardware_version ) );
  ESP_LOGI( m_component_name,
            "Software version: %s (hw: %s)",
            ver->sw_version,
            ver->hw_version );
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_gnss( ubx::cfg_gnss_t *gnss ) {

  const char *gnss_id[ ] = {
    "GPS",
    "SBAS",
    "Galileo",
    "BeiDou",
    "IMES",
    "QZSS",
    "GLONASS",
    "Reserved"
  };

  ESP_LOGI( m_component_name, "UBX_CFG_GNSS" );
  ESP_LOGI( m_component_name, "Message version: %d", gnss->msg_ver );
  ESP_LOGI( m_component_name, "Number of tracking channels: %d", gnss->num_trk_ch_use );
  ESP_LOGI( m_component_name, "Number of configuration blocks: %d", gnss->num_config_blocks );
  for( int i = 0; i < gnss->num_config_blocks; i++ ) {
    ESP_LOGI( m_component_name, "GNSS ID: %d (%s)", gnss->blocks[ i ].gnss_id, gnss_id[ gnss->blocks[ i ].gnss_id ] );
    ESP_LOGI( m_component_name, "Max tracking channels: %d", gnss->blocks[ i ].max_trk_ch );
    ESP_LOGI( m_component_name, "Reserved tracking channels: %d", gnss->blocks[ i ].res_trk_ch );
    ESP_LOGI( m_component_name, "Enabled: %d", gnss->blocks[ i ].flags.enable );
    ESP_LOGI( m_component_name, "Signal configuration mask: 0x%02x", gnss->blocks[ i ].flags.sig_cfg_mask );
  }
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_tp5( ubx::cfg_tp5_t *tp5 ) {
  ESP_LOGI( m_component_name, "UBX_CFG_TP5" );
  ESP_LOGI( m_component_name, "Timepulse is %s", tp5->flags.active ? "active" : "inactive" );
  ESP_LOGI( m_component_name, "Antenna cable delay: %d", tp5->antenna_cable_delay );
  ESP_LOGI( m_component_name, "Timepulse index: %d", tp5->tp_idx );
  if( tp5->flags.is_freq ) {
    ESP_LOGI( m_component_name, "Timepulse frequency: %lu", tp5->freq_period );
  }
  else {
    ESP_LOGI( m_component_name, "Timepulse period: %lu", tp5->freq_period );
  }
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_prt_ddc( ubx::cfg_prt_ddc_t *prt ) {

  ESP_LOGI( m_component_name, "UBX_CFG_PRT" );
  memcpy( &m_cfg_prt_ddc, prt, sizeof( ubx::cfg_prt_ddc_t ) );

  ESP_LOGI( m_component_name, "Slave address %d", prt->mode.slave_addr );

  ESP_LOGI( m_component_name, "UBX output %s", prt->out_proto_mask.ubx ? "enabled" : "disabled" );
  ESP_LOGI( m_component_name, "NMEA output %s", prt->out_proto_mask.nmea ? "enabled" : "disabled" );
  ESP_LOGI( m_component_name, "RTCM3 output %s", prt->out_proto_mask.rtcm3 ? "enabled" : "disabled" );

  ESP_LOGI( m_component_name, "UBX input %s", prt->in_proto_mask.ubx ? "enabled" : "disabled" );
  ESP_LOGI( m_component_name, "NMEA input %s", prt->in_proto_mask.nmea ? "enabled" : "disabled" );
  ESP_LOGI( m_component_name, "RTCM input %s", prt->in_proto_mask.rtcm ? "enabled" : "disabled" );
  ESP_LOGI( m_component_name, "RTCM3 input %s", prt->in_proto_mask.rtcm3 ? "enabled" : "disabled" );

}

void broadcast_clock::lea_m8t::
on_ubx_cfg_tmode2( ubx::cfg_tmode2_t *tmode2 ) {
  ESP_LOGI( m_component_name, "UBX_CFG_TMODE2" );
}

void broadcast_clock::lea_m8t::
on_ubx_cfg_tmode3( ubx::cfg_tmode3_t *tmode3 ) {
  ESP_LOGI( m_component_name, "UBX_CFG_TMODE3" );
}

void broadcast_clock::lea_m8t::
on_ubx_nav_clock( ubx::nav_clock_t *clock ) {
  ESP_LOGI( m_component_name, "UBX_NAV_CLOCK" );
  ESP_LOGI( m_component_name, "Clock drift: %lu", clock->clk_drift );
  ESP_LOGI( m_component_name, "Clock bias: %lu", clock->clk_bias );
  ESP_LOGI( m_component_name, "Time accuracy: %lu", clock->t_acc );
  ESP_LOGI( m_component_name, "Frequency accuracy: %lu", clock->f_acc );
}

void broadcast_clock::lea_m8t::
on_ubx_nav_timegps( ubx::nav_timegps_t *timegps ) {
  ESP_LOGI( m_component_name, "UBX_NAV_TIMEGPS" );
}

void broadcast_clock::lea_m8t::
on_ubx_nav_sat( ubx::nav_sat_t *sat ) {
  ESP_LOGI( m_component_name, "UBX_NAV_SAT" );
}

void broadcast_clock::lea_m8t::
on_ubx_nav_svin( ubx::nav_svin_t *svin ) {
  ESP_LOGI( m_component_name, "UBX_NAV_SVIN" );
}

void broadcast_clock::lea_m8t::
on_ubx_tim_tm2( ubx::tim_tm2_t *tm2 ) {
  ESP_LOGI( m_component_name, "UBX_TIM_TM2" );
}

void broadcast_clock::lea_m8t::
on_ubx_tim_svin( ubx::tim_svin_t *svin ) {
  ESP_LOGI( m_component_name, "UBX_TIM_SVIN" );
}

void broadcast_clock::lea_m8t::
on_ubx_mon_hw( ubx::mon_hw_t *hw ) {
  ESP_LOGI( m_component_name, "UBX_MON_HW" );
}

void broadcast_clock::lea_m8t::
poll_msg( const uint8_t cls, const uint8_t id ) {
  ubx::message_t msg = { cls, id };
  lea_m8t_task_queue_item item = { lea_m8t_task_message::poll, &msg };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::lea_m8t::
on_poll_msg( ubx::message_t *msg ) {
  if( m_i2c_dev ) {
    ESP_LOGI( m_component_name, "Polling message 0x%02x 0x%02x", msg->cls, msg->id );
    uint8_t tx_buf[ 10 ] = { 0xb5, 0x62, 0x06, 0x01, 0x02, 0x00, msg->cls, msg->id, 0x00, 0x00 };
    utils::fletcher8( &tx_buf[ 2 ], 6, &tx_buf[ 8 ] );
    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          -1 ) );
  }
}

void broadcast_clock::lea_m8t::
on_message( lea_m8t_task_message msg, void *arg ) {
  switch( msg ) {
    case lea_m8t_task_message::init:
      on_init( static_cast<i2c_master_bus_handle_t>( arg ) );
      break;
    case lea_m8t_task_message::poll:
      on_poll_msg( static_cast<ubx::message_t *>( arg ) );
      break;
    case lea_m8t_task_message::timepulse:
      on_timepulse();
      break;
  }
}

void broadcast_clock::lea_m8t::
report_software_version() {
  ubx_request( ubx::message::mon::cls, ubx::message::mon::ver );
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
  ESP_ERROR_CHECK( gpio_isr_handler_add( LEA_M8T_TIMEPULSE, &on_timepulse, this ) );
}

void broadcast_clock::lea_m8t::
init_i2c_device() {
  i2c_device_config_t dev_cfg;
  memset( &dev_cfg, 0x00, sizeof( i2c_device_config_t ) );
  dev_cfg.dev_addr_length = I2C_ADDR_BIT_LEN_7;
  dev_cfg.device_address = m_i2c_address;
  dev_cfg.scl_speed_hz = 1000;
  dev_cfg.scl_wait_us = 5000;
  dev_cfg.flags.disable_ack_check = 1;
  ESP_ERROR_CHECK( i2c_master_bus_add_device( m_i2c_bus, &dev_cfg, &m_i2c_dev ) );
}

void broadcast_clock::lea_m8t::
report_gps_time() {
  ubx_request( ubx::message::nav::cls, ubx::message::nav::timegps );
}

void broadcast_clock::lea_m8t::
report_utc_time() {
  ubx_request( ubx::message::nav::cls, ubx::message::nav::timeutc );
}

void broadcast_clock::lea_m8t::
report_clock() {
  ubx_request( ubx::message::tim::cls, ubx::message::tim::tm2 );
  //ubx_request( ubx::message::nav::cls, ubx::message::nav::clock );
}

void broadcast_clock::lea_m8t::
report_ubx_messaging() {
  if( m_i2c_dev ) {
    uint8_t tx_buf[ 9 ] = { 0xb5, 0x62, ubx::message::cfg::cls, ubx::message::cfg::prt, 0x01, 0x00, 0x00, 0x00, 0x00 };
    utils::fletcher8( &tx_buf[ 2 ], 5, &tx_buf[ 7 ] );
    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          -1 ) );
  }
}

void broadcast_clock::lea_m8t::
ubx_request( const uint8_t cls, const uint8_t id ) {

  if( m_i2c_dev ) {
    uint8_t tx_buf[ 8 ] = { 0xb5, 0x62, static_cast<uint8_t>( cls ), static_cast<uint8_t>( id ), 0x00, 0x00, 0x00, 0x00 };
    utils::fletcher8( &tx_buf[ 2 ], 4, &tx_buf[ 6 ] );
    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          -1 ) );
  }
}

/*
void broadcast_clock::lea_m8t::
ubx_poll( const uint8_t cls, const uint8_t id ) {

  if( m_i2c_dev ) {
    uint8_t tx_buf[ 11 ] = { 0xb5, 0x62, 0x06, 0x01, 0x03, 0x00, static_cast<uint8_t>( cls ), static_cast<uint8_t>( id ), 0x01, 0x00, 0x00 };
    utils::fletcher8( &tx_buf[ 2 ], 6, &tx_buf[ 8 ] );
    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          -1 ) );
  }
}
*/

void broadcast_clock::lea_m8t::
report_time_mode_config() {

  if( m_i2c_dev ) {
    ubx::cfg_tmode2_t tm2;
    memset( &tm2, 0x00, sizeof( ubx::cfg_tmode2_t ) );
    
    tm2.time_mode = 0x01; // survey-in
    tm2.fixed_pos_acc = 1000;
    tm2.svin_min_dur = 60;
    tm2.svin_acc_limit = 1000;
    
    uint8_t tx_buf[ 20 ] = { 0xb5, 0x62, ubx::message::cfg::cls, ubx::message::cfg::tmode2, 0x0c, 0x00 };
    memcpy( &tx_buf[ 6 ], &tm2, 12 );

    utils::fletcher8( &tx_buf[ 2 ], 16, &tx_buf[ 18 ] );

    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          -1 ) );
  }
}

void broadcast_clock::lea_m8t::
report_timepulse_config() {
  ubx_request( ubx::message::cfg::cls, ubx::message::cfg::tp5 );
}

void broadcast_clock::lea_m8t::
report_hardware_status() {
  //ubx_poll( ubx::message::mon::cls, ubx::message::mon::hw );
  //ubx_request( ubx::message::mon::cls, ubx::message::mon::hw );
}

void broadcast_clock::lea_m8t::
report_survey_in() {
  //ubx_poll( ubx::message::tim::cls, ubx::message::tim::svin );
  //ubx_poll( ubx::message::nav::cls, ubx::message::nav::svin );
}

void broadcast_clock::lea_m8t::
report_gnss() {
  ubx_request( ubx::message::cfg::cls, ubx::message::cfg::gnss );
}

void broadcast_clock::lea_m8t::
report_satellites() {
  vTaskDelay( 1000 / portTICK_PERIOD_MS );
  ESP_LOGI( m_component_name, "Requesting satellite information" );
  if( m_i2c_dev ) {

    const int timeout = 1000;
    set_out_protocol();
    wait_for_ack( timeout );

    //poll_msg( ubx::message::nav::cls, ubx::message::nav::sat );
    //wait_for_ack( timeout );

    ESP_LOGI( m_component_name, "Setting measurement period" );
    uint8_t tx_buf[14] = { 0xb5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xc8, 0x00,
                          0x01, 0x00, 0x00, 0x00, 0xdd, 0x68 };
    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          1000 ) );
  }


}

void broadcast_clock::lea_m8t::
on_timepulse( void *arg ) {
  ESP_LOGE( "DEBUG", "Timepulse" );
  lea_m8t *inst = static_cast<lea_m8t *>( arg );
  lea_m8t_task_queue_item item = { lea_m8t_task_message::timepulse, nullptr };
  xQueueSend( inst->m_task_queue, &item, 10 );
}

void broadcast_clock::lea_m8t::
on_timepulse() {

}

void broadcast_clock::lea_m8t::
init( i2c_master_bus_handle_t i2c_bus ) {
  lea_m8t_task_queue_item item = { lea_m8t_task_message::init, i2c_bus };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::lea_m8t::
set_time_mode() {

  ubx::cfg_tmode2_t tm2;
  memset( &tm2, 0x00, sizeof( ubx::cfg_tmode2_t ) );

  tm2.time_mode = 2;
  tm2.flags.lla = 1;
  tm2.flags.alt_inv = 0;
  tm2.ecef_x_or_lat = 600942800;
  tm2.ecef_y_or_lon = 102934100;
  tm2.ecef_z_or_alt = 0;
  tm2.fixed_pos_acc = 10000;
  tm2.svin_min_dur = 60;

  uint8_t tx_buf[ 36 ] = { 0xb5, 0x62, ubx::message::cfg::cls, ubx::message::cfg::tmode2, 0x1c, 0x00 };
  memcpy( &tx_buf[ 6 ], &tm2, 28 );

  utils::fletcher8( &tx_buf[ 2 ], 32, &tx_buf[ 34 ] );

  ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                        tx_buf,
                                        sizeof( tx_buf ),
                                        -1 ) );



}

void broadcast_clock::lea_m8t::
set_cfg_prt_ddc() {
  if( m_i2c_dev ) {
    ESP_LOGI( m_component_name, "Setting CFG_PRT_DDC" );
    uint8_t tx_buf[ 28 ] = { 0xb5, 0x62, 0x06, 0x00, 0x14, 0x00 };
    memcpy( &tx_buf[ 6 ], &m_cfg_prt_ddc, 20 );
    utils::fletcher8( &tx_buf[ 2 ], 24, &tx_buf[ 26 ] );
    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          -1 ) );
  }
}

void broadcast_clock::lea_m8t::
reset_device() {
  if( m_i2c_dev ) {
    ESP_LOGI( m_component_name, "Resetting device" );
    uint8_t tx_buf[ 10 ] = { 0xb5, 0x62, 0x06, 0x04, 0x04, 0x00, 0xff, 0xff, 0x00, 0x00 };
    utils::fletcher8( &tx_buf[ 2 ], 6, &tx_buf[ 8 ] );
    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          -1 ) );
  }
}

void broadcast_clock::lea_m8t::
set_out_protocol() {
  if( m_i2c_dev ) {

    ESP_LOGI( m_component_name, "Setting out protocol to UBX" );
    
    ubx::cfg_prt_ddc_t cfg_prt_ddc;
    memset( &cfg_prt_ddc, 0x00, sizeof( ubx::cfg_prt_ddc_t ) );

    cfg_prt_ddc.port_id = 0x00;
    cfg_prt_ddc.tx_ready.enable = 0;
    cfg_prt_ddc.mode.slave_addr = 66;
    cfg_prt_ddc.in_proto_mask.ubx = 1;
    cfg_prt_ddc.out_proto_mask.ubx = 1;
    cfg_prt_ddc.flags.extended_tx_timeout = 0;

    uint8_t tx_buf[ 28 ] = { 0xb5, 0x62, ubx::message::cfg::cls, ubx::message::cfg::prt, 0x14, 0x00 };
    memcpy( &tx_buf[ 6 ], &cfg_prt_ddc, 20 );
    utils::fletcher8( &tx_buf[ 2 ], 24, &tx_buf[ 26 ] );

    ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev,
                                          tx_buf,
                                          sizeof( tx_buf ),
                                          1000 ) );
  }
}

void broadcast_clock::lea_m8t::
set_gnss() {
  if( m_i2c_dev ) {
    
  }
}

void broadcast_clock::lea_m8t::
wait_for_ack( int timeout ) {
  ESP_LOGI( m_component_name, "Waiting for ackowledgement" );
  m_ack = 0x00;
  int i = 0;
  while( i < timeout ) {
    vTaskDelay( 1 / portTICK_PERIOD_MS );
    if( m_ack == 0x00 ) {
      i++;
      continue;
    }
    break;
  }
  if( m_ack == ubx::message::ack::ack ) ESP_LOGI( m_component_name, "Ackowledged!" );
  else if( m_ack == ubx::message::ack::nak ) ESP_LOGW( m_component_name, "Not ackowledged!" );
  else ESP_LOGE( m_component_name, "No response after %d ms", timeout );
}

void broadcast_clock::lea_m8t::
on_init( i2c_master_bus_handle_t i2c_bus ) {

  ESP_LOGI( m_component_name, "Initializing" );
  m_i2c_bus = i2c_bus;
  if( is_present() ) {
    init_isr_timepulse();
    init_i2c_device();
    


    //wait_for_ack( 1000 );
    //report_gnss();
    //report_clock();

    //report_satellites();

    //reset_device();

    //report_software_version();
    //set_time_mode();
    //report_survey_in();
    
    //report_ubx_messaging();
    //report_timepulse_config();

    /*
    m_cfg_prt_ddc.out_proto_mask.ubx = 1;
    m_cfg_prt_ddc.out_proto_mask.nmea = 0;
    m_cfg_prt_ddc.out_proto_mask.rtcm3 = 0;

    m_cfg_prt_ddc.in_proto_mask.ubx = 1;
    m_cfg_prt_ddc.in_proto_mask.nmea = 0;
    m_cfg_prt_ddc.in_proto_mask.rtcm = 0;
    m_cfg_prt_ddc.in_proto_mask.rtcm3 = 0;

    set_cfg_prt_ddc();
    */

    //report_hardware_status();
    //report_gps_time();
    //report_clock();

  }
  else {
    ESP_LOGE( m_component_name, "Not found on i2c bus" );
  }
}
