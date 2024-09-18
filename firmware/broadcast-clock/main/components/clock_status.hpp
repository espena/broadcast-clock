#ifndef __I_CLOCK_STATUS_HPP__
#define __I_CLOCK_STATUS_HPP__

#include "i_indicators.hpp"

namespace espena::broadcast_clock {

  class clock_status {

    i_indicators *m_indicators;
  
  public:

    clock_status( i_indicators *indicators ) : m_indicators( indicators ) { }
    virtual ~clock_status() = default; // Virtual destructor for proper cleanup

  };

}

#endif // __I_CLOCK_STATUS_HPP__