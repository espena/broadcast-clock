#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#define DEFAULT_CONFIG "time_zone=CET-1CEST,M3.5.0,M10.5.0/3&ssid=&password=&ntp=pool.ntp.org"

#include <string>
#include <map>

namespace espena::broadcast_clock {

  class configuration {

    static const char *m_component_name;

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

    void update( ::std::string data );
    void parse();

  };

} // namespace espena::broadcast_clock

#endif // __CONFIGURATION_HPP__