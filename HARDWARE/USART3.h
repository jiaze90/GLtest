#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "sys.h"

#define USART3_REC_LEN  			5000  	//�����������ֽ���
//#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����	  	
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���	
extern u16 USART3_RX_Count;
void USART3_Init(u32 bound);

#define U3_RS485_TX_EN PCout(3)	//485ģʽ����.0,����;1,����.

#endif 
