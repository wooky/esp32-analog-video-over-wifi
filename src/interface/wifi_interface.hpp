#pragma once

#include "../usersettings.hpp"
#include <WiFi.h>

class WifiInterface
{
public:
    WifiInterface(const UserSettings& settings)
    : _settings(settings)
    {}

    void start()
    {
        WiFi.begin(_settings.wifi_ssid, _settings.wifi_pass);
    }

private:
    const UserSettings& _settings;
};
