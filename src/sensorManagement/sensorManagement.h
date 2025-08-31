#ifndef SENSOR_MANAGEMENT_H
#define SENSOR_MANAGEMENT_H

#include <Arduino.h>
#include "projectDefs.h"
#include "wirelessManagement/MQTTManagement.h"

float sensorManagement_movingAverage(float *fSensorBuffer, float fNewValue);
void sensorManagement_isTresholdReached(eSensorType sensorType, float fSensorValue, float fThreshold[2]);

#endif // SENSOR_MANAGEMENT_H