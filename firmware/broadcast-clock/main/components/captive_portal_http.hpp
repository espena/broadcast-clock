#ifndef __captive_portal_http_hpp__
#define __captive_portal_http_hpp__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_http_server.h>

namespace espena::broadcast_clock {

  namespace resources::html {
    extern const uint8_t control_panel_html_start[ ] asm( "_binary_control_panel_html_start" );
    extern const uint8_t control_panel_html_end[ ] asm( "_binary_control_panel_html_end" );
  }

  class captive_portal_http {

    static const char *m_component_name;
    static const size_t m_component_stack_size = 4096;

    QueueHandle_t m_message_queue;
    httpd_handle_t m_server;

    httpd_config_t m_cfg = HTTPD_DEFAULT_CONFIG();

    //event::event_dispatcher m_event_dispatcher;

    std::string m_json_network_list;

    static void task_loop( void *arg );

    static esp_err_t request_handler( httpd_req_t *req );
    esp_err_t on_request( httpd_req_t *req );

    typedef struct captive_portal_http_task_params_struct {
        captive_portal_http *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } captive_portal_http_task_params;

    captive_portal_http_task_params m_task_params;

    enum class captive_portal_http_task_message {
        set_network_list,
        init,
        start,
        stop
    };

    typedef struct captive_portal_http_task_queue_item_struct {
        captive_portal_http_task_message message;
        void *arg;
    } captive_portal_http_task_queue_item;

    void on_message( captive_portal_http_task_message msg, void *arg );

    void enqueue_simple_message( captive_portal_http_task_message msg );

    void init_sync();
    void start_sync();
    void stop_sync();

    public:

      static const esp_event_base_t m_event_base;

      enum class event {
        base = 0x9000,
        ssid_select
      };

      void set_event_loop_handle( esp_event_loop_handle_t esp_event_loop_handle );

      void add_event_listener( int32_t event_id,
                               esp_event_handler_t event_handler,
                               void *instance );

      captive_portal_http();

      void set_network_list( char *json );

      void init();
      void start();
      void stop();

  }; // class captive_portal_http

}; // namespace espena::broadcast_clock

#endif // __captive_portal_http_hpp__