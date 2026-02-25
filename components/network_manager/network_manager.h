#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_context.h"

enum class NetworkState 
{
    INIT, // 0
    CONNECTING_STA,  // 1
    CONNECTED_STA, // 2
    DISCONNECTED, // 3
    ERROR // 4
};

class NetworkManager 
{
    TaskHandle_t task_network_manager_ = nullptr;
    QueueHandle_t queue_data_ = nullptr;
    QueueHandle_t queue_settings_ = nullptr;
    static constexpr uint32_t kUpdateInterval = 100;
    uint32_t counter_ = 0;
public:
    NetworkManager(Queues* queues);
    static void networkTask(void* pvParameters);
};