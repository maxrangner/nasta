#include "system_manager.h"

SystemManager::SystemManager() {
    xTaskCreatePinnedToCore(     // UI Task
      systemTask,                // Function to implement the task
      "systemTask",            // Name of the task
      8192,                      // Stack size in words
      this,                      // Task input parameter
      2,                         // Priority of the task
      &task_system_manager_,     // Task handle.
      0                          // Core where the task should run
    ); 
}


void SystemManager::systemTask(void* pvParameters) {
    uint32_t counter = 0;
    while(true) {
        printf("System: %ld\n", counter++);
        if (counter % 50 == 0) {
            vTaskDelay(pdMS_TO_TICKS(k_system_manager_update));
        }
    }
}