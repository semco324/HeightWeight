#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H
#include "stdint.h"
#include "stm32f1xx_hal.h"


void Hx711_Sck_Out();
void Hx711_Data_In();
void Hx711_Data_Out();
unsigned long Read_Weigh(uint32_t timout);
uint32_t GetRealWeight(unsigned long skin);
#endif // !__ULTRASONIC_H
