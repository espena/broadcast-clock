#ifndef __CLOCK_FACE_HPP__
#define __CLOCK_FACE_HPP__

#include "dial.hpp"
#include "dotmatrix.hpp"
#include "ambient_sensor.hpp"
#include <driver/i2c_master.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_timer.h>

namespace espena::broadcast_clock {

  class clock_face {

  public:

    static const esp_event_base_t m_event_base;
    static const uint32_t EVENT_COUNTDOWN_FINISH = 0x01u;

  private:

    static const char *m_component_name;
    static const int m_component_stack_size = 4096;

    bool m_is_initialized;
    struct timespec m_last_ntp_sync_time;

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
        init
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
    void on_ntp_sync();
    void on_ntp_failed();
    void on_init( i2c_master_bus_handle_t i2c_bus );

    void on_enter_config_mode();
    void on_leave_config_mode();

    void on_stopwatch_start();
    void on_stopwatch_stop();
    void on_stopwatch_reset();

    void on_countdown_start( struct timespec *period );
    void on_countdown_finish();
    void on_countdown_reset();

    static void on_ambient_sensor_interval( void* arg );

    void check_ambient_light();
    void update_indicators();

    i2c_master_bus_handle_t m_i2c_bus;
    esp_timer_handle_t m_ambient_sensor_interval_timer;

    dial m_dial;
    dotmatrix m_dotmatrix;
    ambient_sensor m_ambient_sensor;

    int m_threshold;
    void lux2threshold( uint16_t lux );

  public:

    clock_face();
    ~clock_face();
    void init( i2c_master_bus_handle_t i2c_bus );
    void init_ambient_sensor_interval_timer();
    void set_event_loop_handle( esp_event_loop_handle_t h ) { m_event_loop_handle = h; };
    void display_ip( esp_netif_ip_info_t *ip_info );

  };

}

#endif // __CLOCK_FACE_HPP__