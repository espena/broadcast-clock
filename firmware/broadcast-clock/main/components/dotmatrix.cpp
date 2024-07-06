#include "dotmatrix.hpp"
#include "../gpio_mapping.hpp"
#include <memory.h>
#include <time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/spi_master.h>
#include <driver/gpio.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::dotmatrix::m_component_name = "dotmatrix";

broadcast_clock::dotmatrix::
dotmatrix() : m_current_hour( 0 ),
              m_current_minute( 0 ),
              m_task_queue( nullptr ),
              m_spi( nullptr ) {
    
  m_task_queue = xQueueCreate( 1, sizeof( dotmatrix_task_queue_item ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                    MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &dotmatrix::task_loop,
                      m_component_name,
                      m_component_stack_size,
                      &m_task_params,
                      4 | portPRIVILEGE_BIT,
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
task_loop( void *arg ) {
  dotmatrix_task_params *params = static_cast<dotmatrix_task_params *>( arg );
  dotmatrix *inst = params->instance;
  dotmatrix_task_queue_item item;
  memset( &item, 0x00, sizeof( dotmatrix_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
    time_t now = time( NULL );
    struct tm timeinfo;
    localtime_r( &now, &timeinfo );
    if( inst->m_current_hour != timeinfo.tm_hour || inst->m_current_minute != timeinfo.tm_min ) {
        inst->m_current_hour = timeinfo.tm_hour;
        inst->m_current_minute = timeinfo.tm_min;
        inst->update();
    }
  }
}

void broadcast_clock::dotmatrix::
on_message( dotmatrix_task_message msg, void *arg ) {
  dotmatrix_task_queue_item *item = nullptr;
  switch( msg ) {
    case dotmatrix_task_message::init:
      on_init();
      break;
    case dotmatrix_task_message::enable:

      break;
    case dotmatrix_task_message::disable:

      break;
  }
}

void broadcast_clock::dotmatrix::
transmit( uint8_t command, uint8_t data ) {
  spi_transaction_t t;
  memset( &t, 0x00, sizeof( spi_transaction_t ) );
  uint16_t cmd = data << 8 | command;
  t.length = 16;
  t.tx_buffer = &cmd;  
  ESP_ERROR_CHECK( spi_device_transmit( m_spi, &t ) );
}

void broadcast_clock::dotmatrix::
update() {
  transmit( 0x60u, 0x30u | ( ( m_current_hour / 10 ) & 0x0f ) );
  transmit( 0x61u, 0x30u | ( ( m_current_hour % 10 ) & 0x0f ) );
  transmit( 0x62u, 0x30u | ( ( m_current_minute / 10 ) & 0x0f ) );
  transmit( 0x63u, 0x30u | ( ( m_current_minute % 10 ) & 0x0f ) );
}

void broadcast_clock::dotmatrix::
on_init() {
  ESP_LOGI( m_component_name, "Initializing dot matrix display" );
  init_spi();
  init_display();
  update();
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
  buscfg.max_transfer_sz = 16;

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
  transmit( 0x04u, 0x01u | ( ( m_current_hour / 10 ) & 0x0f ) );
}
