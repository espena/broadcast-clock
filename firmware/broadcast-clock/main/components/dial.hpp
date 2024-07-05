#ifndef __DIAL_HPP__
#define __DIAL_HPP__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace espena::broadcast_clock {

    class dial {

        static const char *m_component_name;
        static const size_t m_component_stack_size = 4096;
        
        QueueHandle_t m_task_queue;

        int m_current_seconds;

        typedef struct dial_task_params_struct {
            dial *instance;
            StackType_t *stack_buffer;
            StaticTask_t task_buffer;
        } dial_task_params;

        dial_task_params m_task_params;

        enum class dial_task_message {
            init,
            enable,
            disable
        };

        typedef struct dial_task_queue_item_struct {
            dial_task_message message;
            void *arg;
        } dial_task_queue_item;

        static void task_loop( void *arg );

        void on_message( dial_task_message msg, void *arg );

        void on_init();

    public:

        dial();
        ~dial();
        void init();
    };

}

#endif // __DIAL_HPP__