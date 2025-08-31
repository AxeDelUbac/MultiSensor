#include "sensorManagement.h"

#define MOVING_AVERAGE_BUFFER_SIZE 6

// Buffers pour le moving average
// static float tempBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};
// static float humBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};
// static float pressBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};
// static float gasBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};
// static float lumiBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};

/**
 * @brief Calculates the moving average on a buffer and adds a new value.
 *
 * Shifts the values in the buffer, inserts the new value at the head,
 * and then calculates the average of the values present in the buffer.
 *
 * @param fSensorBuffer Pointer to the buffer of float values.
 * @param fNewValue New value to insert into the buffer.
 * @return Moving average calculated on the buffer after inserting the new value.
 */
float sensorManagement_movingAverage(float *fSensorBuffer, float fNewValue)
{
    float AverageValue = 0;

    for (int iBcl = MOVING_AVERAGE_BUFFER_SIZE - 1; iBcl > 0; iBcl--)
    {
        fSensorBuffer[iBcl] = fSensorBuffer[iBcl - 1];
    }
    fSensorBuffer[0] = fNewValue;

    for (int iBcl = 0; iBcl < MOVING_AVERAGE_BUFFER_SIZE; iBcl++)
    {
        AverageValue = AverageValue + fSensorBuffer[iBcl];
    }

    AverageValue = AverageValue / MOVING_AVERAGE_BUFFER_SIZE;
    return AverageValue;
}

/**
 * @brief Checks if a sensor value exceeds its defined threshold(s) and triggers an alert if needed.
 *
 * Compares the given sensor value to the provided thresholds (min and max).
 * If the value is outside the range, calls MQTTManagement_ThresholdReached to send an alert.
 *
 * @param sensorType The type of sensor being checked.
 * @param fSensorValue The current value measured by the sensor.
 * @param fThreshold Array of two floats: fThreshold[0] = min threshold, fThreshold[1] = max threshold.
 *                   Use -INFINITY or INFINITY if only one threshold is needed.
 * @return eSensorType The type of sensor if the threshold is exceeded, or -1 (casté) sinon.
 */
void sensorManagement_isTresholdReached(eSensorType sensorType, float fSensorValue, float fThreshold[2]) {
    if ((fSensorValue < fThreshold[0]) || (fSensorValue > fThreshold[1])) {
        MQTTManagement_ThresholdReached(sensorType, fSensorValue);
    }
}

/****
 * END OF FILE
 ****//**
 * @brief End of file marker for documentation purposes.
 */