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
            TaskHandle_t task_handle;
        } dial_task_params;

        dial_task_params m_task_params;

        enum class dial_task_message {
            init,
            ambient_light_level
        };

        typedef struct dial_task_queue_item_struct {
            dial_task_message message;
            void *arg;
        } dial_task_queue_item;

        static void task_loop( void *arg );

        void on_message( dial_task_message msg, void *arg );

        void on_init();

        void on_ambient_light_level( uint16_t lux );

        void update();

        void init_gpio();

        void component_loop();

    public:

        dial();
        ~dial();
        void init();
        void set_ambient_light_level( uint16_t lux );
    };

}

#endif // __DIAL_HPP__