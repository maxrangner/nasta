#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_context.h"
#include "message_types.h"

// SystemManager owns app-facing state and system-side behavior.
class SystemManager {
    TaskHandle_t task_system_manager_ = nullptr;
    QueueHandle_t system_in_queue_ = nullptr;
    static constexpr uint32_t kUpdateInterval_ = 100;
    NetworkSnapshot network_state_ {};
    SystemState system_state_ = SystemState::BOOT;
    RenderState render_state_ {};
    uint8_t selected_direction_ = 1;
public:
    SystemManager(Queues* queues);
    void init();
    static void systemTask(void* pvParameters);
    void setState(SystemState new_state);
    void updateSystemState();
    void updateRenderState();
    const RenderState& getRenderState() const;
};
