#include "wifi_interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "credentials.h"

WifiInterface::WifiInterface() {

}

void WifiInterface::init() {
    // Init phase
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    // Cfg phase
    esp_wifi_set_mode(WIFI_MODE_STA);
    wifi_config_t credentials = setCredentials();
    esp_wifi_set_config(WIFI_IF_STA, &credentials);
    esp_wifi_start();
    esp_wifi_connect();
}

wifi_config_t WifiInterface::setCredentials() {
    wifi_config_t credentials = {};
    memcpy(credentials.sta.ssid, SSID, strlen(SSID));
    memcpy(credentials.sta.password, PASSWORD, strlen(PASSWORD));
    return credentials;
}

void WifiInterface::setMode() {

}