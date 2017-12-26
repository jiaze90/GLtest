#include "sys.h"
#include "USART5.h"

u8 USART5_RX_BUF[USART5_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART5_RX_STA=0;       //接收状态标记	 
u16 USART5_RX_Count=0;		 //接收计数

void UART5_IRQHandler(void)                	//串口5中断服务程序
{
	u8 Res;
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断
		{
			Res=USART_ReceiveData(UART5);	
			//printf("U5:%c\n",Res);
			USART5_RX_BUF[USART5_RX_Count]=Res;
			USART5_RX_Count++;
     
		if(USART5_RX_Count>=USART5_REC_LEN)
		{
			USART5_RX_Count=0;//防止溢出
		}
		USART5_Delay_Count=0;
		
    } 
}


/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch )
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*****************  指定长度的发送字符串 **********************/
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(k < strlen);
}

/*****************  发送字符串 **********************/
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
初始化函数
**************************************************************/
void USART5_Init(u32 bound)
{
			//GPIO端口设置
			GPIO_InitTypeDef GPIO_InitStructure;
			USART_InitTypeDef USART_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE );//使能GPIOC时钟
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE );//使能GPIOC时钟
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//使能USART5
			
			//USART5_TX   GPIOC.12
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC.12
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
			GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.12
			 
			//USART5_RX	  GPIOD.2
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PD.2
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
			GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOC.11 

			//Usart1 NVIC 配置
			NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
			NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
			
			 //USART 初始化设置
			USART_InitStructure.USART_BaudRate = bound;//串口波特率
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
			USART_Init(UART5, &USART_InitStructure); //初始化串口5
			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启串口接受中断
			USART_Cmd(UART5, ENABLE);                    //使能串口1 

}
