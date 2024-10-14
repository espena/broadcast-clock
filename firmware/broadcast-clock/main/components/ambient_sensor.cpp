#include "ambient_sensor.hpp"
#include "../gpio_mapping.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <memory.h>
#include <driver/i2c.h>
#include <esp_log.h>

#define I2C_MASTER_WRITE 0
#define I2C_MASTER_READ 1

using namespace espena;

const char *broadcast_clock::ambient_sensor::m_component_name = "ambient_sensor";

broadcast_clock::ambient_sensor::
ambient_sensor() {
    
}

broadcast_clock::ambient_sensor::
~ambient_sensor() {

}

void broadcast_clock::ambient_sensor::
init() {
  ESP_LOGI( m_component_name, "Initializing" );
  init_sensor();
}

void broadcast_clock::ambient_sensor::
init_sensor() {

  uint8_t cmd_config[ ] = { 0x00, 0b00001000, 0b11000000 };
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start( cmd );
  i2c_master_write_byte( cmd, ( m_i2c_address << 1 ) | I2C_MASTER_WRITE, true );
  i2c_master_write( cmd, cmd_config, sizeof( cmd_config ), true );
  i2c_master_stop( cmd );
  esp_err_t res = i2c_master_cmd_begin( I2C_NUM_0, cmd, 1000 );
  i2c_cmd_link_delete( cmd );

}

uint16_t broadcast_clock::ambient_sensor::
read() {
  uint8_t cmd_read_als[ ] = { 0x04 };
  uint8_t buf_lux_val[ ] = { 0x00, 0x00 };
  uint16_t lux = 0;

  esp_err_t res = i2c_master_write_read_device( I2C_NUM_0,
                                                m_i2c_address,
                                                cmd_read_als,
                                                sizeof( cmd_read_als ),
                                                buf_lux_val,
                                                sizeof( buf_lux_val ),
                                                -1 );

  if( res == ESP_OK ) {
    lux = ( buf_lux_val[ 0 ] << 8 ) | buf_lux_val[ 1 ];
  }

  return lux;
}