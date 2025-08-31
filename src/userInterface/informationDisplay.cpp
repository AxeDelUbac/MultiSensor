#include "informationDisplay.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

int iThresholdReached = 0;
int iDisplayNameCounter = 0;

int iWiFiStatus = 0;
int iMqttStatus = 0;

/****
 * @brief informationDisplay class constructor.
 *
 * Initializes the LCD object with I2C address 0x27 and a 16x2 screen.
 ****/
// informationDisplay_informationDisplay()
//     : lcd(0x27, 16, 2)
// {
// }

/****
 * @brief Initializes the LCD display.
 *
 * Initializes, turns on the backlight, and clears the LCD screen.
 ****/
/**
 * @brief Initializes the LCD display.
 *
 * Initializes, turns on the backlight, and clears the LCD screen.
 */
void informationDisplay_begin()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

/****
 * @brief Clears the LCD screen.
 ****/
/**
 * @brief Clears the LCD screen.
 */
void informationDisplay_clear()
{
    lcd.clear();
}

/****
 * @brief Sets the cursor position on the LCD screen.
 *
 * @param col Column (0-15)
 * @param row Row (0-1)
 ****/
/**
 * @brief Sets the cursor position on the LCD screen.
 *
 * @param col Column (0-15)
 * @param row Row (0-1)
 */
void informationDisplay_setCursor(int col, int row)
{
    lcd.setCursor(col, row);
}

/****
 * @brief Displays an integer value on the LCD.
 *
 * @param value Integer value to display.
 ****/
/**
 * @brief Displays an integer value on the LCD.
 *
 * @param value Integer value to display.
 */
void informationDisplay_display(int value)
{
    lcd.print(value);
}

/****
 * @brief Displays a text string on the LCD.
 *
 * @param text Text to display.
 ****/
/**
 * @brief Displays a text string on the LCD.
 *
 * @param text Text to display.
 */
void informationDisplay_display(const String &text)
{
    lcd.print(text);
}

/****
 * @brief Displays temperature on the LCD.
 *
 * @param fTemperatureValue Temperature value to display (in °C).
 ****/
/**
 * @brief Displays temperature on the LCD.
 *
 * @param fTemperatureValue Temperature value to display (in °C).
 */
void informationDisplay_displayTemperature(float fTemperatureValue)
{
    informationDisplay_display(fTemperatureValue);
    informationDisplay_display(" C");
}

/****
 * @brief Displays humidity on the LCD.
 *
 * @param fHumidityValue Humidity value to display (in %).
 ****/
/**
 * @brief Displays humidity on the LCD.
 *
 * @param fHumidityValue Humidity value to display (in %).
 */
void informationDisplay_displayHumidity(float fHumidityValue)
{
    informationDisplay_display(fHumidityValue);
    informationDisplay_display(" %");
}

/****
 * @brief Displays pressure on the LCD.
 *
 * @param fPressureValue Pressure value to display (in hPa).
 ****/
/**
 * @brief Displays pressure on the LCD.
 *
 * @param fPressureValue Pressure value to display (in hPa).
 */
void informationDisplay_displayPressure(float fPressureValue)
{
    informationDisplay_display(fPressureValue);
    informationDisplay_display(" hPa");
}

/****
 * @brief Displays air quality index (IAQ) on the LCD.
 *
 * @param fIAQValue IAQ value to display.
 ****/
/**
 * @brief Displays air quality index (IAQ) on the LCD.
 *
 * @param fIAQValue IAQ value to display.
 */
void informationDisplay_displayGas(float fIAQValue)
{
    informationDisplay_display("IAQ: ");
    informationDisplay_display(fIAQValue);
}

/****
 * @brief Displays luminosity on the LCD.
 *
 * @param fLuminosityValue Luminosity value to display (in lux).
 ****/
/**
 * @brief Displays luminosity on the LCD.
 *
 * @param fLuminosityValue Luminosity value to display (in lux).
 */
void informationDisplay_displayLuminosity(float fLuminosityValue)
{
    informationDisplay_display(fLuminosityValue);
    informationDisplay_display(" Lux");
}

const int DisplayInformationRollingIndexMax = 2;
int DisplayInformationRollingIndex = 0;

/****
 * @brief Cyclically displays different sensor measurements on the LCD.
 *
 * Displays luminosity,temperature ,humidity, pressure and IAQ according to the rolling index.
 *
 * @param fSensorValue Array containing sensor values.
 ****/
/**
 * @brief Cyclically displays different sensor measurements on the LCD.
 *
 * Displays temperature, humidity, luminosity, pressure, and IAQ according to the rolling index.
 *
 * @param fSensorValue Array containing sensor values.
 */
void informationDisplay_displaySensor(float fSensorValue[5])
{

    switch (DisplayInformationRollingIndex)
    {
    case 0:
        informationDisplay_setCursor(0, 1);
        informationDisplay_displayTemperature(fSensorValue[0]);
        informationDisplay_setCursor(8, 1);
        informationDisplay_displayHumidity(fSensorValue[1]);
        break;
    case 1:
        informationDisplay_setCursor(0, 1);
        informationDisplay_displayLuminosity(fSensorValue[2]);
        informationDisplay_setCursor(8, 1);
        informationDisplay_displayPressure(fSensorValue[3]);
        break;
    case 2:
        informationDisplay_setCursor(0, 1);
        informationDisplay_displayGas(fSensorValue[4]);
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

/**
 * @brief Displays the main information or status on the LCD.
 *
 * Alternates between a welcome message and the current WiFi/MQTT status.
 */
void informationDisplay_displayMainInformation(void)
{
    if(iDisplayNameCounter<4)
    {
        informationDisplay_setCursor(0, 0);
        informationDisplay_display("The Multisensor");
        iDisplayNameCounter++;
    }
    else
    {
        iWiFiStatus = WiFiManagement_getWiFiStatus();
        iMqttStatus = MQTTManagement_getMQTTStatus();

        informationDisplay_setCursor(0, 0);
        informationDisplay_displayStatus(WIFI, iWiFiStatus);
        informationDisplay_setCursor(8, 0);
        informationDisplay_displayStatus(MQTT, iMqttStatus);

        iDisplayNameCounter = 0;
    }
}

/**
 * @brief Displays the connection status for WiFi or MQTT on the LCD.
 *
 * @param itypeStatus The type of connection (WIFI or MQTT).
 * @param iStatus The status code (implementation-specific: 3=WiFi OK, 0=MQTT OK, else NOK).
 */
void informationDisplay_displayStatus(eConnexionStatusType itypeStatus, int iStatus)
{
    if(itypeStatus == WIFI)
    {
        informationDisplay_display("WiFi");
        if(iStatus == 3)
        {
            informationDisplay_display(" OK");
        }
        else
        {
            informationDisplay_display(" NOK");
        }
    }
    else if(itypeStatus == MQTT)
    {
        informationDisplay_display("MQTT");
        if(iStatus == 0)
        {
            informationDisplay_display(" OK");
        }
        else
        {
            informationDisplay_display(" NOK");
        }
    }
}

/****
 * END OF FILE
 ****/