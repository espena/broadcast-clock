#include "dial.hpp"
#include "../utils/micro_delay.hpp"
#include "../gpio_mapping.hpp"
#include <memory.h>
#include <time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::dial::m_component_name = "dial";

broadcast_clock::dial::
dial() : m_task_queue( nullptr ),
         m_current_seconds( 0 ) {

    m_task_queue = xQueueCreate( 10, sizeof( dial_task_queue_item ) );

    m_task_params.instance = this;
    m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                     MALLOC_CAP_SPIRAM );
    xTaskCreateStatic( &dial::task_loop,
                       m_component_name,
                       m_component_stack_size,
                       &m_task_params,
                       4 | portPRIVILEGE_BIT,
                       m_task_params.stack_buffer,
                       &m_task_params.task_buffer );
}

broadcast_clock::dial::
~dial() {

}

void broadcast_clock::dial::
init() {
    dial_task_queue_item item = { dial_task_message::init, nullptr };
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
  dial_task_queue_item *item = nullptr;
  switch( msg ) {
    case dial_task_message::init:
      on_init();
      break;
    case dial_task_message::enable:

      break;
    case dial_task_message::disable:

      break;
  }
}

void broadcast_clock::dial::
update() {
  gpio_set_level( DIAL_SOUT, 0 );
  gpio_set_level( DIAL_GSCLK, 0 );
  gpio_set_level( DIAL_XLAT, 0 );
  gpio_set_level( DIAL_SCLK, 0 );

  gpio_set_level( DIAL_VPRG, 1 );
  utils::micro_delay();
  gpio_set_level( DIAL_VPRG, 0 );

  for( int i = 0; i < 5; i++ ) {
      for( int j = 0; j < 16; j++ ) {
          const int led_id = 60 - ( ( ( i * 16 ) + j ) - 20 );
          for( int k = 0; k < 12; k++ ) {
              utils::micro_delay();
              if( k == 2 && led_id > m_current_seconds ) {
                  gpio_set_level( DIAL_SOUT, 1 );
              }
              else {
                  gpio_set_level( DIAL_SOUT, 0 );
              }
              utils::micro_delay();
              gpio_set_level( DIAL_SCLK, 1 );
              utils::micro_delay();
              gpio_set_level( DIAL_SCLK, 0 );
          }
      }
      utils::micro_delay();
      gpio_set_level( DIAL_XLAT, 1 );
      utils::micro_delay();
      gpio_set_level( DIAL_XLAT, 0 );
      utils::micro_delay();
  }
  gpio_set_level( DIAL_VPRG, 1 );
}

void broadcast_clock::dial::
init_gpio() {
  gpio_set_direction( DIAL_GSCLK, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_SOUT, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_VPRG, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_SCLK, GPIO_MODE_OUTPUT );
  gpio_set_direction( DIAL_BLANK, GPIO_MODE_OUTPUT );
}

void broadcast_clock::dial::
on_init() {
  ESP_LOGI( m_component_name, "Initializing clock dial" );
  init_gpio();
  update();
  component_loop();
}

void broadcast_clock::dial::
component_loop() {
  while( true ) {
    vTaskDelay( 1 );
    gpio_set_level( DIAL_BLANK, 1 );
    time_t now = time( NULL );
    struct tm timeinfo;
    localtime_r( &now, &timeinfo );
    if( m_current_seconds != timeinfo.tm_sec ) {
        m_current_seconds = timeinfo.tm_sec;
        update();
    }
    gpio_set_level( DIAL_BLANK, 0 );
    for( int l = 0; l < 4096; l++) {
        gpio_set_level( DIAL_GSCLK, 1 );
        utils::micro_delay();
        gpio_set_level( DIAL_GSCLK, 0 );
        utils::micro_delay();
    }
  }
}