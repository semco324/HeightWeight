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

//称重清零
#define WEIGHT_RES_Pin GPIO_PIN_0
#define WEIGHT_RES_GPIO_Port GPIOA
//距离清零
#define DISTANCE_RES_Pin GPIO_PIN_1
#define DISTANCE_RES_GPIO_Port GPIOA
//电压检测引脚
#define V_TEST_Pin GPIO_PIN_4
#define V_TEST_GPIO_Port GPIOA
//压力传感器引脚
#define PRESSURE_DT_Pin GPIO_PIN_0
#define PRESSURE_DT_GPIO_Port GPIOB
#define PRESSURE_SCK_Pin GPIO_PIN_1
#define PRESSURE_SCK_GPIO_Port GPIOB
//------------------------------------------ 语音芯片WTN6040
#define WTN6040_DATA_Pin GPIO_PIN_12
#define WTN6040_DATA_GPIO_Port GPIOB
#define WTN6040_SCK_Pin GPIO_PIN_13
#define WTN6040_SCK_GPIO_Port GPIOB
#define WTN6040_BUSY_Pin GPIO_PIN_14
#define WTN6040_BUSY_GPIO_Port GPIOB
#define  CLK_2A                 PBout(13) //时钟输出（位带操作）
#define  P_DATA_2A               PBout(12) //数据输出（位带操作）
//备用按键
#define KEY1_Pin GPIO_PIN_15
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_8
#define KEY2_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_11
#define KEY3_GPIO_Port GPIOA


#endif // !__BSPCONFIG_H
