#include "application.hpp"
#include <nvs_flash.h>

using namespace espena::broadcast_clock;

application::
application() {
    
}

application::
~application() {

}

void application::
init() {
    init_nvs();
    init_timezone();
    esp_netif_init();
    esp_event_loop_create_default();
    m_wifi.init( wifi::mode::station );
    m_clock_face.init();
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
