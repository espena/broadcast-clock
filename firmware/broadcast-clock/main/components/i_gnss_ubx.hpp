#ifndef __I_GNSS_UBX_HPP__
#define __I_GNSS_UBX_HPP__

#include <string>
#include "ubx_types.hpp"

namespace espena::broadcast_clock {

  class i_gnss_ubx {

  public:

    virtual ~i_gnss_ubx() = default; // Virtual destructor for proper cleanup

    virtual void ubx_nav_sat( ubx::nav_sat_t *nav_sat ) = 0;

  };

}

#endif // __I_GNSS_UBX_HPP__
