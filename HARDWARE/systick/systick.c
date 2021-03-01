#include "systick.h"
#include "stm32f10x.h"
#include "car.h"
#include "Remote.h"

u16 TimeDelay=0;

extern void SysTick_Init(void)		  //1ms定时时钟
{
	if (SysTick_Config(SystemCoreClock / 200))	// ST3.5.0库版本   1s/x= a ms  即5ms产生一次systick中断
 	{ 
		while(1);
	}
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)				 //5ms定时器
{  
	BST_u8SpeedControlCount++;
	GetMotorPulse();						//脉冲计算函数
	
	AngleControl();		//角度PD控制PWNM输出
	Remote_Control();
	TurnControl();
	MotorOutput();					  //小车总PWM输出  	

  if(BST_u8SpeedControlCount>=8)       //当计数值8时，即总系统运行40ms时候(每10个角度PWM输出中融入1个速度PWM输出，这样能保持速度PID输出不干扰角度PID输出，从而影响小车平衡)
	{	
		
		SpeedControl();                     //车模速度控制函数   每40ms调用一次
		BST_u8SpeedControlCount=0;		  //小车速度控制调用计数值清零
		//BST_u8SpeedControlPeriod=0;		  //平滑输出比例值清零
	}
}
