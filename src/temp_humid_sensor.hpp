//
//  temp_humid_sensor.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 15/04/2018.
//
//

#ifndef temp_humid_sensor_hpp
#define temp_humid_sensor_hpp

#include "device.hpp"

class cTempHumidSensor : public cDevice{
private:
public:
    cTempHumidSensor();
    ~cTempHumidSensor();

    void setup() override;
    void loop() override;
protected:

};


#endif /* temp_humid_sensor_hpp */
