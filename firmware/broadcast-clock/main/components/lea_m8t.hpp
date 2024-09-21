#ifndef __LEA_M8T__
#define __LEA_M8T__

#include "ubx_types.hpp"
#include "../gpio_mapping.hpp"
#include <time.h>
#include <esp_timer.h>
#include <esp_event.h>
#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace espena::broadcast_clock {

  class lea_m8t {

  public:

    static const char *m_event_base;

    static const uint32_t GNSS_INSTALLED = 0x01u;
    static const uint32_t TIMEPULSE_PRESENT = 0x02u;
    static const uint32_t TIMEPULSE_ABSENT = 0x03u;
    static const uint32_t TIME_SYNC = 0x04u;
    static const uint32_t NO_TIME_SYNC = 0x05u;
    static const uint32_t HIGH_ACCURACY = 0x06u;
    static const uint32_t LOWER_ACCURACY = 0x07u;

  private:

    static const int m_time_pulse_offset_threshold = 15;

    static const char *m_component_name;
    static const size_t m_component_stack_size = 8192;

    static const uint8_t m_i2c_address = 0x42; // u-blox DDC address

    esp_event_loop_handle_t m_event_loop_handle;
    portMUX_TYPE m_spinlock;

    uint8_t m_ack = ubx::message::ack::ack;

    bool m_is_initialized = false;
    int m_seconds_with_no_timesync_data = 0;
    bool m_i2c_installed = false;

    esp_timer_handle_t m_poll_timer = nullptr;
    
    static int64_t m_ns_timepulse;
    static int64_t m_ns_mismatch;

    ubx::nav_sat_t m_nav_sat;
    ubx::cfg_prt_ddc_t m_cfg_prt_ddc;
    ubx::cfg_tmode2_t m_cfg_tmode2;
    ubx::cfg_gnss_t m_cfg_gnss;
    ubx::cfg_ant_t m_cfg_ant;

    char m_software_version[ 30 ] = { 0x00 };
    char m_hardware_version[ 10 ] = { 0x00 };

    QueueHandle_t m_task_queue;

    QueueHandle_t m_egress_queue;

    typedef struct lea_m8t_task_params_struct {
      lea_m8t *instance;
      StackType_t *stack_buffer;
      StaticTask_t task_buffer;
    } lea_m8t_task_params;

    lea_m8t_task_params m_task_params;

    enum class lea_m8t_task_message {
      init,
      poll,
      timepulse
    };

    typedef struct lea_m8t_egress_queue_item_struct {
      uint16_t len;
      ubx::message_t message;
      uint8_t *deletable_payload;
      bool acked;
    } lea_m8t_egress_queue_item_t;

    typedef struct lea_m8t_task_queue_item_struct {
      lea_m8t_task_message message;
      void *arg;
    } lea_m8t_task_queue_item_t;

    static void task_loop( void *arg );
    static void on_poll_timer( void *arg );

    void on_init();

    void init_isr_timepulse();
    void init_ubx();
    void init_ubx_safeboot();
    void init_ubx_normalboot();

    uint16_t get_bytes_available();

    void read();
    void write();
    void update_status();

    static void timepulse_handler( void *arg );
    void on_timepulse();

    void on_task_message( lea_m8t_task_message msg, void *arg );

    void on_ubx_message( const uint8_t msg_class,
                         const uint8_t msg_id,
                         void *payload,
                         const uint16_t len );

    void on_ubx_cfg_ant( ubx::cfg_ant_t *payload );
    void on_ubx_cfg_prt( ubx::cfg_prt_ddc_t *payload );
    void on_ubx_cfg_tmode2( ubx::cfg_tmode2_t *payload );
    void on_ubx_cfg_gnss( ubx::cfg_gnss_t *payload );

    void on_ubx_mon_hw( ubx::mon_hw_t *payload );

    void on_ubx_nav_sat( ubx::nav_sat_t *payload );
    void on_ubx_nav_timeutc( ubx::nav_timeutc_t *payload );

  public:

    lea_m8t();
    ~lea_m8t();

    bool is_present();
    void init();
    void set_event_loop_handle( esp_event_loop_handle_t h ) { m_event_loop_handle = h; };

  };

}

#endif // __LEA_M8T__