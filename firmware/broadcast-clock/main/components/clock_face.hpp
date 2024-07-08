#ifndef __CLOCK_FACE_HPP__
#define __CLOCK_FACE_HPP__

#include "dial.hpp"
#include "dotmatrix.hpp"
#include "ambient_sensor.hpp"
#include <driver/i2c_master.h>
#include <esp_timer.h>

namespace espena::broadcast_clock {

  class clock_face {

    static const char *m_component_name;
    static const int m_component_stack_size = 512;

    QueueHandle_t m_task_queue;

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

    void on_message( clock_face_task_message msg, void *arg );
    void on_init( i2c_master_bus_handle_t i2c_bus );

    static void on_ambient_sensor_interval( void* arg );
    void check_ambient_light();

    i2c_master_bus_handle_t m_i2c_bus;
    esp_timer_handle_t m_ambient_sensor_interval_timer;

    dial m_dial;
    dotmatrix m_dotmatrix;
    ambient_sensor m_ambient_sensor;

  public:

    clock_face();
    ~clock_face();
    void init( i2c_master_bus_handle_t i2c_bus );
    void init_ambient_sensor_interval_timer();

  };

}

#endif // __CLOCK_FACE_HPP__