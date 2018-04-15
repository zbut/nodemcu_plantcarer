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

cWifi::cWifi(): connected(false)  {}
cWifi::~cWifi() {}

void cWifi::setup() {
    LOG_INFO("Wifi setup");
    char ssid[] = "XperiaMoran";  //  your network SSID (name)
    char pass[] = "0535316191";       // your network password
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    for (int i=0; i < 100; i++) {
        if (WiFi.status() != WL_CONNECTED) {
            delay(500);
        } else {
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED) {
        String ipaddress = WiFi.localIP().toString();
        LOG_INFO("Wifi connected with IP address %s", ipaddress.c_str());
    } else {
        LOG_ERROR("Could not connect to %s", ssid);
        return;
    }
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
};
