#include "main.h"
#include "Drv_USART1.h"
#include "Drv_SysTick.h"
#include "Drv_LCD.h"
#include "Drv_LCD.h"
float get_temp(void);
void drawAxis(void);
void drawTemp(float temp, uint8_t x);
uint8_t drawWelPic(void);
