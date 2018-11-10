//
//  thingspeak.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 09/11/2018.
//
//

#include "thingspeak.hpp"
#include <WiFiClientSecure.h>
#include "logger.hpp"
#include "config.hpp"
#include "status.hpp"

cThingspeak::cThingspeak()  {}
cThingspeak::~cThingspeak() {}

void cThingspeak::setup() {

}

void cThingspeak::loop() {
  push_status();
}

void cThingspeak::push_status() {
  WiFiClientSecure client;
  if (!STAT.wifi_connected) {
    LOG_WARNING("Did not push to thingspeak due to no wifi connection");
    return;
  }
  if ( client.connect( CONFIG.thingspeak.host, 443 ) == false ) {
    LOG_WARNING("Cannot connect '%s'", CONFIG.thingspeak.host );
    return;
  }

  if (STAT.was_changed()) {
    // cbuffer "https://api.thingspeak.com/update?api_key=<api key>&field1=0&field2=12"
    String data_to_send = "GET /update?api_key=" + String(CONFIG.thingspeak.api_key);
    data_to_send += "&field1=" + String(CONFIG.water_level.tank_hight_cm - STAT.water_level);
    data_to_send += "&field2=" + String(STAT.pump_working);
    data_to_send += "&field2=" + String(STAT.temperature);
    if (STAT.last_error != "") {
      data_to_send += "&status=" + STAT.last_error;
    }
    data_to_send += " HTTP/1.1\r\nHost: " + String(CONFIG.thingspeak.host) + "\r\nConnection: close\r\n\r\n";
    client.write((const uint8_t *)data_to_send.c_str(), data_to_send.length());
    client.stop();
  }
}
