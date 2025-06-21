#include "environmentalSensor.h"

#define MOVING_AVERAGE_BUFFER_SIZE 6

float fTemperatureValueBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};
float fHumidityValueBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};
float fPressureValueBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};
float fGasValueBuffer[MOVING_AVERAGE_BUFFER_SIZE] = {0};

float fLastValueTemperature = 0;
float fLastValueHumidity = 0;
float fLastValuePressure = 0;
float fLastValueGas = 0;

float fGasResistance = 0;

/****
 * @brief Initializes the BME680 sensor.
 *
 * This function attempts to start the BME680 sensor at I2C address 0x76.
 * If the sensor is not detected, it prints an error message to the serial port
 * and enters an infinite loop to block execution.
 *
 * @note Prints a message to the serial port on success or failure.
 ****/
void environmentalSensor::begin()
{
    if (!bme->begin(0x76))
    { // Essaie 0x77 si 0x76 ne marche pas
        Serial.println("BME680 non détecté !");
        while (1)
            ; // Boucle infinie si le capteur n'est pas détecté
    }
    Serial.println("BME680 détecté !");
}

/****
 * @brief Calculates the moving average on a circular buffer and adds a new value.
 *
 * This function shifts the values in the buffer, inserts the new value at the head,
 * and then calculates the average of the values present in the buffer.
 *
 * @param fSensorBuffer Pointer to the circular buffer of float values.
 * @param fNewValue New value to insert into the buffer.
 * @return Moving average calculated on the buffer after inserting the new value.
 ****/
float environmentalSensor::movingAverage(float *fSensorBuffer, float fNewValue)
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

/****
 * @brief Calculate IAQ (Indoor Air Quality) from gas resistance.
 *
 * This function normalizes the resistance and returns an IAQ value between 0 (excellent) and 500 (very poor).
 *
 * @param fResistance Gas resistance value in Ohms.
 * @return IAQ value (0 = excellent, 500 = very poor).
 ****/
float environmentalSensor::IAQManagement(float fResistance)
{
    // Plage typique : 10 kΩ (mauvais air) à 500 kΩ (excellent air)
    float iaqNorm = (fResistance - 10000.0f) / (500000.0f - 10000.0f);

    // Limiter iaqNorm entre 0 et 1 sans constrain
    if (iaqNorm < 0.0f)
        iaqNorm = 0.0f;
    if (iaqNorm > 1.0f)
        iaqNorm = 1.0f;

    // Inverser l’indice : 0 = excellent, 1 = mauvais
    float iaq = (1.0f - iaqNorm) * 500.0f;
    return iaq; // 0 = excellent, 500 = très mauvais
}

/****
 * @brief Performs a temperature reading and returns the moving average value.
 *
 * This function reads the temperature from the BME680 sensor, updates the moving average buffer,
 * and returns the calculated average temperature.
 *
 * @return Averaged temperature (in degrees Celsius).
 ****/
float environmentalSensor::readTemperatureValue(void)
{
    fLastValueTemperature = bme->readTemperature();
    return movingAverage(fTemperatureValueBuffer, fLastValueTemperature);
}

/****
 * @brief Performs a humidity reading and returns the moving average value.
 *
 * This function reads the humidity from the BME680 sensor, updates the moving average buffer,
 * and returns the calculated average humidity.
 *
 * @return Averaged relative humidity (in percent).
 ****/
float environmentalSensor::readHumidityValue(void)
{
    fLastValueHumidity = bme->readHumidity();
    return movingAverage(fHumidityValueBuffer, fLastValueHumidity);
}

/****
 * @brief Performs a pressure reading and returns the moving average value.
 *
 * This function reads the pressure from the BME680 sensor, updates the moving average buffer,
 * and returns the calculated average pressure.
 *
 * @return Averaged atmospheric pressure (in hPa).
 ****/
float environmentalSensor::readPressureValue(void)
{
    fLastValuePressure = bme->readPressure();
    fLastValuePressure = fLastValuePressure / 100.0f; // Convertion in hPa
    return movingAverage(fPressureValueBuffer, fLastValuePressure);
}

/****
 * @brief Performs a gas resistance reading and returns the moving average value.
 *
 * This function reads the gas resistance from the BME680 sensor, updates the moving average buffer,
 * and returns the calculated average value.
 *
 * @return Averaged gas resistance value (in Ohms).
 ****/
float environmentalSensor::readGasValue(void)
{
    fLastValueGas = bme->readGas();
    fGasResistance = movingAverage(fGasValueBuffer, fLastValueGas);
    return IAQManagement(fGasResistance);
}
/****
 * END OF FILE
 ****/