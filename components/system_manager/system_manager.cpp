#include "system_manager.h"
#include "esp_log.h"

static const char *TAG = "system manager";

SystemManager::SystemManager(Queues* queues)
    : system_in_queue_(queues->system_in_queue) {
}

void SystemManager::init() {
    if (task_system_manager_ != nullptr) {
        return;
    }

    ESP_LOGI(TAG, "State -> %d", static_cast<int>(system_state_));

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

void SystemManager::setState(SystemState new_state) {
    if (system_state_ == new_state) {
        return;
    }

    system_state_ = new_state;
    ESP_LOGI(TAG, "State -> %d", static_cast<int>(system_state_));
}

void SystemManager::updateSystemState() {
    SystemState new_state = system_state_;

    switch (network_state_.connectivity) {
        case NetworkStatus::DISCONNECTED:
            new_state = SystemState::NO_CONNECTION;
            break;

        case NetworkStatus::CONNECTING:
            new_state = SystemState::CONNECTING;
            break;

        case NetworkStatus::SETUP:
            new_state = SystemState::SETUP;
            break;

        case NetworkStatus::NETWORK_ERROR:
            new_state = SystemState::NETWORK_ERROR;
            break;

        case NetworkStatus::CONNECTED:
            break;
    }

    if (network_state_.connectivity == NetworkStatus::CONNECTED) {
        switch (network_state_.fetch_status) {
            case FetchStatus::IDLE:
                new_state = SystemState::CONNECTED;
                break;

            case FetchStatus::FRESH:
                if (totalDepartureCount(network_state_.departures) == 0) {
                    new_state = SystemState::NO_DEPARTURES;
                    break;
                }

                new_state = SystemState::DEPARTURES;
                break;

            case FetchStatus::STALE:
                if (totalDepartureCount(network_state_.departures) == 0) {
                    new_state = SystemState::API_ERROR;
                    break;
                }

                new_state = SystemState::DEPARTURES;
                break;

            case FetchStatus::API_ERROR:
                new_state = SystemState::API_ERROR;
                break;
        }
    }

    setState(new_state);
}

void SystemManager::updateRenderState() {
    render_state_.system_state = system_state_;
    render_state_.selected_direction = selected_direction_;
    render_state_.stale_data = network_state_.fetch_status == FetchStatus::STALE;
    render_state_.active_departures = {};

    if (selected_direction_ < 1 ||
        selected_direction_ > kMaxDepartureDirections) {
        return;
    }

    if (system_state_ != SystemState::DEPARTURES &&
        system_state_ != SystemState::NO_DEPARTURES) {
        return;
    }

    render_state_.active_departures =
        network_state_.departures.directions[selected_direction_ - 1];
}

const RenderState& SystemManager::getRenderState() const {
    return render_state_;
}

void SystemManager::systemTask(void* pvParameters) {
    auto* self = static_cast<SystemManager*>(pvParameters);

    while(true) {
        if (xQueueReceive(self->system_in_queue_, &self->network_state_, pdMS_TO_TICKS(self->kUpdateInterval_))) {
            self->updateSystemState();
            self->updateRenderState();
        }
    }
}
