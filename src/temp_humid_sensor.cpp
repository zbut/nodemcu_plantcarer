//
//  temp_humid_sensor.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 15/04/2018.
//
//

#include "temp_humid_sensor.hpp"
#include "logger.hpp"

DHTesp dht;
const int dht_pin = 12; // D6

cTempHumidSensor::cTempHumidSensor()  {}
cTempHumidSensor::~cTempHumidSensor() {}

void cTempHumidSensor::setup() {
    LOG_INFO("Starting Temperature and humidity sensor");
    dht.setup(dht_pin, DHTesp::DHT22);
    // Check it is working
    get();
}

void cTempHumidSensor::loop() {

}

TempAndHumidity cTempHumidSensor::get() {
    LOG_INFO("Reading temperature and humidity");
    TempAndHumidity newValues = dht.getTempAndHumidity();
    // Check if any reads failed and exit early (to try again).
    if (dht.getStatus() != 0) {
        LOG_ERROR("DHT22 error status: %s", dht.getStatusString());
        return newValues;
    }
    return newValues;
    //LOG_INFO("Temperature is %d and humidty is %d", int(newValues.temperature), int(newValues.humidity));
}
