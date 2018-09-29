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

cStatus status_inst;

cStatus::cStatus() {
    m_status.wifi_connected = false;
    m_status.temperature = 0;
    m_status.water_level = 0;
    m_status.pump_working = false;
    m_status_changed = true;
}
cStatus::~cStatus() {}

sStatus cStatus::get() { return m_status; }

void cStatus::set_wifi_connected(bool connected) {
    if (connected != m_status.wifi_connected) {
        m_status.wifi_connected = connected;
        m_status_changed = true;
    }
}

void cStatus::set_temperature(int temperature) {
    if (temperature != m_status.temperature) {
        m_status.temperature = temperature;
        m_status_changed = true;
    }
}

void cStatus::set_water_level(int water_level) {
    if (water_level != m_status.water_level) {
        m_status.water_level = water_level;
        m_status_changed = true;
    }
}

void cStatus::set_pump_working(bool working) {
    if (working != m_status.pump_working) {
        m_status.pump_working = working;
        m_status_changed = true;
    }
}

void cStatus::set_last_water_time(RtcDateTime water_time) {
    if (water_time != m_status.last_water_time) {
        m_status.last_water_time = water_time;
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

void cStatus::set_ota_in_progress(bool ota_in_progress) {
  if (ota_in_progress != m_status.ota_in_progress) {
    m_status.ota_in_progress = ota_in_progress;
    m_status_changed = true;
  }
}

void cStatus::report_water_level() {
  LOG_INFO("Water level is %d cm", m_status.water_level);
}

bool cStatus::was_changed() { return m_status_changed; };
void cStatus::clean_changed() { m_status_changed = false; };

void status_set_wifi_connected(bool wifi_connected) { status_inst.set_wifi_connected(wifi_connected); };
void status_set_temperature(int temperature) { status_inst.set_temperature(temperature); };
void status_set_water_level(int water_level) { status_inst.set_water_level(water_level); };
void status_set_pump_working(bool working) { status_inst.set_pump_working(working); };
void status_set_last_water_time(RtcDateTime water_time) { status_inst.set_last_water_time(water_time); };
void status_set_ota_in_progress(bool ota_in_progress) {status_inst.set_ota_in_progress(ota_in_progress); };
void status_report_water_level() {status_inst.report_water_level();}
sStatus status_get() { return status_inst.get();};
bool status_was_changed() { return status_inst.was_changed(); };
void status_clear_changed() { status_inst.clean_changed(); };
