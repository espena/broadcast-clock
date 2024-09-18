#include "application.hpp"
#include "clock_face.hpp"
#include "captive_portal_dns.hpp"
#include "captive_portal_http.hpp"
#include "../gpio_mapping.hpp"
#include <rtc_wdt.h>
#include <string>
#include <memory.h>
#include <nvs_flash.h>
#include <driver/i2c_master.h>
#include <esp_timer.h>
#include <esp_log.h>

using namespace espena::broadcast_clock;

const char *application::m_component_name = "application";

application::
application() : m_configuration( nullptr ),
                m_clock_status( m_clock_face.get_indicators() ),
                m_i2c_bus( nullptr ),
                m_event_loop_handle( nullptr ) {

  esp_event_loop_args_t loop_args = {
    .queue_size = 100,
    .task_name = "event_loop",
    .task_priority = 15,
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

    m_configuration = broadcast_clock::configuration::get_instance();
    m_configuration->set_event_loop_handle( m_event_loop_handle );

    init_timezone();
    init_i2c();

    esp_netif_init();
    esp_event_loop_create_default();

    m_captive_portal_http.set_event_loop_handle( m_event_loop_handle );
    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_SAVE,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_CANCEL,
                                     wifi_event_handler,
                                     this );

    m_wifi.set_event_loop_handle( m_event_loop_handle );
    m_wifi.init( wifi::mode::access_point );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::WIFI_EVENT_GOT_IP,
                                     wifi_event_handler,
                                     this );

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

    m_beeper.init();
    m_beeper.set_event_loop_handle( m_event_loop_handle );
    
    m_clock_face.set_event_loop_handle( m_event_loop_handle );

    m_clock_face.init( m_i2c_bus );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::clock_face::m_event_base,
                                     broadcast_clock::clock_face::EVENT_COUNTDOWN_FINISH,
                                     wifi_event_handler,
                                     this );

    m_lea_m8t.init( m_i2c_bus );

    if( m_configuration->get_bool( "configurator" ) ) {
      m_captive_portal_http.init();
      m_captive_portal_http.start();
    }
}

void application::
on_press_test( void *arg ) {

}

void application::
on_start_test( void *arg ) {
  if( gpio_get_level( GPIO_NUM_0 ) == 0 ) {
    application *app = static_cast<application *>( arg );
    app->m_clock_face.test();
  }
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
      case broadcast_clock::wifi::WIFI_EVENT_GOT_IP:
        instance->on_got_ip( static_cast<esp_netif_ip_info_t *>( event_params ) );
        break;
      case broadcast_clock::wifi::ENTER_CONFIG_MODE:
        instance->on_enter_config_mode();
        break;
      case broadcast_clock::wifi::LEAVE_CONFIG_MODE:
        instance->on_leave_config_mode();
        break;
    }
  }
  else if( source == broadcast_clock::captive_portal_http::m_event_base ) {
    broadcast_clock::application *instance = static_cast<broadcast_clock::application *>( handler_arg );
    switch( event_id ) {
      case broadcast_clock::captive_portal_http::EVENT_SAVE:
        instance->on_save_config( std::string( ( char * ) event_params ) );
        break;
      case broadcast_clock::captive_portal_http::EVENT_CANCEL:
        instance->on_cancel_config( std::string( ( char * ) event_params ) );
        break;
    }
  }
  else if( source == broadcast_clock::clock_face::m_event_base ) {
    broadcast_clock::application *instance = static_cast<broadcast_clock::application *>( handler_arg );
    switch( event_id ) {
      case broadcast_clock::clock_face::EVENT_COUNTDOWN_FINISH:
        instance->on_countdown_finish();
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
switch_to_station_mode() {
  wifi_mode_t mode;
  esp_wifi_get_mode( &mode );
  if( mode == WIFI_MODE_STA ) {
    return;
  }
  m_captive_portal_dns.stop();
  if( !m_configuration->get_bool( "configurator" ) ) {
    m_captive_portal_http.stop();
  }
  m_wifi.init( wifi::mode::station );
}

void application::
on_got_ip( esp_netif_ip_info_t *ip_info ) {
  m_clock_face.display_ip( ip_info );
}

void application::
on_enter_config_mode() {
  if( m_ap_duration_timer ) {
    ESP_ERROR_CHECK( esp_timer_stop( m_ap_duration_timer ) );
    ESP_ERROR_CHECK( esp_timer_delete( m_ap_duration_timer ) );
    m_ap_duration_timer = nullptr;
    m_captive_portal_dns.init();
    m_captive_portal_dns.start();
    if( !m_configuration->get_bool( "configurator" ) ) {
      m_captive_portal_http.init();
      m_captive_portal_http.start();
    }
  }
}

void application::
on_save_config( std::string post_data ) {
  ESP_LOGI( "application", "Save config: %s", post_data.c_str() );
  switch_to_station_mode();
  m_configuration->update( post_data );
  init_timezone();
}

void application::
on_cancel_config( std::string post_data ) {
  switch_to_station_mode();
  m_configuration->update( post_data );
  init_timezone();
}

void application::
on_leave_config_mode() {
  switch_to_station_mode();
}

void application::
on_countdown_finish() {
  m_beeper.alarm();
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
  std::string timezone = m_configuration->get_str( "time_zone" );
  ESP_LOGI( "application", "Setting timezone to %s", timezone.c_str() );
  setenv( "TZ", timezone.c_str(), 1 );
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
  bus_config.intr_priority = 1;
  bus_config.flags.enable_internal_pullup = false;
  ESP_ERROR_CHECK( i2c_new_master_bus( &bus_config, &m_i2c_bus ) );
}
