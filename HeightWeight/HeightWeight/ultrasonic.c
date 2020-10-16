#include "ultrasonic.h"
#include "BspConfig.h"

GPIO_TypeDef *GpioArr[4] = { GPIOA, GPIOB, GPIOC, GPIOD};
//************************************
// ����:    Ultrasonic_Init
// ����ȫ��:  Ultrasonic_Init
// ��������:    public 
// ����ֵ:   uint8_t
// Qualifier:
// ����: uint8_t gpioIndex   gpio�˿�����
// ����: uint16_t sk_pin	//ʱ������
// ����: uint16_t dt_pin	//���ݽ�������
//************************************
uint8_t Ultrasonic_Init(uint8_t gpioIndex, uint16_t sk_pin, uint16_t dt_pin)
{
	GPIO_TypeDef *GPIOx;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	switch (gpioIndex)
	{
	case 0:
		__HAL_RCC_GPIOA_CLK_ENABLE(); break;//��GPIOA��ʱ��
	case 1:
		__HAL_RCC_GPIOB_CLK_ENABLE(); break;
	case 2:
		__HAL_RCC_GPIOC_CLK_ENABLE(); break;
	case 3:
		__HAL_RCC_GPIOD_CLK_ENABLE(); break;
	default:
		break;
	}
	//ʱ�����ų�ʼ��
	GPIO_InitStruct.Pin = sk_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GpioArr[gpioIndex], &GPIO_InitStruct);

	//�������ų�ʼ��
	GPIO_InitStruct.Pin = dt_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GpioArr[gpioIndex], &GPIO_InitStruct);
	return 0;
}
