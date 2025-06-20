#include "WiFiManagement.h"

void WiFiManagement::networkConnection(void)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("[WiFi] Connexion en cours...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20)
    {
      delay(500);
      Serial.print(".");
      retry++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("\n[WiFi] Connecté !");
      Serial.print("IP locale : ");
      Serial.println(WiFi.localIP());
    }
    else
    {
      Serial.println("\n[WiFi] Échec de connexion");
      WiFi.disconnect(true); // Déconnexion propre
    }
  }
  // Print the minimum remaining stack space for the current WIFI task (for stack monitoring)
  // UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(NULL);
  // Serial.printf("Stack restante: %u mots pour le WiFi\n", highWaterMark);
}