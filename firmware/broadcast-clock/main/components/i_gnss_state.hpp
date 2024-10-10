#ifndef __I_GNSS_STATE_HPP__
#define __I_GNSS_STATE_HPP__

#include <string>

namespace espena::broadcast_clock {

  class i_gnss_state {

  public:

    virtual ~i_gnss_state() = default; // Virtual destructor for proper cleanup

    virtual bool gnss_chip_installed() = 0;
    virtual std::string gnss_chip_installed_str() = 0;

    virtual std::string gnss_software_version_str() = 0;

    virtual std::string gnss_hardware_version_str() = 0;

    virtual uint8_t gnss_current_system() = 0;
    virtual std::string gnss_current_system_str() = 0;

    virtual uint8_t gnss_satellite_count() = 0;
    virtual std::string gnss_satellite_count_str() = 0;

    virtual uint32_t gnss_mean_systime_offset_us() = 0;
    virtual std::string gnss_mean_systime_offset_us_str() = 0;

    virtual uint8_t gnss_utc_standard() = 0;
    virtual std::string gnss_utc_standard_str() = 0;

    virtual bool gnss_got_timepulse() = 0;
    virtual std::string gnss_got_timepulse_str() = 0;

    virtual uint8_t gnss_time_mode_started() = 0;
    virtual std::string gnss_time_mode_started_str() = 0;

    virtual uint8_t gnss_time_mode() = 0;
    virtual std::string gnss_time_mode_str() = 0;

    virtual bool gnss_svin_active() = 0;
    virtual std::string gnss_svin_active_str() = 0;

    virtual uint32_t gnss_svin_obs() = 0;
    virtual std::string gnss_svin_obs_str() = 0;

    virtual bool gnss_svin_valid() = 0;
    virtual std::string gnss_svin_valid_str() = 0;

    virtual uint32_t gnss_svin_dur() = 0;
    virtual std::string gnss_svin_dur_str() = 0;

    virtual uint32_t gnss_svin_mean_x() = 0;
    virtual std::string gnss_svin_mean_x_str() = 0;

    virtual uint32_t gnss_svin_mean_y() = 0;
    virtual std::string gnss_svin_mean_y_str() = 0;

    virtual uint32_t gnss_svin_mean_z() = 0;
    virtual std::string gnss_svin_mean_z_str() = 0;

    virtual uint32_t gnss_svin_mean_v() = 0;
    virtual std::string gnss_svin_mean_v_str() = 0;

  };

}

#endif // __I_GNSS_STATE_HPP__