#ifndef __I_GNSS_STATE_HPP__
#define __I_GNSS_STATE_HPP__

#include <string>

namespace espena::broadcast_clock {

  class i_gnss_state {

  public:

    virtual ~i_gnss_state() = default; // Virtual destructor for proper cleanup

    virtual bool gnss_chip_installed() = 0;
    virtual std::string gnss_chip_installed_str() = 0;

    virtual uint8_t gnss_current_system() = 0;
    virtual std::string gnss_current_system_str() = 0;

    virtual uint8_t gnss_satellite_count() = 0;
    virtual std::string gnss_satellite_count_str() = 0;

    virtual uint8_t gnss_last_time_source() = 0;
    virtual std::string gnss_last_time_source_str() = 0;

  };

}

#endif // __I_GNSS_STATE_HPP__