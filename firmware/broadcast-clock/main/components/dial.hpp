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
    
    static const int m_refresh_interval = 5000;
    static const int m_pwm_frequency_hz = 2500000;

    struct timespec m_stopwatch_begin;
    struct timespec m_stopwatch_end;

    struct timespec m_countdown_period;

    configuration *m_config;
    
    esp_timer_handle_t m_refresh_timer;

    QueueHandle_t m_task_queue;

    int m_current_seconds;
    int m_brightness_bit;

    bool m_blue_indicator;
    bool m_green_indicator;
    bool m_yellow_indicator;
    bool m_red_indicator;

    typedef struct dial_task_params_struct {
      dial *instance;
      TaskHandle_t task_handle;
    } dial_task_params;

    dial_task_params m_task_params;

    enum class dial_task_message {
      init,
      update,
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

    void set_indicators( bool blue, bool green, bool yellow, bool red );

  public:

    dial();
    ~dial();

    void init();
    void set_ambient_light_level( uint16_t lux );

    void stopwatch_start();
    void stopwatch_stop();
    void stopwatch_reset();

    void countdown_start( struct timespec *period );
    void countdown_reset();

    void set_blue_indicator( bool b ) { set_indicators( b, m_green_indicator, m_yellow_indicator, m_red_indicator ); };
    void set_green_indicator( bool b ) { set_indicators( m_blue_indicator, b, m_yellow_indicator, m_red_indicator ); };
    void set_yellow_indicator( bool b ) { set_indicators( m_blue_indicator, m_green_indicator, b, m_red_indicator ); };
    void set_red_indicator( bool b ) { set_indicators( m_blue_indicator, m_green_indicator, m_yellow_indicator, b ); };

    void blink_green_indicator();

  };

}

#endif // __DIAL_HPP__