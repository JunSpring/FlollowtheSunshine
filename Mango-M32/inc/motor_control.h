#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "stm32f10x.h"

typedef struct {
    uint8_t index;
    uint16_t dirPin;
    GPIO_TypeDef* dirPort;
    GPIO_TypeDef* pwmPort;
    uint16_t pwmPin;
    uint8_t dir;
} Motor;

typedef struct {
    Motor wheel1;
    Motor wheel2;
    Motor waterPump;
    TIM_TypeDef* timer;
} MotorConfig;

void initMotor(MotorConfig* motorConfig);
void setMotorSpeedByIndex(MotorConfig* motorConfig, uint8_t motorIndex, uint16_t speed);
void toggleMotorDirection(Motor* motor);

#endif  // MOTOR_CONTROL_H


