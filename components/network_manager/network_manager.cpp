#include "network_manager.h"

NetworkManager::NetworkManager() {
    xTaskCreatePinnedToCore(     // UI Task
      networkTask,                // Function to implement the task
      "networkTask",            // Name of the task
      8192,                      // Stack size in words
      this,                      // Task input parameter
      1,                         // Priority of the task
      &task_network_manager_,     // Task handle.
      0                          // Core where the task should run
    ); 
}


void NetworkManager::networkTask(void* pvParameters) {
    uint32_t counter = 0;
    while(true) {
        printf("Network: %ld\n", counter++);
        vTaskDelay(pdMS_TO_TICKS(k_network_manager_update));
    }
}