idf_component_register(
    SRCS "test_main.cpp" "utils_test.cpp" "settings_test.cpp" "settings_storage_test.cpp"
    INCLUDE_DIRS "."
    REQUIRES unity common nvs_flash
)
