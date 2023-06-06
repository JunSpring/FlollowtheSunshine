#include "soil_moisture_sensor.h"

void initSoilMoistureSensor(SoilMoisture* sensor, GPIO_TypeDef* port, uint16_t pin, ADC_TypeDef* adc, uint8_t channel)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    sensor->port = port;
    sensor->pin = pin;
    sensor->adc = adc;
    sensor->channel = channel;

    if (adc == ADC1) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    }
    else if (adc == ADC2) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    }
    else if (adc == ADC3) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    }

    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(port, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(adc, &ADC_InitStructure);

    ADC_RegularChannelConfig(adc, channel, 1, ADC_SampleTime_13Cycles5);

    ADC_Cmd(adc, ENABLE);

    ADC_ResetCalibration(adc);
    while (ADC_GetResetCalibrationStatus(adc))
        ;
    ADC_StartCalibration(adc);
    while (ADC_GetCalibrationStatus(adc))
        ;
}

uint16_t readSoilMoistureValue(SoilMoisture* sensor)
{
    ADC_SoftwareStartConvCmd(sensor->adc, ENABLE);
    while (ADC_GetFlagStatus(sensor->adc, ADC_FLAG_EOC) == RESET)
        ;
    uint16_t moistureValue = ADC_GetConversionValue(sensor->adc);
    ADC_SoftwareStartConvCmd(sensor->adc, DISABLE);

    return moistureValue;
}
