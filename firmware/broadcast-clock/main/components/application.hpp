#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "wifi.hpp"
#include "clock_face.hpp"

namespace espena::broadcast_clock {

    class application {

        wifi m_wifi;
        clock_face m_clock_face;

    public:

        application();
        ~application();
        void init();
        void init_nvs();
        void init_timezone();

    };

}

#endif // __APPLICATION_HPP__