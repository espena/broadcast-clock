#ifndef __DIAL_HPP__
#define __DIAL_HPP__

#include "configuration.hpp"
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <vector>
#include <esp_timer.h>

namespace espena::broadcast_clock {

    class dial {

        static const char *m_component_name;
        static const size_t m_component_stack_size = 8192;
        
        struct timespec m_stopwatch_begin;
        struct timespec m_stopwatch_end;

        struct timespec m_countdown_period;

        configuration *m_config;
        
        esp_timer_handle_t m_refresh_timer;

        QueueHandle_t m_task_queue;

        int m_current_seconds;
        int m_brightness_bit;

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

        static void on_refresh_timer( void *arg );

        void on_message( dial_task_message msg, void *arg );
        void on_init();
        void on_ambient_light_level( int threshold );

        void refresh();
        void update();

        void init_gpio();
        void init_refresh_timer();

    public:

        dial();
        ~dial();

        void init();
        void set_ambient_light_level( uint16_t lux );

        void stopwatch_start();
        void stopwatch_stop();
        void stopwatch_reset();

        void countdown_start( struct timespec *period );

    };

}

#endif // __DIAL_HPP__