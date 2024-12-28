#ifndef __CLOCK_FACE_HPP__
#define __CLOCK_FACE_HPP__

#include "dial.hpp"
#include "dotmatrix.hpp"
#include "ambient_sensor.hpp"
#include "i_indicators.hpp"
#include <driver/i2c_master.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_timer.h>

namespace espena::broadcast_clock {

  class clock_face : public i_indicators {

  public:

    static const esp_event_base_t m_event_base;
    static const uint32_t EVENT_COUNTDOWN_FINISH = 0x01u;

  private:

    typedef enum class sync_type {
      ntp,
      gnss
    } sync_type;

    static const char *m_component_name;
    static const int m_component_stack_size = 4096;

    bool m_is_initialized = false;
    bool m_test_mode = false;
    bool m_ready = false;

    uint8_t m_error_flags;
    static const uint8_t ERROR_FLAG_NTP_SYNC_FAILED = 0x01u;

    QueueHandle_t m_task_queue;

    esp_event_loop_handle_t m_event_loop_handle;

    typedef struct clock_face_task_params_struct {
        clock_face *instance;
        StackType_t *stack_buffer;
        StaticTask_t task_buffer;
    } clock_face_task_params;

    clock_face_task_params m_task_params;

    enum class clock_face_task_message {
        init,
        test
    };

    typedef struct clock_face_task_queue_item_struct {
        clock_face_task_message message;
        void *arg;
    } clock_face_task_queue_item;

    static void task_loop( void *arg );

    static void event_handler( void *handler_arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_params );

    void on_message( clock_face_task_message msg, void *arg );
    void on_time_sync( sync_type t );
    void on_init();
    void on_test();

    void on_enter_config_mode();
    void on_leave_config_mode();

    void on_stopwatch_start();
    void on_stopwatch_stop();
    void on_stopwatch_reset();

    void on_countdown_start( struct timespec *period );
    void on_countdown_finish();
    void on_countdown_reset();
    
    static void on_interval_timer( void* arg );

    void check_ambient_light();
    void update_indicators();

    esp_timer_handle_t m_interval_timer;

    dial m_dial;
    dotmatrix m_dotmatrix;
    ambient_sensor m_ambient_sensor;

    int m_threshold;
    void lux2threshold( uint16_t lux );

  public:

    virtual void set_indicators( bool blue, bool green, bool yellow, bool red, bool time_valid ) override {
      m_dial.set_indicators( blue, green, yellow, red, time_valid );
      m_dotmatrix.set_time_valid( time_valid );
    };
    
    virtual void set_blue_indicator( bool blue ) override {
      m_dial.set_blue_indicator( blue );
    };
    
    virtual void set_green_indicator( bool green ) override {
      m_dial.set_green_indicator( green );
    };
    
    virtual void set_yellow_indicator( bool yellow ) override {
      m_dial.set_yellow_indicator( yellow );
    };
    
    virtual void set_red_indicator( bool red ) override {
      m_dial.set_red_indicator( red );
    };
    
    virtual void set_time_valid( bool time_valid ) override {
      m_dial.set_time_valid( true );
      m_dotmatrix.set_time_valid( true );
    };

    clock_face();
    ~clock_face();
    
    void init();
    void test();
    void init_interval_timer();
    void set_event_loop_handle( esp_event_loop_handle_t h ) { m_event_loop_handle = h; };
    void display_ip( esp_netif_ip_info_t *ip_info );

    i_indicators *get_indicators() { return &(*this); };

  };

}

#endif // __CLOCK_FACE_HPP__