/**
  ******************************************************************************
  * @file    main.c
  * @author  彭澎(1252714)
  * @version V2.0
  * @date    2016/9/30
  * @brief   
  ******************************************************************************
  * @attention
	*
  * 同济大学，电子与信息工程学院，控制科学与工程系
  * 此工程为“控制系统设计与实现”水冷控制系统开发板工程模板。
  * 此工程实现了如下硬件驱动：
	* 	SysTick定时器 -- Drv_SysTick.c/Drv_SysTick.h
	*		USART1串口 -- Drv_USART1.c/Drv_USART1.h
	*		LCD显示屏 -- Drv_LCD.c/Drv_LCD.h
	*	请自行实现其余所需的硬件驱动及控制算法以达到设计要求。
  * 如在使用过程中有任何意见或建议，欢迎反馈至1252714pp@tongji.edu.cn
  * 
  ******************************************************************************							
  */  

#include "main.h"
#include "stm32f10x.h"
#include <stdio.h>
#include "DS18B20.h"
#include "k.h"

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 800;
uint16_t CCR2_Val = 200;
uint16_t CCR3_Val = 250;
uint16_t CCR4_Val = 125;
ErrorStatus HSEStartUpStatus;

uint8_t temp_DS18B20 = 20;

//global val
float Temp_O;
uint8_t Temp_dire=47;//期望温度
uint8_t Temp_dire_last=47;//期望温度

uint8_t flag_draw=0;
uint8_t clear_flag=1;
uint8_t draw_clearself=1;
uint8_t flag_Draw_Env=1;
uint8_t Line_Val[10]={0};
uint8_t ii=0;
uint8_t draw_x=10;

uint8_t window=MAIN_WINDOW;
uint8_t high_light_line=MAIN_SET_TEMP;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void GPIO_Init_337(void);

int main(void)
{	
	RCC_Configuration();
	
	/*SysTick定时器初始化，用于提供软件延时*/
	SysTick_Init();
	
	/* GPIO 初始化 */
	
	/*配置GPIO管脚工作模式*/
	GPIO_Init_337();
	
	//DS18B20 初始化
	//while(!DS18B20_Init());
  
	/*USART1初始化，用作格式化输入输出*/
	//串口初始化 使用端口  a9 输出 a10 输入
	USART1_Init(9600);
	
	//USART3_Init(115200);
	USART3_IT_Init(115200);
	printf("\r\n");
	
	/*LCD初始化*/
	LCD_Init();
	
	/*绘制启动logo*/
	LCD_DrawBitmapTypeDef drawBitmatStructure;
	drawBitmatStructure.pBitmapData = (uint8_t *)tongji_logo;
	drawBitmatStructure.width = 176;
	drawBitmatStructure.height = 176;
	drawBitmatStructure.start_x = 0;
	drawBitmatStructure.start_y = 21;
	drawBitmatStructure.color = BLUE;
	LCD_DrawBitmap(&drawBitmatStructure);
	Delay_Ms(1000);
	LCD_Clear(WHITE);
	
	/*LCD使用示例*/
	
	LCD_SetStart(0,0);
	point_color = RED;
	LCD_printf("This is a newbee project.\n BY #7-337\n");
	
	LCD_SetStart(0,50);
	point_color = BLUE;
	LCD_printf("This is a newbee project.\n BY #7-337\n");
	
	Delay_Ms(1000);
	LCD_Clear(WHITE);
	
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
	
	//参数初始化             
	LCD_SetStart(10,15);
  drawWelPic();

	while(1)
	{	
//指示灯		
		  GPIO_Togg_Bits(GPIOB,GPIO_Pin_1,0);
//		  GPIO_Togg_Bits(GPIOB,GPIO_Pin_0,1);
//			GPIO_Togg_Bits(GPIOC,GPIO_Pin_4,2);
//		  GPIO_Togg_Bits(GPIOC,GPIO_Pin_5,3);
		
	  	//根据外部中断返回的标志位来控制		
		  temp_EXTI9_5_IRQHandler();
		
			Temp_O=get_temp();
		  Draw_if_required();
		  Temp_down_control(Temp_dire);									
}
}

void Draw_if_required(void)
{
			if(flag_draw==1)
	    {
				//更新期望曲线
				if(Temp_dire!=Temp_dire_last || draw_clearself==1)
				{
					uint8_t h=210;
					LCD_SetStart(28,h-3*Temp_dire_last+1);
					point_color = GREEN;
					LCD_printf("  ");
					
					LCD_SetStart(28,h-3*Temp_dire+1);
					point_color = GREEN;
					LCD_printf("%d",Temp_dire);		
					
					point_color = WHITE;
					for(uint8_t i=27;i<176;i++)
						LCD_DrawPoint(i,h-3*Temp_dire_last);
					
					point_color = GREEN;
//					uint8_t h=210;
					for(uint8_t i=27;i<176;i++)
						LCD_DrawPoint(i,h-3*Temp_dire);

					Temp_dire_last=Temp_dire;
				}
				
				  clear_flag=1;
				if(draw_clearself==1)
				{
					drawAxis();
					draw_clearself=0;
				}
				  ii++;
					if(ii%20 ==0)
					{
							drawTemp(Temp_O,draw_x);
							draw_x++;
							ii=0;
					}
					if(draw_x>=176)
					{
						draw_clearself=1;
						draw_x=10;
						LCD_Clear_Draw(WHITE);
						//drawAxis();
					}
			}
			else
			{
				 draw_x=10;
						if(clear_flag==1)
						{
							LCD_Clear_Draw(WHITE);
							drawWelPic();
							clear_flag=0;
						}
			}
}

void Tim_Pwm_change_duty(uint16_t duty,uint16_t duty_FAN)
{
	//	/* Timer 初始化*/
	
	
	/* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 36 MHz, Prescaler = 0x0, TIM3 counter clock = 36 MHz
    TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 36 KHz.
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */
	
	CCR1_Val=duty;
	CCR2_Val=duty_FAN;
	  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 999;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */ //泵
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	 /* PWM1 Mode configuration: Channel2 */ //风扇
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  TIM_OC2Init(TIM5, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	

  /* TIM3 enable counter */
	TIM_ARRPreloadConfig(TIM5, ENABLE);
  TIM_Cmd(TIM5, ENABLE);
}

void Tim_Pwm_change_duty_FAN(uint16_t duty)
{
	//	/* Timer 初始化*/
	
	
	/* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 36 MHz, Prescaler = 0x0, TIM3 counter clock = 36 MHz
    TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 36 KHz.
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */
	
	CCR2_Val=duty;
	
	  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 999;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */ //泵
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	 /* PWM1 Mode configuration: Channel2 */ //风扇
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

//  TIM_OC2Init(TIM5, &TIM_OCInitStructure);

//  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
//	

  /* TIM3 enable counter */
	TIM_ARRPreloadConfig(TIM5, ENABLE);
  TIM_Cmd(TIM5, ENABLE);
}


int Read_temp(void)
{
	uint8_t i=0;
	int x=0;
		x=(int)DS18B20_Get_Temp();
		i++;
		if(i<=9)
		{
			LCD_SetStart(0,0+i*15);
			point_color = BLUE;
			LCD_printf("%d",x);
			Delay_Ms(100);
		}
		else
		{
			LCD_Clear(WHITE);
		  i=0;
		}
		return x;
}



//origin test for GPIO_PWM_AN
void change_pwm_duty(uint8_t duty )//0-100
{
	  GPIO_SetBits( GPIOA, GPIO_Pin_5);
		Delay_Ms( duty );
    GPIO_ResetBits( GPIOA, GPIO_Pin_5);
		Delay_Ms( 100- duty);
}



void RCC_Configuration(void)
{
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

  /* PCLK1 = HCLK/4 */
  RCC_PCLK1Config(RCC_HCLK_Div1);

  /* TIM5 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
}



void GPIO_Init_337(void)
{
	//按钮初始化
		GPIO_InitTypeDef GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上啦输入
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_5 | GPIO_Pin_6 ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	  GPIO_Init(GPIOB,&GPIO_InitStructure);    
	
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);
   	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);
	
	  EXTI_InitTypeDef EXTI_InitStructure;
	
		EXTI_InitStructure.EXTI_Line = EXTI_Line5;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
	  
		EXTI_InitStructure.EXTI_Line = EXTI_Line6;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		
    EXTI_InitStructure.EXTI_Line = EXTI_Line8;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		EXTI_InitStructure.EXTI_Line = EXTI_Line9;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
//		
		NVIC_InitTypeDef NVIC_InitStructure;    
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //PPP?????
		
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
		
	//timer pwm
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//LEDs 初始化
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //输出
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	  GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //输出
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	  GPIO_Init(GPIOC,&GPIO_InitStructure); 
	  
//	  GPIO_SetBits( GPIOB, GPIO_Pin_0);
//	  GPIO_SetBits( GPIOB, GPIO_Pin_1);
//	  GPIO_SetBits( GPIOC, GPIO_Pin_4);
//	  GPIO_SetBits( GPIOC, GPIO_Pin_5);
}



void temp_code(void)
{
	//		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
//		{
//			Delay_Ms(20);
//			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
//				flag_draw=1;
//		}
//		
//		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)
//		{
//			Delay_Ms(20);
//			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)
//				flag_draw=0;
//		}
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  断言失败处理函数
  * @param  file: 源文件名指针
  *         line: 断言失败所在的行数
  * @retval 无
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
		/*报告错误信息*/
		printf("Assertion failed: file %s on line %d\r\n",file,line);
		Delay_Ms(1000);
  }
}
#endif
