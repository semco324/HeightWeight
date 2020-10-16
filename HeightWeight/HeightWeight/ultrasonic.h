#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H
#include "stdint.h"
#include "stm32f1xx_hal.h"


uint8_t Ultrasonic_Init(uint8_t gpioIndex, uint16_t sk_pin, uint16_t dt_pin);
#endif // !__ULTRASONIC_H
