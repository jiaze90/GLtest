#include "sys.h"
#include "output.h"
#include "USART1.h"
#include "USART2.h"
#include "USART3.h"
#include "USART4.h"
#include "USART5.h"
#include "timer.h"
#include "dma.h"
u16 USART1_Delay_Count=0;
u16 USART2_Delay_Count=0;
u16 USART3_Delay_Count=0;
u16 USART4_Delay_Count=0;
u16 USART5_Delay_Count=0;
#define SEND_DELAY_COUNT 3
#define RECEIVED_DELAY_COUNT 3
u8 Send_Buf[USART1_REC_LEN];
int main()
{
	u8 Send_Choice=0;
	u8 U1_Sending_flag=0;//�ϴ����ͱ�־λ
	u16 U1_RX_Send_Count=0;
	u16 Send_Flag_Down=0;//�·����ͱ�־λ  
	u16 i_temp=0;
	delay_init();
	Output_Init();
	USART1_Init(345600);
	USART2_Init(115200);
	USART3_Init(115200);
	USART4_Init(115200);
	USART5_Init(115200);
	TIM3_Int_Init(19,7199); //10Khz �ļ���Ƶ�ʣ������� 5000 Ϊ 500ms     ��ǰ����2ms�ж�һ��   9��49 ��Ϊ5ms
	printf("Init OK.\n");
		while(1)
		{
			//U2-U4���� ͨ��U1�ϴ�����
			if(!U1_Sending_flag)
			{
				switch(Send_Choice)
				{
					case 0:

						if(USART2_Delay_Count>=SEND_DELAY_COUNT&&USART2_RX_Count!=0||USART2_RX_Count>=1000)
						{
							//����MDA ִ��һ�δ���
							//USART2_RX_BUF[USART2_RX_Count]=0x45;
							MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)USART2_RX_BUF,USART2_RX_Count);
							USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
							MYDMA_Enable(DMA1_Channel4);//start a sending.
							U1_Sending_flag=1;
							USART2_RX_Count=0;
						}
						Send_Choice++;break;
						
					case 1:
						if(USART3_Delay_Count>=SEND_DELAY_COUNT&&USART3_RX_Count!=0||USART3_RX_Count>=1000)
						{
							//����MDA ִ��һ�δ���
							//USART3_RX_BUF[USART3_RX_Count]=0x46;
							MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)USART3_RX_BUF,USART3_RX_Count);
							USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
							MYDMA_Enable(DMA1_Channel4);//start a sending.
							U1_Sending_flag=1;
							USART3_RX_Count=0;
						}
						Send_Choice++;break;
						
					case 2:
						
						if(USART4_Delay_Count>=SEND_DELAY_COUNT&&USART4_RX_Count!=0||USART4_RX_Count>=1000)
						{
							//����MDA ִ��һ�δ���
							MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)USART4_RX_BUF,USART4_RX_Count);
							USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
							MYDMA_Enable(DMA1_Channel4);//start a sending.
							U1_Sending_flag=1;
							USART4_RX_Count=0;
						}
						Send_Choice++;break;
						
					case 3:
						if(USART5_Delay_Count>=SEND_DELAY_COUNT&&USART5_RX_Count!=0||USART5_RX_Count>=1000)
						{
							//����MDA ִ��һ�δ���
							MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)USART5_RX_BUF,USART5_RX_Count);
							USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
							MYDMA_Enable(DMA1_Channel4);//start a sending.
							U1_Sending_flag=1;
							USART5_RX_Count=0;
						}
					
						Send_Choice=0;break;
				}
			}
			if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)	//�ж�ͨ��4�������
			{
					
					DMA_ClearFlag(DMA1_FLAG_TC4);//���������ɱ�־ 
					U1_Sending_flag=0;
					//delay_ms(2);
			}
			
			//U1���� ͨ��U2-U4�·�����
			if(USART1_RX_Count!=0&&USART1_Delay_Count>=RECEIVED_DELAY_COUNT)
			{
				//��������
				for(i_temp=0;i_temp<USART1_RX_Count;i_temp++)
				{
					Send_Buf[i_temp]=USART1_RX_BUF[i_temp];
				}
				U1_RX_Send_Count=USART1_RX_Count;
				
				USART1_RX_Count=0;
				Send_Flag_Down=1;
			}
			
			if(USART2_RX_Count==0&&USART3_RX_Count==0&&USART4_RX_Count==0&&USART5_RX_Count==0&&Send_Flag_Down==1)//ȫ����ɽ�����
			{
				//ִ�з�������
				Send_Flag_Down=0;
				i_temp=U1_RX_Send_Count;
				U2_RS485_TX_EN=1;//ת����ģʽ
				U3_RS485_TX_EN=1;
				U4_RS485_TX_EN=1;
				U5_RS485_TX_EN=1;
				//printf("Send.");
				while(U1_RX_Send_Count)
				{
					//printf("%c",Send_Buf[i_temp-U1_RX_Send_Count]);
					
					//USART_SendData(USART1,Send_Buf[i_temp-USART1_RX_Count]);
					USART_SendData(USART2,Send_Buf[i_temp-U1_RX_Send_Count]);
					USART_SendData(USART3,Send_Buf[i_temp-U1_RX_Send_Count]);
					USART_SendData(UART4,Send_Buf[i_temp-U1_RX_Send_Count]);
					USART_SendData(UART5,Send_Buf[i_temp-U1_RX_Send_Count]);
					while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!=SET);
					U1_RX_Send_Count--;
				}
				Send_Flag_Down=0;//��λ�����ͱ�־
				U2_RS485_TX_EN=0;//ת����ģʽ
				U3_RS485_TX_EN=0;
				U4_RS485_TX_EN=0;
				U5_RS485_TX_EN=0;
			}

		}
}
			/*U4_RS485_TX_EN=1;
			USART_SendData(UART4,0X41);
			while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);
			U4_RS485_TX_EN=0;
			delay_ms(500);
			Data_LED_ON;
			U5_RS485_TX_EN=1;
			USART_SendData(UART5,0X42);
			while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!=SET);
			U5_RS485_TX_EN=0;
			delay_ms(500);
			Data_LED_OFF;*/
