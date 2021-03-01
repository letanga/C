#include "usart.h"
#include <stdarg.h>
#include "misc.h"
#include "stm32f10x_usart.h"
#include "Remote.h"
//串口接收DMA缓存
u8 newLineReceived = 0;
u8 inputString[80] = {0};
uint8_t Uart_Rx[UART_RX_LEN] = {0};
int num = 0;
u8 startBit = 0;
int int9num =0;
u8 Fore,Back,Left,Right;
u8 Bluetooth_data;
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义初始化结构体
	USART_InitTypeDef USART_InitStructure;//定义初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO和串口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO PA9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO PA10
	
	USART_InitStructure.USART_BaudRate = 115200;//设置波特率115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不使用硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//发送接收模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_Cmd(USART1, ENABLE);//使能串口1
}

void USART3_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	//定义串口初始化结构体
	
	/* config USART3 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
		/* config GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB	, ENABLE);
	/* USART3 GPIO config */
	/* Configure USART3 Tx (PB.10) as alternate function push-pull 推拉输出模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	/* Configure USART3 Rx (PB.11) as input floating 浮点输入模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	
	
	NVIC_Configurationusart3(); 
	/* USART3 mode config */
	//USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_BaudRate = 9600;//波特率9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//禁用RTSCTS硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//使能发送接收
  

	USART_Init(USART3, &USART_InitStructure); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能接收中断
	
	USART_Cmd(USART3, ENABLE);
	
}




void NVIC_Configurationusart3(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;
/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void USART3_IRQHandler(void) 
{
	
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)//接收中断标志位拉高
	{
		Bluetooth_data=USART_ReceiveData(USART3);//保存接收的数据
		
		if(Bluetooth_data==0x00)Fore=0,Back=0,Left=0,Right=0;//刹
		else if(Bluetooth_data==0x01)Fore=1,Back=0,Left=0,Right=0;//前
		else if(Bluetooth_data==0x05)Fore=0,Back=1,Left=0,Right=0;//后
		else if(Bluetooth_data==0x03)Fore=0,Back=0,Left=1,Right=0;//左
		else if(Bluetooth_data==0x07)Fore=0,Back=0,Left=0,Right=1;//右
		else										Fore=0,Back=0,Left=0,Right=0;//刹
	}
}
/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}



//输出字符串到串口1
void PrintChar(char *s)
{
	char *p;
	p=s;
	while(*p != '\0')
	{
		USART_SendData(USART1, *p);        //通过库函数  发送数据
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);//等待发送完成。   检测 USART_FLAG_TC 是否置1；    //见库函数 P359 介绍
		p++;
	}
}

