/**
  ******************************************************************************
  * @file    Drv_SysTick.c
  * @author  ����(1252714)
  * @version V1.0
  * @date    2015/10/26
  * @brief   SysTick����Դ�ļ�
  ******************************************************************************						
  */  
	
#include "Drv_SysTick.h"

volatile uint32_t systick = 0;

/**
  * @brief  SysTick��ʼ������
  * @param  ��
  * @retval ��
  */
void SysTick_Init(void)
{
	RCC_ClocksTypeDef RCC_ClockStructure;
	RCC_GetClocksFreq(&RCC_ClockStructure);
	
	uint32_t cnts = (uint32_t)RCC_ClockStructure.HCLK_Frequency/8000;
	
	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

/**
  * @brief  ΢�뼶��ʱ����
  * @param  Ҫ��ʱ��΢����
  * @retval ��
  */
void Delay_Us(uint32_t n)
{
	uint32_t now = GET_SYSTIME_US;
	while((GET_SYSTIME_US-now)<n);
}	

/**
  * @brief  ���뼶��ʱ����
  * @param  Ҫ��ʱ�ĺ�����
  * @retval ��
  */
void Delay_Ms(uint32_t n)
{
	while(n--)
		Delay_Us(1000);
}
