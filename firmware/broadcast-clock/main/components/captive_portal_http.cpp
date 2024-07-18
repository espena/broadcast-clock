#include <memory.h>
#include <string>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_http_server.h"

#include "captive_portal_http.hpp"
#include "configuration.hpp"

using namespace espena;

const char *broadcast_clock::captive_portal_http::m_component_name = "captive_portal_http";
const esp_event_base_t broadcast_clock::captive_portal_http::m_event_base = "CAPTIVE_PORTAL_HTTP_EVENT";

broadcast_clock::captive_portal_http::captive_portal_http() : m_message_queue( nullptr ),
                                                              m_server( nullptr )
{    
  m_cfg.uri_match_fn = httpd_uri_match_wildcard;
  m_cfg.lru_purge_enable = true;
  m_message_queue = xQueueCreate( 50, sizeof( captive_portal_http_task_queue_item ) );
  m_task_params.instance = this;

  m_task_params.stack_buffer = ( StackType_t * ) heap_caps_malloc( m_component_stack_size,
                                                                   MALLOC_CAP_SPIRAM );

  xTaskCreateStatic( &broadcast_clock::captive_portal_http::task_loop,
                     m_component_name,
                     m_component_stack_size,
                     &m_task_params,
                     22,
                     m_task_params.stack_buffer,
                     &m_task_params.task_buffer ); 

}

void broadcast_clock::captive_portal_http::enqueue_simple_message( captive_portal_http_task_message msg ) {
  captive_portal_http_task_queue_item item = { msg, nullptr };
  xQueueSend( m_message_queue, &item, 10 );
}

void broadcast_clock::captive_portal_http::task_loop( void *arg ) {
  captive_portal_http_task_params *params = static_cast<captive_portal_http_task_params *>( arg );
  captive_portal_http *inst = params->instance;
  captive_portal_http_task_queue_item item;
  memset( &item, 0x00, sizeof( captive_portal_http_task_queue_item ) );
  while( 1 ) {
    if( xQueueReceive( inst->m_message_queue, &item, 10 ) ) {
      inst->on_message( item.message, item.arg );
    }
  }
}

esp_err_t broadcast_clock::captive_portal_http::
request_handler( httpd_req_t *req ) {
  captive_portal_http *inst = static_cast<captive_portal_http *>( req->user_ctx );
  return inst->on_request( req );
}

void broadcast_clock::captive_portal_http::
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
      httpd_resp_send( req, html.c_str(), html.length() );
    }
    else { // AP mode, exit from configuration
      httpd_resp_send( req, buf_ex, buf_ex_len );
    }
}

void broadcast_clock::captive_portal_http::
timers_handler( httpd_req_t *req ) {

  esp_event_post_to( m_event_loop_handle,
                      m_event_base,
                      EVENT_ENTER_TIMERS,
                      "",
                      0,
                      portMAX_DELAY );

  const char *buf_sw = ( char * ) broadcast_clock::resources::html::timers_page_html_start;
  const size_t buf_sw_len = broadcast_clock::resources::html::timers_page_html_end - broadcast_clock::resources::html::timers_page_html_start;
  httpd_resp_send( req, buf_sw, buf_sw_len );
}

void broadcast_clock::captive_portal_http::
stopwatch_handler( httpd_req_t *req ) {

  httpd_resp_send( req, "OK", 3 );
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

esp_err_t broadcast_clock::captive_portal_http::
on_request( httpd_req_t *req ) {

  const size_t req_hdr_host_len = httpd_req_get_hdr_value_len( req, "Host" );
  std::string hostname;
  hostname.resize( req_hdr_host_len + 1 );

  httpd_req_get_hdr_value_str( req, "Host", &hostname[ 0 ], req_hdr_host_len + 1 );

  ESP_LOGI( m_component_name, "Request for %s", req->uri );

  std::string uri( req->uri );

  if( uri == "/save" && req->content_len > 0 && m_event_loop_handle ) {
    httpd_resp_set_status( req, "302 Found" ); 
    httpd_resp_set_type( req, "text/html; charset=is08859-1;" );
    save_handler( req );
  }
  else if( uri == "/timers" && m_event_loop_handle ) {
    httpd_resp_set_status( req, "302 Found" ); 
    httpd_resp_set_type( req, "text/html; charset=is08859-1;" );
    timers_handler( req );
  }
  else if( uri.starts_with( "/stopwatch/start" ) ||
           uri.starts_with( "/stopwatch/stop" ) ||
           uri.starts_with( "/stopwatch/reset" ) ) {
    httpd_resp_set_status( req, "302 Found" ); 
    httpd_resp_set_type( req, "text/html; charset=is08859-1;" );
    stopwatch_handler( req );
  }
  else if( uri == "/styles.css" ) {
    httpd_resp_set_status( req, "302 Found" ); 
    httpd_resp_set_type( req, "text/css; charset=is08859-1;" );
    const char *buf_st = ( char * ) broadcast_clock::resources::html::styles_css_start;
    const size_t buf_st_len = broadcast_clock::resources::html::styles_css_end - broadcast_clock::resources::html::styles_css_start;
    httpd_resp_send( req, buf_st, buf_st_len );
  }
  else {
    std::string html = create_html_response();
    httpd_resp_send( req, html.c_str(), html.length() );
  }
  return ESP_OK;
}

void broadcast_clock::captive_portal_http::on_message( captive_portal_http_task_message msg, void *arg ) {
  switch( msg ) {
    case captive_portal_http_task_message::set_network_list:
      m_json_network_list = static_cast<char *>( arg );
      free( arg );
      break;
    case captive_portal_http_task_message::init:
      init_sync();
      break;
    case captive_portal_http_task_message::start:
      start_sync();
      break;
    case captive_portal_http_task_message::stop:
      stop_sync();
      break;
  }
}

void broadcast_clock::captive_portal_http::init_sync() {

}

void broadcast_clock::captive_portal_http::start_sync() {

  stop_sync(); // Assert server is not running

  if( httpd_start( &m_server, &m_cfg ) != ESP_OK ) {
    ESP_LOGE( m_component_name, "Failed to start HTTP server" );
    return;
  }

  httpd_uri_t location;

  location.uri = "/timers",
  location.handler = request_handler,
  location.user_ctx = this;
  location.method = HTTP_POST,

  location.uri = "/save",
  location.handler = request_handler,
  location.user_ctx = this;
  location.method = HTTP_POST,

  httpd_register_uri_handler( m_server, &location );

  location.uri = "/*",
  location.method = HTTP_GET,
  location.handler = request_handler,
  location.user_ctx = this;

  httpd_register_uri_handler( m_server, &location );

  ESP_LOGI( m_component_name, "HTTP server running" );
  
}

std::string broadcast_clock::captive_portal_http::create_html_response() {

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
          htm += cnf->get_str( tag ) == sel ? ( ele == "option" ? "selected" : "checked" ) : "";
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

void broadcast_clock::captive_portal_http::stop_sync() {
  if( m_server ) {
    httpd_stop( m_server );
    m_server = nullptr;
    ESP_LOGI( m_component_name, "HTTP server stopped" );
  }
}

void broadcast_clock::captive_portal_http::set_network_list( char *json ) {
  captive_portal_http_task_queue_item item;
  item.message = captive_portal_http_task_message::set_network_list;
  item.arg = strdup( json );
  xQueueSend( m_message_queue, &item, 10 );  
}

void broadcast_clock::captive_portal_http::init() {
  enqueue_simple_message( captive_portal_http_task_message::init );
}

void broadcast_clock::captive_portal_http::start() {
  enqueue_simple_message( captive_portal_http_task_message::start );
}

void broadcast_clock::captive_portal_http::stop() {
  enqueue_simple_message( captive_portal_http_task_message::stop );
}
