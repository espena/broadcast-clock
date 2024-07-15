#include "dial.hpp"
#include "configuration.hpp"
#include "../utils/micro_delay.hpp"
#include "../gpio_mapping.hpp"
#include <memory.h>
#include <vector>
#include <time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <driver/ledc.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::dial::m_component_name = "dial";

broadcast_clock::dial::
dial() : m_config( nullptr ),
         m_refresh_timer( nullptr ),
         m_current_seconds( 0 ),
         m_brightness_bit( 0 ) {

    m_task_queue = xQueueCreate( 100, sizeof( dial_task_queue_item ) );

    m_task_params.instance = this;

    xTaskCreate( &dial::task_loop,
                 m_component_name,
                 m_component_stack_size,
                 &m_task_params,
                 24,
                 &m_task_params.task_handle );
}

broadcast_clock::dial::
~dial() {

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
    if( xQueueReceive( inst->m_task_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void broadcast_clock::dial::
on_message( dial_task_message msg, void *arg ) {
  switch( msg ) {
    case dial_task_message::init:
      on_init();
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
  init_refresh_timer();
}

void broadcast_clock::dial::
on_ambient_light_level( int threshold ) {
  switch( threshold ) {
    case 0:
      m_brightness_bit = 7;
      break;
    case 1:
      m_brightness_bit = 5;
      break;
    case 2:
      m_brightness_bit = 3;
      break;
    case 3:
      m_brightness_bit = 2;
      break;
    case 4:
      m_brightness_bit = 1;
      break;
  }
}

void broadcast_clock::dial::
refresh() {
  time_t now = time( NULL );
  struct tm timeinfo;
  localtime_r( &now, &timeinfo );
  ESP_ERROR_CHECK( ledc_set_duty( LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 1 ) );
  ESP_ERROR_CHECK( ledc_update_duty( LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0 ) );
  utils::micro_delay();
  gpio_set_level( DIAL_BLANK, 1 );
  utils::micro_delay();
  if( m_current_seconds != timeinfo.tm_sec ) {
      m_current_seconds = timeinfo.tm_sec;
      update();
  }
  utils::micro_delay();
  gpio_set_level( DIAL_BLANK, 0 );
  utils::micro_delay();
  ESP_ERROR_CHECK( ledc_set_duty( LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 1 ) );
  ESP_ERROR_CHECK( ledc_update_duty( LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0 ) );
}

void broadcast_clock::dial::
update() {

  const char style = m_config->get_str( "dial_style" )[ 0 ];

  gpio_set_level( DIAL_XLAT, 0 );
  gpio_set_level( DIAL_SCLK, 0 );
  gpio_set_level( DIAL_VPRG, 0 );

  gpio_set_level( DIAL_SOUT, 0 );
  for( int i = 0; i < 5; i++ ) {
    for( int j = 0; j < 16; j++ ) {
      const int led_id = 60 - ( ( ( i * 16 ) + j ) - 20 );
      for( int k = 0; k < 12; k++ ) {
        if( style == 'u' && // count up
            k == m_brightness_bit &&
            ( led_id <= m_current_seconds || led_id >= 60 ) ) {
          gpio_set_level( DIAL_SOUT, 1 );
        }
        else if( style == 'd' && // count down
                 ( k == m_brightness_bit ) &&
                 ( led_id >= m_current_seconds ) &&
                 !( led_id < 60 && m_current_seconds == 0 ) ) {
          gpio_set_level( DIAL_SOUT, 1 );
        }
        else {
          gpio_set_level( DIAL_SOUT, 0 );
        }
        utils::micro_delay();
        gpio_set_level( DIAL_SCLK, 1 );
        utils::micro_delay();
        gpio_set_level( DIAL_SCLK, 0 );
        utils::micro_delay();
      }
    }
  }
  gpio_set_level( DIAL_XLAT, 1 );
  utils::micro_delay();
  gpio_set_level( DIAL_XLAT, 0 );
  utils::micro_delay();
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

  ledc_timer_config_t timer_conf;
  memset( &timer_conf, 0x00, sizeof( ledc_timer_config_t ) );
  timer_conf.speed_mode = LEDC_LOW_SPEED_MODE;
  timer_conf.duty_resolution = LEDC_TIMER_2_BIT;
  timer_conf.timer_num = LEDC_TIMER_0;
  timer_conf.freq_hz = 2000000;
  timer_conf.clk_cfg = LEDC_AUTO_CLK;
  ESP_ERROR_CHECK( ledc_timer_config( &timer_conf ) );
  ledc_channel_config_t ledc_conf;

  memset( &ledc_conf, 0x00, sizeof( ledc_channel_config_t ) );
  ledc_conf.gpio_num = DIAL_GSCLK;
  ledc_conf.speed_mode = LEDC_LOW_SPEED_MODE;
  ledc_conf.channel = LEDC_CHANNEL_0;
  ledc_conf.intr_type = LEDC_INTR_DISABLE;
  ledc_conf.timer_sel = LEDC_TIMER_0;
  ledc_conf.duty = 0;
  ledc_conf.hpoint = 0;
  ESP_ERROR_CHECK( ledc_channel_config( &ledc_conf ) );
}

void broadcast_clock::dial::
on_refresh_timer( void* arg ) {
  dial *instance = static_cast<dial *>( arg );
  instance->refresh();
}

void broadcast_clock::dial::
init_refresh_timer() {
  esp_timer_create_args_t timer_args;
  memset( &timer_args, 0x00, sizeof( esp_timer_create_args_t ) );
  timer_args.callback = &dial::on_refresh_timer;
  timer_args.arg = this;
  timer_args.name = m_component_name;
  ESP_ERROR_CHECK( esp_timer_create( &timer_args, &m_refresh_timer ) );
  ESP_ERROR_CHECK( esp_timer_start_periodic( m_refresh_timer, 5000 ) );
}