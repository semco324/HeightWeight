/*!
 *
 * TFT屏和74HC595驱动
 * date 九月 2019
 */
#include "application.h"
#include "system.h"
#include "usart.h"
#include "dwt_stm32_delay.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "BspConfig.h"
//#include "cmsis_os.h"
//************************************
// 函数:    HC595_Init
// 函数全名:  HC595_Init
// 函数类型:    public 
// 返回值:   void
// Qualifier:595初始化
//************************************
void HC595_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(HC595_PORT, HC595_PIN, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = HC595_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(HC595_PORT, &GPIO_InitStruct);
}
//************************************
// 函数:    SendData_595
// 函数全名:  SendData_595
// 函数类型:    public 
// 返回值:   void
// Qualifier:发送数据
// 参数: uint16_t outdate
//************************************
void SendData_595(uint16_t outdate)
{
	uint8_t i = 0;
	for (i = 0; i < 16; i++)
	{
		
		if ((outdate & 0x8000) != 0)
			DS = 1;
		else
			DS = 0;
		SCK = 0;
		__NOP();
		__NOP();
		__NOP();
		SCK = 1;
		__NOP();
		__NOP();
		__NOP();
		outdate <<= 1;

	}
	RCK = 0;
	osDelay(1);
	RCK = 1;

}
/*TFT操作*/
//************************************
// 函数:    write_register_80_1byte
// 函数全名:  write_register_80_1byte
// 函数类型:    public 
// 返回值:   void
// Qualifier:写寄存器1字节
// 参数: uint8_t address
// 参数: uint8_t data
//************************************
void write_register_80_1byte(uint8_t address, uint8_t data) 
{
	uint8_t i;
	uint8_t array[array_length];

	array[0] = USER_R3;
	array[1] = USER_RA;
	array[2] = 0x03;               //指令长度
	array[3] = 0x80;
	array[4] = address;
	array[5] = data;
	MY_USART_SendData(UART_TFT, array, 6);
}

void write_multiple_register_80(uint8_t address, uint8_t data_length, uint8_t *data)
{
	uint8_t i, nDataLen;
	uint8_t array[array_length];

	array[0] = USER_R3;
	array[1] = USER_RA;
	array[2] = 1 + 1 + data_length;   //命令+地址+数据长度
	array[3] = 0x80;
	array[4] = address;

	for (i = 0; i < data_length; i++)
	{
		array[5 + i] = data[i];
	}

	nDataLen = array[2] + 3;        //有效命令长度

	MY_USART_SendData(UART_TFT, array, nDataLen);
}
//************************************
// 函数:    write_variable_store_82_1word
// 函数全名:  write_variable_store_82_1word
// 函数类型:    public 
// 返回值:   void
// Qualifier:写一个变量值
// 参数: uint16_t address
// 参数: uint16_t data
//************************************
void write_variable_store_82_1word(uint16_t address, uint16_t data)
{
	uint8_t i;
	uint8_t array[array_length];

	array[0] = USER_R3;
	array[1] = USER_RA;
	array[2] = 1 + 2 + 2;                  
	array[3] = 0x82;
	array[4] = (address & 0xFF00) >> 8;    
	array[5] = address & 0x00FF;         
	array[6] = (data & 0xFF00) >> 8;      
	array[7] = data & 0x00FF;            

	//MY_USART_SendData(UART_TFT, array, 8);
	HAL_UART_Transmit(UART_TFT, array, 8, 0xffff);
}

//************************************
// 函数:    write_multiple_variable_store_82
// 函数全名:  write_multiple_variable_store_82
// 函数类型:    public 
// 返回值:   void
// Qualifier:写多个变量值
// 参数: uint16_t address
// 参数: uint8_t data_length
// 参数: uint16_t * data
//************************************
void write_multiple_variable_store_82(uint16_t address, uint8_t data_length, uint16_t *data)
{
	uint8_t i, nDataLen;
	uint8_t array[array_length];

	array[0] = USER_R3;
	array[1] = USER_RA;
	array[2] = 1 + 2 + data_length * 2;  
	array[3] = 0x82;
	array[4] = (address & 0xFF00) >> 8;        
	array[5] = address & 0x00FF;             

	for (i = 0; i < data_length; i++)
	{
		array[6 + 2 * i] = (data[i] & 0xFF00) >> 8; 
		array[7 + 2 * i] = data[i] & 0x00FF;      
	}

	nDataLen = array[2] + 3;                 

	//MY_USART_SendData(UART_TFT, array, nDataLen);
	HAL_UART_Transmit(UART_TFT, array, nDataLen, 0xffff);
}
//WTN6040初始化
uint8_t WTN6040_Gpio_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*WTN6040引脚初始化*/
	/*PB13---OUT*/ /*和 PB12---OUT*/
	GPIO_InitStruct.Pin = CLK_2A_PIN | P_DATA_2A_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(WTN_GPIO_Port, &GPIO_InitStruct);
	/*PB15---INPUT*/
	GPIO_InitStruct.Pin = WTN6040_BUSY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(WTN_GPIO_Port, &GPIO_InitStruct);


}
uint8_t  Line_2A_WTN6(uint8_t SB_DATA)
{
	uint8_t S_DATA, B_DATA, j;
	CLK_2A = 1; //时钟线
	P_DATA_2A = 1; //数据线
	S_DATA = SB_DATA;
	CLK_2A = 0;
	osDelay(5);
	B_DATA = S_DATA & 0X01;
	//PBout(13) = 1;
	for (j = 0; j < 8; j++)
	{

		CLK_2A = 0; // 拉低
		P_DATA_2A = B_DATA; //传输数据一位
		//SendByte2(B_DATA);
		
		DWT_Delay_us(300); //延时 300us 
		CLK_2A = 1; //拉高
		DWT_Delay_us(300); //延时 300us 

		S_DATA = S_DATA >> 1;
		B_DATA = S_DATA & 0X01;
	}
	P_DATA_2A = 1;
	CLK_2A = 1;


}
#ifdef TFTPLAY
void TFT_playsound(uint8_t data_length, uint8_t *data, UART_HandleTypeDef *huart)//TFT播放语音
{
	uint8_t i, nDataLen;
	uint8_t array[array_length];

	array[0] = USER_R3;
	array[1] = USER_RA;
	array[2] = 1 + 2 + data_length * 2;
	array[3] = 0x85;
	array[4] = 0x03;
	array[5] = 0x01;

	for (i = 0; i < data_length; i++)
	{
		//array[6 + 2 * i] = (data[i] & 0xFF00) >> 8;
		array[6 + 2 * i] = 0;
		array[7 + 2 * i] = data[i] & 0x00FF;
	}
	
	nDataLen = array[2] + 3;
	
	MY_USART_SendData(huart, array, nDataLen);
}
#else
void WTN6040_PlayOneByte(uint8_t val)
{
	while (HAL_GPIO_ReadPin(WTN_GPIO_Port, WTN6040_BUSY_Pin) != 1);
	Line_2A_WTN6(val);
	
	
}
uint8_t WTN6040_PlayArray(uint8_t arrlen, uint8_t *soundarr)
{
	uint8_t res = 0;
	uint8_t i = 0;
	for (i = 0; i < arrlen; i++)
	{
		WTN6040_PlayOneByte(soundarr[i]);
		//osDelay(10);
		//Uart_printf(&DEBUG_UART.huart, "Data=========%d:%x\r\n", i, soundarr[i]);//测试播放数据
	}
	while (HAL_GPIO_ReadPin(WTN_GPIO_Port, WTN6040_BUSY_Pin) != 1);
	if (i == arrlen)
		res = 1;
	else
		res = 1;//播放完毕
	//Line_2A_WTN6(9);
	return res;
}
#endif
//************************************
// 函数:    playmusic
// 函数全名:  playmusic
// 函数类型:    public 
// 返回值:   void
// Qualifier:音乐播放
// 参数: uint16_t num
// 参数: uint8_t val
//************************************
void playmusic(uint16_t num, uint8_t val)
{
	uint8_t senddat[5] = {0};
	senddat[0] = 0x5b;
	senddat[1] = num >> 8;
	senddat[2] = num & 0x00ff;
	senddat[3] = 0x5A;
	if (val > 64)
		val = 64;
	senddat[4] = val;
	write_multiple_register_80(0x50, 5, senddat);
}
//************************************
// 函数:    stopmusic
// 函数全名:  stopmusic
// 函数类型:    public 
// 返回值:   void
// Qualifier: //停止播放音乐
// 参数: uint16_t num    要停止的音乐地址号
//************************************
void stopmusic(uint16_t num)
{
	uint8_t senddat[3] = { 0 };
	senddat[0] = 0x5c;
	senddat[1] = num >> 8;
	senddat[2] = num & 0x00ff;
	write_multiple_register_80(0x50, 3, senddat);
}
//************************************
// 函数:    Turen_Pic
// 函数全名:  Turen_Pic
// 函数类型:    public 
// 返回值:   void
// Qualifier:切换页面
// 参数: uint16_t num
//************************************
void Turen_Pic(uint16_t num)
{
	uint8_t senddat[2] = { 0 };
	
	senddat[0] = num >> 8;
	senddat[1] = num & 0x00ff;
	write_multiple_register_80(0x03, 2, senddat);
	//pageID = num;
}
void TFT_Beep(uint8_t n)//TFT屏蜂鸣器
{
	write_register_80_1byte(0x02, n);
}
void TFT_Readbytes(uint8_t adress,uint8_t readlen,UART_HandleTypeDef *huart)//读寄存器
{
	uint8_t senddat[3] = { 0 };
	senddat[0] = USER_R3;
	senddat[1] = USER_RA;
	senddat[2] = 3;
    senddat[3] = 0x81;
	senddat[4] = adress;
	senddat[5] = readlen;
	MY_USART_SendData(huart, senddat, 6);//发送读命令

	
}
//发送接收符
void HMI_SendEnd(UART_HandleTypeDef *huart)
{
	MY_USART_SendByte(huart, 0xff);
	MY_USART_SendByte(huart, 0xff);
	MY_USART_SendByte(huart, 0xff);
}
//************************************
// 函数:    HMI_SetVal
// 函数全名:  HMI_SetVal
// 函数类型:    public 
// 返回值:   void
// Qualifier: //发送数据到HMI屏
// 参数: UART_HandleTypeDef * huart
// 参数: const char * com  变量字符串 如"n0.val="
// 参数: uint32_t val    变量值
//************************************
void HMI_SetVal(UART_HandleTypeDef *huart, const char *com,uint32_t val )//发送数据到HMI屏
{
	Uart_printf(huart, "%s%d", com, val);
	HMI_SendEnd(huart);

}
void HMI_SetVal_t(UART_HandleTypeDef *huart, const char *com, uint32_t val)
{
	printf("%s%d", com, val); fflush(stdout);
	HMI_SendEnd(huart);

}

void HMI_SetTxt(UART_HandleTypeDef *huart, const char *com, char *txt)//发送数据到HMI屏
{
	//char DArray[HMIARRAYLENGTH] = {0};
	//sprintf(DArray,"n0.val=%d", val);
	//sprintf(DArray, "%s%d", com, val);
	//MY_USART_chars(huart, "x");
	//sprintf(DArray, "%s\"%s\"",com, txt);
	//MY_USART_chars(huart, DArray);
	Uart_printf(huart, "%s\"%s\"", com, txt);
	HMI_SendEnd(huart);

}
