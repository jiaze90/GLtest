#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
#include "delay.h"
extern u16 USART1_Delay_Count;
extern u16 USART2_Delay_Count;
extern u16 USART3_Delay_Count;
extern u16 USART4_Delay_Count;
extern u16 USART5_Delay_Count;
/**********************************************
��������
**********************************************/
#define MAX_AT_DELAY_TIME 600	//0.005S/��*n
#define WIFI_POWER_OFF_DELAY_TIME 300 //0.005S/��*n
#define READ_WIFI_STATE_MESSAGE_DELAY_TIME1 500 //0.005S/��*n
#define READ_WIFI_STATE_MESSAGE_DELAY_TIME2 1000 //0.005S/��*n
#define AT_and_AT_DELAY_TIME 2 //0.005S/��*n
#define FROM_DATA_TRANS_TO_AT_DELAY_TIME 3  //0.005S/��*n
#define READ_ID_TIME_INTERVAL 300		//0.005S/��  ��ȡIDоƬʱ������ÿһͨ����
#define READ_WIFI_MESSAGE_TIMEOUT 250
#define WIFI_RESTART_DELAY_TIME 20
#define RESET_AT_COUNT 2

#define SEND_BUF_SIZE 51 //�������ݰ��ֽ���

#define DES_ID_L 0x09
#define DES_ID_H 0xB0

#define SRC_ID_L 0x98
#define SRC_ID_H 0x00

#define FILTER_VALUE	5

#define DATA_LENGTH 4 //MAX=36  4�ı��� һ�����ݰ����ɼ��ĳ��� 

#define DATA_BUFFER_SIZE 1600


#define FLASH_SAVE_ADDR  0X08070000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)


/**********************************************
�ṹ�嶨��
***********************************************/



/**********************************************
ȫ�ֱ�������
***********************************************/
extern u8 WIFI_Mode_Flag;//ATָ��ģʽ 1  ͸��ģʽ0
extern u8 Receive_Choice;//0 UART5���� 1UART4����
//extern u8 SendOKflag;//ATָ��ͳɹ���ʶ
//extern u8 ATOKflag;//����ָ��ģʽ��ʶ
extern u8 Enter_AT_flag;
extern u8 Exit_AT_flag;
extern u8 Set_TCP_Parameter_flag;//1 �յ��µ�TCPָ��
extern u8 Wifi_Reset_flag;//1-��Ҫ��λ
extern u8 Send_Enable_flag;//1-TCP�ѽ��� ���Է��� 0-δ���� ���ɷ���
extern u8 Read_Message_Stage;//��ȡWIFI�����Ľ׶�ֵ
extern u8 WIFI_TCP_State;//0-�Ͽ� 1����
extern u8 Received_UDP_flag;//�յ�UDP�� ��1
extern u8 POWER_LED_BLN_Enable;//��Դ�����������˸��־
extern u8 Channel_ID_DATA[4][2];//ID
extern int Run_Count;
extern int Get_Data_Count;
extern int Total_Send_Count;
extern int DMA_Reset_Count;
extern uint16_t AD7193_RawData_Count;
extern uint16_t AD7193_Data_Send_Count;

extern volatile unsigned long AD7193_Raw_Data[DATA_BUFFER_SIZE];
extern volatile u8 AD7193_Send_flag[DATA_BUFFER_SIZE];

/**********************************************
��ʱ����������
************************************************/

extern uint16_t Timer3_AT_Count;//ATָ�ʱ�ж�
extern uint16_t Timer3_Wifi_Reset_Count;//WIFI������ʱ 
extern uint16_t Timer3_Read_Wifi_Message_Count;//��ȡWIFI״̬���������
extern uint16_t Timer3_Read_Wifi_Message_Timeout_Count;//��ȡWIFI״̬��ʱ������
extern uint16_t Timer3_Enter_AT_Mode_Delay_Count;//����ATָ��ǰ����ʱ������
extern uint16_t Timer3_WIFI_LED_Count;		//WIFI/DATA LED���ƶ�ʱ��
extern uint16_t Timer3_Read_ID_Count;		//��ȡIDоƬʱ����
extern uint16_t Timer3_POWER_LED_Count;	//��Դָʾ�ƿ��ƶ�ʱ��
extern uint16_t Timer3_AD7193_Reset_Count;	//AD7193��λ������
extern uint16_t RTC_Wifi_Restart_Count;//����ͳ��reset at�Ĵ���ʱ����Ƽ�����
extern uint16_t Timer3_Send_Delay_Reset_Count;//���ͼ��㸴λ
/**********************************************
IO
***********************************************/
#define WIFI_State GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) //ģ��״̬
#define WIFI_Link GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)  //ģ������״̬



//0,��֧��ucos
//1,֧��ucos
#define SYSTEM_SUPPORT_OS		0		//����ϵͳ�ļ����Ƿ�֧��UCOS
																	    
	 

//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

//����Ϊ��ຯ��
void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(u32 addr);	//���ö�ջ��ַ

#endif
