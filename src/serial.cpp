#include "serial.hpp"
#include "Arduino.h"

cSerial::cSerial() {
    Serial.begin(9600);
    Serial.println("---------------------------------");
    Serial.println("      Welcome to plantcarer      ");
    Serial.println("---------------------------------");
}

cSerial::~cSerial() {
    //Serial.end();
}

int cSerial::println(const char * line) {
    return Serial.println(line);
}
