#ifndef CDS_SENSOR_H
#define CDS_SENSOR_H

#include "stm32f10x.h"

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    ADC_TypeDef* adc;
    uint8_t channel;
} CDS;

void initCDSSensor(CDS* cds);
uint16_t readCDSValue(CDS* cds);

#endif  // CDS_SENSOR_H
