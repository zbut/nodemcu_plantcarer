//
//  ota_update.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 15/06/2018.
//
//

#ifndef ota_update_hpp
#define ota_update_hpp

#include <stdio.h>
#include <device.hpp>

class cOtaUpdate : public cDevice{
private:
public:
    cOtaUpdate();
    ~cOtaUpdate();

    void setup() override;
    void loop() override;
protected:

};


#endif /* ota_update_hpp */
