#include "MQTTManagement.h"

#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient client(espClient);

extern float fRetrieveSensorValueBuffer[5];

/****
 * @brief Connects to the MQTT broker.
 *
 * Sets the MQTT server and attempts to connect using the provided credentials.
 * Retries the connection if it fails.
 ****/
void MQTTManagement::brokerConnection(void)
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

/****
 * @brief Serializes sensor data into a JSON string.
 *
 * Fills the provided buffer with a JSON string containing temperature, humidity, pressure, IAQ, and luminosity.
 *
 * @param cSerialisedData Buffer to store the serialized JSON string.
 * @param cSerialisedDataBufferSize Size of the buffer.
 ****/
void MQTTManagement::jsonDataSerialisation(char *cSerialisedData, size_t cSerialisedDataBufferSize)
{

  JsonDocument oJsonData;

  oJsonData["temperature"] = fRetrieveSensorValueBuffer[0];
  oJsonData["humidity"] = fRetrieveSensorValueBuffer[1];
  oJsonData["pressure"] = fRetrieveSensorValueBuffer[2];
  oJsonData["Indoor Air Quality "] = fRetrieveSensorValueBuffer[3];
  oJsonData["luminosity"] = fRetrieveSensorValueBuffer[4];

  serializeJson(oJsonData, cSerialisedData, cSerialisedDataBufferSize);
}

/****
 * @brief Sends the serialized sensor data to the MQTT broker.
 *
 * Ensures the client is connected, serializes the data, and publishes it to the MQTT topic.
 ****/
void MQTTManagement::sendSerialisedData(void)
{
  if (!client.connected())
  {
    brokerConnection();
  }

  client.loop();

  jsonDataSerialisation(cSerialisedData, sizeof(cSerialisedData));

  client.publish("Multisensor", cSerialisedData);

  Serial.print("MQTT Messages sent: ");
  Serial.println(cSerialisedData);

  // Print the minimum remaining stack space for the current MQTT task (for stack monitoring)
  // UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(NULL);
  // Serial.printf("Stack restante: %u mots pour le MQTT\n", highWaterMark);
}

/****
 * END OF FILE
 ****/
