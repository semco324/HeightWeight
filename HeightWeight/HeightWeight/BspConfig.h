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

//��������
#define WEIGHT_RES_Pin GPIO_PIN_0
#define WEIGHT_RES_GPIO_Port GPIOA
//��������
#define DISTANCE_RES_Pin GPIO_PIN_1
#define DISTANCE_RES_GPIO_Port GPIOA
//��ѹ�������
#define V_TEST_Pin GPIO_PIN_4
#define V_TEST_GPIO_Port GPIOA
//ѹ������������
#define PRESSURE_DT_Pin GPIO_PIN_0
#define PRESSURE_DT_GPIO_Port GPIOB
#define PRESSURE_SCK_Pin GPIO_PIN_1
#define PRESSURE_SCK_GPIO_Port GPIOB
//------------------------------------------ ����оƬWTN6040
#define WTN6040_DATA_Pin GPIO_PIN_12
#define WTN6040_DATA_GPIO_Port GPIOB
#define WTN6040_SCK_Pin GPIO_PIN_13
#define WTN6040_SCK_GPIO_Port GPIOB
#define WTN6040_BUSY_Pin GPIO_PIN_14
#define WTN6040_BUSY_GPIO_Port GPIOB
#define  CLK_2A                 PBout(13) //ʱ�������λ��������
#define  P_DATA_2A               PBout(12) //���������λ��������
//���ð���
#define KEY1_Pin GPIO_PIN_15
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_8
#define KEY2_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_11
#define KEY3_GPIO_Port GPIOA


#endif // !__BSPCONFIG_H
