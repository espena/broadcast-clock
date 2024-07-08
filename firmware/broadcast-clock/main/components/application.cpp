#include "application.hpp"
#include "clock_face.hpp"
#include "../gpio_mapping.hpp"
#include <memory.h>
#include <nvs_flash.h>
#include <driver/i2c_master.h>
#include <esp_log.h>

using namespace espena::broadcast_clock;

application::
application() : m_i2c_bus( nullptr ) {
  
}

application::
~application() {

}

void application::
init() {
    init_nvs();
    init_timezone();
    init_i2c();
    esp_netif_init();
    esp_event_loop_create_default();
    m_wifi.init( wifi::mode::station );
    m_clock_face.init( m_i2c_bus );
}

void application::
init_nvs() {
  esp_err_t nvs_status = nvs_flash_init();
  if ( nvs_status == ESP_ERR_NVS_NO_FREE_PAGES ||
       nvs_status == ESP_ERR_NVS_NEW_VERSION_FOUND )
  {
    ESP_ERROR_CHECK( nvs_flash_erase() );
    nvs_status = nvs_flash_init();
  }
  ESP_ERROR_CHECK( nvs_status );
}

void application::
init_timezone() {
  setenv( "TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1 );
  tzset();
}

void application::
init_i2c() {
  ESP_LOGI( "application", "Initializing i2c" );
  i2c_master_bus_config_t bus_config;
  memset( &bus_config, 0x00, sizeof( i2c_master_bus_config_t ) );
  bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
  bus_config.i2c_port = I2C_NUM_0;
  bus_config.scl_io_num = I2C_SCL;
  bus_config.sda_io_num = I2C_SDA;
  bus_config.glitch_ignore_cnt = 7;
  ESP_ERROR_CHECK( i2c_new_master_bus( &bus_config, &m_i2c_bus ) );
}
