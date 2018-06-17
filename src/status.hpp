//
//  status.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#ifndef status_hpp
#define status_hpp

#include <arduino.h>
#include "RtcDateTime.h"

enum eWaterLevel { WaterLevelHigh, WaterLevelMedium, WaterLevelLow, WaterLevelNone };

struct sStatus {
    bool wifi_connected;
    int temperature;
    int water_level;
    bool pump_working;
    RtcDateTime last_water_time;
    bool ota_in_progress;

    inline void set_null() {wifi_connected = false; temperature = -1; water_level = -1; pump_working = false;};
    eWaterLevel get_water_level_enum();
};

class cStatus {
private:

public:
    sStatus m_status;
    bool    m_status_changed;

    cStatus();
    ~cStatus();

    sStatus get();

    void set_wifi_connected(bool connected);
    void set_temperature(int temperature);
    void set_water_level(int water_level);
    void set_pump_working(bool working);
    void set_last_water_time(RtcDateTime water_time);
    void set_ota_in_progress(bool ota_in_progress);
    void report_water_level();
    bool was_changed();
    void clean_changed();
protected:

};

extern cStatus status_inst;

void status_set_wifi_connected(bool wifi_connected);
void status_set_temperature(int temperature);
void status_set_water_level(int water_level);
void status_set_pump_working(bool working);
void status_set_last_water_time(RtcDateTime water_time);
void status_set_ota_in_progress(bool ota_in_progress);
void status_report_water_level();
sStatus status_get();
bool status_was_changed();
void status_clear_changed();

#endif /* status_hpp */
