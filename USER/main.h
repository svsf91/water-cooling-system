/**
  ******************************************************************************
  * @file    main.h
  * @author  彭澎(1252714)
  * @version V2.0
  * @date    2016/9/30
  * @brief   此文件包含所有用到的头文件
  ******************************************************************************						
  */  
	
#ifndef __MAIN_H
#define __MAIN_H
	
#include <stdio.h>	
#include <stdarg.h>
#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_adc.h"
#include "control.h"
#include "Drv_SysTick.h"
#include "Drv_USART1.h"
#include "Drv_LCD.h"
#include "k.h"

#define DRAW_WINDOW  0xff
#define MAIN_WINDOW  0xfe

#define DRAW_LINE_BACK  0x00
#define DRAW_SET_TEMP   0x01
#define DRAW_SET_KP     0x02
#define DRAW_SET_KI     0x03
#define DRAW_SET_KD     0x04
#define DRAW_LINE_FREE  0x05
#define DRAW_BACK       0x06

#define MAIN_BACK       0x2a
#define MAIN_LINE_FREE  0x20
#define MAIN_IN_DRAW    0x25
#define MAIN_SET_TEMP   0x26
#define MAIN_SET_KP     0x27
#define MAIN_SET_KI     0x28
#define MAIN_SET_KD     0x29

//函数声明
void change_pwm_duty(uint8_t duty );

void Tim_Pwm_change_duty(uint16_t duty,uint16_t duty_FAN);

void Tim_Pwm_change_duty_FAN(uint16_t duty);

void Draw_if_required(void);

int Read_temp(void);

extern float Temp_O;
extern uint8_t Temp_dire;
extern uint8_t flag_draw;
extern uint8_t clear_flag;
extern uint8_t draw_clearself;
extern uint8_t window;
extern uint8_t high_light_line;
extern uint8_t Line_Val[10];
extern uint8_t flag_Draw_Env;
extern uint8_t ii;
/*设置LCD驱动方式*/
//若要使用GPIO模拟时序驱动方式，注释此宏即可
#define LCD_USE_FSMC

#endif /* __MAIN_H */
