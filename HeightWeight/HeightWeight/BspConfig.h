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
#define WEIGHT_MAX	4294967

#define BUTTON_SCAN_CYCLE			50      //按键扫描周期


//芯片flash空间定义
#define CHIP_CAPACITY				128			//芯片flash容量单位Kb
#define CHIP_START_ADDRESS			0x08000000

//语音地址
#define HUAN_YING					43							//欢迎使用启帆体测项目
#define BEN_XIANG_MU					26                        //本项目为您进行
#define CESHI						27						  //测试
#define TI_ZHI_ZHI_SHU				28						//体质指数
#define QING_ZHAN_LI				37						//请您站立在测试位并保持静止不动，以增加测试结果准确性
#define YIN_XIAO_61					61						//音效61
#define QING_AN_KAISHI				41						//请按开始建开始
#define CESHI_KAISHI				44						//测试开始
#define CESHI_JIESHU				45						//测试结束
#define NINDE						33						//您的
#define SHEN_GAO					35						//身高
#define TI_ZHONG					36						//体重
#define SOUND_BIM					28						//体质指数
#define GONG_JIN					16						//公斤
#define GONG_FEN					17						//公分
#define	TI_XING						49						//体型
#define PIAN_PANG					50						//偏胖
#define PIAN_SHOU					51						//偏瘦
#define ZHENG_CHANG					52						//正常
#define HUAN_ZAI_CI_YING			57						//欢迎再次使用

//音量值
#define SOUND_VALUE					0xEF                   //音量       0xe0-----0xef
//TFT屏
#define TFT_VARIABLE_START		0x0001      //TFT屏变量起始地址
#define TFT_BUTTON				0x4F		//TFT屏上的按钮

//调试开关
#define DEBUG_PRINT					1                                
#endif // !__BSPCONFIG_H
