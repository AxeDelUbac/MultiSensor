#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// include Wireless
#include <WiFi.h>
#include <PubSubClient.h>

// include I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// include of the sensor libraries
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <BH1750.h>

// include of the project files
#include "sensorManagement/environmentalSensor.h"
#include "sensorManagement/lightSensor.h"

#include "wirelessManagement/WiFiManagement.h"
#include "wirelessManagement/MQTTManagement.h"
#include "userInterface/informationDisplay.h"

void taskCreation(void);

void WiFiTask(void *pvParameters);
void MQTTTask(void *pvParameters);
void SensorTask(void *pvParameters);
void DebugTask(void *pvParameters);
void displayInformationTask(void *pvParameters);

const int iSizeSensorValueBuffer = 5;
float fRetrieveSensorValueBuffer[iSizeSensorValueBuffer] = {0};
float fRetrieveRawSensorValue[iSizeSensorValueBuffer] = {0};

#endif // MAIN_H