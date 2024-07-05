#ifndef __CLOCK_FACE_HPP__
#define __CLOCK_FACE_HPP__

#include "dial.hpp"

namespace espena::broadcast_clock {

    class clock_face {

        dial m_dial;

    public:

        clock_face();
        ~clock_face();
        void init();

    };

}

#endif // __CLOCK_FACE_HPP__