#include "wifi.hpp"
#include <memory.h>
#include <esp_wifi.h>
#include <time.h>
#include <sys/time.h>
#include <esp_netif_sntp.h>
#include <lwip/ip_addr.h>
#include <esp_sntp.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::wifi::m_component_name = "wifi";

broadcast_clock::wifi::
wifi() : m_task_queue( nullptr ),
         m_current_mode( mode::station ) {

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
  static mode current_mode = m;
  wifi_task_queue_item item = { wifi_task_message::init, &current_mode };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::wifi::
init_ntp() {
  wifi_task_queue_item item = { wifi_task_message::init_ntp, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::wifi::
on_event( void *arg,
          esp_event_base_t event_base,
          int32_t event_id,
          void *event_data ) {
  static int retries = 0;
  wifi *instance = static_cast<wifi *>( arg );
  if( event_base == WIFI_EVENT ) {
    switch( event_id ) {
      case WIFI_EVENT_STA_START:
        esp_wifi_connect();
        break;
      case WIFI_EVENT_STA_DISCONNECTED:
        if( retries++ < 100 ) {
          vTaskDelay( 1000 / portTICK_PERIOD_MS );
          esp_wifi_connect();
          ESP_LOGI( m_component_name, "Retry connection to network %d of %d", retries, 100 );
        }
        else {
          ESP_LOGE( m_component_name, "Unable to connect to WiFi network" );
        }
        break;
    }
  }
  else if( event_base == IP_EVENT ) {
    switch( event_id ) {
      case IP_EVENT_STA_GOT_IP:
        ip_event_got_ip_t *e = static_cast<ip_event_got_ip_t *>( event_data );
        ESP_LOGI( m_component_name, "Got ip:" IPSTR, IP2STR( &( e->ip_info.ip ) ) );
        retries = 0;
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
  }
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
  config.sync_cb = &wifi::on_sync;
  esp_netif_sntp_init( &config );
  esp_netif_sntp_start();
  esp_netif_sntp_sync_wait( 500 );
}

void broadcast_clock::wifi::
init_wifi() {

  if( m_current_mode == mode::station ) {

    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init( &cfg );

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_register( WIFI_EVENT,
                                         ESP_EVENT_ANY_ID,
                                         &wifi::on_event,
                                         this,
                                         &instance_any_id );

    esp_event_handler_instance_t instance_got_ip;
    esp_event_handler_instance_register( IP_EVENT,
                                         IP_EVENT_STA_GOT_IP,
                                         &wifi::on_event,
                                         this,
                                         &instance_got_ip );
    wifi_config_t wifi_config;
    memset( &wifi_config, 0x00, sizeof( wifi_config_t ) );
    strncpy( reinterpret_cast<char *>( wifi_config.sta.ssid ), "ssid_name", sizeof( wifi_config.sta.ssid ) );
    strncpy( reinterpret_cast<char *>( wifi_config.sta.password ), "password", sizeof( wifi_config.sta.password ) );
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    wifi_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_UNSPECIFIED;

    esp_wifi_set_mode( WIFI_MODE_STA );
    esp_wifi_set_config( WIFI_IF_STA, &wifi_config );
    esp_wifi_start();

  }

}

void broadcast_clock::wifi::
on_sync( struct timeval *now ) {
    ESP_LOGI( m_component_name, "Time synchronized" );
    /*
    struct tm timeinfo;
    localtime_r( static_cast<time_t *>( now ), &timeinfo );
    ESP_LOGI( m_component_name, "Time synchronized: %d-%d-%d %d:%d:%d",
              timeinfo.tm_year + 1900,
              timeinfo.tm_mon + 1,
              timeinfo.tm_mday,
              timeinfo.tm_hour,
              timeinfo.tm_min,
              timeinfo.tm_sec );
    */
}
