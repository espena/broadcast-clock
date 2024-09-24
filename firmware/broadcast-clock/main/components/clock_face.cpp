#include "clock_face.hpp"
#include "configuration.hpp"
#include "lea_m8t.hpp"
#include "wifi.hpp"
#include "captive_portal_http.hpp"
#include <string>
#include <memory.h>
#include <esp_timer.h>
#include <esp_sntp.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::clock_face::m_component_name = "clock_face";
const esp_event_base_t broadcast_clock::clock_face::m_event_base = "broadcast_clock_face_event";

broadcast_clock::clock_face::
clock_face() : m_is_initialized( false ),
               m_test_mode( false ),
               m_error_flags( 0x00u ),
               m_task_queue( nullptr ),
               m_event_loop_handle( nullptr ),
               m_interval_timer( nullptr ),
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
      on_init();
      break;
    case clock_face_task_message::test:
      on_test();
      break;
  }
}

void broadcast_clock::clock_face::
on_test() {
  m_test_mode = true;
  m_threshold = 2;
  m_dial.test();
  m_dotmatrix.test();
}

void broadcast_clock::clock_face::
on_init() {
  ESP_LOGI( m_component_name, "Initializing" );

  if( m_event_loop_handle ) {
    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::lea_m8t::m_event_base,
                                     broadcast_clock::lea_m8t::UBX_NAV_TIMEUTC,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC_FAILED,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::ENTER_CONFIG_MODE,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::wifi::m_event_base,
                                     broadcast_clock::wifi::LEAVE_CONFIG_MODE,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_SAVE,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_CANCEL,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_STOPWATCH_START,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_STOPWATCH_STOP,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_STOPWATCH_RESET,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_COUNTDOWN_START,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::captive_portal_http::m_event_base,
                                     broadcast_clock::captive_portal_http::EVENT_COUNTDOWN_RESET,
                                     event_handler,
                                     this );

    esp_event_handler_register_with( m_event_loop_handle,
                                     broadcast_clock::dotmatrix::m_event_base,
                                     broadcast_clock::dotmatrix::EVENT_COUNTDOWN_FINISH,
                                     event_handler,
                                     this );
  }

  m_dotmatrix.set_event_loop_handle( m_event_loop_handle );
  m_dotmatrix.init();

  //m_ambient_sensor.init( m_i2c_bus );

  init_interval_timer();
}

void broadcast_clock::clock_face::
event_handler( void *handler_arg,
                    esp_event_base_t event_base,
                    int32_t event_id,
                    void *event_params )
{
  broadcast_clock::clock_face *instance = static_cast<broadcast_clock::clock_face *>( handler_arg );
  const std::string source = ( char * ) event_base;
  if( source == broadcast_clock::wifi::m_event_base ) {
    switch( event_id ) {
      case broadcast_clock::wifi::WIFI_EVENT_NTP_SYNC:
        instance->on_time_sync( sync_type::ntp );
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
      case broadcast_clock::captive_portal_http::EVENT_COUNTDOWN_START:
        instance->on_countdown_start( static_cast<struct timespec *>( event_params ) );
        break;
      case broadcast_clock::captive_portal_http::EVENT_COUNTDOWN_RESET:
        instance->on_countdown_reset();
        break;
    }
  }
  else if( source == broadcast_clock::dotmatrix::m_event_base ) {
    switch( event_id ) {
      case broadcast_clock::dotmatrix::EVENT_COUNTDOWN_FINISH:
        instance->on_countdown_finish();
        break;
    }
  }
  else if( source == broadcast_clock::lea_m8t::m_event_base ) {
    switch( event_id ) {
      case broadcast_clock::lea_m8t::UBX_NAV_TIMEUTC:
        instance->on_time_sync( sync_type::gnss );
        break;
    }
  }
}

void broadcast_clock::clock_face::
on_time_sync( sync_type t ) {
  if( !m_is_initialized && m_ready ) {
    m_dial.init();
    m_dotmatrix.start();
    m_is_initialized = true;
  }
  ESP_LOGI( m_component_name, "Time synchronized from %s", t == sync_type::ntp ? "NTP" : "GNSS" );
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
on_countdown_start( struct timespec *period ) {
  ESP_LOGI( m_component_name, "Countdown start: %llu", period->tv_sec );
  m_dotmatrix.countdown_start( period );
  m_dial.stopwatch_start();
}

void broadcast_clock::clock_face::
on_countdown_reset() {
  ESP_LOGI( m_component_name, "Countdown reset" );
  m_dotmatrix.countdown_reset();
  m_dial.stopwatch_reset();
}

void broadcast_clock::clock_face::
on_countdown_finish() {
  ESP_LOGI( m_component_name, "Countdown finish" );
  m_dotmatrix.countdown_reset();
  m_dial.countdown_reset();
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                      m_event_base,
                      EVENT_COUNTDOWN_FINISH,
                      "",
                      0,
                      portMAX_DELAY );
  }
}

void broadcast_clock::clock_face::
on_interval_timer( void* arg ) {
  clock_face *instance = static_cast<clock_face *>( arg );
  instance->check_ambient_light();
}

void broadcast_clock::clock_face::
update_indicators() {
  // deprecated
}

void broadcast_clock::clock_face::
init() {
  clock_face_task_queue_item item = { clock_face_task_message::init, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::clock_face::
test() {
  clock_face_task_queue_item item = { clock_face_task_message::test, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::clock_face::
init_interval_timer() {
  esp_timer_create_args_t timer_args;
  memset( &timer_args, 0x00, sizeof( esp_timer_create_args_t ) );
  timer_args.callback = &clock_face::on_interval_timer;
  timer_args.arg = this;
  timer_args.name = m_component_name;
  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &m_interval_timer ) );
  ESP_ERROR_CHECK( esp_timer_start_periodic( m_interval_timer, 1000000 ) );
}

void broadcast_clock::clock_face::
lux2threshold( uint16_t lux ) {
  static float hysteresis = 1.0;
  broadcast_clock::configuration *c = broadcast_clock::configuration::get_instance();
  int threshold = c->get_int( "brightness" );
  if( m_test_mode ) {
    threshold = 2;
  }
  else if( threshold == 0 ) { // auto
    if( lux > ( 15000 * hysteresis ) ) {
      threshold = 4;
    }
    else if( lux > ( 5000 * hysteresis) ) {
      threshold = 3;
    }
    else if( lux > ( 1000 * hysteresis ) ) {
      threshold = 2;
    }
    else if ( lux > ( 50 * hysteresis ) ) {
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
  /*
  uint16_t lux = m_ambient_sensor.read();
  lux2threshold( lux );
  m_dial.set_ambient_light_level( m_threshold );
  m_dotmatrix.set_ambient_light_level( m_threshold );
  */
  m_dotmatrix.set_ambient_light_level( 4 );
}

void broadcast_clock::clock_face::
display_ip( esp_netif_ip_info_t *ip_info ) {
  char octet[ 4 ][ 5 ];
  snprintf( octet[ 0 ], 5, "%03d ", ip4_addr1( &ip_info->ip ) );
  snprintf( octet[ 1 ], 5, "%03d ", ip4_addr2( &ip_info->ip ) );
  snprintf( octet[ 2 ], 5, "%03d ", ip4_addr3( &ip_info->ip ) );
  snprintf( octet[ 3 ], 5, "%03d ", ip4_addr4( &ip_info->ip ) );
  for( int i = 0; i < 4; i++ ) {
    broadcast_clock::dotmatrix::display_message msg = { "  ", octet[ i ], "IP" };
    m_dotmatrix.display( &msg );
    vTaskDelay( 2000 / portTICK_PERIOD_MS );
  }
  m_dotmatrix.display( nullptr );
  m_ready = true;
} 