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
#include "RtcDateTime.h"

class cRtcWNtp : public cDevice {
private:
public:
    cRtcWNtp();
    ~cRtcWNtp();

    void setup() override;
    void loop() override;

    RtcDateTime get_time();
protected:

};

extern cRtcWNtp rtc_w_ntp_inst;

#define GET_TIME(time_struct) rtc_w_ntp_inst.get_time(time_struct)
#define SETUP_TIME() rtc_w_ntp_inst.setup()
#define LOOP_TIME() rtc_w_ntp_inst.loop()

struct sTimer {
public:
  sTimer();
  ~sTimer();

  void set_alarm_on(uint8_t alarm_num);
  void set_alarm_off(uint8_t alarm_num);
  bool is_alarm_on(uint8_t alarm_num) const;
protected:
  std::vector<bool> alarms;
};

extern sTimer TIMER;

#define ONCE_PER_DAY_ALARM 0
#define LOOP_ALARM 1

#endif /* ntp_hpp */
