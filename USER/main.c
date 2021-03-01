#include "stm32f10x.h"
#include "timer.h"
#include "motor.h"
#include "usart.h"
#include "led.h"
#include "I2C.h"
#include "systick.h"
#include "car.h"
#include "mpu6050.h"
#include "NRF24L01.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置优先级分组2
	USART1_Config();//串口1初始化，用于下载程序和打印MPU6050相关的日志
	USART3_Config();
	TIM2_PWM_Init();//定时器2初始化用于产生PWM波控制电机
	TIM3_Encoder_Init(); //定时器3初始化，编码器模式用于计算车速
	TIM4_Encoder_Init();//定时器4初始化，编码器模式用于计算车速
	//NRF24L01_init();
	MOTOR_GPIO_Config();//电机参数初始化
	LED_GPIO_Config();//LED初始化
	i2cInit();//I2C初始化
	delay_nms(10);
	MPU6050_Init();	//MPU6050初始化
	CarUpstandInit();//直立参数初始化
	SysTick_Init();//Systick初始化，用于整个系统运行
	while(1)
	{
		MPU6050_Pose();//不断获取姿态
	}
}

