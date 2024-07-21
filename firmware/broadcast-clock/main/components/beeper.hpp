#ifndef __BEEPER_HPP__
#define __BEEPER_HPP__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <esp_event.h>

namespace espena::broadcast_clock {

  class beeper {

  public:

    static const esp_event_base_t m_event_base;
    static const uint32_t EVENT_BEEP_FINISH = 0x01u;

  private:

    static const char *m_component_name;
    static const int m_component_stack_size = 2048;

    QueueHandle_t m_task_queue;

    esp_event_loop_handle_t m_event_loop_handle;

    typedef struct beeper_task_params_struct {
        beeper *instance;
        StackType_t *stack_buffer;
        StaticTask_t task_buffer;
    } beeper_task_params;

    beeper_task_params m_task_params;

    enum class beeper_task_message {
        init,
        alarm,
        beep,
        beeep,
        beeeep
    };

    typedef struct beeper_task_queue_item_struct {
        beeper_task_message message;
        void *arg;
    } beeper_task_queue_item;

    static void task_loop( void *arg );

    static void event_handler( void *handler_arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_params );

    void on_message( beeper_task_message msg, void *arg );

    void on_init();
    void on_alarm();

  public:

    beeper();
    ~beeper();
    void set_event_loop_handle( esp_event_loop_handle_t h ) { m_event_loop_handle = h; };
    void init();
    void beep();
    void alarm();

  };

}

#endif // __BEEPER_HPP__