#ifndef __USART1_H
#define __USART1_H
#include "stdio.h"	
#include "sys.h"

#define USART1_REC_LEN  			5000  	//定义最大接收字节数
//#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         		//接收状态标记	
extern u16 USART1_RX_Count;
void USART1_Init(u32 bound);



#endif 
