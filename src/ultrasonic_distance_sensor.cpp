//
//  ultrasonic_distance_sensor.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 18/04/2018.
//
//

#include "ultrasonic_distance_sensor.hpp"
#include "arduino.h"
#include "logger.hpp"
#include "status.hpp"
#include "config.hpp"

// defines variables
long duration;
int distance;

cUltrasonicDistanceSensor::cUltrasonicDistanceSensor()  {}
cUltrasonicDistanceSensor::~cUltrasonicDistanceSensor() {}

void cUltrasonicDistanceSensor::setup() {
    pinMode(HC_SR04_TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
    pinMode(HC_SR04_ECHO_PIN, INPUT); // Sets the echoPin as an Input
    // Check it is working
    get_distance();
}

void cUltrasonicDistanceSensor::loop() {
    get_distance();
}

int cUltrasonicDistanceSensor::get_distance() {
    // Clears the trigPin
    digitalWrite(HC_SR04_TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(HC_SR04_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(HC_SR04_TRIG_PIN, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(HC_SR04_ECHO_PIN, HIGH);

    // Calculating the distance
    distance= duration*0.034/2;
    //LOG_INFO("Distance is %d cm", distance);
    STAT.set_water_level(distance);
    if (distance == 0) {
        LOG_ERROR("Distance sensor is not working");
    }
    return distance;
}
