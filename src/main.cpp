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
#include "ultrasonic_distance_sensor.hpp"
#include "web_server.hpp"
#include "lcd.hpp"
#include "water_pump.hpp"
#include "ota_update.hpp"
#include "thingspeak.hpp"
#include "status.hpp"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

cWifi wifi;
cUltrasonicDistanceSensor hc_sr04;
cWebServer web_server;
cLcd lcd;
cWaterPump water_pump;
cOtaUpdate ota_update;
cThingspeak thingspeak;

void setup()
{
    LOG_INFO("Starting setup..");
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.setup();
  lcd.print_line("Initializing..");
  wifi.setup();
  SETUP_TIME();
  hc_sr04.setup();
  web_server.setup();
  water_pump.setup();
  ota_update.setup();
  thingspeak.setup();
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for 1 seconds
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for 1 seconds
  delay(1000);

  wifi.loop();
  LOOP_TIME();
  hc_sr04.loop();
  web_server.loop();
  water_pump.loop();
  ota_update.loop();
  thingspeak.loop();
  lcd.loop();
  STAT.clean_changed();
}
