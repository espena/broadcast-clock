#include "clock_status.hpp"
#include "ubx_types.hpp"
#include "lea_m8t.hpp"

#include <map>
#include <memory.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <esp_log.h>

using namespace espena::broadcast_clock;

void clock_status::
set_event_loop_handle( esp_event_loop_handle_t event_loop_handle ) {
  m_event_loop_handle = event_loop_handle;
  esp_event_handler_register_with( m_event_loop_handle,
                                   lea_m8t::m_event_base,
                                   lea_m8t::UBX_NAV_SAT,
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
ubx_nav_sat( ubx::nav_sat_t *nav_sat ) {
  m_gnss_satellite_count = nav_sat->num_svs;
  std::map<uint8_t, uint8_t> gnss_systems;
  uint8_t i;
  for( i = 0; i < m_gnss_satellite_count; i++ ) {
    gnss_systems[ nav_sat->satellites[ i ].gnss_id ]++;
  }
  i = 0;
  m_gnss_current_system_str = "";
  memset( m_gnss_current_system, 0x00, sizeof( m_gnss_current_system ) );
  for( auto &system : gnss_systems ) {
    if( system.first < ( sizeof( ubx::gnss_id ) / sizeof( ubx::gnss_id[ 0 ] ) ) ) {
      m_gnss_current_system[ i ] = system.first;
      m_gnss_current_system_str += m_gnss_current_system_str.empty() ? "" : ", ";
      m_gnss_current_system_str = ubx::gnss_id[ system.first ];
    }
    if( ++i == sizeof( m_gnss_current_system ) ) break;
  }
  ESP_LOGI( "clock_status", "GNSS system: %s", m_gnss_current_system_str.c_str() );
}