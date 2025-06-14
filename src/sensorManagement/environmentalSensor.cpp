#include "environmentalSensor.h"

void environmentalSensor::begin() {
    if (!bme->begin(0x76)) { // Essaie 0x77 si 0x76 ne marche pas
        Serial.println("BME680 non détecté !");
        while (1); // Boucle infinie si le capteur n'est pas détecté
    }
    Serial.println("BME680 détecté !");
}

float environmentalSensor::readTemperatureValue(float) {
    return bme->readTemperature();
}

float environmentalSensor::readHumidityValue(float) {
    return bme->readHumidity();
}

float environmentalSensor::readPressureValue(float) {
    return bme->readPressure() / 100.0;
}

float environmentalSensor::readGasValue(float) {
    return bme->readGas();
}