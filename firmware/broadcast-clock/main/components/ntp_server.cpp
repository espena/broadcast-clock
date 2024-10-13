#include "ntp_server.hpp"
#include "configuration.hpp"
#include "../utils/hexdump.hpp"
#include "wifi.hpp"
#include <sys/socket.h>
#include <netdb.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <lwip/err.h>
#include <memory.h>
#include <time.h>
#include <sys/time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portmacro.h>
#include <freertos/queue.h>
#include <esp_log.h>
#include <esp_heap_caps.h>

using namespace espena;

const char *broadcast_clock::ntp_server::m_component_name = "ntp_server";
const char *broadcast_clock::ntp_server::m_event_base = "broadcast_clock_ntp_server_event";

broadcast_clock::ntp_server::
ntp_server() : m_event_loop_handle( nullptr ) {

  memset( &m_server_addr, 0x00, sizeof( struct sockaddr_in ) );
  m_sock = -1;

  m_task_queue = xQueueCreate( 1024, sizeof( ntp_server_task_queue_item_t ) );

  m_task_params.instance = this;
  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &ntp_server::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     configMAX_PRIORITIES - 4,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer );
}

broadcast_clock::ntp_server::
~ntp_server() {

}

void broadcast_clock::ntp_server::
set_event_loop_handle( esp_event_loop_handle_t h ) {
  m_event_loop_handle = h;
  if( m_event_loop_handle ) {
    esp_event_handler_register_with( m_event_loop_handle,
                                     configuration::m_event_base,
                                     configuration::CONFIGURATION_UPDATED,
                                     event_handler,
                                     this );
  }
}

void broadcast_clock::ntp_server::
event_handler( void *handler_arg,
               esp_event_base_t event_base,
               int32_t event_id,
               void *event_params ) {

  std::string source = ( char * ) event_base;
  if( source == configuration::m_event_base ) {
    ntp_server *instance = static_cast<ntp_server *>( handler_arg );
    if( instance ) {
      switch( event_id ) {
        case configuration::CONFIGURATION_UPDATED:

          break;
      }
    }
  }
}

void broadcast_clock::ntp_server::
task_loop( void *arg ) {
  ntp_server_task_params *params = static_cast<ntp_server_task_params *>( arg );
  ntp_server *inst = params->instance;
  ntp_server_task_queue_item_t item;
  memset( &item, 0x00, sizeof( ntp_server_task_queue_item_t ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_task_queue, &item, 10 ) ) {
      inst->on_task_message( item.message, item.arg );
    }
    if( inst->m_sock > -1 ) {
      inst->sock_read();
    }
  }
}

void broadcast_clock::ntp_server::
timespec_to_ntp(const struct timespec *ts, uint8_t *ntp_time) {

    const uint64_t NTP_EPOCH_OFFSET = 2208988800ULL; // NTP epoch offset in seconds

    // Convert seconds to NTP seconds
    uint32_t ntp_seconds = static_cast<uint64_t>( ts->tv_sec ) + NTP_EPOCH_OFFSET;

    // Convert nanoseconds to NTP fractional seconds
    uint32_t ntp_fraction = (uint32_t)((ts->tv_nsec * (1LL << 32)) / 1000000000LL);

    // Combine seconds and fractional seconds into a 64-bit NTP timestamp
    uint64_t ntp_timestamp = ( (uint64_t) ntp_seconds << 32 ) | ntp_fraction;

    // Copy the 64-bit NTP timestamp to the output buffer
    for( int i = 8; i > 0; i-- ) {
      ntp_time[ i - 1 ] = reinterpret_cast<uint8_t *>( &ntp_timestamp )[ 8 - i ];
    }
}

void broadcast_clock::ntp_server::
get_ntp_time( uint8_t *ntp_time ) {
  struct timespec now_spec;
  clock_gettime( CLOCK_REALTIME, &now_spec );
  uint8_t ntp_time64[ 8 ];
  timespec_to_ntp( &now_spec, ntp_time64 );
  memcpy( ntp_time, ntp_time64, 8 );
}

void broadcast_clock::ntp_server::
sock_read() {
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof( client_addr );
  uint8_t recv_buf[ 48 ];
  int len = recvfrom( m_sock,
                      recv_buf,
                      sizeof( recv_buf ),
                      0,
                      ( struct sockaddr * ) &client_addr,
                      &client_addr_len );
  if( len > 0 ) {

    uint8_t ntp_receive_time[ 8 ];
    uint8_t ntp_reference_time[ 8 ];
    uint8_t ntp_transmit_time[ 8 ];

    get_ntp_time( ntp_receive_time );

    ESP_LOGI( m_component_name,
              "Received %d bytes from %s:%d",
              len,
              inet_ntoa( client_addr.sin_addr ),
              ntohs( client_addr.sin_port ) );

    ::espena::utils::hexdump( recv_buf, len );

    // Prepare response, initialize with fixed header values
    uint8_t tx_buf[ 48 ] = { 0x1c, 0x01, 0x04, 0xf7, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x50,  'G',  'P',  'S', 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    // Set reference timestamp from request
    get_ntp_time( ntp_reference_time );
    memcpy( &tx_buf[ 16 ], ntp_reference_time, 8 );

    // Set original timestamp from request
    memcpy( &tx_buf[ 24 ], &recv_buf[ 40 ], 8 );

    // Set receive timestamp
    memcpy( &tx_buf[ 32 ], ntp_receive_time, 8 );

    // Set transmit timestamp
    get_ntp_time( ntp_transmit_time );
    memcpy( &tx_buf[ 40 ], ntp_transmit_time, 8 );

    // Send response
    sendto( m_sock,
            tx_buf,
            sizeof( tx_buf ),
            0,
            ( struct sockaddr * ) &client_addr,
            client_addr_len );

    // Send notification
    if( m_event_loop_handle ) {
      esp_event_post_to( m_event_loop_handle,
                          m_event_base,
                          RESPONDED,
                          nullptr,
                          0,
                          10 );
    }

  }
}

void broadcast_clock::ntp_server::
on_task_message( ntp_server_task_message msg, void *arg ) {
  switch( msg ) {
    case ntp_server_task_message::init:
      on_init();
      break;
  }
}

void broadcast_clock::ntp_server::
on_init() {
  configuration *cnf = configuration::get_instance();
  if( cnf ) {
    if( cnf->get_str( "ntp_server_enable" ) == "on" ) {
      ESP_LOGI( m_component_name, "Initializing" );
      m_server_addr.sin_family = AF_INET;
      m_server_addr.sin_addr.s_addr = INADDR_ANY;
      m_server_addr.sin_port = htons( m_ntp_server_port );
      m_sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
      if( m_sock < 0 ) {
        ESP_LOGE( m_component_name, "Failed to create socket" );
        return;
      }
      const int err = bind( m_sock, ( struct sockaddr * ) &m_server_addr, sizeof( m_server_addr ) );
      if( err < 0 ) {
        ESP_LOGE( m_component_name, "Failed to bind socket" );
        close( m_sock );
        m_sock = -1;
        return;
      }
      if( m_event_loop_handle ) {
        esp_event_post_to( m_event_loop_handle,
                           m_event_base,
                           READY,
                           nullptr,
                           0,
                           10 );
      }
    }
  }
}

void broadcast_clock::ntp_server::
init() {
  ntp_server_task_queue_item_t item = { ntp_server_task_message::init, nullptr };
  xQueueSend( m_task_queue, &item, 0 );
}
