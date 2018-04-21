//
//  ntp.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 11/04/2018.
//
//

#ifndef ntp_hpp
#define ntp_hpp

#include <device.hpp>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

struct sTime {
   unsigned int hours;
   unsigned int minutes;
   unsigned int seconds;
   bool is_up_time;
};

class cRtcWNtp : public cDevice {
private:
    bool m_time_ready;
public:
    cRtcWNtp();
    ~cRtcWNtp();

    void setup() override;
    void loop() override;

    void get_time(sTime* time_struct);

    void disable_get_time();
    void enable_get_time();
protected:

};

extern cRtcWNtp rtc_w_ntp_inst;

#define GET_TIME(time_struct) rtc_w_ntp_inst.get_time(time_struct)
#define SETUP_TIME() rtc_w_ntp_inst.setup()

#endif /* ntp_hpp */
