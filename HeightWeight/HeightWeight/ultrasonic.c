#include "ultrasonic.h"
#include "BspConfig.h"
#include "dwt_stm32_delay.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
void Hx711_Data_Out() //���ó����
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = PRESSURE_DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PRESSURE_DT_GPIO_Port, &GPIO_InitStruct);
}
void Hx711_Data_In()//���ó�����
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = PRESSURE_DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(PRESSURE_DT_GPIO_Port, &GPIO_InitStruct);
}
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
void Hx711_Sck_Out()
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//ʱ�����ų�ʼ��
	GPIO_InitStruct.Pin = PRESSURE_SCK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PRESSURE_SCK_GPIO_Port, &GPIO_InitStruct);

	//�������ų�ʼ��
	
	return 0;
}

uint8_t is_ready() {
	uint8_t val = PRE_DT;
	return val == 0;
}
unsigned long Read_Weigh(uint32_t timout)
{
	uint32_t i = 0;
	unsigned long Count = 0;//�޷���4���ֽ�
	Hx711_Data_Out(); //����IO���
	HAL_GPIO_WritePin(PRESSURE_DT_GPIO_Port,PRESSURE_DT_Pin,1);
	HAL_GPIO_WritePin(PRESSURE_SCK_GPIO_Port, PRESSURE_SCK_Pin, 0);
	Hx711_Data_In(); //����IO����

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
	Count = Count ^ 0x800000;//^��������,λֵ��ͬΪ0,��ͬΪ1
	PRE_SCK = 0;
	DWT_Delay_us(1);
	return(Count);
}
///ȡʵ������=����-ë��
uint16_t GetRealWeight(unsigned long skin)
{

}