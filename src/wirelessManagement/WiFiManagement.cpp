#include "WiFiManagement.h"

void Wificonnect(void)
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Connexion en cours...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20) {
      delay(500); // 0.5 seconde
      Serial.print(".");
      retry++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n[WiFi] Connecté !");
      Serial.print("IP locale : ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("\n[WiFi] Échec de connexion");
      WiFi.disconnect(true); // Déconnexion propre
    }
  }
  UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(NULL);
  Serial.printf("Stack restante: %u mots pour le WiFi\n", highWaterMark);
}
