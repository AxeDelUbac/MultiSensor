#include "informationDisplay.h"

/****
 * @brief informationDisplay class constructor.
 *
 * Initializes the LCD object with I2C address 0x27 and a 16x2 screen.
 ****/
informationDisplay::informationDisplay()
    : lcd(0x27, 16, 2)
{
}

/****
 * @brief Initializes the LCD display.
 *
 * Initializes, turns on the backlight, and clears the LCD screen.
 ****/
void informationDisplay::begin()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

/****
 * @brief Clears the LCD screen.
 ****/
void informationDisplay::clear()
{
    lcd.clear();
}

/****
 * @brief Sets the cursor position on the LCD screen.
 *
 * @param col Column (0-15)
 * @param row Row (0-1)
 ****/
void informationDisplay::setCursor(int col, int row)
{
    lcd.setCursor(col, row);
}

/****
 * @brief Displays an integer value on the LCD.
 *
 * @param value Integer value to display.
 ****/
void informationDisplay::display(int value)
{
    lcd.print(value);
}

/****
 * @brief Displays a text string on the LCD.
 *
 * @param text Text to display.
 ****/
void informationDisplay::display(const String &text)
{
    lcd.print(text);
}

/****
 * @brief Displays luminosity on the LCD.
 *
 * @param fLuminosityValue Luminosity value to display (in lux).
 ****/
void informationDisplay::displayLuminosity(float fLuminosityValue)
{
    this->display(fLuminosityValue);
    this->display(" lux");
}

/****
 * @brief Displays temperature on the LCD.
 *
 * @param fTemperatureValue Temperature value to display (in °C).
 ****/
void informationDisplay::displayTemperature(float fTemperatureValue)
{
    this->display(fTemperatureValue);
    this->display(" C");
}

/****
 * @brief Displays humidity on the LCD.
 *
 * @param fHumidityValue Humidity value to display (in %).
 ****/
void informationDisplay::displayHumidity(float fHumidityValue)
{
    this->display(fHumidityValue);
    this->display(" %");
}

/****
 * @brief Displays pressure on the LCD.
 *
 * @param fPressureValue Pressure value to display (in hPa).
 ****/
void informationDisplay::displayPressure(float fPressureValue)
{
    this->display(fPressureValue);
    this->display(" hPa");
}

/****
 * @brief Displays air quality index (IAQ) on the LCD.
 *
 * @param fIAQValue IAQ value to display.
 ****/
void informationDisplay::displayGas(float fIAQValue)
{
    this->display("IAQ: ");
    this->display(fIAQValue);
}

const int DisplayInformationRollingIndexMax = 2;
int DisplayInformationRollingIndex = 0;

/****
 * @brief Cyclically displays different sensor measurements on the LCD.
 *
 * Displays temperature and humidity, then pressure, then IAQ according to the rolling index.
 *
 * @param fTemperatureValue Temperature to display.
 * @param fHumidityValue Humidity to display.
 * @param fPressureValue Pressure to display.
 * @param fIAQValue Air quality index to display.
 ****/
void informationDisplay::displaySensor(float fTemperatureValue, float fHumidityValue, float fPressureValue, float fIAQValue)
{

    switch (DisplayInformationRollingIndex)
    {
    case 0:
        setCursor(0, 1);
        displayTemperature(fTemperatureValue);
        setCursor(8, 1);
        displayHumidity(fHumidityValue);
        break;
    case 1:
        setCursor(0, 1);
        displayPressure(fPressureValue);
        break;
    case 2:
        setCursor(0, 1);
        displayGas(fIAQValue);
        break;
    }

    if (DisplayInformationRollingIndex >= DisplayInformationRollingIndexMax)
    {
        DisplayInformationRollingIndex = 0;
    }
    else
    {
        DisplayInformationRollingIndex++;
    }
}
/****
 * END OF FILE
 ****/