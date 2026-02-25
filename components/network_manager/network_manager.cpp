#include "network_manager.h"

NetworkManager::NetworkManager(Queues* queues) {
    xTaskCreatePinnedToCore(     // UI Task
      networkTask,               // Function to implement the task
      "networkTask",             // Name of the task
      8192,                      // Stack size in words
      this,                      // Task input parameter
      1,                         // Priority of the task
      &task_network_manager_,    // Task handle.
      0                          // Core where the task should run
    );
    queue_data_ = queues->data_queue;
    queue_settings_ = queues->settings_queue;
}


void NetworkManager::networkTask(void* pvParameters) {
    auto* self = static_cast<NetworkManager*>(pvParameters);

    while(true) {
        printf("Network: %ld\n", self->counter_++);
        vTaskDelay(pdMS_TO_TICKS(NetworkManager::kUpdateInterval));
    }
}