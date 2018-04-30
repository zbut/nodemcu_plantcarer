//
//  water_pump.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#ifndef water_pump_hpp
#define water_pump_hpp

#include <device.hpp>

class cWaterPump : cDevice {
private:
public:
    cWaterPump();
    ~cWaterPump();

    void setup() override;
    void loop() override;
    void turn_on();
    void turn_off();
protected:

};


#endif /* water_pump_hpp */
