#include "ambient_sensor.hpp"
#include "../gpio_mapping.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <memory.h>
//#include <driver/i2c.h>
#include <driver/i2c_master.h>
#include <esp_log.h>

#define I2C_MASTER_WRITE 0
#define I2C_MASTER_READ 1

using namespace espena;

const char *broadcast_clock::ambient_sensor::m_component_name = "ambient_sensor";

broadcast_clock::ambient_sensor::
ambient_sensor() : m_i2c_bus( nullptr ),
                   m_i2c_dev( nullptr ) {
    
}

broadcast_clock::ambient_sensor::
~ambient_sensor() {

}

void broadcast_clock::ambient_sensor::
init( i2c_master_bus_handle_t i2c_bus ) {
  ESP_LOGI( m_component_name, "Initializing" );
  m_i2c_bus = i2c_bus;
  init_sensor();
}

void broadcast_clock::ambient_sensor::
init_sensor() {
  i2c_master_probe( m_i2c_bus, m_i2c_address, -1 );
  i2c_device_config_t dev_cfg;
  memset( &dev_cfg, 0x00, sizeof( i2c_device_config_t ) );
  dev_cfg.dev_addr_length = I2C_ADDR_BIT_LEN_7;
  dev_cfg.device_address = m_i2c_address;
  dev_cfg.scl_speed_hz = 10000;
  ESP_ERROR_CHECK( i2c_master_bus_add_device( m_i2c_bus, &dev_cfg, &m_i2c_dev ) );
  uint8_t cmd_config[ ] = { 0x00, 0b00001000, 0b11000000 };
  ESP_ERROR_CHECK( i2c_master_transmit( m_i2c_dev, cmd_config, sizeof( cmd_config ), -1 ) );
}

uint16_t broadcast_clock::ambient_sensor::
read() {
  uint8_t cmd_read_als[ ] = { 0x04 };
  uint8_t buf_lux_val[ ] = { 0x00, 0x00 };
  ESP_ERROR_CHECK( i2c_master_transmit_receive( m_i2c_dev,
                                                cmd_read_als,
                                                sizeof( cmd_read_als ),
                                                buf_lux_val,
                                                sizeof( buf_lux_val ),
                                                -1 ) );
  return ( buf_lux_val[ 0 ] << 8 ) | buf_lux_val[ 1 ];
}