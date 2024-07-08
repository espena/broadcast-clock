#ifndef __WIFI_HPP__
#define __WIFI_HPP__

#include <time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_wifi.h>
#include <esp_log.h>

namespace espena::broadcast_clock {

  class wifi {

  public:

    enum class mode {
      station,
      access_point
    };

  private:

    static const char *m_component_name;
    static const size_t m_component_stack_size = 32768;

    QueueHandle_t m_task_queue;

    mode m_current_mode;

    typedef struct wifi_task_params_struct {
      wifi *instance;
      TaskHandle_t task_handle;
    } wifi_task_params;

    wifi_task_params m_task_params;

    enum class wifi_task_message {
      init,
      init_ntp
    };

    typedef struct wifi_task_queue_item_struct {
      wifi_task_message message;
      void *arg;
    } wifi_task_queue_item;

    static void on_ntp_sync( struct timeval *now );
    
    static void on_event( void *arg,
                          esp_event_base_t event_base,
                          int32_t event_id,
                          void *event_data );

    static void task_loop( void *arg );

    void on_message( wifi_task_message msg, void *arg );

    void on_init( mode m );
    void on_init_ntp();

    void init_wifi();
    void init_ntp();

  public:

    wifi();
    ~wifi();
    void init( mode m = mode::station );

  };

}

#endif // __WIFI_HPP__