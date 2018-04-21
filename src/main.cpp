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
#include "ultrasonic_distance_sensor.hpp"
#include "web_server.hpp"
#include "lcd.hpp"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

cWifi wifi;
cTempHumidSensor dht22;
cUltrasonicDistanceSensor hc_sr04;
cWebServer web_server;
cLcd lcd;

void setup()
{
    LOG_INFO("Starting setup..");
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.setup();
  lcd.print_line("Initializing..");
  wifi.setup();
  SETUP_TIME();
  dht22.setup();
  hc_sr04.setup();
  web_server.setup();
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
  // dht22.loop();
  // hc_sr04.loop();
  web_server.loop();
  lcd.loop();
}
