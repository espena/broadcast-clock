#include "wifi.hpp"
#include "../secrets.hpp"
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

  m_task_params.instance = this;

  xTaskCreate( &wifi::task_loop,
               m_component_name,
               m_component_stack_size,
               &m_task_params,
               2,
               &m_task_params.task_handle );

}

broadcast_clock::wifi::
~wifi() {

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
    }
  }
  else if( event_base == IP_EVENT ) {
    switch( event_id ) {
      case IP_EVENT_STA_GOT_IP:
        ip_event_got_ip_t *e = static_cast<ip_event_got_ip_t *>( event_data );
        ESP_LOGI( m_component_name, "Got ip:" IPSTR, IP2STR( &( e->ip_info.ip ) ) );
        instance->init_ntp();
        break;
    }
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
  wifi_task_queue_item *item = nullptr;
  switch( msg ) {
    case wifi_task_message::init:
      on_init( *( static_cast<mode *>( arg ) ) );
      break;
    case wifi_task_message::init_ntp:
      on_init_ntp();
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
  ESP_LOGI( m_component_name, "Initializing NTP" );
  esp_sntp_config_t config;
  memset( &config, 0x00, sizeof( esp_sntp_config_t ) );
  config.start = true;
  config.num_of_servers = 1;
  config.servers[ 0 ] = "pool.ntp.org";
  config.renew_servers_after_new_IP = true;
  config.index_of_first_server = 0;
  config.ip_event_to_renew = IP_EVENT_STA_GOT_IP;
  config.sync_cb = &wifi::on_ntp_sync;
  esp_netif_sntp_init( &config );
  esp_netif_sntp_start();
  esp_netif_sntp_sync_wait( 500 );
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
    strncpy( reinterpret_cast<char *>( wifi_config.sta.ssid ), WIFI_SSID, sizeof( wifi_config.sta.ssid ) );
    strncpy( reinterpret_cast<char *>( wifi_config.sta.password ), WIFI_PASSWORD, sizeof( wifi_config.sta.password ) );
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    wifi_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_UNSPECIFIED;

    esp_wifi_set_mode( WIFI_MODE_STA );
    esp_wifi_set_config( WIFI_IF_STA, &wifi_config );
    esp_wifi_start();

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
    wifi_config.ap.max_connection = 10;
    wifi_config.ap.authmode = WIFI_AUTH_OPEN;

    ESP_LOGI( m_component_name, "Setting WiFi mode to AP" );
    esp_wifi_set_mode( WIFI_MODE_AP );

    ESP_LOGI( m_component_name, "Setting AP config" );
    ESP_ERROR_CHECK( esp_wifi_set_config( WIFI_IF_AP, &wifi_config ) );

    esp_wifi_set_config( WIFI_IF_AP, &wifi_config );
    esp_wifi_start();

  }

}

void broadcast_clock::wifi::
on_ntp_sync( struct timeval *now ) {
  ESP_LOGI( m_component_name, "Time synchronized" );
  if( m_app_instance && m_app_instance->m_event_loop_handle ) {
    struct tm timeinfo;
    memset( &timeinfo, 0x00, sizeof( struct tm ) );
    time_t epoch = static_cast<time_t>( now->tv_sec );
    localtime_r( &epoch, &timeinfo );
    esp_event_post_to( m_app_instance->m_event_loop_handle,
                       broadcast_clock::wifi::m_event_base,
                       broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC,
                       &timeinfo,
                       sizeof( timeinfo ),
                       10 );
  }
}
