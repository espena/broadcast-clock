#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

namespace espena::semaphores::mutex {

  SemaphoreHandle_t system_clock = xSemaphoreCreateMutex();
  SemaphoreHandle_t ssid_list = xSemaphoreCreateMutex();

} // namespace espena::semaphores::mutex