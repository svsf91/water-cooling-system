#include "stm32f10x.h"
#define DS18B20_PIN GPIO_Pin_1
#define DS18B20_PORT GPIOC
#include "main.h"
// export func
void DS18B20_DATA_OUT(uint8_t set_reset);

float DS18B20_Get_Temp(void);
uint8_t DS18B20_Init(void);
void DS18B20_Start(void);
static uint8_t DS18B20_Read_Bit(void);
uint8_t DS18B20_Read_Byte(void);
void DS18B20_Write_Byte(uint8_t dat);
int DS18B20_Check(void);
