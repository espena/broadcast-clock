#include <memory.h>
#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/event_groups.h>
#include "lwip/sockets.h"
#include "lwip/ip4_addr.h"
#include "lwip/dns.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "captive_portal_dns.hpp"

using namespace espena;

const char *broadcast_clock::captive_portal_dns::m_component_name = "captive_portal_dns";

broadcast_clock::captive_portal_dns::
captive_portal_dns() : m_message_queue( nullptr ),
                                           m_sock( -1 )
{
  m_message_queue = xQueueCreate( 50, sizeof( captive_portal_dns_task_queue_item ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  xTaskCreateStatic( &broadcast_clock::captive_portal_dns::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     2,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer ); 
}

void broadcast_clock::captive_portal_dns::
task_loop( void *arg ) {
  captive_portal_dns_task_params *params = static_cast<captive_portal_dns_task_params *>( arg );
  captive_portal_dns *inst = params->instance;
  captive_portal_dns_task_queue_item item;
  memset( &item, 0x00, sizeof( captive_portal_dns_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

void broadcast_clock::captive_portal_dns::
server_loop() {
  struct sockaddr_in from;
  const size_t fromlen = sizeof( struct sockaddr_in );
  uint8_t udp_msg[ m_dns_buflen ];
  uint32_t res = 0;
  if( !m_sock ) {
    ESP_LOGE( m_component_name, "Socket not initialized" );
  }
  ESP_LOGI( m_component_name, "Entering DNS server loop" );
  while( 1 ) {
    memset( &from, 0x00, sizeof( from ) );
    res = recvfrom( m_sock,
                    ( uint8_t * ) udp_msg,
                    m_dns_buflen,
                    0,
                    ( struct sockaddr * ) &from,
                    ( socklen_t * ) &fromlen );
    if( res > 0 ) {
      ESP_LOGI( m_component_name, "Received packet from m_sock" );
      on_receive( &from, udp_msg, res );
    }
  }
}

void broadcast_clock::captive_portal_dns::
on_message( captive_portal_dns_task_message msg, void *arg ) {
  captive_portal_dns_task_queue_item *item = nullptr;
  switch( msg ) {
    case captive_portal_dns_task_message::init:
      init_sync();
      break;
    case captive_portal_dns_task_message::start:
      start_sync();
      break;
    case captive_portal_dns_task_message::stop:
      stop_sync();
      break;
  }
}

bool broadcast_clock::captive_portal_dns::
packet_valid( uint8_t * udp_msg, uint32_t len ) {
  dns_header *hdr = reinterpret_cast<dns_header *>( udp_msg );
  return (
    len <= m_dns_buflen &&
    len >= sizeof( dns_header ) &&
    hdr->ancount == 0 &&
    hdr->nscount == 0 &&
    hdr->arcount == 0 &&
    !( hdr->flags & ( 1 << 1 ) ) );
}

std::string broadcast_clock::captive_portal_dns::
get_label_part( uint8_t *&p, const uint8_t *eop ) {
  std::string str = "";
  const uint8_t len = *p++;
  for( int i = 0; p < eop && i < len; i++ ) {
    str += static_cast<char>( *p++ );
  }
  return str;
}

std::string broadcast_clock::captive_portal_dns::
get_label( uint8_t *udp_msg, uint8_t *&p, uint32_t len ) {
  static const uint8_t bitmask_if_compressed = 0xC0;
  const uint8_t *eop = udp_msg + len;
  std::string label, label_part;
  do {
    switch( *p & bitmask_if_compressed ) {
      case 0x00:
        // Not compressed
        label_part = get_label_part( p, eop );
        break;
      case 0xC0:
        // Compressed
        uint16_t offset = ntohs( reinterpret_cast<uint16_t *>( p ) ) & ~bitmask_if_compressed;
        if( offset >= len ) return "";
        uint8_t *_p = udp_msg + offset;
        label_part = get_label_part( _p, eop );
        p += 2;
        break;
    }
    if( label_part.length() == 0 ) break;
    if( label.length() > 0 ) label.append( "." );
    label.append( label_part );
  } while( p < eop && *p != 0x00 );
  p++; // Move to next byte after label
  return label;
}

void broadcast_clock::captive_portal_dns::
put_label( std::string label,
                                    uint8_t *&buf,
                                    const uint8_t *eob )
{
  uint8_t *lenptr = buf++;
  *lenptr = 0;
  for( std::string::iterator i = label.begin(); i != label.end(); i++ ) {
    if( *i == '.' ) {
      lenptr = buf++;
      if( lenptr < eob ) *lenptr = 0;
    }
    else if( buf < eob && *lenptr < 0x3F ) {
      *buf++ = static_cast<uint8_t>( *i );
      ( *lenptr )++;
    }
  }
  *buf++ = 0x00;
}

void broadcast_clock::captive_portal_dns::
on_receive( struct sockaddr_in *from,
                                     uint8_t *udp_msg,
                                     uint32_t len )
{
  if( packet_valid( udp_msg, len ) ) {
    dns_header *hdr = reinterpret_cast<dns_header *>( udp_msg );
    uint8_t reply[ m_dns_buflen ];
    memcpy( reply, udp_msg, len );
    uint8_t *reply_insertion_point = reply + len;
    dns_header *rhdr = reinterpret_cast<dns_header *>( reply );
    rhdr->flags |= ( 1 << 7 ); // Set QR bit
    rhdr->flags |= ( 1 << 0 ); // Disable recursion
    uint8_t *answer_count = reinterpret_cast<uint8_t *>( &rhdr->ancount );
    uint8_t *p = udp_msg + sizeof( dns_header );
    esp_netif_ip_info_t ipcfg;
    esp_netif_get_ip_info( esp_netif_next( nullptr ), &ipcfg );
    for( int i = 0; i < ntohs( reinterpret_cast<uint16_t *>( &hdr->qdcount ) ); i++ ) {
      std::string label = get_label( udp_msg, p, len );
      dns_question_footer *question_footer = reinterpret_cast<dns_question_footer *>( p );
      p += sizeof( dns_question_footer );
      switch( static_cast<qtype>( ntohs( &question_footer->type ) ) ) {
        case qtype::a:
          put_label( label,
                     reply_insertion_point,
                     reply + m_dns_buflen );

          // DNS resource footer
          put_n16( reply_insertion_point, static_cast<uint16_t>( qtype::a ) );   // Type
          put_n16( reply_insertion_point, static_cast<uint16_t>( qclass::in ) ); // Class
          put_n32( reply_insertion_point, 0x00000000 ); // TTL

          // IP address
          put_n16( reply_insertion_point, 0x0004 );           // RDLENGTH (IPv4 address)
          *reply_insertion_point++ = ip4_addr1( &ipcfg.ip );  // IP octet 1
          *reply_insertion_point++ = ip4_addr2( &ipcfg.ip );  // IP octet 2
          *reply_insertion_point++ = ip4_addr3( &ipcfg.ip );  // IP octet 3
          *reply_insertion_point++ = ip4_addr4( &ipcfg.ip );  // IP octet 4

          put_n16( answer_count, ntohs( &rhdr->ancount ) + 1 );

          sendto( m_sock,
                  reply,
                  reply_insertion_point - reply,
                  0,
                  reinterpret_cast<struct sockaddr *>( from ),
                  sizeof( struct sockaddr_in ) );

          break;
        case qtype::ns:
          ;
          break;
        case qtype::uri:
          ;
          break;
        default:
          ;
      }
    }
  }
}

void broadcast_clock::captive_portal_dns::
create_sock() {
  do {
    m_sock = socket( AF_INET, SOCK_DGRAM, 0 );
    if( m_sock == -1 ) {
      ESP_LOGI( m_component_name, "Failed to create socket" );
      vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
  } while( m_sock == -1 );
} 

void broadcast_clock::captive_portal_dns::
bind_sock() {
  struct sockaddr_in server_addr;
  memset( &server_addr, 0, sizeof( sockaddr_in ) );
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = lwip_htons( 53 );
  server_addr.sin_len = sizeof( sockaddr_in );
  uint32_t res = 0;
  do {
    res = bind( m_sock, ( struct sockaddr * ) &server_addr, sizeof( sockaddr_in ) );
  } while( res != 0 );
}

void broadcast_clock::captive_portal_dns::
init_sync() {
  ESP_LOGI( m_component_name, "Initialize DNS server" );
  create_sock();
  bind_sock();
}

void broadcast_clock::captive_portal_dns::
start_sync() {
  ESP_LOGI( m_component_name, "Starting DNS server" );
  server_loop();
}

void broadcast_clock::captive_portal_dns::
stop_sync() {
  ESP_LOGI( m_component_name, "Stopping DNS server" );
}

void broadcast_clock::captive_portal_dns::
enqueue_simple_message( captive_portal_dns_task_message msg ) {
  captive_portal_dns_task_queue_item item = { msg, nullptr };
  xQueueSend( m_message_queue, &item, 10 );
}

// Asynchronous methods (called from other tasks)

void broadcast_clock::captive_portal_dns::
init() {
  enqueue_simple_message( captive_portal_dns_task_message::init );
}

void broadcast_clock::captive_portal_dns::
start() {
  enqueue_simple_message( captive_portal_dns_task_message::start );
}

void broadcast_clock::captive_portal_dns::
stop() {
  enqueue_simple_message( captive_portal_dns_task_message::stop );
}
