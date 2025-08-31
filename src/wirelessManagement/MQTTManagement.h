#ifndef MQTT_MANAGEMENT_H
#define MQTT_MANAGEMENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "KeywordManagement.h"
#include "sensorManagement/sensorManagement.h"

    void MQTTManagement_brokerConnection(void);
    void MQTTManagement_jsonDataSerialisation(char *cSerialisedData, size_t cSerialisedDataBufferSize);
    void MQTTManagement_jsonThresholdDataSerialisation(eSensorType sensorType,float fThresholdSensorValue, char *cSerialisedData, size_t cSerialisedDataBufferSize); 
    void MQTTManagement_sendSerialisedData(void);
    void MQTTManagement_ThresholdReached(eSensorType sensorType, float fSensorValue);

    int MQTTManagement_getMQTTStatus(void);

#endif // MQTT_MANAGEMENT_H