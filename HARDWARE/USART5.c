#include "sys.h"
#include "USART5.h"

u8 USART5_RX_BUF[USART5_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART5_RX_STA=0;       //����״̬���	 
u16 USART5_RX_Count=0;		 //���ռ���

void UART5_IRQHandler(void)                	//����5�жϷ������
{
	u8 Res;
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж�
		{
			Res=USART_ReceiveData(UART5);	
			//printf("U5:%c\n",Res);
			USART5_RX_BUF[USART5_RX_Count]=Res;
			USART5_RX_Count++;
     
		if(USART5_RX_Count>=USART5_REC_LEN)
		{
			USART5_RX_Count=0;//��ֹ���
		}
		USART5_Delay_Count=0;
		
    } 
}


/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch )
{
	/* ����һ���ֽ����ݵ�USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ�������� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*****************  ָ�����ȵķ����ַ��� **********************/
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(k < strlen);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str)
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(*(str + k)!='\0');
}

/*************************************************************
��ʼ������
**************************************************************/
void USART5_Init(u32 bound)
{
			//GPIO�˿�����
			GPIO_InitTypeDef GPIO_InitStructure;
			USART_InitTypeDef USART_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE );//ʹ��GPIOCʱ��
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE );//ʹ��GPIOCʱ��
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//ʹ��USART5
			
			//USART5_TX   GPIOC.12
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC.12
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
			GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.12
			 
			//USART5_RX	  GPIOD.2
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PD.2
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
			GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOC.11 

			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
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
			USART_Init(UART5, &USART_InitStructure); //��ʼ������5
			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
			USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ���1 

}
