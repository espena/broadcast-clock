#ifndef __I_INDICATORS_HPP__
#define __I_INDICATORS_HPP__

namespace espena::broadcast_clock {

  class i_indicators {

  public:

    virtual ~i_indicators() = default; // Virtual destructor for proper cleanup

    virtual void set_indicators( bool, bool, bool, bool, bool ) = 0;
    virtual void set_blue_indicator( bool ) = 0;
    virtual void set_green_indicator( bool ) = 0;
    virtual void set_yellow_indicator( bool ) = 0;
    virtual void set_red_indicator( bool ) = 0;
    virtual void set_time_valid( bool ) = 0;

  }; 

}

#endif // __I_INDICATORS_HPP__