#include "main.h"

luminositySensor luminosity(4);
informationDisplay lcdDisplay;
Adafruit_BME680 bme(&Wire);
environmentalSensor environmentalSensor(&bme);

int luminosityValue;
int temperatureValue;
int humidityValue;
int pressureValue;
int gasValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(6,7);

  environmentalSensor.begin();
  luminosity.begin();
  lcdDisplay.begin();

  xTaskCreate(
    WiFiTask,"TaskWiFi",4096,NULL,1,NULL
  );
    xTaskCreate(
    MQTTTask,"TaskMQTT",4096,NULL,1,NULL
  );
  xTaskCreate(
    SensorTask,"SensorTask",2048,NULL,1,NULL
  );
  xTaskCreate(
    DebugTask,"DebugTask",2048,NULL,1,NULL
  );
  xTaskCreate(
    displayInformationTask,"DisplayInformationTask",4096,NULL,1,NULL
  );

}

void loop() {}

void DebugTask(void *pvParameters) {
  while (true) {

    Serial.print("Temperature: ");
    Serial.print(temperatureValue);
    Serial.print(" C, Humidity: ");
    Serial.print(humidityValue);
    Serial.print(" %, Pressure: ");
    Serial.print(pressureValue);
    Serial.print(" hPa, Gas: ");
    Serial.print(gasValue);
    Serial.println(" eC02");

    vTaskDelay(pdMS_TO_TICKS(10500));  // Attendre 1,5 seconde
  }
}

void SensorTask(void *pvParameters) {
  while (true) {

    temperatureValue = environmentalSensor.readTemperatureValue();
    humidityValue = environmentalSensor.readHumidityValue();
    pressureValue = environmentalSensor.readPressureValue();
    gasValue = environmentalSensor.readGasValue();

    vTaskDelay(pdMS_TO_TICKS(5000));
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

const int NB_VALEURS = 3;
int bufferIndex = 0;

void displayInformationTask(void* parameter) {
  for (;;) {

    lcdDisplay.clear();
    lcdDisplay.setCursor(0, 0);
    lcdDisplay.display("The multisensor");

    switch (bufferIndex) {
      case 0:
        lcdDisplay.setCursor(0,1);
        lcdDisplay.displayTemperature(temperatureValue);
        lcdDisplay.setCursor(8,1);
        lcdDisplay.displayHumidity(humidityValue);
        break;
      case 1:
        lcdDisplay.setCursor(0,1);
        lcdDisplay.displayPressure(pressureValue);
        break;
      case 2:
        lcdDisplay.setCursor(0,1);
        lcdDisplay.displayGas(gasValue);
        break;
    }

    bufferIndex = (bufferIndex + 1) % NB_VALEURS; // Incrémente et boucle

  Serial.println();

    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}