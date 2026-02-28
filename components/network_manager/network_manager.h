#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "app_context.h"
#include "wifi_interface.h"
#include "message_types.h"

class NetworkManager {
    enum class NetworkState {
        INIT,
        CONNECTING_STA,
        CONNECTED_STA,
        DISCONNECTED,
        ERROR
    };
    NetworkState network_state = NetworkState::INIT;
    TaskHandle_t task_network_manager_ = nullptr;
    QueueHandle_t queue_data_ = nullptr;
    QueueHandle_t queue_settings_ = nullptr;
    QueueHandle_t wifi_event_queue_ = nullptr;
    WifiInterface wifi_interface_;
    TimerHandle_t wifi_reconnect_timer_;
    uint8_t reconnect_retires_ = 0;
    static constexpr uint32_t kUpdateInterval_ = 100;

    esp_http_client_config_t http_cfg_;
public:
    NetworkManager(Queues* queues);
    static void networkTask(void* pvParameters);
    NetworkState stateMachine(NetworkState curent_state, NetworkEvent event);
    void onStateChange(NetworkState state);
    static void reconnectTimerCallback(TimerHandle_t xTimer);
    void apiFetch(esp_http_client_config_t* cfg);
    void jsonParser(char* buffer);
};