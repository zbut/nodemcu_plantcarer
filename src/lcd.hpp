//
//  lcd.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#ifndef lcd_hpp
#define lcd_hpp

#include <device.hpp>

class cLcd : public cDevice {
private:
public:
    cLcd();
    ~cLcd();

    void setup() override;
    void loop() override;

    void print_line(const char* line);
    void print_status(bool force = false);

protected:

};


#endif /* lcd_hpp */
