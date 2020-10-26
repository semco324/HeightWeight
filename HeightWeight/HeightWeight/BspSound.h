#ifndef __BSPSOUND_H
#define __BSPSOUND_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
void Firstmuis();                    //测试开始，播放语音
void BeginSound();            //开始测试播放
//播放函数
uint8_t ProcessHeight(double numdata); //身高
uint8_t ProcessWeight(double numdata);//体重;
uint8_t ProcessBMI(double numdata);//bmi;
double Cal_BMI(double hei, double wei); //身高/体重的平方;
void PlayHei_Wei(double height, double wei);
#endif // !__BSPSOUND_H
