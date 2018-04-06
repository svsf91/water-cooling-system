#include "control.h"
#include "main.h"
	float error_sum = -500;
	
//	uint8_t temp_DS18B20 = 20;
	
	uint8_t  temp_down_Kp = 30 , temp_down_Ki = 1 , temp_down_Kd=1 ;
	
void Temp_down_control(uint8_t temp_desire)
{
	uint16_t duty_FAN=0;
//	duty_FAN=((uint8_t)(Temp_O)-40)/3*100;
//	if(duty_FAN>=998)
//		duty_FAN=998;
//	if(duty_FAN<=0)
//		duty_FAN=0;
//	  error_sum_down = 100;
		
    static float temp_error;
	 
	  static int32_t pwm_out;
	
	  temp_error = (float)temp_desire - (Temp_O) ;
    
	  error_sum += temp_error ;
	  
	if(temp_error>=0)
		error_sum=-50;
	
	
	  if(error_sum >= 1000) error_sum = 1000;
	  if(error_sum <= -1000) error_sum = -1000;
	
	  pwm_out =   (int32_t)(temp_down_Kp*temp_error + temp_down_Ki*error_sum)  ;
	  
	  if(pwm_out >= 1000)pwm_out = 1000;
	  if(pwm_out<= -1000) pwm_out = -998;
	
	  if(pwm_out < 0)
		{
			pwm_out = -pwm_out ;
			duty_FAN=pwm_out;
	    Tim_Pwm_change_duty( pwm_out ,duty_FAN);
		}
		else
		{
			Tim_Pwm_change_duty(50,50);
		}
}
//Line_Val
void temp_EXTI9_5_IRQHandler(void)
{
	if(window==MAIN_WINDOW)
	{
		draw_clearself=1;
	//	flag_Draw_Env=1;
	}
	
	//left ok
	  if (Line_Val[5] != RESET)
    {
			Line_Val[5]=0;
			//动作
				Delay_Ms(10);
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
			//if(1)
				{
					switch (window)
					{
						case MAIN_WINDOW:
						{
							switch(high_light_line)
							{
								case MAIN_IN_DRAW:
								{
									
									LCD_Clear_Draw(WHITE);
									
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
								
									//action
									flag_draw=1;
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									//标志位变化
									high_light_line=DRAW_SET_TEMP;
			            window=DRAW_WINDOW;
								}
								break;
								case MAIN_SET_TEMP:
								{
									Temp_dire--;
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
									//flags
									window=MAIN_WINDOW;
									high_light_line=MAIN_SET_TEMP;
								}	
								break;
								case MAIN_LINE_FREE:
								{
									//flags
									window=MAIN_WINDOW;
									high_light_line=MAIN_SET_TEMP;
								}
								break;
								case MAIN_BACK:
								{
									high_light_line=MAIN_SET_TEMP;
								}
								break;
								
								default:break;
							}
							
						}	
						break;
						case DRAW_WINDOW:
						{
							switch(high_light_line)
							{
								case DRAW_BACK:
								{
									drawWelPic();
									
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									//action
									flag_draw=0;
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
									//flags
									high_light_line=MAIN_SET_TEMP;
									window=MAIN_WINDOW;
								}
								break;
								case DRAW_SET_TEMP:
								{
									Temp_dire--;
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
								}
								break;
								default:break;
							}
						}
						break;
						default:break;
					}
					return;
				}
    }
		
	//top  ok
		if (Line_Val[6] != RESET)
    {
			Line_Val[6]=0;
		     //flag_draw=0;
			//动作
				Delay_Ms(10);
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==0)
			//if(1)
				{
					switch (window)
					{
						case MAIN_WINDOW:
						{
							switch(high_light_line)
							{
								case MAIN_IN_DRAW:
								{
									//action
									//flag_draw=1;
								 	LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									//标志位变化
									high_light_line=MAIN_SET_TEMP;
			            window=MAIN_WINDOW;
									
								}
								break;
								case MAIN_SET_TEMP:
								{
									//action
									//flag_draw=1;
								 	LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("DRAW_TEMP");
									//标志位变化
									high_light_line=MAIN_IN_DRAW;
			            window=MAIN_WINDOW;
								}	
								break;
								case MAIN_LINE_FREE:
								{
									//action
									//flag_draw=1;
								 	LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
									//flags
									window=MAIN_WINDOW;
									high_light_line=MAIN_SET_TEMP;
								}
								break;
								case MAIN_BACK:
								{
										//action
									//flag_draw=1;
								 	LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
									//flags
									window=MAIN_WINDOW;
									high_light_line=MAIN_SET_TEMP;
								}
								break;
								
								default:break;
							}
							
						}	
						break;
						case DRAW_WINDOW:
						{
							switch(high_light_line)
							{
								case DRAW_BACK:
								{
									//action
									//flag_draw=0;
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									
									//flags
									high_light_line=DRAW_SET_TEMP;
									window=DRAW_WINDOW;
								}
								break;
								case DRAW_SET_TEMP:
								{
									//action
									//flag_draw=0;
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("BACK");
									
									//flags
									high_light_line=DRAW_BACK;
									window=DRAW_WINDOW;
								}
								break;
								default:break;
							}
						}
						
						break;
						default:break;
					
					}
					return;
				}
    }
		
		
	//mid ok
		 if (Line_Val[7] != RESET)
    {
			Line_Val[7]=0;
		  //动作
				Delay_Ms(10);
				//if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)
			if(1)
				{
					switch (window)
					{
						case MAIN_WINDOW:
						{
							switch(high_light_line)
							{
								case MAIN_IN_DRAW:
								{
									//action
									flag_draw=1;//draw_pic
									
									LCD_Clear_Draw(WHITE);
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									
									//标志位变化
									high_light_line=DRAW_SET_TEMP;
			            window=DRAW_WINDOW;
									
								}
								break;
								case MAIN_SET_TEMP:
								{
									//action
									//flag_draw=1;//draw_pic
									
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
									//标志位变化
									high_light_line=MAIN_SET_TEMP;
			            window=MAIN_WINDOW;
								}	
								break;
								case MAIN_LINE_FREE:
								{
										//action
									//flag_draw=1;//draw_pic
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									//flags
									high_light_line=MAIN_SET_TEMP;	
									window=MAIN_WINDOW;
								}
								break;
								case MAIN_BACK:
								{	//action
									//flag_draw=1;//draw_pic
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									//flags
									high_light_line=MAIN_SET_TEMP;
									window=MAIN_WINDOW;
								}
								break;
								
								default:break;
							}
						}	
						break;
						case DRAW_WINDOW:
						{
							switch(high_light_line)
							{
								case DRAW_BACK:
								{
									//action
									flag_draw=0;
									drawWelPic();
										//action
									//flag_draw=1;//draw_pic
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									//flags
									window=MAIN_WINDOW;
									high_light_line=MAIN_SET_TEMP;
								}
								break;
								case DRAW_SET_TEMP:
								{
										//action
									//flag_draw=1;//draw_pic
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									//flags
									window=DRAW_WINDOW;
									high_light_line=DRAW_SET_TEMP;
								}
								break;
								default:break;
							}
						}
						break;
						default:break;
					
					}
					return;
				}
    }
		
	//bottom ok
		 if (Line_Val[8] != RESET)
    {
			Line_Val[8]=0;
		     //flag_draw=1;
				//动作
				Delay_Ms(10);
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0)
			//if(1)
				{
					switch (window)
					{
						case MAIN_WINDOW:
						{
							switch(high_light_line)
							{
								case MAIN_IN_DRAW:
								{
									//action
									//flag_draw=0;
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
									//flags
									high_light_line=MAIN_SET_TEMP;
									window=MAIN_WINDOW;
									
								}
								break;
								case MAIN_SET_TEMP:
								{
									//action
									//flag_draw=0;
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("DRAW_TEMP");
									
									//flags
									high_light_line=MAIN_IN_DRAW;
									window=MAIN_WINDOW;
								}	
								break;
								case MAIN_LINE_FREE:
								{
									//action
									//flag_draw=0;
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									
									//flags
									high_light_line=MAIN_SET_TEMP;
									window=MAIN_WINDOW;
								}
								break;
								case MAIN_BACK:
								{
									//action
									//flag_draw=0;
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									
									//flags
									high_light_line=MAIN_SET_TEMP;
									window=MAIN_WINDOW;
								}
								break;
								
								default:break;
							}
							
						}	
						break;
						case DRAW_WINDOW:
						{
							switch(high_light_line)
							{
								case DRAW_BACK:
								{
									//action
									//flag_draw=0;
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									
									//flags
									high_light_line=DRAW_SET_TEMP;
									window=DRAW_WINDOW;
								}
								break;
								case DRAW_SET_TEMP:
								{
									//action
									//flag_draw=0;
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("BACK");
									
									//flags
									high_light_line=DRAW_BACK;
									window=DRAW_WINDOW;
								}
								break;
								default:break;
							}
						}
						
						break;
						default:break;
					
					}
					return;
				}	
    }
		
	//right  ok
    if (Line_Val[9] != RESET)
    {
			Line_Val[9]=0;
		     //flag_draw=1;
			//动作
				Delay_Ms(10);
				if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)
		//	if(1)
				{
					switch (window)
					{
						case MAIN_WINDOW:
						{
							switch(high_light_line)
							{
								case MAIN_IN_DRAW:
								{
										//action
									flag_draw=1;//draw_pic
									
									LCD_Clear_Draw(WHITE);
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									
									//标志位变化
									high_light_line=DRAW_SET_TEMP;
			            window=DRAW_WINDOW;
								}
								break;
								case MAIN_SET_TEMP:
								{
									//action
									Temp_dire++;
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									
									//flags
									window=MAIN_WINDOW;
									high_light_line=MAIN_SET_TEMP;
								}	
								break;
								case MAIN_LINE_FREE:
								{
										//flags
									high_light_line=MAIN_SET_TEMP;
								  window=MAIN_WINDOW;
								}
								break;
								case MAIN_BACK:
								{
									//flags
									window=MAIN_WINDOW;
									high_light_line=MAIN_SET_TEMP;
								}
								break;
								
								default:break;
							}
							
						}	
						break;
						case DRAW_WINDOW:
						{
							switch(high_light_line)
							{
								case DRAW_BACK:
								{
									//action
									flag_draw=0;
									drawWelPic();
									
									LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
				        	LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("DRAW_TEMP");
									//flags
									high_light_line=MAIN_SET_TEMP;
									window=MAIN_WINDOW;
								}
								break;
								case DRAW_SET_TEMP:
								{
									//actions
									Temp_dire++;
									
										LCD_SetStart(10,180);
	                point_color = BLACK;
		              LCD_printf("               ");
									
									LCD_SetStart(10,195);
	                point_color = RED;
		              LCD_printf("               ");
									
									LCD_SetStart(10,180);
	                point_color = RED;
		              LCD_printf("Temp_Desire:%d",Temp_dire);
									
									LCD_SetStart(10,195);
	                point_color = BLACK;
		              LCD_printf("BACK");
									//flags
									window=DRAW_WINDOW;
									high_light_line=DRAW_SET_TEMP;
								}
								break;
								default:break;
							}
						}
						
						break;
						default:break;
					
					}
					return;
				}
    }
}

