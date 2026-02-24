#pragma once


enum class system_state 
{
    BOOT, // 0
    NO_WIFI, // 1
    NO_DATA, // 2
    NO_API_RESPONSE, // 3
    DATA, // 4
    SETUP,
    ERROR
};

class system_manager 
{
    public:
        void init();
};