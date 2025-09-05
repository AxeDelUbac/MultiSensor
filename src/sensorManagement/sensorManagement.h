#ifndef SENSOR_MANAGEMENT_H
#define SENSOR_MANAGEMENT_H

#include <Arduino.h>
#include "projectDefs.h"
#include "wirelessManagement/MQTTManagement.h"

float sensorManagement_movingAverage(float *fSensorBuffer, float fNewValue);
float sensorManagement_hampelFilter(float *fHampelSensorBuffer, int fHampelBufferSize, float fBufferNewValue, float threshold);
void sensorManagement_isTresholdReached(eSensorType sensorType, float fSensorValue, float fThreshold[2]);

#endif // SENSOR_MANAGEMENT_H