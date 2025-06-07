#ifndef INFORMATION_DISPLAY_H
#define INFORMATION_DISPLAY_H

#include <LiquidCrystal_I2C.h>

class informationDisplay {
public:
    informationDisplay();
    void begin();
    void clear();
    void setCursor(int col, int row);
    void display(int value);
    void display(const String& text);
    void displayLuminosity(int luminosityValue);
    void displayTemperature(int temperatureValue);
    void displayHumidity(int humidityValue);


private:
    LiquidCrystal_I2C lcd;
};

# endif
