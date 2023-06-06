#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include "stm32f10x.h"

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    ADC_TypeDef* adc;
    uint8_t channel;
} SoilMoisture;

void initSoilMoistureSensor(SoilMoisture* sensor, GPIO_TypeDef* port, uint16_t pin, ADC_TypeDef* adc, uint8_t channel);
uint16_t readSoilMoistureValue(SoilMoisture* sensor);

#endif  // SOIL_MOISTURE_SENSOR_H
