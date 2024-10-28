#ifndef __http_server_HPP__
#define __http_server_HPP__

#include <string>
#include <set>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_wifi.h>
#include <esp_http_server.h>
#include <esp_event.h>

#include "wifi.hpp"
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

  class http_server {

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

    static const uint32_t EVENT_REBOOT_CPU          = 0x0eu;
    static const uint32_t EVENT_REBOOT_GNSS         = 0x0fu;

    static const uint32_t EVENT_SSID_REQUEST        = 0x10u;

  private:

    static const char *m_component_name;
    static const size_t m_component_stack_size = 16384;

    QueueHandle_t m_message_queue;
    httpd_handle_t m_server;

    std::set<std::string> m_ssid_list;
    std::string m_json_ssid_list;
    bool volatile m_ssids_received = false;

    void on_ssid_scan_result( wifi::ssid_scan_result_t * );

    esp_event_loop_handle_t m_event_loop_handle;
    i_gnss_state *m_gnss_state;

    httpd_config_t m_cfg = HTTPD_DEFAULT_CONFIG();

    std::string m_json_gnss_status;

    bool m_gnss_installed = false;

    void update_json_gnss_status();
    void update_json_ssid_list();

    static void task_loop( void *arg );

    static void event_handler( void *handler_arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_data );

    static esp_err_t request_handler( httpd_req_t *req );

    esp_err_t on_request( httpd_req_t *req );
    void save_handler( httpd_req_t *req );
    void survey_in_handler( httpd_req_t *req );
    void timers_handler( httpd_req_t *req );

    void stopwatch_handler( httpd_req_t *req );
    void countdown_handler( httpd_req_t *req );
    void reboot_handler( httpd_req_t *req );

    typedef struct http_server_task_params_struct {
        http_server *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } http_server_task_params;

    http_server_task_params m_task_params;

    enum class http_server_task_message {
        init,
        ssid_scan_result,
        start,
        stop
    };

    typedef struct http_server_task_queue_item_struct {
        http_server_task_message message;
        void *arg;
    } http_server_task_queue_item;

    void on_message( http_server_task_message msg, void *arg );

    void enqueue_simple_message( http_server_task_message msg );

    std::string create_html_response();

    void init_sync();
    void start_sync();
    void stop_sync();

    public:

      void set_event_loop_handle( esp_event_loop_handle_t h );
      void set_gnss_state( i_gnss_state *gnss_state ) { m_gnss_state = gnss_state; };

      http_server();

      void init();
      void start();
      void stop();

  }; // class http_server

}; // namespace espena::broadcast_clock

#endif // __http_server_HPP__