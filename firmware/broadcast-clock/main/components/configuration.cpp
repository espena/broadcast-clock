#include "configuration.hpp"
#include "../utils/from_hex.hpp"
#include <algorithm>
#include <cctype>
#include <string>
#include <map>
#include <nvs_flash.h>
#include <esp_event.h>
#include <esp_log.h>

using namespace espena;

const char *broadcast_clock::configuration::m_component_name = "configuration";
const esp_event_base_t broadcast_clock::configuration::m_event_base = "broadcast_clock_configuration_event";

const char *broadcast_clock::configuration::m_nvs_namespace = "default";
broadcast_clock::configuration *broadcast_clock::configuration::m_instance = nullptr;

broadcast_clock::configuration::
configuration() : m_event_loop_handle( nullptr ) {
  m_instance = this;
  read_from_nvs();
}

broadcast_clock::configuration::
~configuration() {

}

void broadcast_clock::configuration::
read_from_nvs() {
  nvs_handle_t nvs;
  nvs_open( m_nvs_namespace, NVS_READONLY, &nvs );
  if( nvs ) {
    size_t required_size = 0;
    nvs_get_str( nvs, "config", NULL, &required_size );
    if( required_size > 0 ) {
      ESP_LOGI( m_component_name, "Configuration found" );
      m_data.resize( required_size );
      ESP_ERROR_CHECK( nvs_get_str( nvs, "config", &m_data[ 0 ], &required_size ) );
    }
    else {
      ESP_LOGI( m_component_name, "No configuration found, using default" );
      m_data = DEFAULT_CONFIG;
    }
    nvs_close( nvs );
  }
  ESP_LOGE( m_component_name, "Current configuration: %s", m_data.c_str() );
  parse();
}

void broadcast_clock::configuration::
save_to_nvs() {
  nvs_handle_t nvs;
  nvs_open( m_nvs_namespace, NVS_READWRITE, &nvs );
  if( nvs ) {
    ESP_LOGE( "configuration", "Saving config: %s", m_data.c_str() );
    ESP_ERROR_CHECK( nvs_set_str( nvs, "config", m_data.c_str() ) );
    ESP_ERROR_CHECK( nvs_commit( nvs ) );
    nvs_close( nvs );
  }
}

void broadcast_clock::configuration::
update( std::string data ) {
  m_data = data;
  save_to_nvs();
  parse();
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                       m_event_base,
                       CONFIGURATION_UPDATED,
                       nullptr,
                       0,
                       portMAX_DELAY );
  }
}

void broadcast_clock::configuration::
parse() {
  m_values.clear();
  std::string key;
  std::string value;
  int hex_bit = 0;
  unsigned char hexval = 0;
  bool is_key = true;
  for( auto c : m_data ) {
    if( hex_bit  ) {
      hex_bit--;
      hexval |= ( utils::from_hex( c ) & 0x0f ) << ( hex_bit * 4 );
      if( hex_bit == 0 ) {
        if( is_key ) key += hexval;
        else value += hexval;
      }
    }
    else if( c == '+' ) {
      if( is_key ) key += ' ';
      else value += ' ';
    }
    else if( c == '=' ) {
      is_key = false;
    }
    else if( c == '&' ) {
      m_values[ key ] = value;
      key = "";
      value = "";
      is_key = true;
    }
    else if( c == '%' ) {
      hexval = 0;
      hex_bit = 2;
    }
    else {
      if( is_key ) key += c;
      else value += c;
    }
  }
  m_values[ key ] = value;
}

std::string broadcast_clock::configuration::
get_str( std::string key ) {
  if( m_values.find( key ) != m_values.end() ) {
    return m_values[ key ];
  }
  return "";
}

int broadcast_clock::configuration::
get_int( std::string key ) {
  return atoi( get_str( key ).c_str() );
}

bool broadcast_clock::configuration::
get_bool( std::string key ) {
  std::string s = get_str( key );
  
  std::transform( s.begin(), s.end(), s.begin(),
    [ ]( unsigned char c ) {
      return std::tolower( c );
    } );
  
  return  ( ( s.empty() || 
              s == "0" ||
              s == "false" ||
              s == "off" ||
              s == "no" ||
              s == " " )
            ? false
            : true );
}