#ifndef __DOTMATRIX_HPP__
#define __DOTMATRIX_HPP__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <driver/spi_master.h>

namespace espena::broadcast_clock {

    class dotmatrix {

        static const char *m_component_name;
        static const size_t m_component_stack_size = 4096;

        uint8_t m_current_hour;
        uint8_t m_current_minute;

        QueueHandle_t m_task_queue;

        spi_device_handle_t m_spi;

        typedef struct dotmatrix_task_params_struct {
            dotmatrix *instance;
            StackType_t *stack_buffer;
            StaticTask_t task_buffer;
        } dotmatrix_task_params;

        dotmatrix_task_params m_task_params;

        enum class dotmatrix_task_message {
            init,
            enable,
            disable
        };

        typedef struct dotmatrix_task_queue_item_struct {
            dotmatrix_task_message message;
            void *arg;
        } dotmatrix_task_queue_item;

        static void task_loop( void *arg );

        void on_message( dotmatrix_task_message msg, void *arg );

        void update();
        void transmit( uint8_t command, uint8_t data );

        void on_init();
        void init_spi();
        void init_display();

    public:

        dotmatrix();
        ~dotmatrix();
        void init();

    };

}

#endif // __DOTMATRIX_HPP__