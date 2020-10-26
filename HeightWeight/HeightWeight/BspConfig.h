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
#define WEIGHT_MAX	4294967

#define BUTTON_SCAN_CYCLE			50      //����ɨ������


//оƬflash�ռ䶨��
#define CHIP_CAPACITY				128			//оƬflash������λKb
#define CHIP_START_ADDRESS			0x08000000

//������ַ
#define HUAN_YING					43							//��ӭʹ�����������Ŀ
#define BEN_XIANG_MU					26                        //����ĿΪ������
#define CESHI						27						  //����
#define TI_ZHI_ZHI_SHU				28						//����ָ��
#define QING_ZHAN_LI				37						//����վ���ڲ���λ�����־�ֹ�����������Ӳ��Խ��׼ȷ��
#define YIN_XIAO_61					61						//��Ч61
#define CESHI_KAISHI				44						//���Կ�ʼ
#define CESHI_JIESHU				45						//���Խ���
#endif // !__BSPCONFIG_H
