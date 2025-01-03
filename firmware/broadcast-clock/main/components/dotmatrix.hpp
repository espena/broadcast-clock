#ifndef __DOTMATRIX_HPP__
#define __DOTMATRIX_HPP__

#include "configuration.hpp"
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <driver/spi_master.h>
#include <esp_event.h>

namespace espena::broadcast_clock {

  class dotmatrix {

  public:

    static const esp_event_base_t m_event_base;
    static const uint32_t EVENT_COUNTDOWN_FINISH = 0x01u;

    typedef struct display_message_struct {
      const char *top;
      const char *middle;
      const char *bottom;
    } display_message;

  private:

    static const char *m_component_name;
    static const size_t m_component_stack_size = 4096;

    configuration *m_config;

    bool m_test_mode;
    bool m_message_mode;
    bool m_init_mode;
    bool m_time_valid;

    uint8_t m_brightness_u1;
    uint8_t m_brightness_u2;

    uint8_t m_current_hour;
    uint8_t m_current_minute;
    uint8_t m_current_second;

    uint32_t m_stopwatch_hour;
    uint32_t m_stopwatch_minute;
    uint32_t m_stopwatch_second;
    uint32_t m_stopwatch_fraction;

    struct timespec m_stopwatch_begin;
    struct timespec m_stopwatch_end;

    struct timespec m_countdown_period;

    QueueHandle_t m_task_queue;
    esp_event_loop_handle_t m_event_loop_handle;

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
      stopwatch_start,
      stopwatch_stop,
      stopwatch_reset,
      countdown_start,
      countdown_reset,
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

    void on_stopwatch_start();
    void on_stopwatch_stop();
    void on_stopwatch_reset();

    void on_countdown_start( struct timespec *period );
    void on_countdown_finish();
    void on_countdown_reset();

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

    void set_event_loop_handle( esp_event_loop_handle_t h ) { m_event_loop_handle = h; };
    void set_time_valid( bool time_valid ) { m_time_valid = time_valid; };

    void init();
    void start();
    void test();

    void set_ambient_light_level( uint16_t lux );

    void display( const display_message *msg );

    void stopwatch_start();
    void stopwatch_stop();
    void stopwatch_reset();

    void countdown_start( struct timespec *period );
    void countdown_reset();

  };

}

#endif // __DOTMATRIX_HPP__