#include "dotmatrix.hpp"
#include "../gpio_mapping.hpp"
#include <memory.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/spi_master.h>
#include <driver/gpio.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::dotmatrix::m_component_name = "dotmatrix";

broadcast_clock::dotmatrix::
dotmatrix() : m_config( nullptr ),
              m_message_mode( false ),
              m_brightness( 0x00 ),
              m_current_hour( 0 ),
              m_current_minute( 0 ),
              m_current_second( 0 ),
              m_stopwatch_hour( 0 ),
              m_stopwatch_minute( 0 ),
              m_stopwatch_second( 0 ),
              m_stopwatch_fraction( 0 ),
              m_task_queue( nullptr ),
              m_spi( nullptr ) {
    
  m_task_queue = xQueueCreate( 1, sizeof( dotmatrix_task_queue_item ) );

  memset( &m_stopwatch_begin, 0x00, sizeof( timespec ) );
  memset( &m_stopwatch_end, 0x00, sizeof( timespec ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                    MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &dotmatrix::task_loop,
                      m_component_name,
                      m_component_stack_size,
                      &m_task_params,
                      8,
                      m_task_params.stack_buffer,
                      &m_task_params.task_buffer );
}

broadcast_clock::dotmatrix::
~dotmatrix() {

}

void broadcast_clock::dotmatrix::
init() {
  dotmatrix_task_queue_item item = { dotmatrix_task_message::init, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dotmatrix::
start() {
  dotmatrix_task_queue_item item = { dotmatrix_task_message::start, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dotmatrix::
set_ambient_light_level( uint16_t lux ) {
  static uint16_t current_lux = 0;
  current_lux = lux;
  dotmatrix_task_queue_item item = { dotmatrix_task_message::ambient_light_level, &current_lux };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dotmatrix::
display( const display_message *msg ) {
  static display_message current_msg;
  if( msg == nullptr ) {
    dotmatrix_task_queue_item item = { dotmatrix_task_message::display, nullptr };
    xQueueSend( m_task_queue, &item, 10 );
  }
  else {
    memcpy( &current_msg, msg, sizeof( display_message ) );
    dotmatrix_task_queue_item item = { dotmatrix_task_message::display, &current_msg };
    xQueueSend( m_task_queue, &item, 10 );
  }
}

void broadcast_clock::dotmatrix::
stopwatch_start() {
  dotmatrix_task_queue_item item = { dotmatrix_task_message::stopwatch_start, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dotmatrix::
stopwatch_stop() {
  dotmatrix_task_queue_item item = { dotmatrix_task_message::stopwatch_stop, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dotmatrix::
stopwatch_reset() {
  dotmatrix_task_queue_item item = { dotmatrix_task_message::stopwatch_reset, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dotmatrix::
test() {
  dotmatrix_task_queue_item item = { dotmatrix_task_message::test, nullptr };
  xQueueSend( m_task_queue, &item, 10 );
}

void broadcast_clock::dotmatrix::
task_loop( void *arg ) {
  dotmatrix_task_params *params = static_cast<dotmatrix_task_params *>( arg );
  dotmatrix *inst = params->instance;
  dotmatrix_task_queue_item item;
  memset( &item, 0x00, sizeof( dotmatrix_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 1 ) ) {
      inst->on_message( item.message, item.arg );
    }
    time_t now = time( NULL );
    struct tm timeinfo;
    localtime_r( &now, &timeinfo );
    
    if( inst->m_stopwatch_begin.tv_nsec != 0 || inst->m_stopwatch_end.tv_nsec != 0 ) {
      if( inst->m_stopwatch_begin.tv_nsec != 0 ) {

        clock_gettime( CLOCK_MONOTONIC, &inst->m_stopwatch_end );
        const uint32_t mstart = inst->m_stopwatch_begin.tv_sec * 1000 + inst->m_stopwatch_begin.tv_nsec / 1000000;
        const uint32_t mend = inst->m_stopwatch_end.tv_sec * 1000 + inst->m_stopwatch_end.tv_nsec / 1000000;
        const uint32_t mdiff = mend - mstart;
        inst->m_stopwatch_hour =     ( mdiff / 3600000 ) % 60;
        inst->m_stopwatch_minute =   ( mdiff /   60000 ) % 60;
        inst->m_stopwatch_second =   ( mdiff /    1000 ) % 60;
        inst->m_stopwatch_fraction = ( mdiff /      10 ) % 100;
        inst->update();
      }
    }
    else if( inst->m_current_hour != timeinfo.tm_hour || 
        inst->m_current_minute != timeinfo.tm_min ||
        inst->m_current_second != timeinfo.tm_sec ) {

        inst->m_current_hour = timeinfo.tm_hour;
        inst->m_current_minute = timeinfo.tm_min;
        inst->m_current_second = timeinfo.tm_sec;
        inst->update();
    }
  }
}

void broadcast_clock::dotmatrix::
on_message( dotmatrix_task_message msg, void *arg ) {
  switch( msg ) {
    case dotmatrix_task_message::init:
      on_init();
      break;
    case dotmatrix_task_message::start:
      on_start();
      break;
    case dotmatrix_task_message::display:
      on_display( static_cast<display_message *>( arg ) );
      break;
    case dotmatrix_task_message::stopwatch_start:
      on_stopwatch_start();
      break;
    case dotmatrix_task_message::stopwatch_stop:
      on_stopwatch_stop();
      break;
    case dotmatrix_task_message::stopwatch_reset:
      on_stopwatch_reset();
      break;
    case dotmatrix_task_message::ambient_light_level:
      on_ambient_light_level( *static_cast<uint16_t *>( arg ) );
      break;
    case dotmatrix_task_message::test:
      on_test();
      break;
  }
}

void broadcast_clock::dotmatrix::
transmit( uint8_t u1_command,
          uint8_t u1_data,
          uint8_t u2_command,
          uint8_t u2_data ) {
  if( m_spi ) {
    spi_transaction_t t;
    memset( &t, 0x00, sizeof( spi_transaction_t ) );
    uint16_t u1 = u1_data << 8 | u1_command;
    uint16_t u2 = u2_data << 8 | u2_command;
    uint32_t payload = u1 << 16 | u2;
    t.length = 32;
    t.tx_buffer = &payload;
    ESP_ERROR_CHECK( spi_device_transmit( m_spi, &t ) );
  }
}

void broadcast_clock::dotmatrix::
update() {
  if( !m_message_mode && !m_init_mode ) {
    if( m_stopwatch_begin.tv_nsec != 0 || m_stopwatch_end.tv_nsec != 0 ) {
      transmit( 0x60u, 0x30u | ( ( m_stopwatch_minute / 10 ) & 0x0f ), 0x60u, 0x30u | ( ( m_stopwatch_fraction / 10 ) & 0x0f ) );
      transmit( 0x61u, 0x30u | ( ( m_stopwatch_minute % 10 ) & 0x0f ), 0x61u, 0x30u | ( ( m_stopwatch_fraction % 10 ) & 0x0f ) );
      transmit( 0x62u, 0x30u | ( ( m_stopwatch_second / 10 ) & 0x0f ), 0x62u, 0x30u | ( ( m_stopwatch_hour / 10 ) & 0x0f ) );
      transmit( 0x63u, 0x30u | ( ( m_stopwatch_second % 10 ) & 0x0f ), 0x63u, 0x30u | ( ( m_stopwatch_hour % 10 ) & 0x0f ) );
    }
    else {
      std::string t = m_config ? m_config->get_str( "time_format" ) : "24h";
      bool f12h = ( t == "12h" );
      const int8_t h = ( f12h ? ( m_current_hour % 12 ? m_current_hour % 12 : 12 ) : m_current_hour );
      const char *meridiem = f12h ? ( m_current_hour >= 12 ? "PM" : "AM" ) : "  ";
      transmit( 0x60u, 0x30u | ( ( h / 10 ) & 0x0f ), 0x60u, 0x30u | ( ( m_current_second / 10 ) & 0x0f ) );
      transmit( 0x61u, 0x30u | ( ( h % 10 ) & 0x0f ), 0x61u, 0x30u | ( ( m_current_second % 10 ) & 0x0f ) );
      transmit( 0x62u, 0x30u | ( ( m_current_minute / 10 ) & 0x0f ), 0x62u, meridiem[ 0 ] );
      transmit( 0x63u, 0x30u | ( ( m_current_minute % 10 ) & 0x0f ), 0x63u, meridiem[ 1 ] );
    }
  }
  transmit( 0x01u, m_brightness, 0x01u, m_brightness );
  transmit( 0x02u, m_brightness, 0x02u, m_brightness );
}

void broadcast_clock::dotmatrix::
on_init() {
  ESP_LOGI( m_component_name, "Initializing" );
  m_config = broadcast_clock::configuration::get_instance();
  init_spi();
  init_display();
  m_init_mode = true;
  display_message msg = { "  ", "Init", "  " };
  set_text( &msg );
}

void broadcast_clock::dotmatrix::
on_start() {
  m_init_mode = false;
}

void broadcast_clock::dotmatrix::
on_ambient_light_level( int threshold ) {
  uint8_t brightness = 0x00;
  switch( threshold ) {
    case 0:
      // fallthru
    case 1:
      brightness = 0x00u;
      break;
    case 2:
      brightness = 0x22u;
      break;
    case 3:
      brightness = 0x55u;
      break;
    case 4:
      brightness = 0x88u;
      break;
  }
  m_brightness = brightness;
}

void broadcast_clock::dotmatrix::
on_display( display_message *msg ) {
  m_message_mode = ( msg == nullptr ) ? false : true;
  if( m_message_mode ) {
    set_text( msg );
  }
}

void broadcast_clock::dotmatrix::
on_stopwatch_start() {
  clock_gettime( CLOCK_MONOTONIC, &m_stopwatch_begin );
}

void broadcast_clock::dotmatrix::
on_stopwatch_stop() {
  memset( &m_stopwatch_begin, 0x00, sizeof( timespec ) );
}

void broadcast_clock::dotmatrix::
on_stopwatch_reset() {
  memset( &m_stopwatch_begin, 0x00, sizeof( timespec ) );
  memset( &m_stopwatch_end, 0x00, sizeof( timespec ) );
}

void broadcast_clock::dotmatrix::
set_text( display_message *msg ) {

  if( msg &&
      strlen( msg->top ) == 2 &&
      strlen( msg->middle ) == 4 &&
      strlen( msg->bottom ) == 2 ) {
    transmit( 0x60u, msg->middle[ 0 ], 0x60u, msg->top[ 0 ] );
    transmit( 0x61u, msg->middle[ 1 ], 0x61u, msg->top[ 1 ] );
    transmit( 0x62u, msg->middle[ 2 ], 0x62u, msg->bottom[ 0 ] );
    transmit( 0x63u, msg->middle[ 3 ], 0x63u, msg->bottom[ 1 ] );
  }
}

void broadcast_clock::dotmatrix::
on_test() {
  // Test mode
  m_test_mode = true;
  transmit( 0x07u, 0x01u, 0x07u, 0x01u );
}

void broadcast_clock::dotmatrix::
init_spi() {
  spi_bus_config_t buscfg;
  memset( &buscfg, 0x00, sizeof( spi_bus_config_t ) );
  buscfg.miso_io_num = DISP_SPI_MISO;
  buscfg.mosi_io_num = DISP_SPI_MOSI;
  buscfg.sclk_io_num = DISP_SPI_CLK;
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;
  buscfg.max_transfer_sz = 32;

  spi_device_interface_config_t devcfg;
  memset( &devcfg, 0x00, sizeof( spi_device_interface_config_t ) );
  devcfg.clock_speed_hz = 100000;
  devcfg.mode = 0;
  devcfg.spics_io_num = DISP_SPI_CS;
  devcfg.queue_size = 7;

  ESP_ERROR_CHECK( spi_bus_initialize( SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO ) );
  ESP_ERROR_CHECK( spi_bus_add_device( SPI2_HOST, &devcfg, &m_spi ) );
}

void broadcast_clock::dotmatrix::
init_display() {
  // Normal mode
  transmit( 0x04u, 0x01u, 0x04u, 0x01u );
  update();
}
