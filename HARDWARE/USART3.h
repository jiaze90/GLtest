#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "sys.h"

#define USART3_REC_LEN  			5000  	//定义最大接收字节数
//#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收	  	
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记	
extern u16 USART3_RX_Count;
void USART3_Init(u32 bound);

#define U3_RS485_TX_EN PCout(3)	//485模式控制.0,接收;1,发送.

#endif 
