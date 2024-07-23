#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#define DEFAULT_CONFIG "time_zone=CET-1CEST,M3.5.0,M10.5.0/3&ssid=&password=&ntp=pool.ntp.org"

#include <string>
#include <map>
#include <esp_event.h>

namespace espena::broadcast_clock {

  class configuration {

  public:

    static const esp_event_base_t m_event_base;
    static const uint32_t CONFIGURATION_UPDATED = 0x01u;

  private:

    static const char *m_component_name;

    esp_event_loop_handle_t m_event_loop_handle;

    ::std::string m_data;
    ::std::map<std::string, std::string> m_values;

    static const char *m_nvs_namespace;
    static configuration *m_instance;

    void read_from_nvs();
    void save_to_nvs();

    configuration();

  public:

    ~configuration();

    static configuration *get_instance() { return m_instance ? m_instance : new configuration(); };

    ::std::string get_str( ::std::string key );
    int get_int( ::std::string key );
    bool get_bool( ::std::string key );

    void set_event_loop_handle( esp_event_loop_handle_t event_loop_handle ) { m_event_loop_handle = event_loop_handle; };

    void update( ::std::string data );
    void parse();

  };

} // namespace espena::broadcast_clock

#endif // __CONFIGURATION_HPP__