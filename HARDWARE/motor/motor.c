#include "motor.h"
#include "stm32f10x.h"

void MOTOR_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//选择要控制的GPIOB引脚	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置引脚模式为通用推挽输出  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速率为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO	  
	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_12 | GPIO_Pin_15);//全部初始化为高电平，制动状态
}
