#ifndef PROJECT_DEFS_H
#define PROJECT_DEFS_H

typedef enum {
    NONE = 0,
    TEMPERATURE,
    HUMIDITY,
    PRESSURE,
    IAQ, // Indoor Air Quality
    LUMINOSITY
} eSensorType;

inline const char* sensorTypeToString(eSensorType type) {
    switch(type) {
        case TEMPERATURE: return "TEMPERATURE";
        case HUMIDITY:    return "HUMIDITY";
        case PRESSURE:    return "PRESSURE";
        case IAQ:         return "IAQ";
        case LUMINOSITY:  return "LUMINOSITY";
        default:          return "UNKNOWN";
    }
}

typedef enum {
    WIFI,
    MQTT
} eConnexionStatusType;

#endif // PROJECT_DEFS_H