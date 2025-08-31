#ifndef INFORMATION_DISPLAY_H
#define INFORMATION_DISPLAY_H

#include <LiquidCrystal_I2C.h>
#include "wirelessManagement/WiFiManagement.h"
#include "wirelessManagement/MQTTManagement.h"

#include "projectDefs.h"

void informationDisplay_begin();
void informationDisplay_clear();
void informationDisplay_setCursor(int col, int row);

void informationDisplay_display(int value);
void informationDisplay_display(const String &text);

void informationDisplay_displayTemperature(float fTemperatureValue);
void informationDisplay_displayHumidity(float fHumidityValue);
void informationDisplay_displayPressure(float fPresureValue);
void informationDisplay_displayGas(float GasValue);
void informationDisplay_displayLuminosity(float fLuminosityValue);

void informationDisplay_displaySensor(float fSensorValue[5]);

void informationDisplay_displayMainInformation(void);

void informationDisplay_displayStatus(eConnexionStatusType itypeStatus, int iStatus);

#endif // INFORMATION_DISPLAY_H
