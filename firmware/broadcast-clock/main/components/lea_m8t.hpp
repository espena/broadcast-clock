#ifndef __LEA_M8T__
#define __LEA_M8T__

#include "configuration.hpp"
#include "../gpio_mapping.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace espena::broadcast_clock {

  class lea_m8t {

    static const char *m_component_name;
    static const size_t m_component_stack_size = 4096;
    
    configuration *m_config;
    
    QueueHandle_t m_task_queue;

    typedef struct lea_m8t_task_params_struct {
      lea_m8t *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } lea_m8t_task_params;

    lea_m8t_task_params m_task_params;

    enum class lea_m8t_task_message {
      init,
      timepulse
    };

    typedef struct lea_m8t_task_queue_item_struct {
      lea_m8t_task_message message;
      void *arg;
    } lea_m8t_task_queue_item;

    static void task_loop( void *arg );

    static void on_timepulse( void *arg );
    void on_timepulse();

    void on_message( lea_m8t_task_message msg, void *arg );
    void on_init();

  public:

    lea_m8t();
    ~lea_m8t();

    void init();

  };

}

#endif // __LEA_M8T__