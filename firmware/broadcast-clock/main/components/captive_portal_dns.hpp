#ifndef __CAPTIVE_PORTAL_DNS_HPP__
#define __CAPTIVE_PORTAL_DNS_HPP__

#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

namespace espena::broadcast_clock {

  class captive_portal_dns {

    QueueHandle_t m_message_queue;
    int m_sock;

    static uint16_t ntohs( uint16_t *i ) {
      uint8_t *b = reinterpret_cast<uint8_t *>( i );
      return ( ( b[ 0 ] << 8 ) & 0xff00 ) | ( b[ 1 ] & 0x00ff );
    };

    static void put_n16( uint8_t *&buf, int16_t n16 ) {
      *buf++ = ( n16 >> 8 ) & 0x00ff; // MSB
      *buf++ = ( n16 & 0x00ff );      // LSB
    }

    static void put_n32( uint8_t *&buf, int32_t n32 ) {
      *buf++ = ( n32 >> 24 ) & 0x000000ff; // MSB
      *buf++ = ( n32 >> 16 ) & 0x000000ff;
      *buf++ = ( n32 >>  8 ) & 0x000000ff;
      *buf++ = ( n32 & 0x000000ff );       // LSB
    }

    typedef struct captive_portal_dns_task_params_struct {
      captive_portal_dns *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } captive_portal_dns_task_params;

    captive_portal_dns_task_params m_task_params;

    enum class captive_portal_dns_task_message {
      init,
      start,
      stop
    };

    enum class qtype {
      a = 0x0001,
      ns = 0x0002,
      uri = 0x00ff
    };

    enum class qclass {
      in = 0x0001,
      any = 0x00ff,
      uri = 0x0100
    };

    typedef struct captive_portal_dns_task_queue_item_struct {
      captive_portal_dns_task_message message;
      void *arg;
    } captive_portal_dns_task_queue_item;

    typedef struct {
      uint16_t id;
      uint8_t flags;
      uint8_t rcode;
      uint16_t qdcount;
      uint16_t ancount;
      uint16_t nscount;
      uint16_t arcount;
    } __attribute__( ( packed ) ) dns_header;

    typedef struct {
      uint16_t type;
      uint16_t cl;
    } __attribute__( ( packed ) ) dns_question_footer;

    typedef struct {
      uint16_t type;
      uint16_t cl;
      uint32_t ttl;
      uint16_t rdlength;
    } __attribute__( ( packed ) ) dns_resource_footer;


    static void task_loop( void *arg );
    
    bool packet_valid( uint8_t * udp_msg, uint32_t len );

    std::string get_label_part( uint8_t *&p,
                                const uint8_t *eop );

    std::string get_label( uint8_t *udp_msg,
                           uint8_t *&p,
                           uint32_t len );
    
    void put_label( std::string label,
                    uint8_t *&p,
                    const uint8_t *eob );

    void on_message( captive_portal_dns_task_message msg, void *arg );
    void on_receive( struct sockaddr_in *from,
                     uint8_t *udp_msg,
                     uint32_t len );

    void server_loop();

    void create_sock();
    void bind_sock();

    void enqueue_simple_message( captive_portal_dns_task_message msg );

    void init_sync();
    void start_sync();
    void stop_sync();

    public:

      static const char *m_component_name;
      static const uint32_t m_component_stack_size = 8192;
      static const uint32_t m_dns_buflen = 512;

      captive_portal_dns();

      void init();
      void start();
      void stop();
  };

}; // espena::broadcast_clock

#endif // __CAPTIVE_PORTAL_DNS_HPP__