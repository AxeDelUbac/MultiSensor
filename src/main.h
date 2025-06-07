#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// include Wireless
#include <WiFi.h>
#include <PubSubClient.h>

// include I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// include of the project files
#include "luminositySensor.h"
#include "WiFiManagement.h"
#include "MQTTManagement.h"
#include "informationDisplay.h"

void WiFiTask(void *pvParameters);
void MQTTTask(void *pvParameters);
void luminosityTask(void *pvParameters);
void Task2(void *pvParameters);
void displayInformationTask(void *pvParameters);

#endif