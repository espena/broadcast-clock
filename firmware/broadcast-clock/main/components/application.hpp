#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "wifi.hpp"
#include "clock_face.hpp"
#include <driver/i2c_master.h>

namespace espena::broadcast_clock {

  class application {

    wifi m_wifi;
    clock_face m_clock_face;
    i2c_master_bus_handle_t m_i2c_bus;

    esp_event_loop_handle_t m_event_loop_handle;

  public:

    application();
    ~application();
    void init();
    void init_nvs();
    void init_timezone();
    void init_i2c();

  };

}

#endif // __APPLICATION_HPP__