idf_component_register(
    SRCS "network_manager.cpp"
    INCLUDE_DIRS "."
    REQUIRES common wifi_interface esp_http_client esp-tls cjson
)