#ifndef __CAPTIVE_PORTAL_HTTP_HPP__
#define __CAPTIVE_PORTAL_HTTP_HPP__

#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_http_server.h>
#include <esp_event.h>

#include "i_gnss_state.hpp"

namespace espena::broadcast_clock {

  namespace resources {
    namespace html {
      extern const uint8_t control_panel_html_start[ ] asm( "_binary_control_panel_html_start" );
      extern const uint8_t control_panel_html_end[ ] asm( "_binary_control_panel_html_end" );
      extern const uint8_t exit_page_html_start[ ] asm( "_binary_exit_page_html_start" );
      extern const uint8_t exit_page_html_end[ ] asm( "_binary_exit_page_html_end" );
      extern const uint8_t timers_page_html_start[ ] asm( "_binary_timers_page_html_start" );
      extern const uint8_t timers_page_html_end[ ] asm( "_binary_timers_page_html_end" );
      extern const uint8_t styles_css_start[ ] asm( "_binary_styles_css_start" );
      extern const uint8_t styles_css_end[ ] asm( "_binary_styles_css_end" );
    }
    namespace gfx {
      extern const uint8_t favicon_ico_start[ ] asm( "_binary_favicon_ico_start" );
      extern const uint8_t favicon_ico_end[ ] asm( "_binary_favicon_ico_end" );
    }
  }

  class captive_portal_http {

  public:

    static const esp_event_base_t m_event_base;

    static const uint32_t EVENT_SAVE                = 0x01u;
    static const uint32_t EVENT_CANCEL              = 0x02u;
    
    static const uint32_t EVENT_ENTER_TIMERS        = 0x03u;
    static const uint32_t EVENT_LEAVE_TIMERS        = 0x04u;
    
    static const uint32_t EVENT_CONFIGURATOR_START  = 0x05u;
    static const uint32_t EVENT_CONFIGURATOR_STOP   = 0x06u;

    static const uint32_t EVENT_STOPWATCH_START     = 0x07u;
    static const uint32_t EVENT_STOPWATCH_STOP      = 0x08u;
    static const uint32_t EVENT_STOPWATCH_RESET     = 0x09u;

    static const uint32_t EVENT_COUNTDOWN_START     = 0x0au;
    static const uint32_t EVENT_COUNTDOWN_RESET     = 0x0bu;

    static const uint32_t EVENT_START_TIME_MODE     = 0x0cu;
    static const uint32_t EVENT_STOP_TIME_MODE      = 0x0du;

  private:

    static const char *m_component_name;
    static const size_t m_component_stack_size = 8192;

    QueueHandle_t m_message_queue;
    httpd_handle_t m_server;

    esp_event_loop_handle_t m_event_loop_handle;
    i_gnss_state *m_gnss_state;

    httpd_config_t m_cfg = HTTPD_DEFAULT_CONFIG();

    std::string m_json_network_list;
    std::string m_json_gnss_status;

    bool m_gnss_installed = false;

    void update_json_gnss_status();

    static void task_loop( void *arg );

    static esp_err_t request_handler( httpd_req_t *req );

    esp_err_t on_request( httpd_req_t *req );
    void save_handler( httpd_req_t *req );
    void survey_in_handler( httpd_req_t *req );
    void timers_handler( httpd_req_t *req );

    void stopwatch_handler( httpd_req_t *req );
    void countdown_handler( httpd_req_t *req );

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

    std::string create_html_response();

    void init_sync();
    void start_sync();
    void stop_sync();

    public:

      void set_event_loop_handle( esp_event_loop_handle_t h ) { m_event_loop_handle = h; };
      void set_gnss_state( i_gnss_state *gnss_state ) { m_gnss_state = gnss_state; };

      captive_portal_http();

      void set_network_list( char *json );

      void init();
      void start();
      void stop();

  }; // class captive_portal_http

}; // namespace espena::broadcast_clock

#endif // __CAPTIVE_PORTAL_HTTP_HPP__