#pragma once

#include <stdint.h>
#include "message_types.h"

enum class DisplayAnimation : uint8_t {
    NONE,
    BOOT,
    CONNECTING,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};

struct DisplayState {
    SystemState system_state = SystemState::BOOT;
    uint8_t active_direction = 1;
    bool has_departure_for_active_direction = false;
    char departure_text[sizeof(Departure {}.display)] = {};
};

void displayInit();
void displaySetState(const DisplayState& display_state);
void displayPlayAnimation(DisplayAnimation animation);
void displayUpdate();
