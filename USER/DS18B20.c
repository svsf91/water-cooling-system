#include "DS18B20.h"


static void DS18B20_GPIO_Config(void)
{ 
/*????GPIO_InitTypeDef??????*/
GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//RCC_APB2PeriphClockCmd(DS18B20_CLK, ENABLE); 

GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

/*?????,???DS18B20_PORT*/
GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
GPIO_SetBits(DS18B20_PORT, DS18B20_PIN);
}
static void DS18B20_Mode_IPU(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}
/*
 * ???:DS18B20_Mode_Out_PP
 * ??  :?DS18B20-DATA????????
 * ??  :?
 * ??  :?
 */
static void DS18B20_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}
/*
 *???????????
 */
static void DS18B20_Rst(void)
{
/* ????????? */
DS18B20_Mode_Out_PP();
DS18B20_DATA_OUT(0);
/* ??????480us???????? */
Delay_Us(750);
/* ??????????,?????? */
DS18B20_DATA_OUT(1);
/*?????????????,??15~60us???????????*/
Delay_Us(15);
}
/*
 * ??????????????
 * 1:??
 * 0:??
 */
int DS18B20_Check(void)
{
uint8_t pulse_time = 0;
/* ????????? */
DS18B20_Mode_IPU();
/* ?????????,???????60~240us?????? 
* ???????????????,?????????????,??15~60us???????????
*/
while( DS18B20_DATA_IN() && pulse_time <100 )
{
pulse_time++;
Delay_Us(1);
} 
/* ??100us?,??????????*/
if( pulse_time >=100 )
return 0;
else
pulse_time = 0;
/* ??????,??????????240us */
while( !DS18B20_DATA_IN() && pulse_time<240 )
{
pulse_time++;
Delay_Us(1);
}
if( pulse_time >=240 )
return 0;
else
return 1;
}
/*
 * ?DS18B20????bit
 */


static uint8_t DS18B20_Read_Bit(void)
{
uint8_t dat;
DS18B20_Mode_Out_PP();
DS18B20_DATA_OUT(0);
Delay_Us(10);
DS18B20_Mode_IPU();
if( DS18B20_DATA_IN() == SET )
dat = 1;
else
dat = 0;
Delay_Us(45);
return dat;
}

uint8_t DS18B20_Read_Byte(void)
{
uint8_t i, j, dat = 0;
for(i=0; i<8; i++)
{
j = DS18B20_Read_Bit();
dat = (dat) | (j<<i);
}
return dat;
}

void DS18B20_Write_Byte(uint8_t dat)
{
uint8_t i, testb;
DS18B20_Mode_Out_PP();

for( i=0; i<8; i++ )
{
testb = dat&0x01;
dat = dat>>1; 

if (testb)
{ 
DS18B20_DATA_OUT(0);
/* 1us < ???? < 15us */
Delay_Us(8);
DS18B20_DATA_OUT(1);
Delay_Us(58);
} 
else
{ 
DS18B20_DATA_OUT(0);
/* 60us < Tx 0 < 120us */
Delay_Us(70);
DS18B20_DATA_OUT(1);
/* 1us < Trec(????) < ???*/
Delay_Us(2);
}
}
}

void DS18B20_Start(void)
{
	
	DS18B20_Rst();
	DS18B20_Check();
DS18B20_Write_Byte(0XCC);
/* ?? ROM */
DS18B20_Write_Byte(0X44);
/* ???? */
}

uint8_t DS18B20_Init(void)
{
DS18B20_GPIO_Config();
DS18B20_Rst();
return	DS18B20_Check();
// return DS18B20_Presence();
}

float DS18B20_Get_Temp(void)
{

uint8_t tpmsb, tplsb;

short s_tem;

float f_tem;
DS18B20_Start();
DS18B20_Rst();
DS18B20_Check();
Delay_Us(300);
//DS18B20_Write_Byte(0XCC);
///* ?? ROM */
//DS18B20_Write_Byte(0X44);
///* ???? */
//DS18B20_Rst();
//Delay_Us(300);
DS18B20_Write_Byte(0XCC);
/* ?? ROM */
DS18B20_Write_Byte(0XBE);
/* ???? */
tplsb = DS18B20_Read_Byte();
tpmsb = DS18B20_Read_Byte();
s_tem = tpmsb<<8;
s_tem = s_tem | tplsb;
if( s_tem < 0 )
/* ??? */
f_tem = (~s_tem+1) * 0.0625;
else
f_tem = s_tem * 0.0625;
return f_tem;
}
void DS18B20_DATA_OUT(uint8_t set_reset)
{
 if(set_reset == 1)	
 {
	 GPIO_SetBits( DS18B20_PORT, DS18B20_PIN);
 }
 else
 {
	 GPIO_ResetBits( DS18B20_PORT, DS18B20_PIN);
 }
	 
}

int DS18B20_DATA_IN(void)
{
  uint8_t x =	GPIO_ReadInputDataBit(DS18B20_PORT, DS18B20_PIN);
	return x;
}
