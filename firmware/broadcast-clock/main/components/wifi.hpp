#ifndef __WIFI_HPP__
#define __WIFI_HPP__

#include "configuration.hpp"

#include <time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_wifi.h>
#include <esp_sntp.h>
#include <esp_log.h>
#include <esp_event.h>

namespace espena::broadcast_clock {

  class wifi {

  public:

    static const esp_event_base_t m_event_base;
    static const uint32_t WIFI_EVENT_NTP_SYNC = 0x01u;
    static const uint32_t WIFI_EVENT_NTP_SYNC_FAILED = 0x02u;
    static const uint32_t WIFI_EVENT_GOT_IP = 0x03u;
    static const uint32_t ENTER_CONFIG_MODE = 0x04u;
    static const uint32_t LEAVE_CONFIG_MODE = 0x05u;

    enum class mode {
      none,
      station,
      access_point
    };

  private:

    static wifi *m_app_instance;

    static const char *m_component_name;
    static const size_t m_component_stack_size = 16384;

    QueueHandle_t m_task_queue;
    esp_event_loop_handle_t m_event_loop_handle;

    mode m_current_mode;

    esp_netif_t *m_netif;

    typedef struct wifi_task_params_struct {
      wifi *instance;
      TaskHandle_t task_handle;
    } wifi_task_params;

    wifi_task_params m_task_params;

    enum class wifi_task_message {
      init,
      init_ntp,
      enter_config_mode,
      leave_config_mode
    };

    typedef struct wifi_task_queue_item_struct {
      wifi_task_message message;
      void *arg;
    } wifi_task_queue_item;

    struct timespec m_last_ntp_sync_time;

    static void on_ntp_sync( struct timeval *now );
    
    static void on_event( void *arg,
                          esp_event_base_t event_base,
                          int32_t event_id,
                          void *event_data );

    static void task_loop( void *arg );

    void enter_config_mode();
    void on_enter_config_mode();
    void on_configuration_changed();

    void leave_config_mode();
    void on_leave_config_mode();

    void on_message( wifi_task_message msg, void *arg );

    void on_init( mode m );
    void on_init_ntp();

    void init_wifi();
    void init_ntp();

    void got_ip( esp_netif_ip_info_t *ip_info );

    //void on_client_connected();
    
  public:

    wifi();
    ~wifi();

    void init( mode m = mode::station );
    void set_event_loop_handle( esp_event_loop_handle_t h );

  };

}

#endif // __WIFI_HPP__