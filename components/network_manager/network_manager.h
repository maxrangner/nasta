#pragma once
#include "freertos/FreeRTOS.h"

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
    static constexpr uint32_t k_network_manager_update = 100;
public:
    NetworkManager();
    static void networkTask(void* pvParameters);
};