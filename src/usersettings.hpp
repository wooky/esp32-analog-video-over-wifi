#pragma once

struct UserSettings
{
    const char *wifi_ssid;
    const char *wifi_pass;

    char scl_pin;
    char sda_pin;

    int dclk_pin;
    int enable_pin;
    int hsync_pin;
    int vsync_pin;
    int d7_pin;
    int d6_pin;
    int d5_pin;
    int d4_pin;
    int d3_pin;
    int d2_pin;
    int d1_pin;
    int d0_pin;
};
