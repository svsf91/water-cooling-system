/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	
	systick++;
	
}
void EXTI9_5_IRQHandler(void)
{   
	  if (EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
         EXTI_ClearITPendingBit(EXTI_Line5); //????
				 EXTI_ClearFlag(EXTI_Line5);
			   //flag_draw=1;
			for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			
			Line_Val[5]=1;
			
			
		}
		
		 if (EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
         EXTI_ClearITPendingBit(EXTI_Line6); //????
				 EXTI_ClearFlag(EXTI_Line6);
			
			for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			
			Line_Val[6]=1;
			
			   
		}
		 if (EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
         EXTI_ClearITPendingBit(EXTI_Line7); //????
				 EXTI_ClearFlag(EXTI_Line7);
				for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			
			  Line_Val[7]=1;
		}
		
		
		
		 if (EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
         EXTI_ClearITPendingBit(EXTI_Line8); //????
				 EXTI_ClearFlag(EXTI_Line8);
			   for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			
			Line_Val[8]=1;
		}
	
		 if (EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
         EXTI_ClearITPendingBit(EXTI_Line9); //????
				 EXTI_ClearFlag(EXTI_Line9);
			   for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			
			Line_Val[9]=1;
		}
	
}

uint8_t Set_temp_from_usart=0;
void USART3_IRQHandler(void)
{
	 USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
/* ?? USART1 ???? */
  //USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
	 uint8_t buffer=0;
	 buffer=freadc_3();
	if(Set_temp_from_usart==1)
	{
	   	Set_temp_from_usart=0;
			Temp_dire=buffer;
		if(window==MAIN_WINDOW)
		{
			window=MAIN_WINDOW;
			high_light_line=MAIN_SET_TEMP;
				for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			Line_Val[7]=1;
		}
		else
		{
			window=DRAW_WINDOW;
			high_light_line=DRAW_SET_TEMP;
				for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			Line_Val[7]=1;
		}
		//½ûÖ¹ÖÐ¶Ï
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			return;
	}
	switch (buffer)
	{
		case 0xff:   
		{
			fwritec_3((uint8_t)Temp_O);
		}	
		break;
		case 0xfe:  
		{
	    flag_draw=1;
			window=MAIN_WINDOW;
			high_light_line=MAIN_IN_DRAW;
				for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			Line_Val[7]=1;
//			LCD_SetStart(10,85);
//			point_color = BLUE;
//		  LCD_printf("%d",buffer);
		}
		break;
		case 0xfd:
		{
			flag_draw=0;
			window=DRAW_WINDOW;
			high_light_line=DRAW_BACK;
				for(uint8_t i=0;i<10;i++)
			   Line_Val[i]=0;
			Line_Val[7]=1;
		}
		case 0xdd:
		{
			Set_temp_from_usart=1;
		}
		default:
		{
//			Temp_dire=buffer;
//			LCD_Clear(WHITE);
//			LCD_SetStart(10,100);
//			point_color = BLUE;
//			LCD_printf("temp_desire:%d",buffer);
		}break;
	}
	 
 
//  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
//  {   
//    USART_SendData(USART3, );
//  }    
	
	//½ûÖ¹ÖÐ¶Ï
	 USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
/* ?? USART1 ???? */
   //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
