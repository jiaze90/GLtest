#ifndef __USART5_H
#define __USART5_H
#include "stdio.h"	
#include "sys.h"

#define USART5_REC_LEN  			5000  	//�����������ֽ���
#define EN_USART5_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����	  	
extern u8  USART5_RX_BUF[USART5_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART5_RX_STA;         		//����״̬���	
extern u16 USART5_RX_Count;		//���ռ���

void USART5_Init(u32 bound);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch );
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen );
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str);

#define U5_RS485_TX_EN PBout(13)	//485ģʽ����.0,����;1,����.

#endif 
