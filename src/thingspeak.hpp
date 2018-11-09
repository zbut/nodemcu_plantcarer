//
//  thingspeak.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 09/11/2018.
//
//

#ifndef thingspeak_hpp
#define thingspeak_hpp

#include <device.hpp>

class cThingspeak : public cDevice {
private:
public:
    cThingspeak();
    ~cThingspeak();

    void setup() override;
    void loop() override;

protected:

    void push_status();
};


#endif /* thingspeak_hpp */
