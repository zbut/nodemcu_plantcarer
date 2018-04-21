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

cLcd::cLcd()  {}
cLcd::~cLcd() {}

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2);

void cLcd::setup() {
    LOG_INFO("Starting lcd display");
    lcd_i2c.begin(4,5);
    // Turn on the backlight.
    lcd_i2c.backlight();
}

void cLcd::loop() {}

void cLcd::print_line(const char* line) {
    lcd_i2c.setCursor(0, 0);
    lcd_i2c.print(line);
}
