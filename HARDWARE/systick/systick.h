#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "stm32f10x.h"

extern u16 TimeDelay;
extern void delay_nms(u16 nTime);
extern void SysTick_Init(void);
#endif
