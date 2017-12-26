#ifndef __INPUT_H
#define __INPUT_H


#include "sys.h"


#define WIFI_READY_State GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)	//PB4 nReady 模块工作正常 低有效
#define WIFI_LINK_State  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) //PB3 nLink  模块 WiFi 连接 低有效
#define CHARGE_STATE GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)	 //PB0 CHARGE STATE
#define CHARGE_OK GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)			//PB1 CHARGE OK


void Input_Init(void);

#endif
