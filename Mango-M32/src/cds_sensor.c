#include "cds_sensor.h"

void initCDSSensor(CDS* cds)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    if (cds->adc == ADC1) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    }
    else if (cds->adc == ADC2) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    }
    else if (cds->adc == ADC3) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    }

    GPIO_InitStructure.GPIO_Pin = cds->pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(cds->port, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(cds->adc, &ADC_InitStructure);

    ADC_RegularChannelConfig(cds->adc, cds->channel, 1, ADC_SampleTime_55Cycles5);

    ADC_Cmd(cds->adc, ENABLE);

    ADC_ResetCalibration(cds->adc);
    while (ADC_GetResetCalibrationStatus(cds->adc))
        ;
    ADC_StartCalibration(cds->adc);
    while (ADC_GetCalibrationStatus(cds->adc))
        ;
}

uint16_t readCDSValue(CDS* cds)
{
    ADC_SoftwareStartConvCmd(cds->adc, ENABLE);
    while (ADC_GetFlagStatus(cds->adc, ADC_FLAG_EOC) == RESET)
        ;
    uint16_t cdsValue = ADC_GetConversionValue(cds->adc);
    ADC_SoftwareStartConvCmd(cds->adc, DISABLE);

    return cdsValue;
}
