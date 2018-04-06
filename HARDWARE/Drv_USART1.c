/**
  ******************************************************************************
  * @file    Drv_USART1.c
  * @author  彭澎(1252714)
  * @version V1.0
  * @date    2015/10/26
  * @brief   USART1驱动源文件
  ******************************************************************************	
  * @attention
  * USART1_TX --> PA9
  * USART2_RX --> PA10
  ******************************************************************************			
  */ 
	
#include "Drv_USART1.h"

/**
* @brief  USART1初始化函数
* @param  baud:波特率
* @retval 无
*/
void USART1_Init(uint32_t baud)
{
	/*开启GPIOA、USART1外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/*配置GPIO管脚工作模式*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //复用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //最大工作频率：50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                        
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                            
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                    //上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                       
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                            
	                                                                                 
	/*配置USART1工作模式*/                                                           
	USART_InitTypeDef USART_InitStructure;                                           
	USART_InitStructure.USART_BaudRate = baud;                                       //设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //8位数据位
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //无校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //1位停止位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //收发使能
	USART_Init(USART1,&USART_InitStructure);
	
	/*开启USART1*/
	USART_Cmd(USART1,ENABLE);
}

void USART3_Init(uint32_t baud)
{
	/*开启GPIOA、USART1外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);      
	
	/*配置GPIO管脚工作模式*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //复用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //最大工作频率：50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                        
	GPIO_Init(GPIOC,&GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                    //上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                       
	GPIO_Init(GPIOC,&GPIO_InitStructure);      
                                      
	                                                                           
	/*配置USART3工作模式*/                                                           
	USART_InitTypeDef USART_InitStructure;                                           
	USART_InitStructure.USART_BaudRate = baud;                                       //设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //8位数据位
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //无校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //1位停止位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //收发使能
	USART_Init(USART3,&USART_InitStructure);
	
	
	/*开启USART3*/
	USART_Cmd(USART3,ENABLE);
}

void USART3_IT_Init(uint32_t baud)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);     
	
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//??????0
  
  /* ?? USART1 ?? */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
		/*配置GPIO管脚工作模式*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //复用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //最大工作频率：50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                        
	GPIO_Init(GPIOC,&GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                    //上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                       
	GPIO_Init(GPIOC,&GPIO_InitStructure);      
	
	/*配置USART3工作模式*/                                                           
	USART_InitTypeDef USART_InitStructure;                                           
	USART_InitStructure.USART_BaudRate = baud;                                       //设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //8位数据位
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //无校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //1位停止位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //收发使能
	USART_Init(USART3,&USART_InitStructure);
	
	//中断使能
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//??????,????? ??????????
  //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//??????,?????? ????
	USART_Cmd(USART3, ENABLE); //USART1??
	
	
	//
}	


/**
  * @brief  将printf函数重定向到USART1
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
  /*USART1发送一个字符*/
  USART_SendData(USART1,(uint8_t)ch);

  /*等待传输完成*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);

  return ch;
}

/**
  * @brief  将scanf函数重定向到USART1
  * @param  None
  * @retval None
  */
int fgetc(FILE *f)
{
  /*等待接收到一个字符*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);

	/*从USART1读取一个字符并返回*/
  return USART_ReceiveData(USART1);
}


int fwritec(int ch)
{
  /*USART1发送一个字符*/
  USART_SendData(USART1,(uint8_t)ch);

  /*等待传输完成*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);

  return 1;
}

int fwritec_3(int ch)
{
  /*USART1发送一个字符*/
  USART_SendData(USART3,(uint8_t)ch);

  /*等待传输完成*/
  while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);

  return 1;
}

int freadc(void)
{
  /*等待接收到一个字符*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);

	/*从USART1读取一个字符并返回*/
  return USART_ReceiveData(USART1);
}

int freadc_3(void)
{
  /*等待接收到一个字符*/
  while(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) == RESET);

	/*从USART1读取一个字符并返回*/
  return USART_ReceiveData(USART3);
}
