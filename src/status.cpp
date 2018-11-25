//
//  status.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#include "status.hpp"
#include "config.hpp"
#include "logger.hpp"

sStatus STAT;

sStatus::sStatus() : wifi_connected(false),
                     temperature(0),
                     water_level(0),
                     pump_working(false),
                     last_error(""),
                     m_status_changed(false) {}


sStatus::~sStatus() {}

void sStatus::set_wifi_connected(bool connected) {
    if (connected != wifi_connected) {
        wifi_connected = connected;
        m_status_changed = true;
    }
}

void sStatus::set_temperature(int temperature) {
    if (this->temperature != temperature) {
        this->temperature = temperature;
        m_status_changed = true;
    }
}

void sStatus::set_water_level(int water_level) {
    if (this->water_level != water_level) {
        this->water_level = water_level;
        m_status_changed = true;
    }
}

void sStatus::set_pump_working(bool working) {
    if (working != this->pump_working) {
        this->pump_working = working;
        m_status_changed = true;
    }
}

void sStatus::set_last_water_time(RtcDateTime water_time) {
    if (water_time != this->last_water_time) {
        this->last_water_time = water_time;
        m_status_changed = true;
    }
}

eWaterLevel sStatus::get_water_level_enum() {
    if (CONFIG.water_level.tank_hight_cm < water_level) {
        LOG_ERROR("Water level %d is beyond tank hight %d", water_level, CONFIG.water_level.tank_hight_cm);
        return WaterLevelNone;
    }
    // Distance sensor not working properly
    if (water_level == 0) {
        return WaterLevelNone;
    }
    float water_ratio = float(CONFIG.water_level.tank_hight_cm - water_level) / CONFIG.water_level.tank_hight_cm;
    if (water_ratio > 0.6) return WaterLevelHigh;
    if (water_ratio > 0.4)  return WaterLevelMedium;
    if (water_ratio > 0.1) return WaterLevelLow;
    return WaterLevelNone;
}

void sStatus::set_ota_in_progress(bool ota_in_progress) {
  if (this->ota_in_progress != ota_in_progress) {
    this->ota_in_progress = ota_in_progress;
    m_status_changed = true;
  }
}

void sStatus::set_last_error(const char* error_line) {
  last_error = error_line;
  m_status_changed = true;
}

void sStatus::report_water_level() {
  LOG_INFO("Water level is %d cm", water_level);
}

bool sStatus::was_changed() { return m_status_changed; };
void sStatus::clean_changed() { m_status_changed = false; last_error = "";};
