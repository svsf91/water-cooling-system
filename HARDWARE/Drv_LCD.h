/**
  ******************************************************************************
  * @file    Drv_LCD.h
  * @author  ����(1252714)
  * @version V2.0
  * @date    2016/9/30
  * @brief   2.2'TFT LCD����ͷ�ļ�
  ******************************************************************************	
  * @attention
  * TFT_LED --> PD12
  * TFT_REST --> PD11
	*	TFT_CS --> FSMC_NE1(PD7)
	*	TFT_DB0 --> FSMC_D0(PD14)
	*	TFT_DB1 --> FSMC_D1(PD15)
	*	TFT_DB2 --> FSMC_D2(PD0)
	*	TFT_DB3 --> FSMC_D3(PD1)
	*	TFT_DB4 --> FSMC_D4(PE7)
	*	TFT_DB5 --> FSMC_D5(PE8)
	*	TFT_DB6 --> FSMC_D6(PE9)
	*	TFT_DB7 --> FSMC_D7(PE10)
	*	TFT_DB8 --> FSMC_D8(PE11)
	*	TFT_DB9 --> FSMC_D9(PE12)
	*	TFT_DB10 --> FSMC_D10(PE13)
	*	TFT_DB11 --> FSMC_D11(PE14)
	*	TFT_DB12 --> FSMC_D12(PE15)
	*	TFT_DB13 --> FSMC_D13(PD8)
	*	TFT_DB14 --> FSMC_D14(PD9)
	*	TFT_DB15 --> FSMC_D15(PD10)
	*	TFT_RS --> FSMC_A18(PD13)
	*	TFT_RD --> FSMC_NOE(PD4)
	*	TFT_WR --> FSMC_NWE(PD5)
	*
	*	����֧��FSMC���������ģ��8080��������
	* ʹ��FSMC��������Ӻ궨�塰#define LCD_USE_FSMC"������ʹ�����ģ��8080��������
	* FSMC����Ч����ߣ���FSMC����TIM4_CH2(PB7)�ܽŷ�����ͻ�������ڸùܽŲ����������PWM�ź�
	* ����ʹ��TIM4_CH2(PB7)���PWM�źţ���ѡ�����ģ��8080��������LCD
	*
	* ʹ�ñ�����Ҫʵ�ֺ��뼶��ʱ���� "void Delay_Ms(uint32_t nms)"
  ******************************************************************************			
  */ 
	
#ifndef __DRV_LCD_H
#define __DRV_LCD_H
	
#include "main.h"
	
#define LCD_W 176          //LCD���176����
#define LCD_H 220          //LCD�߶�220����

typedef struct
{
	uint8_t *pBitmapData;
	uint8_t start_x;
	uint8_t start_y;
	uint8_t width;
	uint8_t height;
	uint16_t color;
}LCD_DrawBitmapTypeDef;

#define LCD_REST_HIGH      GPIOD->BSRR = 1<<11
#define LCD_REST_LOW       GPIOD->BSRR = 1<<27
#define LCD_LED_ON         GPIOD->BSRR = 1<<12
#define LCD_LED_OFF        GPIOD->BSRR = 1<<28
	
#ifdef LCD_USE_FSMC
	
typedef struct
{
	__IO uint16_t CR;        //�����LCD��ָ��Ĵ�����
	__IO uint16_t DR;        //�����LCD�����ݼĴ�����
}LCD_TypeDef;

/*LCD�ĵ�ַ������Ӳ������ȷ����*/
#define LCD_BASE           (uint32_t)(0x60000000|0x0007FFFE)
#define LCD                ((LCD_TypeDef *) LCD_BASE)

/*FSMC��ʽʵ��LCD��дʱ��*/
#define LCD_WR_CMD(value)  LCD->CR = (value)
#define LCD_WR_DATA(value) LCD->DR = (value)
#define LCD_RD_DATA        LCD->DR					

#else /* LCD_USE_FSMC */

#define LCD_CS_HIGH        GPIOD->BSRR = 1<<7
#define LCD_CS_LOW         GPIOD->BSRR = 1<<23
#define LCD_RS_HIGH        GPIOD->BSRR = 1<<13
#define LCD_RS_LOW         GPIOD->BSRR = 1<<29
#define LCD_RD_HIGH        GPIOD->BSRR = 1<<4
#define LCD_RD_LOW         GPIOD->BSRR = 1<<20
#define LCD_WR_HIGH        GPIOD->BSRR = 1<<5
#define LCD_WR_LOW         GPIOD->BSRR = 1<<21

/*���ģ��8080���ڷ�ʽʵ��LCDдʱ��*/
#define LCD_DATA_OUT(data) {                     \
													 GPIOD->ODR &= 0x38FC; \
                           GPIOD->ODR |= ((data&0x000C)>>2)|((data&0xE000)>>5)|((data&0x0003)<<14);  \
													 GPIOE->ODR &= 0x007F; \
													 GPIOE->ODR |= (data&0x1FF0)<<3; \
                           }

#define LCD_WR_CMD(value)  {                     \
	                         LCD_RS_LOW;           \
                           LCD_CS_LOW;           \
													 LCD_DATA_OUT(value);  \
													 LCD_WR_LOW;           \
													 LCD_WR_HIGH;          \
													 LCD_CS_HIGH;          \
                           }
													 
#define LCD_WR_DATA(value) {                     \
	                         LCD_RS_HIGH;          \
                           LCD_CS_LOW;           \
                           LCD_DATA_OUT(value);  \
                           LCD_WR_LOW;           \
                           LCD_WR_HIGH;          \
                           LCD_CS_HIGH;          \
                           }

#endif /* LCD_USE_FSMC */

/*Ԥ������ɫ*/
//��ɫ��ʽRGB565��Ҳ�ɲ���ɫֵ�����ж���
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define RED           	 0xF800
#define GREEN         	 0x07E0
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 
#define GRAY  			     0X8430 

/*ȫ�ֱ���*/
extern const uint8_t tongji_logo[176][22];                                //ͬ��У�յ�������
extern uint16_t point_color;                                              //������ɫ

#ifdef LCD_USE_FSMC

static inline uint16_t LCD_ReadReg(uint8_t reg_addr);                     //LCD���Ĵ���

#endif /* LCD_USE_FSMC */

static inline void LCD_WriteReg(uint16_t reg_addr,uint16_t reg_value);    //LCDд�Ĵ���
void LCD_Clear(uint16_t color);                                           //LCD����
void LCD_Window(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);             //LCD���ô���
void LCD_Init(void);                                                      //LCD��ʼ��	
void LCD_DrawBitmap(LCD_DrawBitmapTypeDef *structure);                    //LCD����ͼƬ
void LCD_DrawPoint(uint8_t x,uint8_t y);	                                //LCD����
void LCD_ShowChar(uint8_t x,uint8_t y,uint8_t ch);                        //LCD��ʾ�ַ�
void LCD_SetStart(uint8_t start_x,uint8_t start_y);                       //���ø�ʽ����ӡ��ʼ����
void LCD_printf(char *fmt, ...);                                          //LCD��ʽ����ӡ
void LCD_Clear_Draw(uint16_t color);
#endif /* __DRV_LCD_H */
