#include "stm32f10x.h"
#include "usart3.h"
#include "motor_control.h"
#include "soil_moisture_sensor.h"
#include "cds_sensor.h"
#include <stdio.h>

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure_PWM;
TIM_OCInitTypeDef TIM_OCInitStructure_PWM;

// USART3
#define USART3_PORT                 GPIOB
#define USART3_TXPIN                GPIO_PIN_10
#define USART3_RXPIN                GPIO_PIN_11
#define USART3_BAUDRATE             9600

// Motor
#define MOTOR_WHEEL1_INDEX          1
#define MOTOR_WHEEL1_DIR            1
#define MOTOR_WHEEL1_DIRPIN         GPIO_Pin_6
#define MOTOR_WHEEL1_DIRPROT        GPIOB
#define MOTOR_WHEEL1_PWMPIN         GPIO_Pin_12
#define MOTOR_WHEEL1_PWMPORT        GPIOB

#define MOTOR_WHEEL2_INDEX          2
#define MOTOR_WHEEL2_DIR            1
#define MOTOR_WHEEL2_DIRPIN         GPIO_Pin_7
#define MOTOR_WHEEL2_DIRPROT        GPIOB
#define MOTOR_WHEEL2_PWMPIN         GPIO_Pin_13
#define MOTOR_WHEEL2_PWMPORT        GPIOB

#define MOTOR_WATERPUMP_INDEX       3
#define MOTOR_WATERPUMP_DIR         1
#define MOTOR_WATERPUMP_DIRPIN      GPIO_Pin_8
#define MOTOR_WATERPUMP_DIRPROT     GPIOB
#define MOTOR_WATERPUMP_PWMPIN      GPIO_Pin_14
#define MOTOR_WATERPUMP_PWMPORT     GPIOB

#define MOTOR_TIMER                 TIM4

// �Ƴ��α� ����� ���� �� ����
#define SOIL_MOISTURE_PIN           GPIO_Pin_4
#define SOIL_MOISTURE_PORT          GPIOA
#define SOIL_MOISTURE_ADC           ADC1
#define SOIL_MOISTURE_CHANNEL       ADC_Channel_4

// CDS1 ��ȣ �� ����
#define CDS1_PIN                    GPIO_Pin_4
#define CDS1_PORT                   GPIOC
#define CDS1_ADC                    ADC2
#define CDS1_CHANNEL                ADC_Channel_14

// CDS2 ��ȣ �� ����
#define CDS2_PIN                    GPIO_Pin_5
#define CDS2_PORT                   GPIOC
#define CDS2_ADC                    ADC2
#define CDS2_CHANNEL                ADC_Channel_15

int main(void)
{
    //RCC �ʱ�ȭ
    SystemInit();
    
    USART3_config usart3;
    initUSART3(&usart3, GPIOB, GPIO_Pin_10, GPIO_Pin_11, 9600);
    
    MotorConfig motorconfig;
    motorconfig.wheel1.index =      MOTOR_WHEEL1_INDEX;
    motorconfig.wheel1.dir =        MOTOR_WHEEL1_DIR;
    motorconfig.wheel1.dirPin =     MOTOR_WHEEL1_DIRPIN;
    motorconfig.wheel1.dirPort =    MOTOR_WHEEL1_DIRPROT;
    motorconfig.wheel1.pwmPin =     MOTOR_WHEEL1_PWMPIN;
    motorconfig.wheel1.pwmPort =    MOTOR_WHEEL1_PWMPORT;
    
    motorconfig.wheel2.index =      MOTOR_WHEEL2_INDEX;
    motorconfig.wheel2.dir =        MOTOR_WHEEL2_DIR;
    motorconfig.wheel2.dirPin =     MOTOR_WHEEL2_DIRPIN;
    motorconfig.wheel2.dirPort =    MOTOR_WHEEL2_DIRPROT;
    motorconfig.wheel2.pwmPin =     MOTOR_WHEEL2_PWMPIN;
    motorconfig.wheel2.pwmPort =    MOTOR_WHEEL2_PWMPORT;
    
    motorconfig.waterPump.index =   MOTOR_WATERPUMP_INDEX;
    motorconfig.waterPump.dir =     MOTOR_WATERPUMP_DIR;  
    motorconfig.waterPump.dirPin =  MOTOR_WATERPUMP_DIRPIN;
    motorconfig.waterPump.dirPort = MOTOR_WATERPUMP_DIRPROT;
    motorconfig.waterPump.pwmPin =  MOTOR_WATERPUMP_PWMPIN;
    motorconfig.waterPump.pwmPort = MOTOR_WATERPUMP_PWMPORT;
    
    motorconfig.timer =             MOTOR_TIMER;
    initMotor(&motorconfig);
    
    SoilMoisture soilmoisture;
    initSoilMoistureSensor(&soilmoisture, SOIL_MOISTURE_PORT, SOIL_MOISTURE_PIN, SOIL_MOISTURE_ADC, SOIL_MOISTURE_CHANNEL);
    
    CDS cds1;
    cds1.port =     CDS1_PORT;
    cds1.pin =      CDS1_PIN;
    cds1.adc =      CDS1_ADC;
    cds1.channel =  CDS1_CHANNEL;
    
    CDS cds2;
    cds2.port =     CDS2_PORT;
    cds2.pin =      CDS2_PIN;
    cds2.adc =      CDS2_ADC;
    cds2.channel =  CDS2_CHANNEL;
    
    printf("start!\n");
    
    uint16_t sm, c1, c2;
    
    sm = readSoilMoistureValue(&soilmoisture);
    printf("soilmoisture: %d\n", sm);
    
    initCDSSensor(&cds1);
    c1 = readCDSValue(&cds1);
    printf("cds1: %d\n", c1);
    
    initCDSSensor(&cds2);
    c2 = readCDSValue(&cds2);
    printf("cds2: %d\n", c2);
    
    toggleMotorDirection(&motorconfig.wheel1);
    toggleMotorDirection(&motorconfig.wheel2);
    toggleMotorDirection(&motorconfig.waterPump);
    
    uint16_t data =32;
    while(1)
    {
        data = USART_ReceiveData(USART3);
        switch(data)
        {
        case 'i':
            sm = readSoilMoistureValue(&soilmoisture);
            initCDSSensor(&cds1);
            c1 = readCDSValue(&cds1);
            initCDSSensor(&cds2);
            c2 = readCDSValue(&cds2);
            printf("%d %d %d\n", sm, c1, c2);
            delay_m();
            delay_m();
            delay_m();
            delay_m();
            delay_m();
            delay_m();
            break;
        case 'w':
            printf("hi");
            break;
        }
    
        setMotorSpeedByIndex(&motorconfig, 1, 500);
        setMotorSpeedByIndex(&motorconfig, 2, 500);
        setMotorSpeedByIndex(&motorconfig, 3, 500);
    
    }
}