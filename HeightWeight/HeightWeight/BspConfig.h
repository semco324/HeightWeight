#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "system.h"

//外设串口定义
//设备串口波特率设置
#define BLE_BAND				115200        //蓝牙串口
#define DEBUG_BAND				115200        //调试用串口
#define HMI_BAND				115200		//HML串口屏(淘晶驰)

//串口分配

#define  UART_BLE				&huart1			//蓝牙
#define  UART_ULTRASONIC		&huart2			//超声波接口	
#define  UART_TFT				&huart3			//TFT屏(武汉晶显)


//电压检测引脚
#define V_TEST_Pin GPIO_PIN_4
#define V_TEST_GPIO_Port GPIOA

//------------------------------------------ 语音芯片WTN6040

//#define  CLK_2A                 PBout(13) //时钟输出（位带操作）
//#define  P_DATA_2A               PBout(12) //数据输出（位带操作）


#define DIV 220              //比例因子
#define ERROR		23     //误差调节   +1表示向上加10g 反之表示向下减10g
#endif // !__BSPCONFIG_H
