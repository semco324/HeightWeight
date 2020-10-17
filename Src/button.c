/*
===============================================================
*概述:按键驱动
*硬件:STM32F103ZET6
*文件:button.c  
*日期:2020/5/23      
*作者: xiaowenlg   原创
*基本原理：判断两次获取的按键值是否相同，相同就不动作，不同就动作

*使用方法=======================================================
1，在要使用的文件中#include "button.h"
2,声明Key_Message 结构体 数组，按键信息数组
3，声明两个全局变量用于存储本次和上次按键的值
4,初始化按键信息
5，定义按键处理回调函数
6，调用按键扫描函数
===============================================================
*/
#include "button.h"
//按键引脚初始化
void Key_Gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = WEIGHT_RES_Pin | DISTANCE_RES_Pin | KEY2_Pin | KEY3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin */
	GPIO_InitStruct.Pin =KEY1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

//取按键值
//************************************
// 函数:    GetKey_Value
// 函数全名:  GetKey_Value
// 函数类型:    public 
// 返回值:   uint16_t                     返回键值
// Qualifier://取按键值
// 参数: Key_Message * t_keymessage       按键结构体
// 参数: uint16_t * KeyValue              储存按键值        声明为全局变量，指针形式，目的是传数据的地址
//************************************
uint16_t GetKey_Value(Key_Message *t_keymessage, uint16_t *KeyValue)
{
	uint8_t Key_Count = t_keymessage[0].Key_count;
	for (int i = 0; i < Key_Count; i++)
	{
		if (HAL_GPIO_ReadPin(t_keymessage[i].GPIOx, t_keymessage[i].GPIO_Pin))
			*KeyValue |= (1 << i);                    //或运算       置位为1
		else
			*KeyValue &= ~(1 << i);                  //取反再做与运输   复位为0
		//Uartx_printf(&huart1, "value is %x\r\n", *KeyValue);
	}
	return *KeyValue;
}
//************************************
// 函数:    Decide_KeyValue
// 函数全名:  Decide_KeyValue
// 函数类型:    public 
// 返回值:   void
// Qualifier:  扫描按键值并执行按键回调函数
// 参数: uint16_t value          获取到的按键值
// 参数: uint16_t * lastvalue    存储上一次的按键值               声明为全局变量，指针形式，目的是传数据的地址
// 参数: fun callback            回调函数
//************************************
void  Decide_KeyValue(uint16_t value, uint16_t *lastvalue, Key_Message *t_keymessage, fun callback)
{
	char s[16] = { 0 };
	uint16_t tempvalue = 0;
	if (value^*lastvalue)
	{
		tempvalue = value;
		for (uint8_t i = 0; i < 16; i++)
		{
			if (!(tempvalue & 0x0001))
			{
				//执行回调函数
				(*callback)(t_keymessage[i]);        //返回按键结构体
			}
			tempvalue >>= 1;
		}
		*lastvalue = value;
	}
	HAL_Delay(10);
}
//总体扫描函数
void ScanKeys(uint16_t *KeyValue, uint16_t *lastvalue, Key_Message *t_keymessage, fun callback)
{
	Decide_KeyValue(GetKey_Value(t_keymessage,KeyValue), lastvalue, t_keymessage, callback);
}