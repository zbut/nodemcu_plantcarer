//
//  ultrasonic_distance_sensor.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 18/04/2018.
//
//

#ifndef ultrasonic_distance_sensor_hpp
#define ultrasonic_distance_sensor_hpp

#include <device.hpp>

class cUltrasonicDistanceSensor : public cDevice {
private:
public:
    cUltrasonicDistanceSensor();
    ~cUltrasonicDistanceSensor();

    void setup() override;
    void loop() override;

    int get_distance();
protected:

};


#endif /* ultrasonic_distance_sensor_hpp */
