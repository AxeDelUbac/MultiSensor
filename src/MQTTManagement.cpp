#include "MQTTManagement.h"

WiFiClient espClient;
PubSubClient client(espClient);

extern int luminosityValue;

void MQTTConnection() {
  client.setServer(MQTT_SERVEUR_IP, MQTT_SERVEUR_PORT);

  while (!client.connected()) {
    Serial.print("[MQTT] Connexion...");
    if (client.connect("ESP32Client",MQTT_USERNAME, MQTT_PASSWORD)) {
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

void MQTTconnect(void){
    if (!client.connected()) {
      MQTTConnection();
    }

    client.loop();

    char msg[64];
    snprintf(msg, sizeof(msg), "%d", luminosityValue);

    client.publish("Multisensor", msg);
    Serial.print("Lux envoyé : ");
    Serial.println(msg);

    UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(NULL);
    Serial.printf("Stack restante: %u mots pour le MQTT\n", highWaterMark);
}
