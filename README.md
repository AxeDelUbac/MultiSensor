# MultiSensor

This is a measurement station project based on an ESP32-C6 microcontroller.

## Project Structure and Code Organization

### 1. `sensorManagement/`
This folder contains all classes related to sensor management:
- **`environmentalSensor`**: Manages environmental measurements (temperature, humidity, pressure, gas/IAQ) using the BME680 sensor. Provides initialization, moving average filtering, and IAQ calculation. All sensor readings are encapsulated in this class.
- **(Optional) `luminositySensor`**: If present, handles ambient light measurement. Not always used in the current codebase.

All sensor classes encapsulate hardware access and expose high-level methods for use in the main application or tasks. The environmentalSensor class is central for all environmental data.

### 2. `wirelessManagement/`
This directory contains classes for network connectivity:
- **`WiFiManagement`**: Handles WiFi connection, reconnection, and status monitoring. Provides a method to connect to WiFi and manages connection retries.
- **`MQTTManagement`**: Manages MQTT communication (publish/subscribe), serializes sensor data into JSON, and publishes it to a remote MQTT broker. Includes methods for broker connection, data serialization, and publishing.

These classes abstract the complexity of network protocols and provide simple APIs for the rest of the application. They use the ArduinoJson and PubSubClient libraries for JSON and MQTT support.

### 3. `userInterface/`
This folder manages user interaction and display:
- **`informationDisplay`**: Controls the I2C LCD display (16x2), including text output, backlight control, and custom characters. Provides methods to display sensor values (temperature, humidity, pressure, IAQ) and system messages. Includes rolling display logic to cycle through different sensor values.

All display logic is encapsulated in this class, making it easy to update or extend the user interface.

---

The project is organized to separate hardware abstraction (sensors, display) from communication (WiFi, MQTT) and user interface, making it modular and maintainable.
