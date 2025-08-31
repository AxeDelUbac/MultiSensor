#include "main.h"

/**
 * @brief Main setup function.
 *
 * Initializes serial communication, I2C, sensors, LCD, and creates all FreeRTOS tasks.
 */
void setup()
{

  Serial.begin(115200);
  Wire.begin(6, 7);

  Serial.println("Scan complete.");

  environmentalSensor_begin();
  lightSensor_begin();
  informationDisplay_begin();

  taskCreation();
}

/**
 * @brief Creates all FreeRTOS tasks for the application.
 *
 * Creates tasks for WiFi, MQTT, sensor reading, debugging, and LCD display.
 */
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

/**
 * @brief Main loop (unused with FreeRTOS tasks).
 *
 * Required by Arduino framework, but not used since all logic is handled by FreeRTOS tasks.
 */
void loop() {}

/**
 * @brief Task for debugging: prints sensor values to serial output.
 *
 * Prints all sensor values to the serial monitor every 10 seconds.
 *
 * @param pvParameters Unused FreeRTOS task parameter.
 */
void DebugTask(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(10000);

  for (;;)
  {

    Serial.print("Temperature: ");
    Serial.print(fRetrieveSensorValueBuffer[0]);
    Serial.print(" C, Humidity: ");
    Serial.print(fRetrieveSensorValueBuffer[1]);
    Serial.print(" Pressure: ");
    Serial.print(fRetrieveSensorValueBuffer[2]);
    Serial.print(" hPa, IAQ : ");
    Serial.print(fRetrieveSensorValueBuffer[3]);
    Serial.print(" ,Light: ");
    Serial.print(fRetrieveSensorValueBuffer[4]);
    Serial.print(" Lux");

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * @brief Task for reading sensor values and updating the buffer.
 *
 * Reads all sensors, updates the global buffer, and checks thresholds every 5 minutes (300 seconds).
 *
 * @param pvParameters Unused FreeRTOS task parameter.
 */
void SensorTask(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(300000);

  for (;;)
  {
    fRetrieveSensorValueBuffer[0] = environmentalSensor_readTemperatureValue();
    fRetrieveSensorValueBuffer[1] = environmentalSensor_readHumidityValue();
    fRetrieveSensorValueBuffer[2] = environmentalSensor_readPressureValue();
    fRetrieveSensorValueBuffer[3] = environmentalSensor_readGasValue();
    fRetrieveSensorValueBuffer[4] = lightSensor_readLuminosityValue();

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * @brief Task for managing WiFi connection.
 *
 * Periodically checks and manages the WiFi connection every 2 minutes and 30 seconds (150 seconds).
 *
 * @param parameter Unused FreeRTOS task parameter.
 */
void WiFiTask(void *parameter)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(150000);

  for (;;)
  {

    WiFiManagement_networkConnection();

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * @brief Task for sending sensor data via MQTT.
 *
 * Serializes and publishes sensor data to the MQTT broker every 30 minutes (1800 seconds).
 *
 * @param parameter Unused FreeRTOS task parameter.
 */
void MQTTTask(void *parameter)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(1800000);

  for (;;)
  {

    MQTTManagement_sendSerialisedData();

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * @brief Task for displaying sensor information on the LCD.
 *
 * Clears the LCD, displays main information and sensor values every 5 seconds.
 *
 * @param parameter Unused FreeRTOS task parameter.
 */
void displayInformationTask(void *parameter)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(5000);

  for (;;)
  {

    informationDisplay_clear();

    informationDisplay_displayMainInformation();

    informationDisplay_displaySensor(fRetrieveSensorValueBuffer);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/****
 * END OF FILE
 ****/