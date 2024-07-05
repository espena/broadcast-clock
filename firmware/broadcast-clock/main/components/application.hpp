#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "clock_face.hpp"

namespace espena::broadcast_clock {

    class application {

        clock_face m_clock_face;

    public:

        application();
        ~application();
        void init();

    };

}

#endif // __APPLICATION_HPP__