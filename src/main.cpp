#include <Arduino.h>

#include "luminositySensor.h"
#include "WiFiManagement.h"
#include "MQTTManagement.h"

#include <WiFi.h>
#include <PubSubClient.h>

void TaskWiFi(void *pvParameters);
void TaskMQTT(void *pvParameters);
void TaskLuminosity(void *pvParameters);
void Task2(void *pvParameters);

luminositySensor luminosity(4);

  int luminosityValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
// Serial.print("Connexion au Wi-Fi : ");
//   Serial.println(ssid);

//   WiFi.begin(ssid, password);  // Lancement de la connexion

//   // Attente jusqu'à la connexion
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   // Connexion réussie
//   Serial.println("\nConnecté au Wi-Fi !");
//   Serial.print("Adresse IP : ");
//   Serial.println(WiFi.localIP());

    luminosity.begin();  // Initialisation du capteur de luminosité

  xTaskCreate(
    TaskWiFi,            // Fonction de la tâche
    "TaskWiFi",         // Nom de la tâche (pour debug)
    4096,             // Taille de la pile (en mots)
    NULL,             // Paramètre (non utilisé ici)
    1,                // Priorité
    NULL              // Handle (pas utilisé ici)
  );

    xTaskCreate(
    TaskMQTT,
    "TaskMQTT",
    4096,
    NULL,
    1,
    NULL
  );


  xTaskCreate(
    TaskLuminosity,            // Fonction de la tâche
    "TaskLuminosity",         // Nom de la tâche (pour debug)
    2048,             // Taille de la pile (en mots)
    NULL,             // Paramètre (non utilisé ici)
    1,                // Priorité
    NULL              // Handle (pas utilisé ici)
  );

  // Création de la deuxième tâche
  xTaskCreate(
    Task2,
    "Tache2",
    2048,
    NULL,
    1,
    NULL
  );

}

void loop() {
  // put your main code here, to run repeatedly:
}

// Définition de la première tâche
void TaskLuminosity(void *pvParameters) {
  while (true) {
    Serial.println("Luminosity reading...");
    luminosityValue = luminosity.readRaw();  // Lire la luminosité
    Serial.print("Luminosity: ");
    Serial.println(luminosityValue);
    vTaskDelay(pdMS_TO_TICKS(5000));  // Attendre 5 secondes
  }
}

// Définition de la deuxième tâche
void Task2(void *pvParameters) {
  while (true) {
    Serial.println("Tâche 2 en cours...");
    vTaskDelay(pdMS_TO_TICKS(1500));  // Attendre 1,5 seconde
  }
}

// Tâche RTOS
void TaskWiFi(void* parameter) {
  for (;;) {
    Wificonnect();
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}


// Tâche MQTT
void TaskMQTT(void* parameter) {
  for (;;) {

    MQTTconnect();
    vTaskDelay(pdMS_TO_TICKS(10000));  // toutes les 5 secondes
  }
}