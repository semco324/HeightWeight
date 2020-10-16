#include "ultrasonic.h"
#include "BspConfig.h"
#include "dwt_stm32_delay.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
void Hx711_Data_Out() //设置成输出
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = PRESSURE_DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PRESSURE_DT_GPIO_Port, &GPIO_InitStruct);
}
void Hx711_Data_In()//设置成输入
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = PRESSURE_DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(PRESSURE_DT_GPIO_Port, &GPIO_InitStruct);
}
//************************************
// 函数:    Ultrasonic_Init
// 函数全名:  Ultrasonic_Init
// 函数类型:    public 
// 返回值:   uint8_t
// Qualifier:
// 参数: uint8_t gpioIndex   gpio端口索引
// 参数: uint16_t sk_pin	//时钟引脚
// 参数: uint16_t dt_pin	//数据接收引脚
//************************************
void Hx711_Sck_Out()
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//时钟引脚初始化
	GPIO_InitStruct.Pin = PRESSURE_SCK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PRESSURE_SCK_GPIO_Port, &GPIO_InitStruct);

	//数据引脚初始化
	
	return 0;
}

uint8_t is_ready() {
	uint8_t val = PRE_DT;
	return val == 0;
}
unsigned long Read_Weigh(uint32_t timout)
{
	uint32_t i = 0;
	unsigned long Count = 0;//无符号4个字节
	Hx711_Data_Out(); //设置IO输出
	HAL_GPIO_WritePin(PRESSURE_DT_GPIO_Port,PRESSURE_DT_Pin,1);
	HAL_GPIO_WritePin(PRESSURE_SCK_GPIO_Port, PRESSURE_SCK_Pin, 0);
	Hx711_Data_In(); //设置IO输入

	long tim = HAL_GetTick();
	while (HAL_GetTick()-tim<timout)
	{
		if (!HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port,PRESSURE_DT_Pin))
		{
			break;
		}
	}
	for (i = 0; i < 24; i++)
	{
		PRE_SCK = 1;
		DWT_Delay_us(1);
		Count = Count << 1;
		PRE_SCK = 0;
		if (HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin))
			Count++;
		DWT_Delay_us(1);
	}
	PRE_SCK = 1;
	DWT_Delay_us(1);
	Count = Count ^ 0x800000;//^异或运算符,位值相同为0,不同为1
	PRE_SCK = 0;
	DWT_Delay_us(1);
	return(Count);
}
///取实际重量=测试-毛坯
uint16_t GetRealWeight(unsigned long skin)
{

}