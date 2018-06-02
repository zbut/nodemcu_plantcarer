#include "serial.hpp"
#include "Arduino.h"

cSerial::cSerial() {
    Serial.begin(115200);
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
