#include "clock_face.hpp"
#include <memory.h>
#include <esp_timer.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::clock_face::m_component_name = "clock_face";

broadcast_clock::clock_face::
clock_face() : m_task_queue( nullptr ),
               m_i2c_bus( nullptr ),
               m_ambient_sensor_interval_timer( nullptr ),
               m_threshold( 0 ) {

  m_task_queue = xQueueCreate( 100, sizeof( clock_face_task_queue_item ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                    MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &clock_face::task_loop,
                      m_component_name,
                      m_component_stack_size,
                      &m_task_params,
                      15,
                      m_task_params.stack_buffer,
                      &m_task_params.task_buffer );
}

broadcast_clock::clock_face::
~clock_face() {

}

void broadcast_clock::clock_face::
task_loop( void *arg ) {
  clock_face_task_params *params = static_cast<clock_face_task_params *>( arg );
  clock_face *inst = params->instance;
  clock_face_task_queue_item item;
  memset( &item, 0x00, sizeof( clock_face_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void broadcast_clock::clock_face::
on_message( clock_face_task_message msg, void *arg ) {
  switch( msg ) {
    case clock_face_task_message::init:
      on_init( *static_cast<i2c_master_bus_handle_t *>( arg ) );
      break;
  }
}

void broadcast_clock::clock_face::
on_init( i2c_master_bus_handle_t i2c_bus ) {
  ESP_LOGI( m_component_name, "Initializing" );
  m_dial.init();
  m_dotmatrix.init();
  m_i2c_bus = i2c_bus;
  m_ambient_sensor.init( m_i2c_bus );
  init_ambient_sensor_interval_timer();
}

void broadcast_clock::clock_face::
on_ambient_sensor_interval( void* arg ) {
  clock_face *instance = static_cast<clock_face *>( arg );
  instance->check_ambient_light();
}

void broadcast_clock::clock_face::
init( i2c_master_bus_handle_t i2c_bus ) {
  static i2c_master_bus_handle_t current_i2c_bus = i2c_bus;
  clock_face_task_queue_item item = { clock_face_task_message::init, &current_i2c_bus };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::clock_face::
init_ambient_sensor_interval_timer() {
  esp_timer_create_args_t timer_args;
  memset( &timer_args, 0x00, sizeof( esp_timer_create_args_t ) );
  timer_args.callback = &clock_face::on_ambient_sensor_interval;
  timer_args.arg = this;
  timer_args.name = m_component_name;
  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &m_ambient_sensor_interval_timer ) );
  ESP_ERROR_CHECK( esp_timer_start_periodic( m_ambient_sensor_interval_timer, 1000000 ) );
}

void broadcast_clock::clock_face::
lux2threshold( uint16_t lux ) {
  static float hysteresis = 1.0;
  int threshold = 1;
  if( lux > ( 60000 * hysteresis ) ) {
    threshold = 4;
  }
  else if( lux > ( 20000 * hysteresis) ) {
    threshold = 3;
  }
  else if( lux > ( 1000 * hysteresis ) ) {
    threshold = 2;
  }
  else {
    threshold = 1;
  }
  if( m_threshold == threshold  ) {
    hysteresis = 1.0;
  }
  else {
    hysteresis = m_threshold < threshold ? 0.9 : 1.1;
  }
  m_threshold = threshold;
}

void broadcast_clock::clock_face::
check_ambient_light() {
  uint16_t lux = m_ambient_sensor.read();
  lux2threshold( lux );
  m_dial.set_ambient_light_level( m_threshold );
  m_dotmatrix.set_ambient_light_level( m_threshold );
}