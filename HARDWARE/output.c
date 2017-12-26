#include "output.h"

void Data_LED_Init(void);//data指示灯
void U2_RS485_Ctl_Init(void);//U2 485控制脚
void U3_RS485_Ctl_Init(void);
void U4_RS485_Ctl_Init(void);
void U5_RS485_Ctl_Init(void);
void TTL_COM_Ctl_Init(void);
void Output_Init(void)
{
	Data_LED_Init();
	U4_RS485_Ctl_Init();
	U5_RS485_Ctl_Init();
	TTL_COM_Ctl_Init();
}

void Data_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_Structure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_15;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);//置低	
}

void U2_RS485_Ctl_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_S;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_Init_S.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init_S.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_S);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void U3_RS485_Ctl_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_S;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_Init_S.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init_S.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Init_S);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}

void U4_RS485_Ctl_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_S;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_Init_S.GPIO_Pin=GPIO_Pin_14;
	GPIO_Init_S.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_S);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void U5_RS485_Ctl_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_S;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_Init_S.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init_S.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_S);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}
void TTL_COM_Ctl_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_S;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_Init_S.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init_S.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_S.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_S);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
}
