/*
  Udp NTP Client
  Get the time from a Network Time Protocol (NTP) time server
  Demonstrates use of UDP sendPacket and ReceivePacket
  For more on NTP time servers and the messages needed to communicate with them,
  see http://en.wikipedia.org/wiki/Network_Time_Protocol
  created 4 Sep 2010
  by Michael Margolis
  modified 9 Apr 2012
  by Tom Igoe
  updated for the ESP8266 12 Apr 2015
  by Ivan Grokhotkov
  This code is in the public domain.
*/


#include "rtc_w_ntp.hpp"
#include "logger.hpp"
#include "status.hpp"
/* for normal hardware wire use below */
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
/* for normal hardware wire use above */
cRtcWNtp rtc_w_ntp_inst;


cRtcWNtp::cRtcWNtp() {};
cRtcWNtp::~cRtcWNtp() {};

// local port to listen for UDP packets
unsigned int localPort = 8885;
// time.nist.gov NTP server address
IPAddress timeServerIP;
// NTP Servers:
static const char ntpServerName[] = "us.pool.ntp.org";
//static const char ntpServerName[] = "time.nist.gov";
//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";

//const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)
const int timeZone = 3;  // Israel

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress& address) {
  LOG_INFO("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

time_t getNtpTime() {
  IPAddress ntpServerIP; // NTP server's ip address

  while (udp.parsePacket() > 0) ; // discard any previously received packets
  LOG_INFO("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      LOG_INFO("Receive NTP Response");
      udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * 60 * 60;
    }
  }
  LOG_ERROR("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

void set_time_from_ntp_if_needed() {
    if (!Rtc.IsDateTimeValid()) {
        // Common Cuases:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing
        LOG_WARNING("RTC lost confidence in the DateTime!");
        time_t ntp_time = getNtpTime();
        RtcDateTime rtc_date_time;
        rtc_date_time.InitWithEpoch32Time(ntp_time);
        LOG_INFO("Setting time to %d:%d:%d on %d/%d/%d", rtc_date_time.Hour(), rtc_date_time.Minute(), rtc_date_time.Second(), rtc_date_time.Day(), rtc_date_time.Month(), rtc_date_time.Year());
        Rtc.SetDateTime(rtc_date_time);
    }
}

void cRtcWNtp::setup() {
    LOG_INFO("Starting rtc");
    Rtc.Begin();
    LOG_INFO("Starting ntp");
    udp.begin(localPort);
    set_time_from_ntp_if_needed();
}

void cRtcWNtp::loop() {
    set_time_from_ntp_if_needed();
    RtcTemperature temp = Rtc.GetTemperature();
    int temp_int = 100 + int(temp.AsFloatDegC());
    status_set_temperature(temp_int);
}

RtcDateTime cRtcWNtp::get_time() {
    if (Rtc.IsDateTimeValid()) {
        return Rtc.GetDateTime();
    }
    RtcDateTime now;
    now.InitWithEpoch32Time(0);
    return now;
}
