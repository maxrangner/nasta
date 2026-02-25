#pragma once
#include "freertos/FreeRTOS.h"

enum class SystemState 
{
    BOOT, // 0
    NOT_CONNECTED, // 1
    CONNECTED, // 2
    SETUP, // 3
    ERROR
};

class SystemManager 
{
    TaskHandle_t task_system_manager_ = nullptr;
    QueueHandle_t queue_data_ = nullptr;
    static constexpr uint32_t k_system_manager_update = 100;
public:
    SystemManager();
    static void systemTask(void* pvParameters);
};