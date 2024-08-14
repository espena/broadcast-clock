#include "lea_m8t.hpp"
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::lea_m8t::m_component_name = "lea_m8t";

broadcast_clock::lea_m8t::
lea_m8t() {

  m_task_queue = xQueueCreate( 1, sizeof( lea_m8t_task_queue_item ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &lea_m8t::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     8,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer );
}

broadcast_clock::lea_m8t::
~lea_m8t() {

}

void broadcast_clock::lea_m8t::
task_loop( void *arg ) {
  lea_m8t_task_params *params = static_cast<lea_m8t_task_params *>( arg );
  lea_m8t *inst = params->instance;
  lea_m8t_task_queue_item item;
  memset( &item, 0x00, sizeof( lea_m8t_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 1 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void broadcast_clock::lea_m8t::
on_message( lea_m8t_task_message msg, void *arg ) {
  switch( msg ) {
    case lea_m8t_task_message::init:
      on_init();
      break;
    case lea_m8t_task_message::timepulse:
      on_timepulse();
      break;
  }
}

void broadcast_clock::lea_m8t::
on_init() {
  ESP_LOGI( m_component_name, "Initializing" );
  gpio_set_direction( LEA_M8T_TIMEPULSE, GPIO_MODE_INPUT );
  gpio_set_intr_type( LEA_M8T_TIMEPULSE, GPIO_INTR_POSEDGE );
  gpio_install_isr_service( 0 );
  gpio_isr_handler_add( LEA_M8T_TIMEPULSE, &on_timepulse, this );
}

void broadcast_clock::lea_m8t::
on_timepulse( void *arg ) {
  lea_m8t *inst = static_cast<lea_m8t *>( arg );
  lea_m8t_task_queue_item item = { lea_m8t_task_message::timepulse, nullptr };
  xQueueSend( inst->m_task_queue, &item, 10 );
}

void broadcast_clock::lea_m8t::
on_timepulse() {
  struct timeval tv;
  gettimeofday( &tv, NULL );
  tv.tv_sec += ( tv.tv_usec < 500 ? 0 : 1 );
  tv.tv_usec = 0;
  settimeofday( &tv, NULL );
  struct tm* timeinfo = localtime( &tv.tv_sec );
  char time_str[ 64 ];
  strftime( time_str, sizeof( time_str ), "%Y-%m-%d %H:%M:%S", timeinfo );
  ESP_LOGI( m_component_name, "System time: %s", time_str );
}

void broadcast_clock::lea_m8t::
init() {
  lea_m8t_task_queue_item item = { lea_m8t_task_message::init, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}
