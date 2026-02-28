#pragma once
#include "freertos/FreeRTOS.h"
#include "types.h"

struct Departure {
    TimeDisplayType time_display;
    TransportMode transport;
    uint8_t direction;
    uint8_t line;
    uint8_t min_to_departure;
    char clock_next_departure[6];
};

struct DeparturesPacket {
    Departure departures[3];
    uint8_t num_departures;
};

struct SettingsPacket {
    TransportMode setting_transport_mode;
    uint8_t setting_direction_code;
    char setting_ssid[30];
    char setting_password[30];
};

enum class NetworkEvent{
    STARTED,
    CONNECTED,
    DISCONNECTED,
    RETRY_TIMER,
    ERROR
};
