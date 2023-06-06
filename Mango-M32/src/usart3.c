#include "usart3.h"

void initUSART3(USART3_config* config, GPIO_TypeDef* port, uint16_t txPin, uint16_t rxPin, uint32_t baudRate)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    // Configure USARTx_Tx as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = txPin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(port, &GPIO_InitStructure);

    // Configure USARTx_Rx as input floating
    GPIO_InitStructure.GPIO_Pin = rxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(port, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = baudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure the USARTx */
    USART_Init(USART3, &USART_InitStructure);

    /* Enable the USART1 */
    USART_Cmd(USART3, ENABLE);
}


#ifdef __GNUC__
int __io_putchar(int ch)
{
    // Transmit Data 
    USART_SendData(USART3, (uint8_t)ch);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
    {
    }
    return ch;
}
#else
int fputc(int ch, FILE *f)
{
    // Transmit Data 
    USART_SendData(USART3, (uint8_t)ch);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
    {
    }
    return ch;
}
#endif