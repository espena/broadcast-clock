#ifndef __I_CLOCK_STATUS_HPP__
#define __I_CLOCK_STATUS_HPP__

#include "i_indicators.hpp"

namespace espena::broadcast_clock {

  class clock_status {

    i_indicators *m_indicators;

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

    bool is_blue() { return m_got_time_sync && m_got_timepulse && m_gnss_installed; };
    bool is_green() { return m_sntp_sync; };
    bool is_yellow() { return m_configurator_enabled; };
    bool is_red() { return m_high_accuracy; };

  public:

    clock_status( i_indicators *indicators ) : m_indicators( indicators ) { }
    virtual ~clock_status() = default; // Virtual destructor for proper cleanup
    void gnss_timepulse( bool ok );
    void gnss_time_sync( bool ok );
    void gnss_installed();
    void high_accuracy( bool ok );
    void sntp_sync( bool ok );
    void configurator_enabled( bool ok );

  };

}

#endif // __I_CLOCK_STATUS_HPP__