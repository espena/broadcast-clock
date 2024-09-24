#ifndef __I_GNSS_UBX_HPP__
#define __I_GNSS_UBX_HPP__

#include <string>
#include "ubx_types.hpp"

namespace espena::broadcast_clock {

  class i_gnss_ubx {

  public:

    virtual ~i_gnss_ubx() = default; // Virtual destructor for proper cleanup

    virtual void ubx_mon_ver( ubx::mon_ver_t *mon_ver ) = 0;
    virtual void ubx_nav_sat( ubx::nav_sat_t *nav_sat ) = 0;
    virtual void ubx_nav_timeutc( ubx::nav_timeutc_t *nav_timeutc ) = 0;
    virtual void ubx_cfg_tmode2( ubx::cfg_tmode2_t *cfg_tmode2 ) = 0;
    virtual void ubx_tim_svin( ubx::tim_svin_t *tim_svin ) = 0;

  };

}

#endif // __I_GNSS_UBX_HPP__
