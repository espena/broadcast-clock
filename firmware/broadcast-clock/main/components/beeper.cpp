#include "beeper.hpp"
#include "../gpio_mapping.hpp"
#include <memory.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::beeper::m_component_name = "beeper";
const esp_event_base_t broadcast_clock::beeper::m_event_base = "broadcast_clock_beeper_event";

broadcast_clock::
beeper::beeper() {

  m_task_queue = xQueueCreate( 100, sizeof( beeper_task_queue_item ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &beeper::task_loop,
                      m_component_name,
                      m_component_stack_size,
                      &m_task_params,
                      15,
                      m_task_params.stack_buffer,
                      &m_task_params.task_buffer );
}

broadcast_clock::
beeper::~beeper() {

}

void broadcast_clock::beeper::
task_loop( void *arg ) {
  beeper_task_params *params = static_cast<beeper_task_params *>( arg );
  beeper *inst = params->instance;
  beeper_task_queue_item item;
  memset( &item, 0x00, sizeof( beeper_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}


void broadcast_clock::beeper::
on_message( beeper_task_message msg, void *arg ) {
    switch( msg ) {
      case beeper_task_message::init:
        on_init();
        break;
      case beeper_task_message::alarm:
        on_alarm();
        break;
      case beeper_task_message::beep:

        break;
      case beeper_task_message::beeep:
        break;
      case beeper_task_message::beeeep:
        break;
    }
}

void broadcast_clock::beeper::
on_init() {

  ESP_LOGI( m_component_name,  "Initializing" );

  gpio_set_direction( PIEZO_TRANSDUCER, GPIO_MODE_OUTPUT );
  gpio_set_level( PIEZO_TRANSDUCER, 0 );

}

void broadcast_clock::beeper::
on_alarm() {
  for( int i = 0; i < 10; i++ ) {
    for( int j = 0; j < 3; j++ ) {
        gpio_set_level( PIEZO_TRANSDUCER, 1 );
        vTaskDelay( 100 / portTICK_PERIOD_MS );
        gpio_set_level( PIEZO_TRANSDUCER, 0 );
        vTaskDelay( 100 / portTICK_PERIOD_MS );
    }
    vTaskDelay( 500 / portTICK_PERIOD_MS );
  }
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                       m_event_base,
                       EVENT_BEEP_FINISH,
                       nullptr,
                       0,
                       10 );
  }
}

void broadcast_clock::beeper::
init() {
  beeper_task_queue_item item;
  memset( &item, 0x00, sizeof( beeper_task_queue_item ) );
  item.message = beeper_task_message::init;
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::beeper::
beep() {
  beeper_task_queue_item item;
  memset( &item, 0x00, sizeof( beeper_task_queue_item ) );
  item.message = beeper_task_message::beep;
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::beeper::
alarm() {
  beeper_task_queue_item item;
  memset( &item, 0x00, sizeof( beeper_task_queue_item ) );
  item.message = beeper_task_message::alarm;
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::beeper::
event_handler( void *handler_arg,
               esp_event_base_t event_base,
               int32_t event_id,
               void *event_params ) {

}

