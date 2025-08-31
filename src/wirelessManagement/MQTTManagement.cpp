#include "MQTTManagement.h"

#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient client(espClient);

char cSerialisedData[256] = {0};
char cThresholdSerialisedData[64] = {0};

extern float fRetrieveSensorValueBuffer[5];

/**
 * @brief Connects to the MQTT broker.
 *
 * Sets the MQTT server and attempts to connect using the provided credentials.
 * Retries the connection if it fails until a connection is established.
 *
 * @note Prints connection status to the serial port.
 */
void MQTTManagement_brokerConnection(void)
{
  client.setServer(MQTT_SERVEUR_IP, MQTT_SERVEUR_PORT);

  while (!client.connected())
  {
    Serial.print("[MQTT] Connexion...");
    if (client.connect("ESP32Client", MQTT_USERNAME, MQTT_PASSWORD))
    {
      Serial.println("Connecté !");
    }
    else
    {
      Serial.print("Échec, rc=");
      Serial.print(client.state());
      Serial.println(" nouvelle tentative dans 2s");
      delay(2000);
    }
  }
}

/**
 * @brief Serializes sensor data into a JSON string.
 *
 * Fills the provided buffer with a JSON string containing temperature, humidity, pressure, IAQ, and luminosity.
 *
 * @param cSerialisedData Buffer to store the serialized JSON string.
 * @param cSerialisedDataBufferSize Size of the buffer.
 */
void MQTTManagement_jsonDataSerialisation(char *cSerialisedData, size_t cSerialisedDataBufferSize)
{
  JsonDocument oJsonData;

  oJsonData["temperature"] = fRetrieveSensorValueBuffer[0];
  oJsonData["humidity"] = fRetrieveSensorValueBuffer[1];
  oJsonData["pressure"] = fRetrieveSensorValueBuffer[2];
  oJsonData["IndoorAirQuality"] = fRetrieveSensorValueBuffer[3];
  oJsonData["luminosity"] = fRetrieveSensorValueBuffer[4];

  serializeJson(oJsonData, cSerialisedData, cSerialisedDataBufferSize);
}

/**
 * @brief Serializes threshold alert data into a JSON string.
 *
 * Fills the provided buffer with a JSON string containing the sensor type and the threshold value that was exceeded.
 *
 * @param sensorType The type of sensor for which the threshold was exceeded.
 * @param fThresholdSensorValue The value of the sensor that exceeded the threshold.
 * @param cThresholdSerialisedData Buffer to store the serialized JSON string.
 * @param cThresholdSerialisedDataBufferSize Size of the buffer.
 */
void MQTTManagement_jsonThresholdDataSerialisation(eSensorType sensorType, float fThresholdSensorValue, char *cThresholdSerialisedData, size_t cThresholdSerialisedDataBufferSize)
{
  JsonDocument oJsonThresholdData;

  oJsonThresholdData["sensorType"] = sensorTypeToString(sensorType); 
  oJsonThresholdData["thresholdSensorValue"] = fThresholdSensorValue;

  serializeJson(oJsonThresholdData, cThresholdSerialisedData, cThresholdSerialisedDataBufferSize);
}

/**
 * @brief Sends the serialized sensor data to the MQTT broker.
 *
 * Ensures the client is connected, serializes the data, and publishes it to the MQTT topic "Multisensor".
 *
 * @note Calls MQTTManagement_brokerConnection if not already connected.
 */
void MQTTManagement_sendSerialisedData(void)
{
  if (!client.connected())
  {
    MQTTManagement_brokerConnection();
  }

  client.loop();

  MQTTManagement_jsonDataSerialisation(cSerialisedData, sizeof(cSerialisedData));

  client.publish("Multisensor", cSerialisedData);

  // Serial.print("MQTT Messages sent: ");
  // Serial.println(cSerialisedData);
}

/**
 * @brief Publishes a threshold alert message to the MQTT broker.
 *
 * Publishes a JSON message to the topic "Multisensor/threshold/<sensorType>" when a sensor value exceeds its threshold.
 *
 * @param sensorType The type of sensor for which the threshold was exceeded.
 * @param fSensorValue The value of the sensor that exceeded the threshold.
 */
void MQTTManagement_ThresholdReached(eSensorType sensorType, float fSensorValue)
{

  char cThresholdTopic[64] = {0};
  snprintf(cThresholdTopic, sizeof(cThresholdTopic), "Multisensor/threshold/%s", sensorTypeToString(sensorType));

  MQTTManagement_jsonThresholdDataSerialisation(sensorType, fSensorValue, cThresholdSerialisedData, sizeof(cThresholdSerialisedData));

  client.publish(cThresholdTopic, cThresholdSerialisedData);

  // Serial.print("MQTT Threshold Messages sent: ");
  // Serial.println(cThresholdSerialisedData);
}

/**
 * @brief Returns the current MQTT client connection status.
 *
 * @return The status code from PubSubClient::state().
 */
int MQTTManagement_getMQTTStatus(void)
{
    return client.state();
}

/****
 * END OF FILE
 ****/
