#include "wifi.hpp"
#include "configuration.hpp"
#include "http_server.hpp"
#include "../utils/hexdump.hpp"
#include "../secrets.hpp"
#include "../semaphores/mutex.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <memory.h>
#include <esp_wifi.h>
#include <time.h>
#include <sys/time.h>
#include <esp_netif_sntp.h>
#include <lwip/ip_addr.h>
#include <esp_sntp.h>
#include <esp_log.h>

using namespace espena;

broadcast_clock::wifi *broadcast_clock::wifi::m_app_instance = nullptr;

const char *broadcast_clock::wifi::m_component_name = "wifi";
const esp_event_base_t broadcast_clock::wifi::m_event_base = "broadcast_clock_wifi_event";

broadcast_clock::wifi::
wifi() : m_task_queue( nullptr ),
         m_current_mode( mode::station ),
         m_netif( nullptr ) {

  esp_netif_init();
  m_app_instance = this;
  m_task_queue = xQueueCreate( 10, sizeof( wifi_task_queue_item ) );

  memset( &m_last_ntp_sync_time, 0x00, sizeof( struct timespec ) );

  m_task_params.instance = this;

  xTaskCreate( &wifi::task_loop,
               m_component_name,
               m_component_stack_size,
               &m_task_params,
               4,
               &m_task_params.task_handle );

}

broadcast_clock::wifi::
~wifi() {

}

void broadcast_clock::wifi::
set_event_loop_handle( esp_event_loop_handle_t h ) {

  m_event_loop_handle = h;

  esp_event_handler_register_with( m_event_loop_handle,
                                   broadcast_clock::configuration::m_event_base,
                                   broadcast_clock::configuration::CONFIGURATION_UPDATED,
                                   on_event,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   broadcast_clock::http_server::m_event_base,
                                   broadcast_clock::http_server::EVENT_SSID_REQUEST,
                                   on_event,
                                   this );

  esp_event_handler_register_with( m_event_loop_handle,
                                   WIFI_EVENT,
                                   WIFI_EVENT_SCAN_DONE,
                                   on_event,
                                   this );

}

void broadcast_clock::wifi::
init( mode m ) {
  static mode current_mode;
  current_mode = m;
  wifi_task_queue_item item = { wifi_task_message::init, &current_mode };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::wifi::
init_ntp() {
  wifi_task_queue_item item = { wifi_task_message::init_ntp, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::wifi::
enter_config_mode() {
  wifi_task_queue_item item = { wifi_task_message::enter_config_mode, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::wifi::
leave_config_mode() {
  wifi_task_queue_item item = { wifi_task_message::leave_config_mode, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::wifi::
on_event( void *arg,
          esp_event_base_t event_base,
          int32_t event_id,
          void *event_data ) {

  wifi *instance = static_cast<wifi *>( arg );
  ESP_LOGI( instance->m_component_name, "Event received, base %s, id %lu", event_base, event_id );
  if( event_base == WIFI_EVENT ) {
    switch( event_id ) {
      case WIFI_EVENT_STA_START:
        esp_wifi_connect();
        break;
      case WIFI_EVENT_AP_STACONNECTED:
        instance->enter_config_mode();
        break;
      case WIFI_EVENT_AP_STADISCONNECTED:
        instance->leave_config_mode();
        break;
      case WIFI_EVENT_STA_DISCONNECTED:
        // Retry forever
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
        esp_wifi_connect();
        ESP_LOGI( m_component_name, "Retry connection to network" );
        break;
      case WIFI_EVENT_SCAN_DONE:
        wifi_task_queue_item item = { wifi_task_message::ssid_scan_done, nullptr };
        xQueueSend( instance->m_task_queue, &item, 10 );
        break;
    }
  }
  else if( event_base == IP_EVENT ) {
    switch( event_id ) {
      case IP_EVENT_STA_GOT_IP:
        ip_event_got_ip_t *e = static_cast<ip_event_got_ip_t *>( event_data );
        ESP_LOGI( m_component_name, "Got ip:" IPSTR, IP2STR( &( e->ip_info.ip ) ) );
        instance->got_ip( &( e->ip_info ) );
        instance->init_ntp();
        break;
    }
  }
  else if( event_base == broadcast_clock::http_server::m_event_base ) {
    switch( event_id ) {
      case broadcast_clock::http_server::EVENT_SSID_REQUEST:
        {
          wifi_task_queue_item item = { wifi_task_message::ssid_request, nullptr };
          xQueueSend( instance->m_task_queue, &item, 10 );
        }
        break;
    }
  }
  else if( event_base == broadcast_clock::configuration::m_event_base ) {
    switch( event_id ) {
      case broadcast_clock::configuration::CONFIGURATION_UPDATED:
        instance->on_configuration_changed();
        break;
    }
  }
}

void broadcast_clock::wifi::
on_ssid_request() {
  esp_wifi_scan_start( nullptr, false );
}

void broadcast_clock::wifi::
on_ssid_response() {
  if( xSemaphoreTake( semaphores::mutex::ssid_list, portMAX_DELAY ) ) {
    static ssid_scan_result_t ssid_scan_result;
    memset( &ssid_scan_result, 0x00, sizeof( ssid_scan_result_t ) );
    wifi_ap_record_t buffer[ max_ssid_scan_result ];
    uint16_t n = max_ssid_scan_result;
    if( esp_wifi_scan_get_ap_records( &n, buffer ) == ESP_OK ) {
      ssid_scan_result.ap_count = n;
      for( int16_t i = 0; i < ssid_scan_result.ap_count; i++ ) {
        memcpy( &ssid_scan_result.ap_records[ i ], &buffer[ i ], sizeof( wifi_ap_record_t ) );
      }
    }
    if( m_event_loop_handle ) {
      esp_event_post_to( m_event_loop_handle,
                        broadcast_clock::wifi::m_event_base,
                        broadcast_clock::wifi::SSID_SCAN_RESULT,
                        &ssid_scan_result,
                        sizeof( ssid_scan_result_t ),
                        10 );
    }
    xSemaphoreGive( semaphores::mutex::ssid_list );
  }
}

void broadcast_clock::wifi::
got_ip( esp_netif_ip_info_t *_ip_info ) {
  static esp_netif_ip_info_t ip_info;
  memcpy( &ip_info, _ip_info, sizeof( esp_netif_ip_info_t ) );
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                       broadcast_clock::wifi::m_event_base,
                       broadcast_clock::wifi::WIFI_EVENT_GOT_IP,
                       &ip_info,
                       sizeof( ip_info ),
                       10 );
  }
}

void broadcast_clock::wifi::
task_loop( void *arg ) {
  wifi_task_params *params = static_cast<wifi_task_params *>( arg );
  wifi *inst = params->instance;
  wifi_task_queue_item item;
  memset( &item, 0x00, sizeof( wifi_task_queue_item ) );
  while( 1 ) {
    vTaskDelay( 10 );
    if( xQueueReceive( inst->m_task_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void broadcast_clock::wifi::
on_message( wifi_task_message msg, void *arg ) {
  switch( msg ) {
    case wifi_task_message::init:
      on_init( *( static_cast<mode *>( arg ) ) );
      break;
    case wifi_task_message::init_ntp:
      on_init_ntp();
      break;
    case wifi_task_message::ssid_request:
      on_ssid_request();
      break;
    case wifi_task_message::ssid_scan_done:
      on_ssid_response();
      break;
    case wifi_task_message::enter_config_mode:
      on_enter_config_mode();
      break;
    case wifi_task_message::leave_config_mode:
      on_leave_config_mode();
      break;
  }
}

void broadcast_clock::wifi::
on_configuration_changed() {
  broadcast_clock::configuration *c = broadcast_clock::configuration::get_instance();
  const int upint = c->get_int( "update_interval" );
  if( sntp_get_sync_interval() != upint ) {
    ESP_LOGI( m_component_name, "NTP interval changed to %d minutes, updating...", upint / 60000 );
    sntp_set_sync_interval( upint );
  }
}

void broadcast_clock::wifi::
on_enter_config_mode() {
  esp_event_post_to( m_event_loop_handle,
                     broadcast_clock::wifi::m_event_base,
                     broadcast_clock::wifi::ENTER_CONFIG_MODE,
                     nullptr,
                     0,
                     10 );
}

void broadcast_clock::wifi::
on_leave_config_mode() {
  esp_event_post_to( m_event_loop_handle,
                     broadcast_clock::wifi::m_event_base,
                     broadcast_clock::wifi::LEAVE_CONFIG_MODE,
                     nullptr,
                     0,
                     10 );
}

void broadcast_clock::wifi::
on_init( wifi::mode m ) {
  ESP_LOGI( m_component_name, "Initializing" );
  m_current_mode = m;
  init_wifi();
}

void broadcast_clock::wifi::
on_init_ntp() {
  static char ntpserv[ 1024 ];
  ESP_LOGI( m_component_name, "Initializing NTP" );
  esp_netif_sntp_deinit();
  configuration *appconf = configuration::get_instance();
  memset( ntpserv, 0x00, sizeof( ntpserv ) );
  strncpy( ntpserv, appconf->get_str( "ntp" ).c_str(), sizeof( ntpserv ) );
  const int upint = appconf->get_int( "update_interval" );
  ESP_LOGI( m_component_name, "NTP server(s): %s, Update interval: %d ms", ntpserv, upint );
  esp_sntp_config_t config;
  memset( &config, 0x00, sizeof( esp_sntp_config_t ) );
  config.start = true;
  config.num_of_servers = 1;
  config.servers[ 0 ] = ntpserv;
  config.renew_servers_after_new_IP = true;
  config.index_of_first_server = 0;
  config.ip_event_to_renew = IP_EVENT_STA_GOT_IP;
  config.sync_cb = &wifi::on_ntp_sync;
  ESP_ERROR_CHECK( esp_netif_sntp_init( &config ) );
  ESP_ERROR_CHECK( esp_netif_sntp_start() );
  sntp_set_sync_interval( upint );
}

void broadcast_clock::wifi::
init_wifi() {

  wifi_mode_t m;
  if( esp_wifi_get_mode( &m ) != ESP_ERR_WIFI_NOT_INIT ) {
    esp_wifi_stop();
    esp_wifi_deinit();
  }
  
  if( m_netif ) {
    ESP_LOGI( m_component_name, "Destroy netif" );
    esp_netif_destroy( m_netif );
    m_netif = nullptr;
  }

  esp_event_handler_unregister( WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi::on_event );
  esp_event_handler_unregister( IP_EVENT, ESP_EVENT_ANY_ID, &wifi::on_event );

  if( m_current_mode == mode::station ) {

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init( &cfg );

    m_netif = esp_netif_create_default_wifi_sta();
    assert( m_netif );

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_register( WIFI_EVENT,
                                         ESP_EVENT_ANY_ID,
                                         &wifi::on_event,
                                         this,
                                         &instance_any_id );

    esp_event_handler_instance_t instance_got_ip;
    esp_event_handler_instance_register( IP_EVENT,
                                         ESP_EVENT_ANY_ID,
                                         &wifi::on_event,
                                         this,
                                         &instance_got_ip );
    
    wifi_config_t wifi_config;
    memset( &wifi_config, 0x00, sizeof( wifi_config_t ) );

    broadcast_clock::configuration *c = broadcast_clock::configuration::get_instance();

    strncpy( reinterpret_cast<char *>( wifi_config.sta.ssid ),
             c->get_str( "ssid" ).c_str(),
             sizeof( wifi_config.sta.ssid ) );

    strncpy( reinterpret_cast<char *>( wifi_config.sta.password ),
             c->get_str( "password" ).c_str(),
             sizeof( wifi_config.sta.password ) );

    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    wifi_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_UNSPECIFIED;

    esp_wifi_set_mode( WIFI_MODE_STA );
    esp_wifi_set_config( WIFI_IF_STA, &wifi_config );
    esp_wifi_start();
    esp_wifi_set_ps( WIFI_PS_NONE );

  }
  else if( m_current_mode == mode::access_point ) {

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init( &cfg );

    m_netif = esp_netif_create_default_wifi_ap();
    assert( m_netif );

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_register( WIFI_EVENT,
                                         ESP_EVENT_ANY_ID,
                                         &wifi::on_event,
                                         this,
                                         &instance_any_id );
    wifi_config_t wifi_config;
    memset( &wifi_config, 0x00, sizeof( wifi_config_t ) );
    
    const char ssid[ ] = "broadcast_clock";
    memcpy( reinterpret_cast<char *>( wifi_config.ap.ssid ), ssid, sizeof( ssid ) );
    wifi_config.ap.ssid_len = sizeof( ssid );
    wifi_config.ap.channel = 7;
    wifi_config.ap.password[ 0 ] = '\0';
    wifi_config.ap.max_connection = 100;
    wifi_config.ap.authmode = WIFI_AUTH_OPEN;

    ESP_LOGI( m_component_name, "Setting WiFi mode to AP" );
    esp_wifi_set_mode( WIFI_MODE_APSTA );

    ESP_LOGI( m_component_name, "Setting AP config" );
    ESP_ERROR_CHECK( esp_wifi_set_config( WIFI_IF_AP, &wifi_config ) );

    esp_wifi_set_config( WIFI_IF_AP, &wifi_config );
    esp_wifi_start();
    esp_wifi_scan_start( nullptr, false );

  }
}

void broadcast_clock::wifi::
on_ntp_sync( struct timeval *now ) {
  if( m_app_instance && m_app_instance->m_event_loop_handle ) {
    struct tm timeinfo;
    memset( &timeinfo, 0x00, sizeof( struct tm ) );
    time_t epoch = static_cast<time_t>( now->tv_sec );
    localtime_r( &epoch, &timeinfo );

    uint32_t e = 0;
    if( sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED ) {
      e = broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC;
      if( xSemaphoreTake( semaphores::mutex::system_clock, portMAX_DELAY ) ) {
        clock_gettime( CLOCK_MONOTONIC, &m_app_instance->m_last_ntp_sync_time );
        xSemaphoreGive( semaphores::mutex::system_clock );
      }
    }
    else {
      e = wifi::WIFI_EVENT_NTP_SYNC_FAILED;
    }

    esp_event_post_to( m_app_instance->m_event_loop_handle,
                       broadcast_clock::wifi::m_event_base,
                       e,
                       &timeinfo,
                       sizeof( timeinfo ),
                       10 );
  }
}
