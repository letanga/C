#ifndef _DELAY_H_
#define _DELAY_H_
#include "stm32f10x.h"

extern void delay_us(u32 n);
extern void delay_ms(u32 n);
extern void get_ms(unsigned long *time);
extern void delay_nms(u16 time);

#endif
