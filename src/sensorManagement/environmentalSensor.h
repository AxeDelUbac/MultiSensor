#ifndef ENVIRONMENTAL_SENSOR_H
#define ENVIRONMENTAL_SENSOR_H


#include <Arduino.h>
#include <Adafruit_BME680.h>

class environmentalSensor {
public:
    environmentalSensor(Adafruit_BME680* bme) : bme(bme) {}

    void begin();

    float movingAverage(float* fSensorBuffer, float fNewValue);
    float IAQManagement(float fResistance);

    float readTemperatureValue(void);
    float readHumidityValue(void);
    float readPressureValue(void);
    float readGasValue(void);

private:
    Adafruit_BME680* bme;
};

#endif // ENVIRONMENTAL_SENSOR_H