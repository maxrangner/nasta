#include "system_manager.h"
#include "esp_log.h"
#include "types.h"
#include "credentials.h"

static const char *TAG = "system manager";

SystemManager::SystemManager(Queues* queues)
    : system_in_queue_(queues->system_in_queue),
      network_in_queue_(queues->network_in_queue) {
}

void SystemManager::init() {
    if (task_system_manager_ != nullptr) {
        return;
    }

    xTaskCreatePinnedToCore(     // UI Task
        systemTask,                // Function to implement the task
        "systemTask",              // Name of the task
        8192,                      // Stack size in words
        this,                      // Task input parameter
        2,                         // Priority of the task
        &task_system_manager_,     // Task handle.
        0                          // Core where the task should run
    );
}

void SystemManager::systemTask(void* pvParameters) {
    auto* self = static_cast<SystemManager*>(pvParameters);

    while(true) {
        if (xQueueReceive(self->system_in_queue_, &self->packet_, pdMS_TO_TICKS(self->kUpdateInterval_))) {
            if (self->packet_.type == SystemPacketType::NETWORK_STATUS) {
                ESP_LOGI(TAG, "Packet - NETWORK_STATUS: %d", static_cast<int>(self->packet_.network_status));
            }

            if (self->packet_.type == SystemPacketType::DEPARTURES_DATA) {
                ESP_LOGI(TAG, "Packet - DEPARTURES_DATA");
            }
        }
    }
}
