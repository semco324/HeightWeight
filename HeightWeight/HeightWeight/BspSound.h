#ifndef __BSPSOUND_H
#define __BSPSOUND_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
void Firstmuis();                    //���Կ�ʼ����������
void BeginSound();            //��ʼ���Բ���
//���ź���
uint8_t ProcessHeight(double numdata); //���
uint8_t ProcessWeight(double numdata);//����;
uint8_t ProcessBMI(double numdata);//bmi;
double Cal_BMI(double hei, double wei); //���/���ص�ƽ��;
void PlayHei_Wei(double height, double wei);
#endif // !__BSPSOUND_H
