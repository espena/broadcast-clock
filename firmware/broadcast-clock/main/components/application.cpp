#include "application.hpp"
#include "clock_face.hpp"
#include "captive_portal_dns.hpp"
#include "captive_portal_http.hpp"
#include "../gpio_mapping.hpp"
#include <string>
#include <memory.h>
#include <nvs_flash.h>
#include <driver/i2c_master.h>
#include <esp_timer.h>
#include <esp_log.h>

using namespace espena::broadcast_clock;

const char *application::m_component_name = "application";

application::
application() : m_i2c_bus( nullptr ),
                m_event_loop_handle( nullptr ) {
  esp_event_loop_args_t loop_args = {
    .queue_size = 1000,
    .task_name = "event_loop",
    .task_priority = uxTaskPriorityGet( NULL ),
    .task_stack_size = 4096,
    .task_core_id = tskNO_AFFINITY
  };
  esp_event_loop_create( &loop_args, &m_event_loop_handle );
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

    m_wifi.set_event_loop_handle( m_event_loop_handle );
    m_wifi.init( wifi::mode::access_point );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::ENTER_CONFIG_MODE,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::LEAVE_CONFIG_MODE,
                                     wifi_event_handler,
                                     this );
    init_ap_duration_timeout();

    m_clock_face.set_event_loop_handle( m_event_loop_handle );
    m_clock_face.init( m_i2c_bus );
}

void application::
wifi_event_handler( void *handler_arg,
                    esp_event_base_t event_base,
                    int32_t event_id,
                    void *event_params )
{
  const std::string source = ( char * ) event_base;
  if( source == broadcast_clock::wifi::m_event_base ) {
    broadcast_clock::application *instance = static_cast<broadcast_clock::application *>( handler_arg );
    switch( event_id ) {
      case broadcast_clock::wifi::ENTER_CONFIG_MODE:
        instance->on_enter_config_mode();
        break;
      case broadcast_clock::wifi::LEAVE_CONFIG_MODE:
        instance->on_leave_config_mode();
        break;
    }
  }
}

void application::
init_ap_duration_timeout() {
  esp_timer_create_args_t timer_args;
  memset( &timer_args, 0x00, sizeof( esp_timer_create_args_t ) );
  timer_args.callback = &application::on_ap_duration_timeout;
  timer_args.arg = this;
  timer_args.name = m_component_name;
  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &m_ap_duration_timer ) );
  ESP_ERROR_CHECK( esp_timer_start_once( m_ap_duration_timer, 30000000 ) );
}

void application::
on_enter_config_mode() {
  if( m_ap_duration_timer ) {
    ESP_ERROR_CHECK( esp_timer_stop( m_ap_duration_timer ) );
    ESP_ERROR_CHECK( esp_timer_delete( m_ap_duration_timer ) );
    m_ap_duration_timer = nullptr;
    m_captive_portal_dns.init();
    m_captive_portal_dns.start();
    m_captive_portal_http.init();
    m_captive_portal_http.start();
  }
}

void application::
on_leave_config_mode() {
  m_captive_portal_dns.stop();
  m_captive_portal_http.stop();
  m_wifi.init( wifi::mode::station );
}

void application::
on_ap_duration_timeout( void *arg ) {
  ESP_LOGI( "application", "Terminate access mode, start station mode" );
  application *app = static_cast<application *>( arg );
  app->m_wifi.init( wifi::mode::station );
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
