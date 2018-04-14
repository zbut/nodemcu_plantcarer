//
//  device.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 11/04/2018.
//
//

#ifndef device_hpp
#define device_hpp

#include <stdio.h>

class cDevice {
private:
public:
    cDevice();
    ~cDevice();

    virtual void setup() = 0;
    virtual void loop() = 0;
protected:

};


#endif /* device_hpp */
