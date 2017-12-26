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
常量定义
**********************************************/
#define MAX_AT_DELAY_TIME 600	//0.005S/次*n
#define WIFI_POWER_OFF_DELAY_TIME 300 //0.005S/次*n
#define READ_WIFI_STATE_MESSAGE_DELAY_TIME1 500 //0.005S/次*n
#define READ_WIFI_STATE_MESSAGE_DELAY_TIME2 1000 //0.005S/次*n
#define AT_and_AT_DELAY_TIME 2 //0.005S/次*n
#define FROM_DATA_TRANS_TO_AT_DELAY_TIME 3  //0.005S/次*n
#define READ_ID_TIME_INTERVAL 300		//0.005S/次  读取ID芯片时间间隔（每一通道）
#define READ_WIFI_MESSAGE_TIMEOUT 250
#define WIFI_RESTART_DELAY_TIME 20
#define RESET_AT_COUNT 2

#define SEND_BUF_SIZE 51 //单个数据包字节数

#define DES_ID_L 0x09
#define DES_ID_H 0xB0

#define SRC_ID_L 0x98
#define SRC_ID_H 0x00

#define FILTER_VALUE	5

#define DATA_LENGTH 4 //MAX=36  4的倍数 一个数据包所采集的长度 

#define DATA_BUFFER_SIZE 1600


#define FLASH_SAVE_ADDR  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)


/**********************************************
结构体定义
***********************************************/



/**********************************************
全局变量定义
***********************************************/
extern u8 WIFI_Mode_Flag;//AT指令模式 1  透传模式0
extern u8 Receive_Choice;//0 UART5接收 1UART4接收
//extern u8 SendOKflag;//AT指令发送成功标识
//extern u8 ATOKflag;//进入指令模式标识
extern u8 Enter_AT_flag;
extern u8 Exit_AT_flag;
extern u8 Set_TCP_Parameter_flag;//1 收到新的TCP指令
extern u8 Wifi_Reset_flag;//1-需要复位
extern u8 Send_Enable_flag;//1-TCP已建立 可以发送 0-未建立 不可发送
extern u8 Read_Message_Stage;//读取WIFI参数的阶段值
extern u8 WIFI_TCP_State;//0-断开 1连接
extern u8 Received_UDP_flag;//收到UDP包 置1
extern u8 POWER_LED_BLN_Enable;//电源灯允许呼吸闪烁标志
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
定时器变量定义
************************************************/

extern uint16_t Timer3_AT_Count;//AT指令超时判断
extern uint16_t Timer3_Wifi_Reset_Count;//WIFI重启计时 
extern uint16_t Timer3_Read_Wifi_Message_Count;//读取WIFI状态间隔计数器
extern uint16_t Timer3_Read_Wifi_Message_Timeout_Count;//读取WIFI状态超时计数器
extern uint16_t Timer3_Enter_AT_Mode_Delay_Count;//进入AT指令前的延时计数器
extern uint16_t Timer3_WIFI_LED_Count;		//WIFI/DATA LED控制定时器
extern uint16_t Timer3_Read_ID_Count;		//读取ID芯片时间间隔
extern uint16_t Timer3_POWER_LED_Count;	//电源指示灯控制定时器
extern uint16_t Timer3_AD7193_Reset_Count;	//AD7193复位计数器
extern uint16_t RTC_Wifi_Restart_Count;//用于统计reset at的次数时间控制计数器
extern uint16_t Timer3_Send_Delay_Reset_Count;//发送计算复位
/**********************************************
IO
***********************************************/
#define WIFI_State GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) //模块状态
#define WIFI_Link GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)  //模块连接状态



//0,不支持ucos
//1,支持ucos
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持UCOS
																	    
	 

//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
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
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址

#endif
