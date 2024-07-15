#ifndef __DOTMATRIX_HPP__
#define __DOTMATRIX_HPP__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <driver/spi_master.h>

namespace espena::broadcast_clock {

    class dotmatrix {

    public:

        typedef struct display_message_struct {
            const char *top;
            const char *middle;
            const char *bottom;
        } display_message;

    private:

        static const char *m_component_name;
        static const size_t m_component_stack_size = 4096;

        bool m_test_mode;
        bool m_message_mode;
        bool m_init_mode;
        
        uint8_t m_brightness;

        uint8_t m_current_hour;
        uint8_t m_current_minute;
        uint8_t m_current_second;

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
            start,
            ambient_light_level,
            display,
            test
        };

        typedef struct dotmatrix_task_queue_item_struct {
            dotmatrix_task_message message;
            void *arg;
        } dotmatrix_task_queue_item;

        static void task_loop( void *arg );

        void on_message( dotmatrix_task_message msg, void *arg );

        void on_init();
        void on_start();
        void on_ambient_light_level( int threshold );
        void on_display( display_message *msg );
        void on_test();


        void init_spi();
        void init_display();

        void update();
        void transmit( uint8_t u1_command, 
                       uint8_t u1_data,
                       uint8_t u2_command,
                       uint8_t u2_data );

        void set_text( display_message *msg );

    public:

        dotmatrix();
        ~dotmatrix();

        void init();
        void start();
        void test();

        void set_ambient_light_level( uint16_t lux );

        void display( const display_message *msg );

    };

}

#endif // __DOTMATRIX_HPP__