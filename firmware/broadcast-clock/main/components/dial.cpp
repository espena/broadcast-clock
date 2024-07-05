#include "dial.hpp"
#include <memory.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

using namespace espena::broadcast_clock;

const char *dial::m_component_name = "dial";

dial::dial() : m_current_seconds( 0 ) {

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

dial::~dial() {

}

void dial::init() {
    dial_task_queue_item item = { dial_task_message::init, nullptr };
    xQueueSend( m_task_queue, &item, 10 );
}

void dial::task_loop( void *arg ) {
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

void dial::on_message( dial_task_message msg, void *arg ) {
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

void dial::on_init() {
  
}