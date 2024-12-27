#include <memory.h>
#include <string>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_http_server.h"

#include "http_server.hpp"
#include "wifi.hpp"
#include "configuration.hpp"

#include "../semaphores/mutex.hpp"
#include "../utils/hexdump.hpp"
#include "../utils/get_query_field.hpp"
#include "../utils/span_to_timespec.hpp"
#include "../utils/replace_substring.hpp"

using namespace espena;

const char *broadcast_clock::http_server::m_component_name = "http_server";
const esp_event_base_t broadcast_clock::http_server::m_event_base = "http_server_EVENT";

broadcast_clock::http_server::http_server() : m_message_queue( nullptr ),
                                                              m_server( nullptr ),
                                                              m_event_loop_handle( nullptr ),
                                                              m_gnss_state( nullptr )
{    
  m_cfg.uri_match_fn = httpd_uri_match_wildcard;
  m_cfg.lru_purge_enable = true;
  m_cfg.enable_so_linger = false;
  m_message_queue = xQueueCreate( 50, sizeof( http_server_task_queue_item ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );
  update_json_gnss_status();
  
  xTaskCreateStatic( &broadcast_clock::http_server::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     12,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer );
}

void broadcast_clock::http_server::
set_event_loop_handle( esp_event_loop_handle_t h ) {
  m_event_loop_handle = h;
  if( m_event_loop_handle ) {
    ESP_ERROR_CHECK( esp_event_handler_register_with( m_event_loop_handle,
                                                      wifi::m_event_base,
                                                      wifi::SSID_SCAN_RESULT,
                                                      &event_handler,
                                                      this ) );
  }
}

void broadcast_clock::http_server::
event_handler( void *handler_arg,
               esp_event_base_t event_base,
               int32_t event_id,
               void *event_data ) {

  auto *instance = static_cast<broadcast_clock::http_server *>( handler_arg );
  if( event_base == wifi::m_event_base ) {
    if( event_id == wifi::SSID_SCAN_RESULT ) {
      http_server_task_queue_item item;
      static wifi::ssid_scan_result_t scan_result;
      memcpy( &scan_result, event_data, sizeof( wifi::ssid_scan_result_t ) );
      item.message = http_server_task_message::ssid_scan_result;
      item.arg = &scan_result;
      xQueueSend( instance->m_message_queue, &item, 10 );
    }
  }
}

void broadcast_clock::http_server::
on_ssid_scan_result( wifi::ssid_scan_result_t * scan_result ) {
  if( xSemaphoreTake( semaphores::mutex::ssid_list, portMAX_DELAY ) ) {
    for( uint16_t u = 0; u < scan_result->ap_count; u++ ) {
      m_ssid_list.insert( std::string( reinterpret_cast<char *>( scan_result->ap_records[ u ].ssid ) ) );
    }
    xSemaphoreGive( semaphores::mutex::ssid_list );
  }
  m_ssids_received = true;
}

void broadcast_clock::http_server::
update_json_gnss_status() {

  if( m_gnss_state ) {

    m_json_gnss_status = "{ \
                            \"status\": \"__status__\", \
                            \"system_uptime\": \"__system_uptime__\", \
                            \"system_wifi_mode\": \"__system_wifi_mode__\", \
                            \"chip_installed\": \"__gnss_chip_installed__\", \
                            \"software_version\": \"__gnss_software_version__\", \
                            \"hardware_version\": \"__gnss_hardware_version__\", \
                            \"system\": \"__gnss_system__\", \
                            \"satellites_found\": __gnss_satellite_count__, \
                            \"got_timepulse\": \"__gnss_got_timepulse__\", \
                            \"utc_standard\": \"__gnss_utc_standard__\", \
                            \"time_mode_started\": \"__gnss_time_mode_started__\", \
                            \"time_mode_status\": \"__gnss_time_mode__\", \
                            \"time_accuracy\": \"__gnss_offset_us__\", \
                            \"ntp_server_client_count\": \"__ntp_server_client_count__\", \
                            \"survey_in\": {\
                              \"active\": \"__gnss_svin_active__\", \
                              \"valid\": \"__gnss_svin_valid__\", \
                              \"duration\": __gnss_svin_dur__, \
                              \"observations\": __gnss_svin_obs__, \
                              \"mean_x\": __gnss_svin_mean_x__, \
                              \"mean_y\": __gnss_svin_mean_y__, \
                              \"mean_z\": __gnss_svin_mean_z__, \
                              \"mean_v\": __gnss_svin_mean_v__ \
                            }\
                          }";

    utils::replace_substring( m_json_gnss_status, "__status__", m_gnss_state->rebooting() ? "rebooting" : "running" );
    utils::replace_substring( m_json_gnss_status, "__system_uptime__", m_gnss_state->system_uptime_str() );
    utils::replace_substring( m_json_gnss_status, "__system_wifi_mode__", m_gnss_state->system_wifi_mode_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_chip_installed__", m_gnss_state->gnss_chip_installed_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_software_version__", m_gnss_state->gnss_software_version_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_hardware_version__", m_gnss_state->gnss_hardware_version_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_system__", m_gnss_state->gnss_current_system_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_satellite_count__", m_gnss_state->gnss_satellite_count_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_got_timepulse__", m_gnss_state->gnss_got_timepulse_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_utc_standard__", m_gnss_state->gnss_utc_standard_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_time_mode_started__", m_gnss_state->gnss_time_mode_started_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_time_mode__", m_gnss_state->gnss_time_mode_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_offset_us__", m_gnss_state->gnss_mean_systime_offset_us_str() );
    utils::replace_substring( m_json_gnss_status, "__ntp_server_client_count__", m_gnss_state->gnss_ntp_server_client_count_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_active__", m_gnss_state->gnss_svin_active_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_valid__", m_gnss_state->gnss_svin_valid_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_dur__", m_gnss_state->gnss_svin_dur_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_obs__", m_gnss_state->gnss_svin_obs_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_mean_x__", m_gnss_state->gnss_svin_mean_x_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_mean_y__", m_gnss_state->gnss_svin_mean_y_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_mean_z__", m_gnss_state->gnss_svin_mean_z_str() );
    utils::replace_substring( m_json_gnss_status, "__gnss_svin_mean_v__", m_gnss_state->gnss_svin_mean_v_str() );

  }
  else {
    m_json_gnss_status = "{ \"status\": \"initializing\" }";
  }
}

void broadcast_clock::http_server::
update_json_ssid_list() {
  if( m_event_loop_handle ) {
    m_ssids_received = false;
    esp_event_post_to( m_event_loop_handle,
                      m_event_base,
                      EVENT_SSID_REQUEST,
                      nullptr,
                      0,
                      portMAX_DELAY );
  }
  int timeout = 0;
  while( !m_ssids_received && timeout < 10000 ) {
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    timeout += 100;
  }
  m_json_ssid_list = "{ \"ssids\": [";
  int i = 0;
  for( const auto &ssid : m_ssid_list ) {
    m_json_ssid_list += ( i++ > 0 ? "," : "" ) + ( "\"" + ssid + "\"" );
  }
  m_json_ssid_list += "]}";
}

void broadcast_clock::http_server::
enqueue_simple_message( http_server_task_message msg ) {
  http_server_task_queue_item item = { msg, nullptr };
  xQueueSend( m_message_queue, &item, 10 );
}

void broadcast_clock::http_server::
task_loop( void *arg ) {
  http_server_task_params *params = static_cast<http_server_task_params *>( arg );
  http_server *inst = params->instance;
  static http_server_task_queue_item item;
  memset( &item, 0x00, sizeof( http_server_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

esp_err_t broadcast_clock::http_server::
request_handler( httpd_req_t *req ) {
  http_server *inst = static_cast<http_server *>( req->user_ctx );
  return inst->on_request( req );
}

esp_err_t broadcast_clock::http_server::
respond( httpd_req_t *req, const char *buf, size_t buf_len ) {
  if( xSemaphoreTake( semaphores::mutex::http_port, portMAX_DELAY ) ) {
    httpd_resp_send( req, buf, buf_len );
    xSemaphoreGive( semaphores::mutex::http_port );
  }
  return ESP_OK;
}

void broadcast_clock::http_server::
save_handler( httpd_req_t *req ) {

    static std::string post_data;
    post_data.resize( req->content_len + 1 );
    httpd_req_recv( req, &post_data[ 0 ], req->content_len );
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        post_data.find( "action=Save" ) != std::string::npos ? EVENT_SAVE : EVENT_CANCEL,
                        post_data.c_str(),
                        post_data.length(),
                        portMAX_DELAY );

    const char *buf_ex = ( char * ) broadcast_clock::resources::html::exit_page_html_start;
    const size_t buf_ex_len = broadcast_clock::resources::html::exit_page_html_end - broadcast_clock::resources::html::exit_page_html_start;

    wifi_mode_t mode;
    esp_wifi_get_mode( &mode );

    if( mode == WIFI_MODE_STA ) { // Station mode, stay on configuration
      vTaskDelay( 100 / portTICK_PERIOD_MS ); // Wait for save completed
      std::string html = create_html_response();
      httpd_resp_set_hdr( req, "Connection", "Close"  );
      ESP_ERROR_CHECK( respond( req, html.c_str(), html.length() ) );
    }
    else { // AP mode, exit from configuration
      ESP_ERROR_CHECK( respond( req, buf_ex, buf_ex_len ) );
    }
}


void broadcast_clock::http_server::
survey_in_handler( httpd_req_t *req ) {

    static std::string post_data;
    post_data.resize( req->content_len + 1 );
    httpd_req_recv( req, &post_data[ 0 ], req->content_len );

    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        post_data.find( "time_mode_enable=1" ) != std::string::npos ? EVENT_START_TIME_MODE : EVENT_STOP_TIME_MODE,
                        post_data.c_str(),
                        post_data.length(),
                        portMAX_DELAY );

    ESP_ERROR_CHECK( respond( req, "OK", 3 ) );
}

void broadcast_clock::http_server::
timers_handler( httpd_req_t *req ) {

  esp_event_post_to( m_event_loop_handle,
                      m_event_base,
                      EVENT_ENTER_TIMERS,
                      "",
                      0,
                      portMAX_DELAY );

  const char *buf_sw = ( char * ) broadcast_clock::resources::html::timers_page_html_start;
  const size_t buf_sw_len = broadcast_clock::resources::html::timers_page_html_end - broadcast_clock::resources::html::timers_page_html_start;
  ESP_ERROR_CHECK( respond( req, buf_sw, buf_sw_len ) );
}

void broadcast_clock::http_server::
stopwatch_handler( httpd_req_t *req ) {

  ESP_ERROR_CHECK( respond( req, "OK", 3 ) );
  std::string uri( req->uri );
  uint32_t e = 0;
  if( uri.starts_with( "/stopwatch/start" ) ) e = EVENT_STOPWATCH_START;
  else if( uri.starts_with( "/stopwatch/stop" ) ) e = EVENT_STOPWATCH_STOP;
  else e = EVENT_STOPWATCH_RESET;

  esp_event_post_to( m_event_loop_handle,
                     m_event_base,
                     e,
                     "",
                     0,
                     portMAX_DELAY );
}

void broadcast_clock::http_server::
countdown_handler( httpd_req_t *req ) {
  ESP_ERROR_CHECK( respond( req, "OK", 3 ) );
  std::string uri( req->uri );

  static struct timespec countdown_period;
  static std::string period;

  period = utils::get_query_field( uri, "period" );
  memset( &countdown_period, 0x00, sizeof( struct timespec ) );

  utils::span_to_timespec( period, &countdown_period );  
  uint32_t e = 0;

  if( uri.starts_with( "/countdown/start" ) ) e = EVENT_COUNTDOWN_START;
  else e = EVENT_COUNTDOWN_RESET;

  esp_event_post_to( m_event_loop_handle,
                     m_event_base,
                     e,
                     &countdown_period,
                     sizeof( struct timespec ),
                     portMAX_DELAY );
}

void broadcast_clock::http_server::
reboot_handler( httpd_req_t *req ) {
  ESP_ERROR_CHECK( respond( req, "OK", 3 ) );
  std::string uri( req->uri );
  uint32_t e = uri.starts_with( "/reboot/gnss" ) ? EVENT_REBOOT_GNSS : EVENT_REBOOT_CPU;
  esp_event_post_to( m_event_loop_handle,
                     m_event_base,
                     e,
                     nullptr,
                     0,
                     portMAX_DELAY );
}

esp_err_t broadcast_clock::http_server::
on_request( httpd_req_t *req ) {

  const size_t req_hdr_host_len = httpd_req_get_hdr_value_len( req, "Host" );
  std::string hostname;
  hostname.resize( req_hdr_host_len + 1 );

  httpd_req_get_hdr_value_str( req, "Host", &hostname[ 0 ], req_hdr_host_len + 1 );

  ESP_LOGI( m_component_name, "Request for %s", req->uri );

  std::string uri( req->uri );

  if( uri == "/save" && req->content_len > 0 && m_event_loop_handle ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "text/html; charset=utf-8;" );
    save_handler( req );
  }
  else if( uri == "/survey_in" && req->content_len > 0 && m_event_loop_handle ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "text/html; charset=utf-8;" );
    survey_in_handler( req );
  }
  else if( uri == "/timers" && m_event_loop_handle ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "text/html; charset=utf-8;" );
    timers_handler( req );
  }
  else if( uri.starts_with( "/stopwatch/start" ) ||
           uri.starts_with( "/stopwatch/stop" ) ||
           uri.starts_with( "/stopwatch/reset" ) ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "text/html; charset=utf-8;" );
    stopwatch_handler( req );
  }
  else if( uri.starts_with( "/countdown/start" ) ||
           uri.starts_with( "/countdown/reset" ) ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "text/html; charset=utf-8;" );
    countdown_handler( req );
  }
  else if( uri.starts_with( "/reboot/cpu" ) ||
           uri.starts_with( "/reboot/gnss" ) ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "text/html; charset=utf-8;" );
    reboot_handler( req );
  }
  else if( uri == "/styles.css" ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "text/css; charset=utf-8" );
    const char *buf_st = ( char * ) broadcast_clock::resources::html::styles_css_start;
    const size_t buf_st_len = broadcast_clock::resources::html::styles_css_end - broadcast_clock::resources::html::styles_css_start;
    ESP_ERROR_CHECK( respond( req, buf_st, buf_st_len ) );
  }
  else if( uri == "/gnss-status" ) {
    update_json_gnss_status();
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "application/json; charset=utf-8" );
    ESP_ERROR_CHECK( respond( req, m_json_gnss_status.c_str(), m_json_gnss_status.length() ) );
  }
  else if( uri == "/ssid-list" ) {
    update_json_ssid_list();
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "application/json; charset=utf-8" );
    ESP_ERROR_CHECK( respond( req, m_json_ssid_list.c_str(), m_json_ssid_list.length() ) );
  }
  else if( uri == "/favicon.ico" ) {
    httpd_resp_set_status( req, "200 OK" ); 
    httpd_resp_set_type( req, "image/x-icon;" );
    const char *buf_ico = ( char * ) broadcast_clock::resources::gfx::favicon_ico_start;
    const size_t buf_ico_len = broadcast_clock::resources::gfx::favicon_ico_end - broadcast_clock::resources::gfx::favicon_ico_start;
    ESP_ERROR_CHECK( respond( req, buf_ico, buf_ico_len ) );
  }
  else {
    std::string html = create_html_response();
    ESP_ERROR_CHECK( respond( req, html.c_str(), html.length() ) );
  }
  return ESP_OK;
}

void broadcast_clock::http_server::
on_message( http_server_task_message msg, void *arg ) {
  switch( msg ) {
    case http_server_task_message::init:
      init_sync();
      break;
    case http_server_task_message::ssid_scan_result:
      on_ssid_scan_result( static_cast<wifi::ssid_scan_result_t *>( arg ) );
      break;
    case http_server_task_message::start:
      start_sync();
      break;
    case http_server_task_message::stop:
      stop_sync();
      break;
  }
}

void broadcast_clock::http_server::
init_sync() {

}

void broadcast_clock::http_server::
start_sync() {

  stop_sync(); // Assert server is not running

  if( httpd_start( &m_server, &m_cfg ) != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to start HTTP server" );
    return;
  }

  httpd_uri_t location;

  /*
  location.uri = "/timers",
  location.handler = request_handler,
  location.user_ctx = this;
  location.method = HTTP_POST,
  */

  location.uri = "/save",
  location.handler = request_handler,
  location.user_ctx = this;
  location.method = HTTP_POST,

  httpd_register_uri_handler( m_server, &location );

  location.uri = "/survey_in",
  location.handler = request_handler,
  location.user_ctx = this;
  location.method = HTTP_POST,

  httpd_register_uri_handler( m_server, &location );

  location.uri = "/*",
  location.method = HTTP_GET,
  location.handler = request_handler,
  location.user_ctx = this;

  httpd_register_uri_handler( m_server, &location );

  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        EVENT_CONFIGURATOR_START,
                        nullptr,
                        0,
                        portMAX_DELAY );
  }

  ESP_LOGI( m_component_name, "HTTP server running" );
  
}

std::string broadcast_clock::http_server::
create_html_response() {

  const char *buf_cp = ( char * ) broadcast_clock::resources::html::control_panel_html_start;
  const size_t buf_cp_len = broadcast_clock::resources::html::control_panel_html_end - broadcast_clock::resources::html::control_panel_html_start;

  broadcast_clock::configuration *cnf = broadcast_clock::configuration::get_instance();

  bool is_ele = false;
  bool is_tag = false;
  bool is_sel = false;

  std::string ele;
  std::string tag;
  std::string sel;
  std::string htm;

  for( size_t i = 0; i < buf_cp_len; i++ ) {
    const unsigned char c = buf_cp[ i ];
    if( c == '<' ) {
      is_ele = true;
      ele.clear();
      htm += c;
    }
    else if( c == '>' ) {
      is_ele = false;
      htm += c;
    }
    else if( is_ele && c == ' ' ) {
      is_ele = false;
      htm += c;
    }
    else if( is_ele && c == '/' ) {
      is_ele = false;
      ele.clear();
      htm += c;
    }
    else if( c == '|' ) {
      if( is_tag ) {
        if( is_sel ) {
          if( ele == "option" ) {
            htm += cnf->get_str( tag ) == sel ? "selected" : "";
          }
          else if ( ele == "input" ) {
            htm += cnf->get_str( tag ) == sel ? "checked" : "";
          }
          else if ( ele == "table" ) {
            htm += cnf->get_str( tag ) == sel ? "enabled" : "disabled";
          }
        }
        else {
          htm += cnf->get_str( tag );
        }
        is_tag = false;
        is_sel = false;
      }
      else {
        is_tag = true;
        tag.clear();
        sel.clear();
      }
    }
    else if( c == ':' ) {
      if( is_tag ) {
        is_sel = true;
      }
      else {
        htm += c;
      }
    }
    else {
      if( is_tag ) {
        if( is_sel ) {
          sel += c;
        }
        else {
          tag += c;
        }
      }
      else {
        if( is_ele ) {
          ele += c;
        }
        htm += c;
      }
    }
  }
  return htm;
}

void broadcast_clock::http_server::stop_sync() {
  if( m_server ) {
    httpd_stop( m_server );
    m_server = nullptr;
  if( m_event_loop_handle ) {
    esp_event_post_to( m_event_loop_handle,
                        m_event_base,
                        EVENT_CONFIGURATOR_STOP,
                        nullptr,
                        0,
                        portMAX_DELAY );
  }
    ESP_LOGI( m_component_name, "HTTP server stopped" );
  }
}

void broadcast_clock::http_server::
init() {
  enqueue_simple_message( http_server_task_message::init );
}

void broadcast_clock::http_server::
start() {
  enqueue_simple_message( http_server_task_message::start );
}

void broadcast_clock::http_server::
stop() {
  enqueue_simple_message( http_server_task_message::stop );
}
