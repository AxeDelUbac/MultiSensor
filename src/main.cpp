#include "main.h"

luminositySensor luminosity(4);
informationDisplay lcdDisplay;

int luminosityValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(6,7);

  luminosity.begin();
  lcdDisplay.begin();

  xTaskCreate(
    WiFiTask,"TaskWiFi",4096,NULL,1,NULL
  );
    xTaskCreate(
    MQTTTask,"TaskMQTT",4096,NULL,1,NULL
  );
  xTaskCreate(
    luminosityTask,"TaskLuminosity",2048,NULL,1,NULL
  );
  xTaskCreate(
    Task2,"Tache2",2048,NULL,1,NULL
  );
  xTaskCreate(
    displayInformationTask,"TaskDisplayInformation",4096,NULL,1,NULL
  );

}

void loop() {}

void luminosityTask(void *pvParameters) {
  while (true) {
    Serial.println("Luminosity reading...");
    luminosityValue = luminosity.readRaw();
    // Serial.print("Luminosity: ");
    // Serial.println(luminosityValue);
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void Task2(void *pvParameters) {
  while (true) {
    Serial.println("Tâche 2 en cours...");
    vTaskDelay(pdMS_TO_TICKS(1500));  // Attendre 1,5 seconde
  }
}

void WiFiTask(void* parameter) {
  for (;;) {
    Wificonnect();
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

void MQTTTask(void* parameter) {
  for (;;) {

    MQTTconnect();
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

void displayInformationTask(void* parameter) {
  for (;;) {
    lcdDisplay.setCursor(0, 0);
    lcdDisplay.display(" Lets GO ESP32");
    lcdDisplay.setCursor(0,1);
    lcdDisplay.displayLuminosity(luminosityValue);
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}