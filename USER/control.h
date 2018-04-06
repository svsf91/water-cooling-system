#include "main.h"
extern uint8_t temp_DS18B20 ;
void Temp_down_control(uint8_t temp_desire);
void temp_EXTI9_5_IRQHandler(void);


extern float error_sum ;
extern uint8_t  temp_down_Kp , temp_down_Ki ,  temp_down_Kd ;
