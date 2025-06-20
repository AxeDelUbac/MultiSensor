#include "main.h"

informationDisplay lcdDisplay;
Adafruit_BME680 bme(&Wire);
environmentalSensor EnvironmentalSensor(&bme);
WiFiManagement oWIFIManagement;
MQTTManagement oMQTTManagement;

/****
 * @brief Main setup function.
 *
 * Initializes serial communication, I2C, sensors, LCD, and creates FreeRTOS tasks.
 ****/
void setup()
{

  Serial.begin(115200);
  Wire.begin(6, 7);

  EnvironmentalSensor.begin();
  lcdDisplay.begin();

  taskCreation();
}

/****
 * @brief Creates all FreeRTOS tasks for the application.
 ****/
void taskCreation(void)
{
  xTaskCreate(
      WiFiTask, "TaskWiFi", 4096, NULL, 1, NULL);
  xTaskCreate(
      MQTTTask, "TaskMQTT", 4096, NULL, 1, NULL);
  xTaskCreate(
      SensorTask, "SensorTask", 4096, NULL, 1, NULL);
  xTaskCreate(
      DebugTask, "DebugTask", 4096, NULL, 1, NULL);
  xTaskCreate(
      displayInformationTask, "DisplayInformationTask", 4096, NULL, 1, NULL);
}

/****
 * @brief Main loop (unused with FreeRTOS tasks).
 ****/
void loop() {}

/****
 * @brief Task for debugging: prints sensor values to serial output.
 ****/
void DebugTask(void *pvParameters)
{
  for (;;)
  {

    Serial.print("Temperature: ");
    Serial.print(fRetrieveSensorValueBuffer[0]);
    Serial.print(" C, Humidity: ");
    Serial.print(fRetrieveSensorValueBuffer[1]);
    Serial.print(" %, Pressure: ");
    Serial.print(fRetrieveSensorValueBuffer[2]);
    Serial.print("IAQ Value: ");
    Serial.print(fRetrieveSensorValueBuffer[3]);

    vTaskDelay(pdMS_TO_TICKS(10000)); // Attendre 1,5 seconde
  }
}

/****
 * @brief Task for reading sensor values and updating the buffer.
 ****/
void SensorTask(void *pvParameters)
{
  Serial.println("SensorTask start");
  for (;;)
  {

    fRetrieveSensorValueBuffer[0] = EnvironmentalSensor.readTemperatureValue();
    fRetrieveSensorValueBuffer[1] = EnvironmentalSensor.readHumidityValue();
    fRetrieveSensorValueBuffer[2] = EnvironmentalSensor.readPressureValue();
    fRetrieveSensorValueBuffer[3] = EnvironmentalSensor.readGasValue();

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

/****
 * @brief Task for managing WiFi connection.
 ****/
void WiFiTask(void *parameter)
{
  for (;;)
  {

    oWIFIManagement.networkConnection();

    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

/****
 * @brief Task for sending sensor data via MQTT.
 ****/
void MQTTTask(void *parameter)
{
  for (;;)
  {

    oMQTTManagement.sendSerialisedData();

    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

/****
 * @brief Task for displaying sensor information on the LCD.
 ****/
void displayInformationTask(void *parameter)
{
  for (;;)
  {

    lcdDisplay.clear();

    lcdDisplay.setCursor(0, 0);
    lcdDisplay.display("The multisensor");

    lcdDisplay.setCursor(0, 1);
    lcdDisplay.displaySensor(fRetrieveSensorValueBuffer[0], fRetrieveSensorValueBuffer[1], fRetrieveSensorValueBuffer[2], fRetrieveSensorValueBuffer[3]);

    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}