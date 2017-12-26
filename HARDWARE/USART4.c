#include "sys.h"
#include "USART4.h"

u8 USART4_RX_BUF[USART4_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART4_RX_Count=0;									//���ռ���
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART4_RX_STA=0;       //����״̬���	 


void UART4_IRQHandler(void)                	//����4�жϷ������
	{
	u8 Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res=USART_ReceiveData(UART4);	//��ȡ���յ�������
			//printf("U4:%c\n",Res);
			USART4_RX_BUF[USART4_RX_Count]=Res;
			USART4_RX_Count++;
     
		if(USART4_RX_Count>=USART4_REC_LEN)
		{
			USART4_RX_Count=0;//��ֹ���
		}
		USART4_Delay_Count=0;
			
     } 
	}

void USART4_Init(u32 bound)
{
			//GPIO�˿�����
			GPIO_InitTypeDef GPIO_InitStructure;
			USART_InitTypeDef USART_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE );//ʹ��GPIOCʱ��
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//ʹ��USART4
			
			//USART4_TX   GPIOC.10
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
			GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.10
			 
			//USART4_RX	  GPIOC.11
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC.11
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
			GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.11 

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
			
			 //USART ��ʼ������
			USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
			USART_Init(UART4, &USART_InitStructure); //��ʼ������4
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
			USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���1 

}
