/**
  ******************************************************************************
  * @file    Drv_USART1.c
  * @author  ����(1252714)
  * @version V1.0
  * @date    2015/10/26
  * @brief   USART1����Դ�ļ�
  ******************************************************************************	
  * @attention
  * USART1_TX --> PA9
  * USART2_RX --> PA10
  ******************************************************************************			
  */ 
	
#include "Drv_USART1.h"

/**
* @brief  USART1��ʼ������
* @param  baud:������
* @retval ��
*/
void USART1_Init(uint32_t baud)
{
	/*����GPIOA��USART1����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/*����GPIO�ܽŹ���ģʽ*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //�����Ƶ�ʣ�50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                        
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                            
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                    //��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                       
	GPIO_Init(GPIOA,&GPIO_InitStructure);                                            
	                                                                                 
	/*����USART1����ģʽ*/                                                           
	USART_InitTypeDef USART_InitStructure;                                           
	USART_InitStructure.USART_BaudRate = baud;                                       //���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //8λ����λ
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //��У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //1λֹͣλ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //�շ�ʹ��
	USART_Init(USART1,&USART_InitStructure);
	
	/*����USART1*/
	USART_Cmd(USART1,ENABLE);
}

void USART3_Init(uint32_t baud)
{
	/*����GPIOA��USART1����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);      
	
	/*����GPIO�ܽŹ���ģʽ*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //�����Ƶ�ʣ�50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                        
	GPIO_Init(GPIOC,&GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                    //��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                       
	GPIO_Init(GPIOC,&GPIO_InitStructure);      
                                      
	                                                                           
	/*����USART3����ģʽ*/                                                           
	USART_InitTypeDef USART_InitStructure;                                           
	USART_InitStructure.USART_BaudRate = baud;                                       //���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //8λ����λ
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //��У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //1λֹͣλ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //�շ�ʹ��
	USART_Init(USART3,&USART_InitStructure);
	
	
	/*����USART3*/
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
	
		/*����GPIO�ܽŹ���ģʽ*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //�����Ƶ�ʣ�50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                        
	GPIO_Init(GPIOC,&GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                    //��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                       
	GPIO_Init(GPIOC,&GPIO_InitStructure);      
	
	/*����USART3����ģʽ*/                                                           
	USART_InitTypeDef USART_InitStructure;                                           
	USART_InitStructure.USART_BaudRate = baud;                                       //���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      //8λ����λ
	USART_InitStructure.USART_Parity = USART_Parity_No;                              //��У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                           //1λֹͣλ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //�շ�ʹ��
	USART_Init(USART3,&USART_InitStructure);
	
	//�ж�ʹ��
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//??????,????? ??????????
  //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//??????,?????? ????
	USART_Cmd(USART3, ENABLE); //USART1??
	
	
	//
}	


/**
  * @brief  ��printf�����ض���USART1
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
  /*USART1����һ���ַ�*/
  USART_SendData(USART1,(uint8_t)ch);

  /*�ȴ��������*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);

  return ch;
}

/**
  * @brief  ��scanf�����ض���USART1
  * @param  None
  * @retval None
  */
int fgetc(FILE *f)
{
  /*�ȴ����յ�һ���ַ�*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);

	/*��USART1��ȡһ���ַ�������*/
  return USART_ReceiveData(USART1);
}


int fwritec(int ch)
{
  /*USART1����һ���ַ�*/
  USART_SendData(USART1,(uint8_t)ch);

  /*�ȴ��������*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);

  return 1;
}

int fwritec_3(int ch)
{
  /*USART1����һ���ַ�*/
  USART_SendData(USART3,(uint8_t)ch);

  /*�ȴ��������*/
  while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);

  return 1;
}

int freadc(void)
{
  /*�ȴ����յ�һ���ַ�*/
  while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);

	/*��USART1��ȡһ���ַ�������*/
  return USART_ReceiveData(USART1);
}

int freadc_3(void)
{
  /*�ȴ����յ�һ���ַ�*/
  while(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) == RESET);

	/*��USART1��ȡһ���ַ�������*/
  return USART_ReceiveData(USART3);
}
