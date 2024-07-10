#ifndef __CLOCK_FACE_HPP__
#define __CLOCK_FACE_HPP__

#include "dial.hpp"
#include "dotmatrix.hpp"
#include "ambient_sensor.hpp"
#include <driver/i2c_master.h>
#include <esp_event.h>
#include <esp_timer.h>

namespace espena::broadcast_clock {

  class clock_face {

    static const char *m_component_name;
    static const int m_component_stack_size = 2048;

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

    static void wifi_event_handler( void *handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void *event_params );

    void on_message( clock_face_task_message msg, void *arg );
    void on_ntp_sync();
    void on_init( i2c_master_bus_handle_t i2c_bus );

    static void on_ambient_sensor_interval( void* arg );
    void check_ambient_light();

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

  };

}

#endif // __CLOCK_FACE_HPP__