#include "motor_control.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure_PWM;
TIM_OCInitTypeDef TIM_OCInitStructure_PWM;
    
void initMotor(MotorConfig* motorConfig)
{
    // Enable TIM and GPIO clocks
    if (motorConfig->timer == TIM1) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (motorConfig->timer == TIM2) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (motorConfig->timer == TIM3) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (motorConfig->timer == TIM4) {
        // TIM4 clock enable 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

        // GPIOB ENABLE
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if (motorConfig->timer == TIM5) {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 | RCC_APB2Periph_GPIOA, ENABLE);
    }
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure_PWM;

    // Configure PWM GPIO pins
    GPIO_InitStructure_PWM.GPIO_Pin = motorConfig->wheel1.pwmPin | motorConfig->wheel2.pwmPin | motorConfig->waterPump.pwmPin;
    GPIO_InitStructure_PWM.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(motorConfig->wheel1.pwmPort, &GPIO_InitStructure_PWM);

    // Configure Direction GPIO pins
    GPIO_InitStructure_PWM.GPIO_Pin = motorConfig->wheel1.dirPin | motorConfig->wheel2.dirPin | motorConfig->waterPump.dirPin;
    GPIO_InitStructure_PWM.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(motorConfig->wheel1.dirPort, &GPIO_InitStructure_PWM);

    // Configure TIM Time Base
    TIM_TimeBaseStructure_PWM.TIM_Period = 999;
    TIM_TimeBaseStructure_PWM.TIM_Prescaler = 71;
    TIM_TimeBaseStructure_PWM.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure_PWM.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(motorConfig->timer, &TIM_TimeBaseStructure_PWM);

    // Configure TIM Output Compare
    TIM_OCInitStructure_PWM.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure_PWM.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure_PWM.TIM_Pulse = 0;
    TIM_OCInitStructure_PWM.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(motorConfig->timer, &TIM_OCInitStructure_PWM);
    TIM_OC1PreloadConfig(motorConfig->timer, TIM_OCPreload_Enable);
    
    /*
    TIM_OCInitStructure_PWM.TIM_OutputState = TIM_OutputState_Enable;   //아래는 위와 동일
    TIM_OCInitStructure_PWM.TIM_Pulse = 0;//CCR2_Val;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure_PWM);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCInitStructure_PWM.TIM_OutputState = TIM_OutputState_Enable;   //아래는 위와 동일
    TIM_OCInitStructure_PWM.TIM_Pulse = 0;//CCR2_Val;
    TIM_OC3Init(TIM4, &TIM_OCInitStructure_PWM);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    */
    
    TIM_Cmd(TIM4, ENABLE);
}

void setMotorSpeedByIndex(MotorConfig* motorConfig, uint8_t motorIndex, uint16_t speed)
{
    switch (motorIndex) {
    case 1:
        TIM_OCInitStructure_PWM.TIM_Pulse = speed;
        TIM_OC1Init(motorConfig->timer, &TIM_OCInitStructure_PWM);
        break;
    case 2:
        TIM_OCInitStructure_PWM.TIM_Pulse = speed;
        TIM_OC2Init(motorConfig->timer, &TIM_OCInitStructure_PWM);
        break;
    case 3:
        TIM_OCInitStructure_PWM.TIM_Pulse = speed;
        TIM_OC3Init(motorConfig->timer, &TIM_OCInitStructure_PWM);
        break;
    default:
        // Invalid motor index
        break;
    }
}

void toggleMotorDirection(Motor* motor)
{
    if (motor->dir == 0) {
        GPIO_WriteBit(motor->dirPort, motor->dirPin, Bit_RESET);
        motor->dir = 1;
    }
    else {
        GPIO_SetBits(motor->dirPort, motor->dirPin);
        motor->dir = 0;
    }
}
