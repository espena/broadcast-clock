#include "clock_status.hpp"
#include "ubx_types.hpp"
#include "captive_portal_http.hpp"
#include "lea_m8t.hpp"

#include <map>
#include <memory.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <esp_timer.h>
#include <esp_log.h>

using namespace espena::broadcast_clock;

clock_status::
clock_status( i_indicators *indicators ) : m_indicators( indicators ),
                                           m_event_loop_handle( nullptr ),
                                           m_blink_timer( nullptr ) {
  esp_timer_create_args_t timer_args;
  memset( &timer_args, 0x00, sizeof( timer_args ) );
  timer_args.callback = on_blink_timer;
  timer_args.arg = this;
  timer_args.name = "clock_status_blink_timer";
  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &m_blink_timer ) );
  ESP_ERROR_CHECK( esp_timer_start_periodic( m_blink_timer, 1000000 ) );
}

void clock_status::
on_blink_timer( void *arg ) {
  ESP_LOGW( "clock_status", "on_blink_timer" );
  clock_status *inst = static_cast<clock_status *>( arg );
  inst->m_blink = !inst->m_blink;
}

void clock_status::
set_event_loop_handle( esp_event_loop_handle_t event_loop_handle ) {
  m_event_loop_handle = event_loop_handle;

  esp_event_handler_register_with( m_event_loop_handle,
                                   lea_m8t::m_event_base,
                                   lea_m8t::UBX_NAV_SAT,
                                   event_handler,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   lea_m8t::m_event_base,
                                   lea_m8t::UBX_NAV_TIMEUTC,
                                   event_handler,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   lea_m8t::m_event_base,
                                   lea_m8t::UBX_MON_VER,
                                   event_handler,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   lea_m8t::m_event_base,
                                   lea_m8t::UBX_CFG_TMODE2,
                                   event_handler,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   captive_portal_http::m_event_base,
                                   captive_portal_http::EVENT_START_TIME_MODE,
                                   event_handler,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   captive_portal_http::m_event_base,
                                   captive_portal_http::EVENT_STOP_TIME_MODE,
                                   event_handler,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   lea_m8t::m_event_base,
                                   lea_m8t::UBX_TIM_SVIN,
                                   event_handler,
                                   this );
}

void clock_status::
event_handler( void *handler_arg,
               esp_event_base_t event_base,
               int32_t event_id,
               void *event_params ) {
  clock_status *inst = static_cast<clock_status *>( handler_arg );
  if( lea_m8t::m_event_base == event_base ) {
    switch( event_id ) {
      case lea_m8t::UBX_NAV_SAT:
        inst->ubx_nav_sat( static_cast<ubx::nav_sat_t *>( event_params ) );
        break;
      case lea_m8t::UBX_NAV_TIMEUTC:
        inst->ubx_nav_timeutc( static_cast<ubx::nav_timeutc_t *>( event_params ) );
        break;
      case lea_m8t::UBX_MON_VER:
        inst->ubx_mon_ver( static_cast<ubx::mon_ver_t *>( event_params ) );
        break;
      case lea_m8t::UBX_CFG_TMODE2:
        inst->ubx_cfg_tmode2( static_cast<ubx::cfg_tmode2_t *>( event_params ) );
        break;
      case lea_m8t::UBX_TIM_SVIN:
        inst->ubx_tim_svin( static_cast<ubx::tim_svin_t *>( event_params ) );
        break;
    }
  }
  else if( captive_portal_http::m_event_base == event_base ) {
    switch( event_id ) {
      case captive_portal_http::EVENT_START_TIME_MODE:
        inst->m_gnss_time_mode_started = 1;
        break;
      case captive_portal_http::EVENT_STOP_TIME_MODE:
        inst->m_gnss_time_mode_started = 0;
        break;
    }
  }
}

void clock_status::
gnss_timepulse( bool ok ) {
  m_got_timepulse = ok;
  m_indicators->set_blue_indicator( is_blue() );
}

void clock_status::
gnss_time_sync( bool ok ) {
  m_got_time_sync = ok;
  m_indicators->set_blue_indicator( is_blue() );
}

void clock_status::
gnss_installed() {
  m_gnss_installed = true;
  m_indicators->set_blue_indicator( is_blue() );
}

void clock_status::
high_accuracy( bool ok ) {
  m_high_accuracy = ok;
  m_indicators->set_red_indicator( is_red() );
}

void clock_status::
sntp_sync( bool ok ) {
  m_sntp_sync = ok;
  m_indicators->set_green_indicator( is_green() );
}

void clock_status::
configurator_enabled( bool ok ) {
  m_configurator_enabled = ok;
  m_indicators->set_yellow_indicator( is_yellow() );
}

void clock_status::
ubx_mon_ver( ubx::mon_ver_t *mon_ver ) {
  memcpy( m_gnss_software_version, mon_ver->sw_version, sizeof( m_gnss_software_version ) );
  memcpy( m_gnss_hardware_version, mon_ver->hw_version, sizeof( m_gnss_software_version ) );
}

void clock_status::
ubx_cfg_tmode2( ubx::cfg_tmode2_t *cfg_tmode2 ) {
  uint8_t time_mode = cfg_tmode2->time_mode > 2 ? 3 : cfg_tmode2->time_mode;
  m_gnss_time_mode = cfg_tmode2->time_mode;
  if( m_gnss_time_mode_started == -1 ) {
    m_gnss_time_mode_started = m_gnss_time_mode > 0 ? 1 : 0;
  }
  strncpy( m_gnss_time_mode_str, ubx::time_mode[ time_mode ], sizeof( m_gnss_time_mode_str ) );
}

void clock_status::
ubx_tim_svin( ubx::tim_svin_t *tim_svin ) {
  m_gnss_svin_active = tim_svin->active;
  m_gnss_svin_dur = tim_svin->dur;
  m_gnss_svin_mean_x = tim_svin->mean_x;
  m_gnss_svin_mean_y = tim_svin->mean_y;
  m_gnss_svin_mean_z = tim_svin->mean_z;
  m_gnss_svin_mean_v = tim_svin->mean_v;
  m_gnss_svin_obs = tim_svin->obs;
  m_gnss_svin_valid = tim_svin->valid;
}

void clock_status::
ubx_nav_sat( ubx::nav_sat_t *nav_sat ) {
  m_gnss_satellite_count = nav_sat->num_svs;
  std::map<uint8_t, uint8_t> gnss_systems;
  uint8_t i;
  for( i = 0; i < m_gnss_satellite_count; i++ ) {
    gnss_systems[ nav_sat->satellites[ i ].gnss_id ]++;
  }
  i = 0;
  memset( m_gnss_current_system_str, 0x00, sizeof( m_gnss_current_system_str ) );
  memset( m_gnss_current_system, 0x00, sizeof( m_gnss_current_system ) );
  for( auto &system : gnss_systems ) {
    if( system.first < sizeof( ubx::gnss_id ) ) {
      m_gnss_current_system[ i ] = system.first;
      strncpy( m_gnss_current_system_str, ubx::gnss_id[ system.first ], sizeof( m_gnss_current_system_str ) );
      i++;
    }
  }
}

void clock_status::
ubx_nav_timeutc( ubx::nav_timeutc_t *nav_timeutc ) {
  m_gnss_utc_standard = ( nav_timeutc->valid & 0xf0 ) >> 4;
  const uint8_t id = m_gnss_utc_standard > 8 ? 9 : m_gnss_utc_standard;
  strncpy( m_gnss_utc_standard_str, ubx::utc_standard_timesource[ id ], sizeof( m_gnss_utc_standard_str ) );
}
