#ifndef __MUTEXES_H__
#define __MUTEXES_H__

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace espena::semaphores::mutex {

  extern SemaphoreHandle_t system_clock;
  extern SemaphoreHandle_t ssid_list;
  extern SemaphoreHandle_t http_port;

} // namespace espena::semaphores::mutex

#endif // __MUTEXES_H__