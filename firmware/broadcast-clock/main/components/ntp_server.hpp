#ifndef __NTP_SERVER__
#define __NTP_SERVER__

#include <time.h>
#include <lwip/sockets.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace espena::broadcast_clock {

  class ntp_server {

  public:

    static const char *m_event_base;
    static const uint32_t NTP_SERVER_RESPONDED = 0x01u;

    static const uint16_t m_ntp_server_port = 123;

  private:

    static const char *m_component_name;
    static const size_t m_component_stack_size = 8192;

    static void event_handler( void *handler_arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_params );

    esp_event_loop_handle_t m_event_loop_handle;

    QueueHandle_t m_task_queue;

    typedef struct ntp_server_task_params_struct {
      ntp_server *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } ntp_server_task_params;

    ntp_server_task_params m_task_params;

    enum class ntp_server_task_message {
      init
    };

    typedef struct ntp_server_task_queue_item_struct {
      ntp_server_task_message message;
      void *arg;
    } ntp_server_task_queue_item_t;

    struct sockaddr_in m_server_addr; // NTP server address
    int m_sock; // Socket file descriptor

    static void task_loop( void *arg );
    void on_task_message( ntp_server_task_message msg, void *arg );

    void sock_read();

    void on_init();

  public:

    void set_event_loop_handle( esp_event_loop_handle_t h );

    ntp_server();
    ~ntp_server();

    void init();

  };

}

#endif // __NTP_SERVER__