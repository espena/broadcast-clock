#ifndef __I_CLOCK_STATUS_HPP__
#define __I_CLOCK_STATUS_HPP__

#include <esp_event.h>
#include <esp_timer.h>

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

    static void on_blink_timer( void *arg );

    bool m_blink = false;
    esp_timer_handle_t m_blink_timer;

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

    int32_t m_sntp_aquiring = 0;

    bool m_ntp_server_ready = false;
    uint32_t m_ntp_server_client_count = 0;
    uint8_t m_ntp_server_responded = 0;

    uint32_t m_offset_us_cumulative = 0;
    uint32_t m_offset_us_sample_count = 0;

    uint8_t m_gnss_svin_active = 0;
    uint8_t m_gnss_svin_valid = 0;
    uint32_t m_gnss_svin_dur = 0;
    uint32_t m_gnss_svin_obs = 0;
    int32_t m_gnss_svin_mean_x = 0;
    int32_t m_gnss_svin_mean_y = 0;
    int32_t m_gnss_svin_mean_z = 0;
    uint32_t m_gnss_svin_mean_v = 0;

    char m_gnss_software_version[ sizeof( ubx::mon_ver_t::sw_version ) ] = { 0x00 };
    char m_gnss_hardware_version[ sizeof( ubx::mon_ver_t::hw_version ) ] = { 0x00 };

    uint8_t m_gnss_current_system[ 8 ] = { 0x00 };
    char m_gnss_current_system_str[ 10 ] = { 0x00 };

    uint8_t m_gnss_utc_standard = 0;
    char m_gnss_utc_standard_str[ 64 ] = { 0x00 };

    uint8_t m_gnss_time_mode = 3;
    char m_gnss_time_mode_str[ 16 ] = { 0x00 };

    uint8_t m_gnss_satellite_count = 0;

    int8_t m_gnss_time_mode_started = -1;

    bool blue_blinker() { return m_gnss_svin_active ? m_blink : true; };
    bool green_blinker() { return ( m_sntp_aquiring > 0 && --m_sntp_aquiring > 0 ) ? m_blink : true; };
    bool yellow_blinker() { return ( m_ntp_server_responded > 0 && --m_ntp_server_responded > 0 ) ? m_blink : true; };
    bool red_blinker() { return m_high_accuracy ? true : m_blink; };

    bool is_blue() { return m_gnss_installed && m_got_time_sync && m_got_timepulse && blue_blinker(); };
    bool is_green() { return m_sntp_sync && green_blinker(); };
    bool is_yellow() { return m_ntp_server_ready && yellow_blinker(); };
    bool is_red() { return m_got_timepulse && red_blinker(); };

  public:

    clock_status( i_indicators *indicators );
    virtual ~clock_status() = default; // Virtual destructor for proper cleanup

    void set_event_loop_handle( esp_event_loop_handle_t h );

    // setters

    void gnss_timepulse( bool ok );
    void gnss_time_sync( bool ok );
    void gnss_installed();
    void gnss_satellite_count( uint8_t count ) { m_gnss_satellite_count = count; };

    void high_accuracy( bool ok, int32_t *offset_us );
    void sntp_sync( bool ok );
    void configurator_enabled( bool ok );

    void ntp_server_ready( bool ok ) { m_ntp_server_ready = ok; };
    void ntp_server_client_count( uint32_t count ) { m_ntp_server_client_count = count; };
    void ntp_server_responded( bool ok ) { m_ntp_server_responded = ok ? 10 : 0; };

    // i_gnss_ubx interface (u-blox messages)
    void ubx_mon_ver( ubx::mon_ver_t *mon_ver ) override;
    void ubx_nav_sat( ubx::nav_sat_t *nav_sat ) override;
    void ubx_nav_timeutc( ubx::nav_timeutc_t *nav_timeutc ) override;
    void ubx_cfg_tmode2( ubx::cfg_tmode2_t *cfg_tmode2 ) override;
    void ubx_tim_svin( ubx::tim_svin_t *tim_svin ) override;

    // i_gnss_state interface (getters)

    bool gnss_chip_installed() override { return m_gnss_installed; };
    std::string gnss_chip_installed_str() override { return m_gnss_installed ? "Yes" : "No"; };

    std::string gnss_software_version_str() override { return m_gnss_software_version; };
    std::string gnss_hardware_version_str() override { return m_gnss_hardware_version; };

    uint8_t gnss_current_system() override { return m_gnss_current_system[ 0 ]; };
    std::string gnss_current_system_str() override { return m_gnss_current_system_str; };

    uint8_t gnss_satellite_count() override { return m_gnss_satellite_count; };
    std::string gnss_satellite_count_str() override { return std::to_string( static_cast<int>( m_gnss_satellite_count ) ); };

    uint32_t gnss_mean_systime_offset_us() override {
      uint32_t mean = m_offset_us_sample_count == 0 ? 0 : m_offset_us_cumulative / m_offset_us_sample_count;
      m_offset_us_cumulative = 0;
      m_offset_us_sample_count = 0;
      return mean;
    };
    std::string gnss_mean_systime_offset_us_str() override { return std::to_string( static_cast<int>( gnss_mean_systime_offset_us() ) ); };

    uint8_t gnss_utc_standard() override { return m_gnss_utc_standard; };
    std::string gnss_utc_standard_str() override { return ubx::utc_standard_timesource[ m_gnss_utc_standard > 8 ? 9 : m_gnss_utc_standard ]; };

    bool gnss_got_timepulse() override { return m_got_timepulse; };
    std::string gnss_got_timepulse_str() override { return m_got_timepulse ? "Yes" : "No"; };

    uint8_t gnss_time_mode_started() override { return m_gnss_time_mode_started; };
    std::string gnss_time_mode_started_str() override { return m_gnss_time_mode_started == 1 ? "Yes" : "No"; };

    uint8_t gnss_time_mode() override { return m_gnss_time_mode; };
    std::string gnss_time_mode_str() override { return m_gnss_time_mode_str; };

    bool gnss_svin_active() override { return m_gnss_svin_active == 1; };
    std::string gnss_svin_active_str() override { return m_gnss_svin_active == 1 ? "Yes" : "No"; };

    uint32_t gnss_svin_obs() override { return m_gnss_svin_obs; };
    std::string gnss_svin_obs_str() override { return std::to_string( static_cast<int>( m_gnss_svin_obs ) ); };

    bool gnss_svin_valid() override { return m_gnss_svin_valid == 1; };
    std::string gnss_svin_valid_str() override { return m_gnss_svin_valid == 1 ? "Yes" : "No"; };

    uint32_t gnss_svin_dur() override { return m_gnss_svin_dur; };
    std::string gnss_svin_dur_str() override { return std::to_string( static_cast<int>( m_gnss_svin_dur ) ); };

    uint32_t gnss_svin_mean_x() override { return m_gnss_svin_mean_x; };
    std::string gnss_svin_mean_x_str() override { return std::to_string( static_cast<int>( m_gnss_svin_mean_x ) ); };

    uint32_t gnss_svin_mean_y() override { return m_gnss_svin_mean_y; };
    std::string gnss_svin_mean_y_str() override { return std::to_string( static_cast<int>( m_gnss_svin_mean_y ) ); };

    uint32_t gnss_svin_mean_z() override { return m_gnss_svin_mean_z; };
    std::string gnss_svin_mean_z_str() override { return std::to_string( static_cast<int>( m_gnss_svin_mean_z ) ); };

    uint32_t gnss_svin_mean_v() override { return m_gnss_svin_mean_v; };
    std::string gnss_svin_mean_v_str() override { return std::to_string( static_cast<int>( m_gnss_svin_mean_v ) ); };

    uint32_t gnss_ntp_server_client_count() override { return m_ntp_server_client_count; };
    std::string gnss_ntp_server_client_count_str() override { return std::to_string( static_cast<int>( m_ntp_server_client_count ) ); };

  };

}

#endif // __I_CLOCK_STATUS_HPP__