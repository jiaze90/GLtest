#ifndef __USART4_H
#define __USART4_H
#include "stdio.h"	
#include "sys.h"

#define USART4_REC_LEN  			5000  	//�����������ֽ���
#define EN_USART4_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����	  	
extern u8  USART4_RX_BUF[USART4_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART4_RX_STA;         		//����״̬���	
extern u16 USART4_RX_Count;					  //���ռ���
void USART4_Init(u32 bound);
#define U4_RS485_TX_EN PBout(14)	//485ģʽ����.0,����;1,����.


#endif 
