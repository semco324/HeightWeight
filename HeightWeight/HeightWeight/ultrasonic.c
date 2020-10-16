#include "ultrasonic.h"
#include "BspConfig.h"

GPIO_TypeDef *GpioArr[4] = { GPIOA, GPIOB, GPIOC, GPIOD};
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
uint8_t Ultrasonic_Init(uint8_t gpioIndex, uint16_t sk_pin, uint16_t dt_pin)
{
	GPIO_TypeDef *GPIOx;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	switch (gpioIndex)
	{
	case 0:
		__HAL_RCC_GPIOA_CLK_ENABLE(); break;//开GPIOA的时钟
	case 1:
		__HAL_RCC_GPIOB_CLK_ENABLE(); break;
	case 2:
		__HAL_RCC_GPIOC_CLK_ENABLE(); break;
	case 3:
		__HAL_RCC_GPIOD_CLK_ENABLE(); break;
	default:
		break;
	}
	//时钟引脚初始化
	GPIO_InitStruct.Pin = sk_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GpioArr[gpioIndex], &GPIO_InitStruct);

	//数据引脚初始化
	GPIO_InitStruct.Pin = dt_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GpioArr[gpioIndex], &GPIO_InitStruct);
	return 0;
}
