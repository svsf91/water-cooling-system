/**
  ******************************************************************************
  * @file    Drv_SysTick.h
  * @author  彭澎(1252714)
  * @version V1.0
  * @date    2015/10/26
  * @brief   SysTick驱动头文件
  ******************************************************************************						
  */  
	
#ifndef __DRV_SYSTICK_H
#define __DRV_SYSTICK_H

#include "main.h"

#define GET_SYSTIME_US systick*1000+(SysTick->LOAD-SysTick->VAL)*1000/SysTick->LOAD

extern volatile uint32_t systick;

void SysTick_Init(void);                        //SysTick初始化函数
void Delay_Us(uint32_t n);                      //微秒级延时函数
void Delay_Ms(uint32_t n);                      //毫秒级延时函数

#endif /* __DRV_SYSTICK_H */
