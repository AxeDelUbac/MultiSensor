#ifndef ENVIRONMENTAL_SENSOR_H
#define ENVIRONMENTAL_SENSOR_H


#include <Arduino.h>
#include <Adafruit_BME680.h>

#include "sensorManagement.h"
#include "projectDefs.h"

void environmentalSensor_begin();

float environmentalSensor_IAQManagement(float fResistance);

float environmentalSensor_readTemperatureValue(void);
float environmentalSensor_readHumidityValue(void);
float environmentalSensor_readPressureValue(void);
float environmentalSensor_readGasValue(void);

#endif // ENVIRONMENTAL_SENSOR_H