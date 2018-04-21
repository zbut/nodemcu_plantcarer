//
//  wifi.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 11/04/2018.
//
//

#include "wifi.hpp"
#include <ESP8266WiFi.h>
#include "logger.hpp"
#include "status.hpp"
#include "config.hpp"

cWifi::cWifi(): connected(false)  {}
cWifi::~cWifi() {}

void cWifi::setup() {
    LOG_INFO("Wifi setup");
    WiFi.mode(WIFI_STA);
    WiFi.begin(CONFIG.wifi.ssid, CONFIG.wifi.password);
    unsigned long cur_time_sec = millis();
    while ((millis() - cur_time_sec) < (CONFIG.wifi.connection_timout_sec * 1000)) {
        if (WiFi.status() != WL_CONNECTED) {
            delay(500);
        } else {
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED) {
        String ipaddress = WiFi.localIP().toString();
        LOG_INFO("Wifi connected with IP address %s", ipaddress.c_str());
        connected = true;
    } else {
        LOG_ERROR("Could not connect to %s", CONFIG.wifi.ssid);
        connected = false;
    }
    status_set_wifi_connected(connected);
}

void cWifi::loop() {
    if (connected && (WiFi.status() != WL_CONNECTED)) {
        connected = false;
        LOG_ERROR("Wifi connection lost");
    }
    if (!connected && (WiFi.status() == WL_CONNECTED)) {
        connected = true;
        LOG_INFO("Wifi reconnected");
    }
    status_set_wifi_connected(connected);
};
