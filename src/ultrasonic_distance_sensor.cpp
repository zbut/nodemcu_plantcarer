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

// defines pins numbers

const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

// defines variables
long duration;
int distance;

cUltrasonicDistanceSensor::cUltrasonicDistanceSensor()  {}
cUltrasonicDistanceSensor::~cUltrasonicDistanceSensor() {}

void cUltrasonicDistanceSensor::setup() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void cUltrasonicDistanceSensor::loop() {
    get_distance();
}

int cUltrasonicDistanceSensor::get_distance() {
    LOG_INFO("Measuring distance");
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance= duration*0.034/2;
    LOG_INFO("Distance is %d cm", distance);
    return distance;
}
