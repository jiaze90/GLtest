#define INPUT_MODULE

#include "input.h"


void Wifi_State_Init(void);
void Power_State_Init(void);


void Input_Init(void)
{
	Wifi_State_Init();
	Power_State_Init();

}

//PB3 nLink  模块 WiFi 连接
//PB4 nReady 模块工作正常
void Wifi_State_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4 ;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIO_Init_Structure);
	
}

//PB0 CHARGE STATE
//PB1 CHARGE OK
/* test code

while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
				USART_SendData(USART1,GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0));
				
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
				USART_SendData(USART1,GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
*/
void Power_State_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 ;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
	
}

