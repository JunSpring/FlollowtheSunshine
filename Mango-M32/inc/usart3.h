#ifndef USART3_H
#define USART3_H

#include "stm32f10x.h"

typedef struct {
    GPIO_TypeDef* port;
    uint16_t txPin;
    uint16_t rxPin;
    uint32_t baudRate;
} USART3_config;

void initUSART3(USART3_config* config, GPIO_TypeDef* port, uint16_t txPin, uint16_t rxPin, uint32_t baudRate);

#endif  // USART3_H
