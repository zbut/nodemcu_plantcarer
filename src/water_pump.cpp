//
//  water_pump.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#include "water_pump.hpp"
#include "config.hpp"
#include "arduino.h"
#include "logger.hpp"
#include "rtc_w_ntp.hpp"

cWaterPump::cWaterPump(): status(false)  {}
cWaterPump::~cWaterPump() {}

void cWaterPump::setup() {
    pinMode( PUMP_PIN, OUTPUT );
    digitalWrite( PUMP_PIN, 0 );
    status = false;
}

void cWaterPump::loop() {
    RtcDateTime now = GET_TIME();

}

void cWaterPump::turn_on() {
    LOG_INFO("Turning on pump");
    digitalWrite( PUMP_PIN, 1 );
    status = true;
}

void cWaterPump::turn_off() {
    LOG_INFO("Turning off pump");
    digitalWrite( PUMP_PIN, 0 );
    status = false;
}

bool cWaterPump::is_working() {
    return status;
}
