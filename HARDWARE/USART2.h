#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"	
#include "sys.h"

#define USART2_REC_LEN  			5000  	//�����������ֽ���
//#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����	  	
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         		//����״̬���	
extern u16 USART2_RX_Count;

void USART2_Init(u32 bound);

#define U2_RS485_TX_EN PAout(1)	//485ģʽ����.0,����;1,����.

#endif 
