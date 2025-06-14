#include <Arduino.h>
#include <Adafruit_BME680.h>

class environmentalSensor {
public:
    environmentalSensor(Adafruit_BME680* bme) : bme(bme) {}

    void begin();
    float readTemperatureValue(float dummy = 0);
    float readHumidityValue(float dummy = 0);
    float readPressureValue(float dummy = 0);
    float readGasValue(float dummy = 0);

private:
    Adafruit_BME680* bme;
};