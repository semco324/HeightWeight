#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "system.h"

//���贮�ڶ���
//�豸���ڲ���������
#define BLE_BAND				115200        //��������
#define DEBUG_BAND				115200        //�����ô���
#define HMI_BAND				115200		//HML������(�Ծ���)

//���ڷ���

#define  UART_BLE				&huart1			//����
#define  UART_ULTRASONIC		&huart2			//�������ӿ�	
#define  UART_TFT				&huart3			//TFT��(�人����)


//��ѹ�������
#define V_TEST_Pin GPIO_PIN_4
#define V_TEST_GPIO_Port GPIOA

//------------------------------------------ ����оƬWTN6040

//#define  CLK_2A                 PBout(13) //ʱ�������λ��������
//#define  P_DATA_2A               PBout(12) //���������λ��������


#define DIV 220              //��������
#define ERROR		23     //������   +1��ʾ���ϼ�10g ��֮��ʾ���¼�10g
#endif // !__BSPCONFIG_H
