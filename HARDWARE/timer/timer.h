#ifndef _TIMER_H_
#define _TIMER_H_
#include "sys.h"

extern void TIM2_PWM_Init(void);
extern void TIM3_Encoder_Init(void);
extern void TIM4_Encoder_Init(void);

extern void TIM3_IRQHandler(void);
extern void TIM4_IRQHandler(void);



#endif
