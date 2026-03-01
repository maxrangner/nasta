#pragma once
#include "freertos/FreeRTOS.h"
#include "wifi_interface.h"
#include "types.h"

enum class PacketType {
    WIFI_EVENT,
    WIFI_UPDATE,
    NETWORK_EVENT,
    API_DATA,
    SETTINGS_DATA
};

struct DataPacket {
    PacketType type;
    WifiInterface::WifiState network_event;
};

struct Departure {
    TimeDisplayType time_display;
    TransportMode transport;
    uint8_t direction;
    uint8_t line;
    uint8_t min_to_departure;
    char clock_next_departure[6];
};
