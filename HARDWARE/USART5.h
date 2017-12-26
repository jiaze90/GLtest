#ifndef __USART5_H
#define __USART5_H
#include "stdio.h"	
#include "sys.h"

#define USART5_REC_LEN  			5000  	//定义最大接收字节数
#define EN_USART5_RX 			1		//使能（1）/禁止（0）串口1接收	  	
extern u8  USART5_RX_BUF[USART5_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART5_RX_STA;         		//接收状态标记	
extern u16 USART5_RX_Count;		//接收技术

void USART5_Init(u32 bound);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch );
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen );
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str);

#define U5_RS485_TX_EN PBout(13)	//485模式控制.0,接收;1,发送.

#endif 
