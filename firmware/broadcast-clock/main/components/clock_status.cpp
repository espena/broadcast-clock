#include "clock_status.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <esp_log.h>

using namespace espena::broadcast_clock;

void clock_status::
gnss_timepulse( bool ok ) {
  m_got_timepulse = ok;
  m_indicators->set_blue_indicator( is_blue() );
}

void clock_status::
gnss_time_sync( bool ok ) {
  m_got_time_sync = ok;
  m_indicators->set_blue_indicator( is_blue() );
}

void clock_status::
gnss_installed() {
  m_gnss_installed = true;
  m_indicators->set_blue_indicator( is_blue() );
}

void clock_status::
high_accuracy( bool ok ) {
  m_high_accuracy = ok;
  m_indicators->set_red_indicator( is_red() );
}

void clock_status::
sntp_sync( bool ok ) {
  m_sntp_sync = ok;
  m_indicators->set_green_indicator( is_green() );
}

void clock_status::
configurator_enabled( bool ok ) {
  m_configurator_enabled = ok;
  m_indicators->set_yellow_indicator( is_yellow() );
}