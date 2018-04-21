//
//  config.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#ifndef config_hpp
#define config_hpp

struct sConfigWifi {
    const char* ssid;
    const char* password;
    const int   connection_timout_sec;
};

struct sConfig {
    sConfigWifi wifi;
};

extern const sConfig CONFIG;

#define DHT_PIN 12 // D6
// Black is gnd and blue is vcc
#define HC_SR04_TRIG_PIN 2  //D4 - Green
#define HC_SR04_ECHO_PIN 14  //D5 - Yellow

#endif /* config_hpp */
