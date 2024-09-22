#ifndef __I_CLOCK_STATUS_HPP__
#define __I_CLOCK_STATUS_HPP__

#include <esp_event.h>

#include "i_indicators.hpp"
#include "i_gnss_ubx.hpp"
#include "i_gnss_state.hpp"

#include "ubx_types.hpp"

namespace espena::broadcast_clock {

  class clock_status : public i_gnss_ubx,
                       public i_gnss_state {

    i_indicators *m_indicators;
    esp_event_loop_handle_t m_event_loop_handle;

    static void event_handler( void *handler_arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_params );

    bool m_status_gnss_sync_ok;
    bool m_status_ntp_sync_ok;
    bool m_status_wifi_connected;
    bool m_status_error;

    bool m_got_timepulse = false;
    bool m_got_time_sync = false;
    bool m_gnss_installed = false;
    bool m_high_accuracy = false;
    bool m_sntp_sync = false;
    bool m_configurator_enabled = false;

    uint8_t m_gnss_current_system[ 8 ] = { 0x00 };
    std::string m_gnss_current_system_str;
    uint8_t m_gnss_satellite_count = 0;
    uint8_t m_gnss_last_time_source = 0;

    bool is_blue() { return m_got_time_sync && m_got_timepulse && m_gnss_installed; };
    bool is_green() { return m_sntp_sync; };
    bool is_yellow() { return m_configurator_enabled; };
    bool is_red() { return m_high_accuracy; };

  public:

    clock_status( i_indicators *indicators ) : m_indicators( indicators ),
                                               m_event_loop_handle( nullptr ) { }
    virtual ~clock_status() = default; // Virtual destructor for proper cleanup

    void set_event_loop_handle( esp_event_loop_handle_t h );

    // setters

    void gnss_timepulse( bool ok );
    void gnss_time_sync( bool ok );
    void gnss_installed();
    void gnss_satellite_count( uint8_t count ) { m_gnss_satellite_count = count; };
    void gnss_last_time_source( uint8_t source_id ) { m_gnss_last_time_source = source_id; };

    void high_accuracy( bool ok );
    void sntp_sync( bool ok );
    void configurator_enabled( bool ok );

    // i_gnss_ubx interface (u-blox messages)
    void ubx_nav_sat( ubx::nav_sat_t *nav_sat ) override;

    // i_gnss_state interface (getters)

    bool gnss_chip_installed() override { return m_gnss_installed; };
    std::string gnss_chip_installed_str() override { return m_gnss_installed ? "yes" : "no"; };

    uint8_t gnss_current_system() override { return m_gnss_current_system[ 0 ]; };
    std::string gnss_current_system_str() override { return m_gnss_current_system_str; };

    uint8_t gnss_satellite_count() override { return m_gnss_satellite_count; };
    std::string gnss_satellite_count_str() override { return std::to_string( static_cast<int>( m_gnss_satellite_count ) ); };

    uint8_t gnss_last_time_source() override { return m_gnss_last_time_source; };
    std::string gnss_last_time_source_str() override { return ubx::utc_standard_timesource[ m_gnss_last_time_source ]; };

  };

}

#endif // __I_CLOCK_STATUS_HPP__