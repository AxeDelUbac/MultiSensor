#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H


#include <Arduino.h>
#include <BH1750.h>

#include "sensorManagement.h"
#include "projectDefs.h"

void lightSensor_begin(void);

float lightSensor_readLuminosityValue(void);

#endif // LIGHT_SENSOR_H