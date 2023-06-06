#include "stm32f10x.h"

/* for문으로 제작한 딜레이 함수 */
static void delay_int_count(volatile unsigned int nTime)
{
    for(; nTime>0; nTime--);
}
void delay_m(void)
{
    delay_int_count(806596/*6*/);
}