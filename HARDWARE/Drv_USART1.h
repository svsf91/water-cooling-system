/**
  ******************************************************************************
  * @file    Drv_USART1.h
  * @author  彭澎(1252714)
  * @version V1.0
  * @date    2015/10/26
  * @brief   USART1驱动头文件
  ******************************************************************************	
  * @attention
  * USART1_TX --> PA9
  * USART2_RX --> PA10
  ******************************************************************************			
  */  
	
#ifndef __DRV_USART1_H
#define __DRV_USART1_H

#include "main.h"

void USART1_Init(uint32_t baud);    //USART1初始化函数
void USART3_Init(uint32_t baud);    //USART1初始化函数
void USART3_IT_Init(uint32_t baud);
int fwritec(int ch);
int freadc(void);
int freadc_3(void);
int fwritec_3(int ch);
#endif /* __DRV_USART1_H */
