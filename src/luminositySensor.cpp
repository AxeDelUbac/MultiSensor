#include "luminositySensor.h"

// luminositySensor::luminositySensor(int pin) : _pin(pin) {}
luminositySensor::luminositySensor(int pin, float vcc, int resolution, float tirage) : _pin(pin), _vcc(vcc), _resolution(resolution), _tirage(tirage) {}

void luminositySensor::begin() {
    pinMode(_pin, INPUT);
}

int luminositySensor::readRaw() {
    return analogRead(_pin);
}

int luminositySensor::getLux() {
    int raw = readRaw();
    float voltage = raw * _vcc / pow(2, _resolution);
    int lux = (955 * (pow(2, _resolution) - raw)) / (_tirage * raw);
    return lux;
}