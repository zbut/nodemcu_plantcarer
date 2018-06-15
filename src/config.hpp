//
//  config.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#ifndef config_hpp
#define config_hpp
#include "arduino.h"

struct sConfigWifi {
    const char* ssid;
    const char* password;
    const int   connection_timout_sec;
};

struct sPumpTime {
    const uint8_t day;
    const uint8_t hour;
    const uint8_t minute;
    const uint8_t second;

    inline uint32_t to_sec() const {return second + minute * 60 + hour * 60 * 60 + day * 24 *60 * 60;};
    inline bool operator < (const sPumpTime& other) {return to_sec() < other.to_sec();};
    inline bool operator > (const sPumpTime& other) {return to_sec() > other.to_sec();};
    inline bool operator <= (const sPumpTime& other) {return to_sec() <= other.to_sec();};
    inline bool operator >= (const sPumpTime& other) {return to_sec() >= other.to_sec();};
    inline bool operator == (const sPumpTime& other) {return to_sec() == other.to_sec();};
};

struct sConfigPumpTimes {
    // Time at which pump can be active
    const sPumpTime active_time_of_day_start;
    // Time at which pump stops being active
    const sPumpTime active_time_of_day_end;
    // Period for pump off during active time
    const sPumpTime pump_off_period;
    // Period for pump on during active time
    const sPumpTime pump_on_period;
};

struct sConfigWaterLevel {
    const int tank_hight_cm;
};

struct sConfigOtaUpdate {
    const char* ota_hostname;
    const char* ota_password;
};

struct sConfig {
    sConfigWifi wifi;
    sConfigPumpTimes pump_times;
    sConfigWaterLevel water_level;
    sConfigOtaUpdate ota;
};

extern const sConfig CONFIG;

#define DHT_PIN 12 // D6
// Black is gnd and blue is vcc
#define HC_SR04_TRIG_PIN 2  //D4 - Green
#define HC_SR04_ECHO_PIN 14  //D5 - Yellow
#define PUMP_PIN 13 // D7

#endif /* config_hpp */
