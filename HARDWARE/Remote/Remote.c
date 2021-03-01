#include "Remote.h"
#include "NRF24L01.h"
#include "stm32f10x.h"
#include "car.h"
#include "usart.h"
float BST_BluetoothSpeed=0;
void Remote_Control(void)
{
	if(Fore==0&&Back==0&&Left==0&&Right==0)
	{
		if(BST_BluetoothSpeed<=2.5&&BST_BluetoothSpeed>=-2.5)
		{
			BST_BluetoothSpeed=0;
		}
		if(BST_BluetoothSpeed>5)
		{
			BST_BluetoothSpeed-=5;
		}
		if(BST_BluetoothSpeed<-5)
		{
			BST_BluetoothSpeed+=5;
		}
		if(BST_BluetoothSpeed==0&&BST_fCarSpeed>=-2.5&&BST_fCarSpeed<=2.5)
		{
			BST_fCarTurn_Kd=0.24;
		}
		BST_fCarTurn_Kp=0;
	}
	else if(Fore==1)
	{
		//BST_fCarTurn_Kd=0;
		BST_fCarTurn_Kd=0.24;
		BST_BluetoothSpeed+=5;
	}
	else if(Back==1)
	{
		//BST_fCarTurn_Kd=0;
		BST_fCarTurn_Kd=0.24;
		BST_BluetoothSpeed-=5;
	}
	
//	
//	if(Left==0&&Right==0)
//	{
//		BST_fCarTurn_Kd=0.25;
//		BST_fCarTurn_Kp=0;
//	}
	else if(Left==1)
	{
		BST_fCarTurn_Kd=0;
		BST_fCarTurn_Kp=1;
		BST_TurnSpeed+=20;
	}
	else if(Right==1)
	{
		BST_fCarTurn_Kd=0;
		BST_fCarTurn_Kp=1;
		BST_TurnSpeed-=20;
	}
	BST_BluetoothSpeed=BST_BluetoothSpeed>300?300:(BST_BluetoothSpeed<-300?-300:BST_BluetoothSpeed);
	BST_TurnSpeed=BST_TurnSpeed>500?500:(BST_TurnSpeed<-500?-500:BST_TurnSpeed);
}
