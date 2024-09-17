#ifndef __LEA_M8T__
#define __LEA_M8T__

#include "ubx_types.hpp"
#include "configuration.hpp"
#include "../gpio_mapping.hpp"
//#include <driver/i2c.h>
#include <driver/i2c_master.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace espena::broadcast_clock {

  class lea_m8t {

    static const char *m_component_name;
    static const size_t m_component_stack_size = 8192;
    static const uint8_t m_i2c_address = 0x42; // u-blox DDC address

    uint8_t m_ack = 0x00;

    char m_software_version[ 30 ] = { 0x00 };
    char m_hardware_version[ 10 ] = { 0x00 };

    ubx::cfg_prt_ddc_t m_cfg_prt_ddc;

    configuration *m_config;
    
    QueueHandle_t m_task_queue;

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

    typedef struct lea_m8t_task_queue_item_struct {
      lea_m8t_task_message message;
      void *arg;
    } lea_m8t_task_queue_item;

    i2c_master_bus_handle_t m_i2c_bus;
    i2c_master_dev_handle_t m_i2c_dev;

    static void task_loop( void *arg );

    static void on_timepulse( void *arg );
    void on_timepulse();
    
    uint16_t get_bytes_available();
    void poll();

    void on_message( lea_m8t_task_message msg, void *arg );

    void on_ubx_message( const uint8_t msg_class,
                         const uint8_t msg_id,
                         void *payload,
                         const uint16_t len );

    void on_ubx_ack_ack( uint8_t port_id );
    void on_ubx_ack_nak( uint8_t msg_cls, uint8_t msg_id );

    void on_ubx_mon_ver( ubx::mon_ver_t *ver );
    void on_ubx_mon_hw( ubx::mon_hw_t *hw );

    void on_ubx_cfg_gnss( ubx::cfg_gnss_t *gnss );
    void on_ubx_cfg_tp5( ubx::cfg_tp5_t *tp5 );
    void on_ubx_cfg_prt_ddc( ubx::cfg_prt_ddc_t *prt );
    void on_ubx_cfg_tmode2( ubx::cfg_tmode2_t *tmode2 );
    void on_ubx_cfg_tmode3( ubx::cfg_tmode3_t *tmode3 );

    void on_ubx_nav_timegps( ubx::nav_timegps_t *timegps );
    void on_ubx_nav_sat( ubx::nav_sat_t *sat );
    void on_ubx_nav_svin( ubx::nav_svin_t *svin );
    void on_ubx_nav_clock( ubx::nav_clock_t *clock );

    void on_ubx_tim_tm2( ubx::tim_tm2_t *tm2 );
    void on_ubx_tim_svin( ubx::tim_svin_t *svin );

    void on_init( i2c_master_bus_handle_t i2c_bus );

    void ubx_request( const uint8_t cls, const uint8_t id );
    void poll_msg( const uint8_t cls, const uint8_t id );
    //void ubx_poll( const uint8_t cls, const uint8_t id );
    
    void on_poll_msg( ubx::message_t *msg );
    void wait_for_ack( int timeout );

    void init_isr_timepulse();
    void init_i2c_device();

    void reset_device();

    void report_software_version();
    void report_hardware_status();
    void report_ubx_messaging();
    void report_time_mode_config();
    void report_timepulse_config();
    void report_gps_time();
    void report_utc_time();
    void report_clock();
    void report_survey_in();
    void report_gnss();

    void set_out_protocol();
    void set_time_mode();
    void set_cfg_prt_ddc();
    void set_gnss();

  public:

    void report_satellites();


    lea_m8t();
    ~lea_m8t();

    bool is_present();
    void init( i2c_master_bus_handle_t i2c_bus );

  };

}

#endif // __LEA_M8T__