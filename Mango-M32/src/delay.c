#include "stm32f10x.h"

/* for������ ������ ������ �Լ� */
static void delay_int_count(volatile unsigned int nTime)
{
    for(; nTime>0; nTime--);
}

// ����ũ����(us) ���� ������ �Լ�
void delay_us(uint32_t us)
{
    // �ý��� Ŭ�� ���ļ��� ���� (��: 16MHz)
    uint32_t freq = SystemCoreClock / 1000000;
    
    // ����ũ���� ���� ������
    delay_int_count(us * freq);
}

// �и���(ms) ���� ������ �Լ�
void delay_ms(uint32_t ms)
{
    // �ý��� Ŭ�� ���ļ��� ���� (��: 16MHz)
    uint32_t freq = SystemCoreClock / 1000;
    
    // �и��� ���� ������
    delay_int_count(ms * freq);
}

// ��(s) ���� ������ �Լ�
void delay_s(uint32_t s)
{
    // �ý��� Ŭ�� ���ļ��� ���� (��: 16MHz)
    uint32_t freq = SystemCoreClock;
    
    // �� ���� ������
    delay_int_count(s * freq);
}