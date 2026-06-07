#include "settings_storage.h"
#include "nvs_flash.h"
#include "unity.h"
#include <string.h>

TEST_CASE("saveDeviceSettings and loadDeviceSettings keep the same values", "[settings_storage][integration]")
{
    TEST_ASSERT_EQUAL(ESP_OK, nvs_flash_init());

    DeviceSettings saved {};
    strcpy(saved.wifi.ssid, "TestWifi");
    strcpy(saved.wifi.password, "secret123");
    saved.site.site_id = 1234;
    saved.site.transport_filter = TransportMode::BUS;
    saved.startup_direction = 2;
    saved.setup.needs_setup = false;

    TEST_ASSERT_TRUE(saveDeviceSettings(saved));

    DeviceSettings loaded {};
    TEST_ASSERT_TRUE(loadDeviceSettings(&loaded));

    TEST_ASSERT_EQUAL_STRING(saved.wifi.ssid, loaded.wifi.ssid);
    TEST_ASSERT_EQUAL_STRING(saved.wifi.password, loaded.wifi.password);
    TEST_ASSERT_EQUAL(saved.site.site_id, loaded.site.site_id);
    TEST_ASSERT_EQUAL(saved.site.transport_filter, loaded.site.transport_filter);
    TEST_ASSERT_EQUAL(saved.startup_direction, loaded.startup_direction);
    TEST_ASSERT_EQUAL(saved.setup.needs_setup, loaded.setup.needs_setup);
}
