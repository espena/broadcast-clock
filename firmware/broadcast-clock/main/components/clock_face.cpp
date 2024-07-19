#include "clock_face.hpp"
#include "configuration.hpp"
#include "wifi.hpp"
#include "captive_portal_http.hpp"
#include <string>
#include <memory.h>
#include <esp_timer.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::clock_face::m_component_name = "clock_face";

broadcast_clock::clock_face::
clock_face() : m_task_queue( nullptr ),
               m_event_loop_handle( nullptr ),
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
  if( m_event_loop_handle ) {
    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::ENTER_CONFIG_MODE,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::LEAVE_CONFIG_MODE,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_SAVE,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_CANCEL,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_STOPWATCH_START,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_STOPWATCH_STOP,
                                     wifi_event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_STOPWATCH_RESET,
                                     wifi_event_handler,
                                     this );
  }

  m_dotmatrix.init();
  m_i2c_bus = i2c_bus;
  m_ambient_sensor.init( m_i2c_bus );
  init_ambient_sensor_interval_timer();
}

void broadcast_clock::clock_face::
wifi_event_handler( void *handler_arg,
                    esp_event_base_t event_base,
                    int32_t event_id,
                    void *event_params )
{
  const std::string source = ( char * ) event_base;
  if( source == broadcast_clock::wifi::m_event_base ) {
    broadcast_clock::clock_face *instance = static_cast<broadcast_clock::clock_face *>( handler_arg );
    switch( event_id ) {
      case broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC:
        instance->on_ntp_sync();
        break;
      case broadcast_clock::wifi::ENTER_CONFIG_MODE:
        instance->on_enter_config_mode();
        break;
      case broadcast_clock::wifi::LEAVE_CONFIG_MODE:
        instance->on_leave_config_mode();
        instance->m_dotmatrix.display( nullptr );
        break;
    }
  }
  else if( source == broadcast_clock::captive_portal_http::m_event_base ) {
    broadcast_clock::clock_face *instance = static_cast<broadcast_clock::clock_face *>( handler_arg );
    switch( event_id ) {
      case broadcast_clock::captive_portal_http::EVENT_SAVE:
        instance->on_leave_config_mode();
        break;
      case broadcast_clock::captive_portal_http::EVENT_CANCEL:
        instance->on_leave_config_mode();
        break;
      case broadcast_clock::captive_portal_http::EVENT_STOPWATCH_START:
        instance->on_stopwatch_start();
        break;
      case broadcast_clock::captive_portal_http::EVENT_STOPWATCH_STOP:
        instance->on_stopwatch_stop();
        break;
      case broadcast_clock::captive_portal_http::EVENT_STOPWATCH_RESET:
        instance->on_stopwatch_reset();
        break;
    }
  }
}

void broadcast_clock::clock_face::
on_ntp_sync() {

  m_dial.init();
  m_dotmatrix.start();

  esp_event_handler_unregister_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC,
                                     wifi_event_handler );
}

void broadcast_clock::clock_face::
on_leave_config_mode() {
  m_dotmatrix.display( nullptr );
}

void broadcast_clock::clock_face::
on_enter_config_mode() {
  broadcast_clock::dotmatrix::display_message msg = { "  ", "Conf", "  " };
  m_dotmatrix.display( &msg );
}

void broadcast_clock::clock_face::
on_stopwatch_start() {
  ESP_LOGI( m_component_name, "Stopwatch started" );
  m_dotmatrix.stopwatch_start();
  m_dial.stopwatch_start();
}

void broadcast_clock::clock_face::
on_stopwatch_stop() {
  ESP_LOGI( m_component_name, "Stopwatch stopped" );
  m_dotmatrix.stopwatch_stop();
  m_dial.stopwatch_stop();
}

void broadcast_clock::clock_face::
on_stopwatch_reset() {
  ESP_LOGI( m_component_name, "Stopwatch reset" );
  m_dotmatrix.stopwatch_reset();
  m_dial.stopwatch_reset();
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
  broadcast_clock::configuration *c = broadcast_clock::configuration::get_instance();
  int threshold = c->get_int( "brightness" );
  if( threshold == 0 ) { // auto
    if( lux > ( 15000 * hysteresis ) ) {
      threshold = 4;
    }
    else if( lux > ( 8000 * hysteresis) ) {
      threshold = 3;
    }
    else if( lux > ( 1000 * hysteresis ) ) {
      threshold = 2;
    }
    else if ( lux > ( 100 * hysteresis ) ) {
      threshold = 1;
    }
    else {
      threshold = 0;
    }
    if( m_threshold == threshold  ) {
      hysteresis = 1.0;
    }
    else {
      hysteresis = m_threshold < threshold ? 0.9 : 1.1;
    }
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