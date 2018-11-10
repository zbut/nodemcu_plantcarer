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
public:
    sStatus();
    ~sStatus();
    bool wifi_connected;
    int temperature;
    int water_level;
    bool pump_working;
    RtcDateTime last_water_time;
    bool ota_in_progress;
    String last_error;
    inline void set_null() {wifi_connected = false; temperature = -1; water_level = -1; pump_working = false;};
    eWaterLevel get_water_level_enum();

    void set_wifi_connected(bool connected);
    void set_temperature(int temperature);
    void set_water_level(int water_level);
    void set_pump_working(bool working);
    void set_last_water_time(RtcDateTime water_time);
    void set_ota_in_progress(bool ota_in_progress);
    void set_last_error(const char* error_line);
    void report_water_level();
    bool was_changed();
    void clean_changed();

  protected:
    bool    m_status_changed;
};

extern sStatus STAT;

#endif /* status_hpp */
