//
//  lcd.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#include "lcd.hpp"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "logger.hpp"
#include "status.hpp"

cLcd::cLcd()  {}
cLcd::~cLcd() {}

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2);

void cLcd::setup() {
    LOG_INFO("Starting lcd display");
    lcd_i2c.begin(4,5);
    // Turn on the backlight.
    lcd_i2c.backlight();
}

void cLcd::loop() {
    print_status();
}

void cLcd::print_line(const char* line) {
    lcd_i2c.setCursor(0, 0);
    lcd_i2c.print(line);
}

void cLcd::print_status(bool force) {
    if (STAT.was_changed() || force) {
        lcd_i2c.clear();
        lcd_i2c.print("Wifi:");
        bool wifi = STAT.wifi_connected;
        if (wifi) {
            lcd_i2c.print("O.K.");
        }
        else {
            lcd_i2c.print("N/A");
        }
        lcd_i2c.setCursor(0, 1);
        char status_line[16];
        snprintf( status_line , 16, "WL:%02i LW:%02u:%02u", STAT.water_level, STAT.last_water_time.Day(), STAT.last_water_time.Month() );
        lcd_i2c.print(status_line);
    }
}
