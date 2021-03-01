#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>
#define UART_RX_LEN		128
extern u8 newLineReceived;
extern u8 inputString[80];
extern uint8_t Uart_Rx[UART_RX_LEN];

extern int num;
extern u8 startBit;
extern int int9num;
extern u8 Bluetooth_data;

void USART1_Config(void);
void USART3_Config(void);
int  fputc(int ch, FILE *f);
void PrintChar(char *s);
void NVIC_Configurationusart3(void);
extern u8 Fore,Back,Left,Right;

#endif /* __USART1_H */
