#ifndef MQTT_MANAGEMENT_H
#define MQTT_MANAGEMENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "KeywordManagement.h"

class MQTTManagement
{
public:
    void brokerConnection(void);
    void jsonDataSerialisation(char *cSerialisedData, size_t cSerialisedDataBufferSize);
    void sendSerialisedData(void);

    char cSerialisedData[256] = {0};
};

#endif