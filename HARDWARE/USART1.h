#ifndef __USART1_H
#define __USART1_H
#include "stdio.h"	
#include "sys.h"

#define USART1_REC_LEN  			5000  	//�����������ֽ���
//#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���	
extern u16 USART1_RX_Count;
void USART1_Init(u32 bound);



#endif 
