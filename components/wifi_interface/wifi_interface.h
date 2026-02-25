#pragma once

#include "esp_wifi_types.h"


class WifiInterface {
    char ssid_[100];
    char password_[100];
public:
    WifiInterface();
    void init();
    wifi_config_t setCredentials();
    void setMode();
};