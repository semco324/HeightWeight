#include "BspSound.h"
#include "APPTooL.h"
#include "application.h"
#include "BspConfig.h"
uint8_t sonundArray[5] = { HUAN_YING, BEN_XIANG_MU, TI_ZHI_ZHI_SHU, CESHI, QING_ZHAN_LI};
//uint8_t dalaytim[4] = { 0xf3,YIN_XIAO_61,0xf8,10};				//F3H + ��ַ + F8H + 10H
void Firstmuis()
{
	WTN6040_PlayArray(5, sonundArray);
	//WTN6040_PlayArray(4, dalaytim);
	osDelay(2000);
	WTN6040_PlayOneByte(YIN_XIAO_61);
	osDelay(100);
	WTN6040_PlayOneByte(CESHI_KAISHI);
}
void OverTest()					//���Խ���
{
	WTN6040_PlayOneByte(CESHI_JIESHU);
}
uint8_t ProcessHeight(double numdata)//���
{
	uint8_t dat[16] = { 0 };
	uint8_t reslen = 0, templen = 0;
	uint8_t tdat[16] = { 0 };
	templen = DataSeparation(numdata, tdat);
	dat[0] = NINDE;
	dat[1] = SHEN_GAO;
	dat[2] = GONG_FEN;
	reslen = insertArray(dat, 3, tdat, templen, 2);
	WTN6040_PlayArray(reslen, dat);
	return reslen;
}

uint8_t ProcessWeight(double numdata)//����
{
	uint8_t dat[16] = { 0 };
	uint8_t reslen = 0, templen = 0;
	uint8_t tdat[16] = { 0 };
	templen = DataSeparation(numdata, tdat);
	dat[0] = TI_ZHONG;
	dat[1] = GONG_JIN;
	reslen = insertArray(dat, 2, tdat, templen, 1);
	WTN6040_PlayArray(reslen, dat);
	return reslen;
}

uint8_t ProcessBMI(double numdata)//bmi
{
	uint8_t dat[16] = {0};
	uint8_t reslen = 0, templen = 0;
	uint8_t tdat[16] = { 0 };
	templen = DataSeparation(numdata, tdat);
	dat[0] = SOUND_BIM;
	dat[1] = 0;
	reslen = insertArray(dat, 1, tdat, templen, 1);
	WTN6040_PlayArray(reslen, dat);
	return (reslen);
}

double Cal_BMI(double hei, double wei)        //���/���ص�ƽ��
{
	double h = hei*hei;
	return (wei/h);
}
//************************************
// ����:    PlayHei_Wei
// ����ȫ��:  PlayHei_Wei
// ��������:    public 
// ����ֵ:   void
// Qualifier: //���岥�ź���
// ����: double height      ���
// ����: double wei			����
//************************************
void PlayHei_Wei(double height, double wei)          //���岥�ź���
{
	double bmi = Cal_BMI(height / 100.00, wei);
	uint8_t len = ProcessHeight(height);
	osDelay(100);
	ProcessWeight(wei);
	osDelay(100);
	ProcessBMI(bmi);
	osDelay(300);
	WTN6040_PlayOneByte(TI_XING);
	if (bmi <= 18.40)
	{
		WTN6040_PlayOneByte(PIAN_SHOU);
	}
	else if ((bmi > 18.50) && (bmi < 25.90))
	{
		WTN6040_PlayOneByte(ZHENG_CHANG);
	}
	else if (bmi >= 28.00)
		WTN6040_PlayOneByte(PIAN_PANG);
}