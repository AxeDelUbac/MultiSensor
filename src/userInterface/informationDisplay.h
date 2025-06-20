#ifndef INFORMATION_DISPLAY_H
#define INFORMATION_DISPLAY_H

#include <LiquidCrystal_I2C.h>

class informationDisplay
{
public:
    informationDisplay();
    void begin();
    void clear();
    void setCursor(int col, int row);

    void display(int value);
    void display(const String &text);

    void displayLuminosity(float fLuminosityValue);
    void displayTemperature(float fTemperatureValue);
    void displayHumidity(float fHumidityValue);
    void displayPressure(float fPresureValue);
    void displayGas(float GasValue);

    void displaySensor(float fTemperatureValue, float fHumidityValue, float fPresureValue, float fIAQValue);

private:
    LiquidCrystal_I2C lcd;
};

#endif
