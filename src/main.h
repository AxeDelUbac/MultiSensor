#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// include Wireless
#include <WiFi.h>
#include <PubSubClient.h>

// include I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// include of the project files
#include "sensorManagement/luminositySensor.h"
#include "sensorManagement/environmentalSensor.h"
#include "wirelessManagement/WiFiManagement.h"
#include "wirelessManagement/MQTTManagement.h"
#include "userInterface/informationDisplay.h"


void WiFiTask(void *pvParameters);
void MQTTTask(void *pvParameters);
void SensorTask(void *pvParameters);
void DebugTask(void *pvParameters);
void displayInformationTask(void *pvParameters);

#endif