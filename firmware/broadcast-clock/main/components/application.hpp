#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "wifi.hpp"
#include "configuration.hpp"
#include "clock_face.hpp"
#include "clock_status.hpp"
#include "beeper.hpp"
#include "lea_m8t.hpp"
#include "ntp_server.hpp"
#include "captive_portal_dns.hpp"
#include "http_server.hpp"
#include <string>
#include <esp_timer.h>
//#include <driver/i2c_master.h>

namespace espena::broadcast_clock {

  class application {

    static const char *m_component_name;

    esp_timer_handle_t m_ap_duration_timer;

    configuration *m_configuration;

    wifi m_wifi;
    captive_portal_dns m_captive_portal_dns;
    http_server m_http_server;
    lea_m8t m_lea_m8t;
    ntp_server m_ntp_server;
    clock_face m_clock_face;
    clock_status m_clock_status;
    beeper m_beeper;

    esp_event_loop_handle_t m_event_loop_handle;

    static void wifi_event_handler( void *handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void *event_params );

    static void on_ap_duration_timeout( void *arg );

    void switch_to_station_mode();

    void on_got_ip( esp_netif_ip_info_t *ip_info );
    void on_enter_config_mode();
    void on_save_config( std::string post_data );
    void on_cancel_config( std::string post_data );
    void on_leave_config_mode();
    void on_countdown_finish();

    static void on_press_test( void *arg );
    static void on_start_test( void *arg );

  public:

    application();
    ~application();
    void init();
    void init_nvs();
    void init_timezone();
    void init_i2c();
    void init_ap_duration_timeout();

  };

}

#endif // __APPLICATION_HPP__