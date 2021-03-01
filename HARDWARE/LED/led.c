#include "led.h"
#include "stm32f10x.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义初始化结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO,ENABLE);//使能GPIOB和AFIO的外设时钟
	
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能													   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//选择要控制的GPIOB引脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速率为50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置引脚模式为通用推挽输出
	
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOB	 
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);//打开led灯
}

