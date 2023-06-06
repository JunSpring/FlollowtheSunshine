#include "stm32f10x.h"

/* for문으로 제작한 딜레이 함수 */
static void delay_int_count(volatile unsigned int nTime)
{
    for(; nTime>0; nTime--);
}

// 마이크로초(us) 단위 딜레이 함수
void delay_us(uint32_t us)
{
    // 시스템 클럭 주파수를 얻어옴 (예: 16MHz)
    uint32_t freq = SystemCoreClock / 1000000;
    
    // 마이크로초 단위 딜레이
    delay_int_count(us * freq);
}

// 밀리초(ms) 단위 딜레이 함수
void delay_ms(uint32_t ms)
{
    // 시스템 클럭 주파수를 얻어옴 (예: 16MHz)
    uint32_t freq = SystemCoreClock / 1000;
    
    // 밀리초 단위 딜레이
    delay_int_count(ms * freq);
}

// 초(s) 단위 딜레이 함수
void delay_s(uint32_t s)
{
    // 시스템 클럭 주파수를 얻어옴 (예: 16MHz)
    uint32_t freq = SystemCoreClock;
    
    // 초 단위 딜레이
    delay_int_count(s * freq);
}