#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H
#include "stdint.h"
#include "stm32f1xx_hal.h"

//压力传感器引脚
#define PRESSURE_DT_Pin GPIO_PIN_8
#define PRESSURE_DT_GPIO_Port GPIOB
#define PRESSURE_SCK_Pin GPIO_PIN_9
#define PRESSURE_SCK_GPIO_Port GPIOB

#define PRE_SCK		PBout(9)   //时钟
#define PRE_DT		PBin(0);   //数据

void Hx711_Sck_Out();
void Hx711_Data_In();
void Hx711_Data_Out();
unsigned long Read_Weigh(uint32_t timout);
uint32_t GetRealWeight(unsigned long skin);
unsigned long Read_Weigh_1(uint32_t timout);
#endif // !__ULTRASONIC_H
