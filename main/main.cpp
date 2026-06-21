#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_context.h"
#include "display.h"
#include "system_manager.h"
#include "network_manager.h"
#include "message_types.h"
#include "system_init.h"

extern "C" void app_main(void)
{
    systemInit();

    static Queues queues = {
        .system_in_queue = xQueueCreate(kSystemQueueLength, sizeof(SystemEvent)),
        .network_in_queue = xQueueCreate(kNetworkQueueLength, sizeof(NetworkCommand)),
    };

    static Display display;
    static SystemManager system_manager(&queues, &display);
    static NetworkManager network_manager(&queues);
    
    display.init();
    network_manager.init();
    system_manager.init();
}
