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

float environmentalSensor_readRawTemperature(void);
float environmentalSensor_readRawHumidity(void);
float environmentalSensor_readRawPressure(void);
float environmentalSensor_readRawGas(void);

#endif // ENVIRONMENTAL_SENSOR_H