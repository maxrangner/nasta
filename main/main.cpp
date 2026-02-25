#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system_manager.h"
#include "network_manager.h"

extern "C" void app_main(void)
{
    SystemManager system_manager;
    NetworkManager network_manager;

    while(1) {
        vTaskDelay(portMAX_DELAY);
    }
}
