#include "dial.hpp"
#include "configuration.hpp"
#include "../utils/micro_delay.hpp"
#include "../gpio_mapping.hpp"
#include <memory.h>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <driver/ledc.h>
#include <esp_task_wdt.h>
#include <esp_log.h>
#include <esp_heap_caps.h>

using namespace espena;

const char *broadcast_clock::dial::m_component_name = "dial";

broadcast_clock::dial::
dial() : m_initialized( false ),
         m_test_mode( false ),
         m_config( nullptr ),
         m_refresh_timer( nullptr ),
         m_current_seconds( 0 ),
         m_brightness_bit( 0 ),
         m_blue_indicator( false ),
         m_green_indicator( false ),
         m_yellow_indicator( false ),
         m_red_indicator( false ) {

    memset( &m_stopwatch_begin, 0x00, sizeof( timespec ) );
    memset( &m_stopwatch_end, 0x00, sizeof( timespec ) );
    memset( &m_countdown_period, 0x00, sizeof( timespec ) );

    m_task_queue = xQueueCreate( 100, sizeof( dial_task_queue_item ) );

    m_task_params.instance = this;

    xTaskCreate( &dial::task_loop,
                 m_component_name,
                 m_component_stack_size,
                 &m_task_params,
                 configMAX_PRIORITIES - 2,
                 &m_task_params.task_handle );
}

broadcast_clock::dial::
~dial() {

}

void broadcast_clock::dial::
test() {
  dial_task_queue_item item = { dial_task_message::test, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dial::
init() {
  m_config = configuration::get_instance();
  dial_task_queue_item item = { dial_task_message::init, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dial::
set_ambient_light_level( uint16_t lux ) {
  static uint16_t current_lux = 0;
  current_lux = lux;
  dial_task_queue_item item = { dial_task_message::ambient_light_level, &current_lux };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dial::
task_loop( void *arg ) {
  ESP_LOGI( m_component_name, "Entering task loop" );
  dial_task_params *params = static_cast<dial_task_params *>( arg );
  dial *inst = params->instance;
  dial_task_queue_item item;
  memset( &item, 0x00, sizeof( dial_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 0 ) ) {
      inst->on_message( item.message, item.arg );
    }
    if( inst->m_initialized ) {
      inst->refresh();
    }
    vTaskDelay( 1 );
  }
}

void broadcast_clock::dial::
on_message( dial_task_message msg, void *arg ) {
  switch( msg ) {
    case dial_task_message::init:
      on_init();
      break;
    case dial_task_message::test:
      on_test();
      break;
    case dial_task_message::update:
      update();
      break;
    case dial_task_message::ambient_light_level:
      on_ambient_light_level( *static_cast<uint16_t *>( arg ) );
      break;
  }
}

void broadcast_clock::dial::
on_init() {
  ESP_LOGI( m_component_name, "Initializing" );
  init_gpio();
  m_initialized = true;
}

void broadcast_clock::dial::
on_test() {
  ESP_LOGI( m_component_name, "Test dial" );
  m_test_mode = true;
}

void broadcast_clock::dial::
on_ambient_light_level( int threshold ) {
  switch( threshold ) {
    /*
    case 0:
      m_brightness_bit = 6;
      break;
    case 1:
      m_brightness_bit = 5;
      break;
    case 2:
      m_brightness_bit = 4;
      break;
    case 3:
      m_brightness_bit = 2;
      break;
    case 4:
      m_brightness_bit = 1;
      break;
    */

    case 0:
      m_brightness_bit = 5;
      break;
    case 1:
      m_brightness_bit = 4;
      break;
    case 2:
      m_brightness_bit = 3;
      break;
    case 3:
      m_brightness_bit = 1;
      break;
    case 4:
      m_brightness_bit = 0;
      break;
  }
}

void broadcast_clock::dial::
refresh() {
  time_t now = time( NULL );
  struct tm timeinfo;
  localtime_r( &now, &timeinfo );
  if( m_stopwatch_begin.tv_nsec > 0 ||
      m_stopwatch_begin.tv_sec > 0 ) {
      //update();
  }
  else if( m_current_seconds != timeinfo.tm_sec ) {
      m_current_seconds = timeinfo.tm_sec;
      //update();
  }
  update();

  gpio_set_level( DIAL_BLANK, 1 );
  gpio_set_level( DIAL_BLANK, 0 );

  portDISABLE_INTERRUPTS();
  for( int i = 0; i < 4096; i++ ) {
    gpio_set_level( DIAL_GSCLK, 1 );
    utils::micro_delay();
    gpio_set_level( DIAL_GSCLK, 0 );
    utils::micro_delay();
  }
  portENABLE_INTERRUPTS();
}

void broadcast_clock::dial::
update() {

  const char style = m_config->get_str( "dial_style" )[ 0 ];
  const bool indicators_enabled = m_config->get_bool( "indicators" );

  gpio_set_level( DIAL_XLAT, 0 );
  gpio_set_level( DIAL_SCLK, 0 );
  gpio_set_level( DIAL_VPRG, 0 );

  bool stopwatch_running = m_stopwatch_begin.tv_nsec > 0 || m_stopwatch_begin.tv_sec > 0;
  bool stopwatch_stopped = !stopwatch_running && ( m_stopwatch_end.tv_nsec > 0 || m_stopwatch_end.tv_sec > 0 );
  static int16_t stopwatch_led_runner = 0;
  if( stopwatch_running ) {
      clock_gettime( CLOCK_MONOTONIC, &m_stopwatch_end );
      uint32_t stopwatch_begin_ms = ( m_stopwatch_begin.tv_sec * 1000 ) + ( m_stopwatch_begin.tv_nsec / 1000000 );
      uint32_t stopwatch_end_ms = ( m_stopwatch_end.tv_sec * 1000 ) + ( m_stopwatch_end.tv_nsec / 1000000 );
      uint32_t ms_delta = ( stopwatch_end_ms - stopwatch_begin_ms ) % 1000;
      stopwatch_led_runner = static_cast<int16_t>( static_cast<float>( 0.06 * ms_delta ) ) + 1;
  }
  gpio_set_level( DIAL_SOUT, 0 );
  for( int i = 0; i < 5; i++ ) {
    for( int j = 0; j < 16; j++ ) {
      const int led_id = 60 - ( ( ( i * 16 ) + j ) - 20 );
      for( int k = 0; k < 12; k++ ) {
        if( m_test_mode ) {
          if( k == m_brightness_bit ) {
            gpio_set_level( DIAL_SOUT, 1 );
          }
          else {
            gpio_set_level( DIAL_SOUT, 0 );
          }
        }
        else if( stopwatch_running || stopwatch_stopped ) {
          if( k == m_brightness_bit &&
            ( led_id == stopwatch_led_runner || led_id >= 77 ) ) {
            gpio_set_level( DIAL_SOUT, 1 );
          }
          else {
            gpio_set_level( DIAL_SOUT, 0 );
          }
        }
        else if( style == 'u' && // count up
                 k == m_brightness_bit &&
                 ( led_id <= m_current_seconds || led_id == 60 || led_id > 64 ) ) {
          gpio_set_level( DIAL_SOUT, 1 );
        }
        else if( style == 'd' && // count down
                 ( k == m_brightness_bit ) &&
                 ( led_id >= m_current_seconds && ( led_id < 61 || led_id > 64 ) ) &&
                 !( led_id < 60 && m_current_seconds == 0 ) ) {
          gpio_set_level( DIAL_SOUT, 1 );
        }
        else if( led_id >= 61 && led_id <= 64 ) { // Indicators
          gpio_set_level( DIAL_SOUT, 0 );
          if( indicators_enabled ) {
            switch( led_id ) {
              case 61:
                if( k == 4 ) {
                  gpio_set_level( DIAL_SOUT, m_blue_indicator ? 1 : 0 );
                }
                break;
              case 62:
                if( k == 2 ) {
                  gpio_set_level( DIAL_SOUT, m_green_indicator ? 1 : 0 );
                }
                break;
              case 63:
                if( k == 2 ) {
                  gpio_set_level( DIAL_SOUT, m_yellow_indicator ? 1 : 0 );
                }
                break;
              case 64:
                if( k == 2 ) {
                  gpio_set_level( DIAL_SOUT, m_red_indicator ? 1 : 0 );
                }
                break;
            }
          }
        }
        else {
          gpio_set_level( DIAL_SOUT, 0 );
        }
        gpio_set_level( DIAL_SCLK, 1 );
        gpio_set_level( DIAL_SCLK, 0 );
      }
    }
  }
  gpio_set_level( DIAL_XLAT, 1 );
  gpio_set_level( DIAL_XLAT, 0 );
}

void broadcast_clock::dial::
init_gpio() {
  gpio_set_direction( DIAL_GSCLK, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_SOUT, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_SIN, GPIO_MODE_INPUT );
  gpio_set_direction( DIAL_XLAT, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_XERR, GPIO_MODE_INPUT );
  gpio_set_direction( DIAL_VPRG, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_DCPRG, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_SCLK, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_BLANK, GPIO_MODE_OUTPUT );
}

void broadcast_clock::dial::
countdown_start( struct timespec *period ) {
  memcpy( &m_countdown_period, period, sizeof( timespec ) );
  clock_gettime( CLOCK_MONOTONIC, &m_stopwatch_begin );
}

void broadcast_clock::dial::
countdown_reset() {
  memset( &m_countdown_period, 0x00, sizeof( timespec ) );
  memset( &m_stopwatch_begin, 0x00, sizeof( timespec ) );
  memset( &m_stopwatch_end, 0x00, sizeof( timespec ) );
}

void broadcast_clock::dial::
stopwatch_start() {
  clock_gettime( CLOCK_MONOTONIC, &m_stopwatch_begin );
}

void broadcast_clock::dial::
stopwatch_stop() {
  memset( &m_stopwatch_begin, 0x00, sizeof( timespec ) );
}

void broadcast_clock::dial::
stopwatch_reset() {
  memset( &m_stopwatch_begin, 0x00, sizeof( timespec ) );
  memset( &m_stopwatch_end, 0x00, sizeof( timespec ) );
}

void broadcast_clock::dial::
blink_green_indicator() {
  m_green_indicator = !m_green_indicator;
  dial_task_queue_item item = { dial_task_message::update, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
  vTaskDelay( 500 / portTICK_PERIOD_MS );
  m_green_indicator = !m_green_indicator;
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dial::
set_indicators( bool blue, bool green, bool yellow, bool red ) {
  m_blue_indicator = blue;
  m_green_indicator = green;
  m_yellow_indicator = yellow;
  m_red_indicator = red;
}
