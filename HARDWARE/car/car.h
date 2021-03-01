#ifndef _CAR_H_
#define _CAR_H_

#include "stm32f10x.h"

#define CAR_POSITION_SET (0)

#define MOTOR_OUT_DEAD_VAL       0	   //死区值0
#define MOTOR_OUT_MAX           1000	   //占空比正最大值
#define MOTOR_OUT_MIN         (-1000)   //占空比负最大值

#define CAR_POSITION_MAX	8000       //8000
#define CAR_POSITION_MIN	(-8000)     //-8000

extern float CAR_SPEED_SET;
extern float CAR_ZERO_ANGLE;
extern s16 BST_s16LeftMotorPulse;
extern s16 BST_s16RightMotorPulse;

extern s32 BST_s32LeftMotorPulseSigma;
extern s32 BST_s32RightMotorPulseSigma;

extern float BST_fCarSpeed;
extern float BST_fCarSpeedOld;
extern float BST_TurnSpeed;
extern float BST_fCarPosition;
extern float BST_fCarAngle;
extern float BST_fAngleControlOut;
extern float BST_fSpeedControlOut;
extern float BST_fLeftMotorOut;
extern float BST_fRightMotorOut;

extern float BST_u8MainEventCount;
extern float BST_u8SpeedControlCount;
extern float BST_u8SpeedControlPeriod;

/*****************多数据************************/

extern u8 BST_u8DirectionControlPeriod;
extern u8 BST_u8DirectionControlCount;					  //转向控制循环计数  在SysTick_Handler(void)中使用 每5ms加1 
extern u8 BST_u8trig;
extern u8 ucBluetoothValue;                      //蓝牙接收数据
extern float volt;



/******电机控制参数******/
extern float BST_fSpeedControlOut;						   //速度控制PWM
extern float BST_fSpeedControlOutOld;
extern float BST_fSpeedControlOutNew;
extern float BST_fAngleControlOut;
extern float BST_fTurnControlOut;
extern float BST_fLeftMotorOut;
extern float BST_fRightMotorOut;

extern float BST_fCarAngle;						 //角度控制PWM
extern float gyro_z;
extern float gyrx;
extern float gy0;

/*-----角度环和速度环PID控制参数-----*///以下参考为重点调试参考，同电池电压有关，建议充好电再调试
extern float  BST_fCarAngle_P; //调大小时会左右摆，调大时会振动  请调到基本能够站立 P=91.3是用于给小车在运动过程使用
extern float  BST_fCarAngle_D;	// 0.001 0.002 0.004 0.008 0.0010 0.011	 调小时反应慢，调大时会干扰

extern float  BST_fCarSpeed_P;
extern float  BST_fCarSpeed_I;

extern float BST_fCarTurn_Kd;
extern float BST_fCarTurn_Kp;
extern const double PID_Original[4];
extern char  alldata[80];
extern char *iap;

/******速度控制参数******/
extern s16   BST_s16LeftMotorPulse;					  //左电机脉冲数
extern s16	  BST_s16RightMotorPulse;					   //右电机脉冲数

extern s32   BST_s32LeftMotorPulseOld;
extern s32   BST_s32RightMotorPulseOld;
extern s32   BST_s32LeftMotorPulseSigma;				  //50ms左电机叠加值
extern s32   BST_s32RightMotorPulseSigma;				 //50ms右电机叠加值

extern float BST_fCarSpeed;							 //测速码盘得出的车速
extern float BST_fCarSpeedOld;

extern float BST_fCarPosition;						   //测速码盘通过计算得到的小车位移

/*-----悬停参数-----*/
extern int stopflag;
extern int leftstop;
extern int righttstop;

extern void SetMotorVoltageAndDirection(s16 s16LeftVoltage,s16 s16RightVoltage);
extern void GetMotorPulse(void);
extern void AngleControl(void);
extern void MotorOutput(void);
extern void SetMotorVoltageAndDirection(s16 s16LeftVoltage,s16 s16RightVoltage);
extern void SpeedControl(void);
extern void CarUpstandInit(void);
extern void TurnControl(void);

#endif
