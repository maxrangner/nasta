#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system_manager.h"

extern "C" void app_main(void)
{
    system_manager sys_mgr;
    sys_mgr.init();
    while(1) {
        vTaskDelay(portMAX_DELAY);
    }
}
