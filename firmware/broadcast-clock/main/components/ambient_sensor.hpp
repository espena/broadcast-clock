#ifndef __AMBIENT_SENSOR_HPP__
#define __AMBIENT_SENSOR_HPP__

#include <driver/i2c_master.h>

namespace espena::broadcast_clock {

    class ambient_sensor {

      static const char *m_component_name;
      static const uint8_t m_i2c_address = 0x10;

      i2c_master_bus_handle_t m_i2c_bus;
      i2c_master_dev_handle_t m_i2c_dev;

      void init_sensor();

    public:

        ambient_sensor();
        ~ambient_sensor();

        void init( i2c_master_bus_handle_t i2c_bus );
        uint16_t read();

    };

} // namespace espena::broadcast_clock

#endif // __AMBIENT_SENSOR_HPP__
