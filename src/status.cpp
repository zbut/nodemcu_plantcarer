//
//  status.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#include "status.hpp"

cStatus status_inst;

cStatus::cStatus() {
    m_status.wifi_connected = false;
    m_status.temperature = 0;
    m_status.water_level = 0;
    m_status.pump_working = false;
    m_status_changed = true;
}
cStatus::~cStatus() {}

sStatus cStatus::get() { return m_status; };

void cStatus::set_wifi_connected(bool connected) {
    if (connected != m_status.wifi_connected) {
        m_status.wifi_connected = connected;
        m_status_changed = true;
    }
};

void cStatus::set_temperature(int temperature) {
    if (temperature != m_status.temperature) {
        m_status.temperature = temperature;
        m_status_changed = true;
    }
};

void cStatus::set_water_level(int water_level) {
    if (water_level != m_status.water_level) {
        m_status.water_level = water_level;
        m_status_changed = true;
    }
};

void cStatus::set_pump_working(bool working) {
    if (working != m_status.pump_working) {
        m_status.pump_working = working;
        m_status_changed = true;
    }
};

bool cStatus::was_changed() { return m_status_changed; };
void cStatus::clean_changed() { m_status_changed = false; };

void status_set_wifi_connected(bool wifi_connected) { status_inst.set_wifi_connected(wifi_connected); };
void status_set_temperature(int temperature) { status_inst.set_temperature(temperature); };
void status_set_water_level(int water_level) { status_inst.set_water_level(water_level); };
void status_set_pump_working(bool working) { status_inst.set_pump_working(working); };
sStatus status_get() { return status_inst.get();};
bool status_was_changed() { return status_inst.was_changed(); };
void status_clear_changed() { status_inst.clean_changed(); };
