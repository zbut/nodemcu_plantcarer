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
#include "status.hpp"

cWaterPump::cWaterPump() {}
cWaterPump::~cWaterPump() {}

void cWaterPump::setup() {
    LOG_INFO("Starting water pump");
    pinMode( PUMP_PIN, OUTPUT );
    digitalWrite( PUMP_PIN, 0 );
    STAT.set_pump_working(false);
}

void cWaterPump::loop() {
    RtcDateTime now = GET_TIME();
    RtcDateTime today(now.Year(), now.Month(), now.Day(), 0, 0, 0);
    RtcDateTime today_active_start = today + CONFIG.pump_times.active_time_of_day_start.to_sec();
    RtcDateTime today_active_end   = today + CONFIG.pump_times.active_time_of_day_end.to_sec();
    // Check if in active hour
    bool active_time = (now > today_active_start) && (now < today_active_end);
    bool status = STAT.pump_working;
    // If not active time, turn off if needed
    if (!active_time) {
        if (status) {
            LOG_INFO("Entered inactive pump time");
            turn_off();
        }
        return;
    }
    if (STAT.ota_in_progress) {
      LOG_INFO("Turning off pump due to ota update");
      turn_off();
    }
    uint32_t total_period = CONFIG.pump_times.pump_on_period.to_sec() + CONFIG.pump_times.pump_off_period.to_sec();
    RtcDateTime time_from_active_start = now - today_active_start;
    uint32_t period_num = time_from_active_start.TotalSeconds() / total_period;
    uint32_t time_in_period = time_from_active_start.TotalSeconds() - period_num * total_period;
    // First part of the period is one
    bool should_be_on = time_in_period < CONFIG.pump_times.pump_on_period.to_sec();
    if (should_be_on && !status) {
        turn_on();
        STAT.set_last_water_time(now);
    } else {
        if (!should_be_on && status) {
            turn_off();
        } else {
          if (should_be_on && status && (STAT.get_water_level_enum() == WaterLevelNone)) {
            LOG_ERROR("Water level dropped below limit during on period");
            turn_off();
          }
        }
    }
}

void cWaterPump::turn_on() {
    if (STAT.get_water_level_enum() != WaterLevelNone) {
        LOG_INFO("Turning on pump");
        digitalWrite( PUMP_PIN, 1 );
        STAT.set_pump_working(true);
    } else {
        LOG_ERROR("Did not activate pump due to not enough water");
    }
    STAT.report_water_level();
}

void cWaterPump::turn_off() {
    LOG_INFO("Turning off pump");
    digitalWrite( PUMP_PIN, 0 );
    STAT.set_pump_working(false);
    STAT.report_water_level();
}
