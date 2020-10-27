/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "usart.h"
#include "ultrasonic.h"
#include "BspConfig.h"
#include "button.h"
#include "stmflash.h"
#include "gpio.h"
#include "application.h"
#include "BspSound.h"
#include "adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//按键用变量
uint16_t KeyValue_t = 0xffff; uint16_t lastvalue_t = 0xffff;
Key_Message keys[5] = { 0 };

//毛坯重量
uint32_t Weight_Skin = 0;
uint16_t Skin_arr[2] = {0};   //毛皮重量数组，为存到mcuflash中

//flash中
uint32_t Weight_flash = 0;
uint16_t Weight_flash_array[2] = {0};
uint16_t Height_flash_array[1] = { 0 };//传感器到地面高度
//距离传感器变量
uint16_t Distance = 0;
uint16_t AllDistance = 0;       //传感器到地面高度
uint16_t Height_res = 0;
//语音播报地址数组
uint8_t height_array[16] = {0};
uint32_t sound_weight = 0;
uint16_t tip_play_num = 0;   //提示计数
uint8_t  tip_flag = 0;		//提示标志
uint8_t  clear_num = 0;
//线程句柄
osThreadId SensorDriveHandle;//传感器驱动线程
osThreadId ButtonProcessHandle;//按键处理线程
/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void SensorDrive_CallBack(void const *argument);
void  ButtonProcess_CallBack(void const *argument);

//按键回调函数
void  Key_CallBack(Key_Message index);

//向TFT屏发数据
void SendMessageToTFT(uint16_t address);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	STMFLASH_Read(FLASH_BEGIN, Weight_flash_array, 2);
	STMFLASH_Read(FLASH_BEGIN + 6, Height_flash_array, 1);//读高度记录
	Weight_flash = Weight_flash_array[1];
	Weight_flash = (Weight_flash << 16) + Weight_flash_array[0];
	Weight_Skin = Weight_flash;
	AllDistance = Height_flash_array[0];
	/////////////////////////////////////////////////////////////////////////////////////////////////////
#if DEBUG_PRINT
	Uartx_printf(&huart1, "The Weight_skin is %d\r\n", Weight_flash);
	Uartx_printf(&huart1, "The Height_skin is %d\r\n", Height_flash_array[0]);
#endif
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	//unsigned long val = 0;
	//unsigned int  Weight_Shiwu = 0;
 // for(;;)
 // {
	//  val = Read_Weigh_1(1000);
	//  val = val / 100;
	//  Weight_Shiwu = val;
	//  Weight_Shiwu = (unsigned int)((float)Weight_Shiwu / 0.0214);
	//  printf("The Weight is:%dg", GetRealWeight(0)); fflush(stdout);//必须刷新输出流**************************************
	// //printf("The Weight is:%ldg", Weight_Shiwu); fflush(stdout);//必须刷新输出流
 //   osDelay(500);
	//
 // }
	taskENTER_CRITICAL();//进入临界区
	//传感器驱动线程
	osThreadDef(SensorDrive, SensorDrive_CallBack, 4, 0, 128);
	SensorDriveHandle = osThreadCreate(osThread(SensorDrive), NULL);
	//按键处理线程
	osThreadDef(ButtonProcess, ButtonProcess_CallBack, 5, 0, 128);
	ButtonProcessHandle = osThreadCreate(osThread(ButtonProcess), NULL);
#if DEBUG_PRINT
	Uart_printf(&huart1, "Start sub stask\r\n");
#endif	
	vTaskDelete(defaultTaskHandle); //删除任务
	taskEXIT_CRITICAL();//推出临界区
  /* USER CODE END StartDefaultTask */
	
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void SensorDrive_CallBack(void const *argument)             //传感器操作线程
{
	WTN6040_PlayOneByte(SOUND_VALUE);//调节音量
	Firstmuis();					//播放开始音乐
	for (;;)
	{
		
		MY_USART_SendByte(&huart2, 0x55);
		sound_weight = GetRealWeight(Weight_Skin);
		SendMessageToTFT(TFT_VARIABLE_START); 
#if DEBUG_PRINT
		printf("The Weight is:%dg\r\n", abs(sound_weight)); fflush(stdout);//必须刷新输出流**************************************
#endif		
		HAL_GPIO_TogglePin(LED_LEFT_PORT, LED_LEFT_PIN);//线程活动指示灯
		osDelay(500);
	}
}
void  ButtonProcess_CallBack(void const *argument)
{
	for (;;)
	{
		if (uart2_rec.reover == 1)
		{
			uart2_rec.reover = 0;
			Distance = uart2_rec.redata[0] * 256 + uart2_rec.redata[1];

			if (AllDistance >= Distance)   //限制数据 不出现负数
				Height_res = AllDistance - Distance;
			else
				Height_res = 0;
#if DEBUG_PRINT
			Uart_printf(&huart1, "The ResDistance is %d mm\r\n", Height_res); //等待蓝牙信息-0
			//Uart_printf(&huart1, "The Distance is %d mm\r\n", Distance); //等待蓝牙信息-0
			//Uart_printf(&huart1, uart2_rec.redata);
#endif
		}
		//用户踩到秤上但没按开始键处理--------------提示
		if ((tip_flag == 0) && (abs(sound_weight)>10000))    //当用户踩到秤上没按开始键时计时开始sound_weight大于10公斤触发
		{
			if (tip_play_num++>200)           //200*50ms后提示用户按开始键
			{
				tip_play_num = 0;
				WTN6040_PlayOneByte(QING_AN_KAISHI);
				if (clear_num++>5)							//限制提示次数为5次，5次后不再提示
				{
					clear_num = 0;
					tip_flag = 1;
				}
			}
		}
		ScanKeys(&KeyValue_t, &lastvalue_t, keys, Key_CallBack);
		HAL_GPIO_TogglePin(LED_RITHT_PORT, LED_RIGHT_PIN);                  //线程活动指示灯
		///Uart_printf(&huart1, "Task2\r\n");
		osDelay(BUTTON_SCAN_CYCLE);

	}
}
void Key_Regist()
{
	//重量清零
	keys[0].GPIOx = WEIGHT_RES_GPIO_Port;
	keys[0].GPIO_Pin = WEIGHT_RES_Pin;
	keys[0].Key_count = 5;

	//身高清零按键
	keys[1].GPIOx = DISTANCE_RES_GPIO_Port;
	keys[1].GPIO_Pin = DISTANCE_RES_Pin;
	keys[1].Key_count = 5;

	//备用1
	keys[2].GPIOx = KEY1_GPIO_Port;
	keys[2].GPIO_Pin = KEY1_Pin;
	keys[2].Key_count = 5;

	keys[3].GPIOx = KEY2_GPIO_Port;
	keys[3].GPIO_Pin = KEY2_Pin;
	keys[3].Key_count = 5;

	keys[4].GPIOx = KEY3_GPIO_Port;
	keys[4].GPIO_Pin = KEY3_Pin;
	keys[4].Key_count = 5;
}

void  Key_CallBack(Key_Message index)
{

	if (index.GPIO_Pin == WEIGHT_RES_Pin) //秤重清零
	{

		Weight_Skin = GetRealWeight(0);
		Skin_arr[0] = Weight_Skin & 0x0000ffff;
		Skin_arr[1] = Weight_Skin >> 16;
		STMFLASH_Write(FLASH_BEGIN, Skin_arr, 2);//把清零数据存储到flash中
	}
	if (index.GPIO_Pin==DISTANCE_RES_Pin) //距离清零
	{
		AllDistance = Distance;
		STMFLASH_Write(FLASH_BEGIN+6, &Distance, 1);
	}
	if (index.GPIO_Pin==KEY1_Pin)
	{
		//Uartx_printf(&huart1, "*****************************\r\n");
		tip_flag = 1;
		BeginSound();
		osDelay(2000);//等待数据稳定
		if (abs(sound_weight) > 200)                                   //大于0.2公斤才播放
		{
			PlayHei_Wei(Height_res / 10.00, abs(sound_weight) / 1000.00);
		}
		else
		{
			WTN6040_PlayOneByte(QING_ZHAN_LI);
			osDelay(300);
			WTN6040_PlayOneByte(QING_AN_KAISHI);
		}
		
	}
	//Uartx_printf(&huart1, "Key===%d\r\n", index);
}
//向TFT屏发送数据
void SendMessageToTFT(uint16_t address)
{
	uint16_t TFT_SendArray[4] = { 0 };
	double bmires = 0.00;
	uint16_t TFT_bmi = 0;
	bmires = Cal_BMI_TFT(sound_weight, Height_res);
	TFT_bmi = (uint16_t)(bmires * 10);
	TFT_SendArray[0] = Height_res; //身高
	TFT_SendArray[1] = (uint16_t)(abs(sound_weight) / 100);//体重
	TFT_SendArray[2] = TFT_bmi;
	TFT_SendArray[3] = ADC_GetValue(&hadc1, 10);			//电池电量
	write_multiple_variable_store_82(address, 4, TFT_SendArray);
	write_register_80_1byte(TFT_BUTTON, 1);
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
