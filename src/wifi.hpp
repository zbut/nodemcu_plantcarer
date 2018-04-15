//
//  wifi.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 11/04/2018.
//
//

#ifndef wifi_hpp
#define wifi_hpp

#include <stdio.h>
#include "device.hpp"

class cWifi : public cDevice {
private:
    bool connected;
public:
    cWifi();
    ~cWifi();

    void setup() override;
    void loop() override;
protected:

};


#endif /* wifi_hpp */
