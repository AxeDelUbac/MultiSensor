#ifndef LUMINOSITY_SENSOR_H
#define LUMINOSITY_SENSOR_H

#include <Arduino.h>

class luminositySensor {
public:
    // luminositySensor(int pin);
    luminositySensor(int pin, float vcc = 3.3, int resolution = 12, float tirage = 10.0);
    void begin();
    int readRaw();
    int getLux(); 


private:
    int _pin;
    float _vcc;
    int _resolution;
    float _tirage;
};

#endif
