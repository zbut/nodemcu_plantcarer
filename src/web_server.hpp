//
//  web_server.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 18/04/2018.
//
//

#ifndef web_server_hpp
#define web_server_hpp

#include <device.hpp>

class cWebServer : public cDevice {
private:
public:
    cWebServer();
    ~cWebServer();

    void setup() override;
    void loop() override;
protected:

};


#endif /* web_server_hpp */
