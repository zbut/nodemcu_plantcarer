/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "logger.hpp"
#include "wifi.hpp"
#include "rtc_w_ntp.hpp"
#include "temp_humid_sensor.hpp"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

cWifi wifi;
cTempHumidSensor dht22;

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  wifi.setup();
  SETUP_TIME();
  dht22.setup();
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(1000);

  wifi.loop();
  dht22.loop();
  
  LOG_INFO("Finished loop");
}
