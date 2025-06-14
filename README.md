# MultiSensor

This is a mesurement station project based on a ESP32-C6 microcontroller.

## Project Structure and Code Organization

### 1. `sensorManagement/`
This folder contains all classes related to sensor management:
- **`luminositySensor`**: Handles ambient light measurement. Provides methods for initialization and reading the luminosity value.
- **`environmentalSensor`**: Manages environmental measurements (temperature, humidity, pressure, gas) using the BME680 sensor. Offers methods to initialize the sensor and retrieve each environmental value.
- **Abstract base class**: All sensor classes inherit from a common abstract class (`SensorMeasurement`), which defines the interface for measurement and value retrieval. This makes it easy to add new sensors by simply extending this base class.

Each sensor class encapsulates the hardware access and exposes high-level methods for use in the main application or tasks.

### 2. `wirelessManagement/`
This directory contains classes for network connectivity:
- **`WiFiManagement`**: Handles WiFi connection, reconnection, and status monitoring.
- **`MQTTManagement`**: Manages MQTT communication (publish/subscribe), allowing sensor data to be sent to or received from a remote server.

These classes abstract the complexity of network protocols and provide simple APIs for the rest of the application.

### 3. `userInterface/`
This folder manages user interaction and display:
- **`informationDisplay`**: Controls the I2C LCD display, including text output, backlight control, and custom characters. It provides methods to display sensor values and system messages.
