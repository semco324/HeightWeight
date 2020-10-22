#ifndef __STMFLASH_H__
#define __STMFLASH_H__

#include <stdint-gcc.h>
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32 FLASH 驱动代码	   
//Copyright(C) xiaowenlg
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
//用户根据自己的需要设置
#define STM32_FLASH_SIZE			CHIP_CAPACITY      //stm32flash 大小	
#define STM32_FLASH_BASE			CHIP_START_ADDRESS   //起始地址
#define FLASH_BEGIN_BASE(n)					STM32_FLASH_BASE+(STM32_FLASH_SIZE-n)*1024    //n为扇区个数           返回: EERPOM开始地址
#define FLASH_BEGIN                 FLASH_BEGIN_BASE(2)                                   //操作内存开始地址 倒数第二个地址段
#define STM32_FLASH_WREN 1              //使能FLASH写入(0，不是能;1，使能)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
//FLASH解锁键值
 

uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  //读出半字
void STMFLASH_WriteLenByte(uint32_t WriteAddr,uint32_t DataToWrite,uint16_t Len);	//指定地址开始写入指定长度的数据
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr,uint16_t Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead);   		//从指定地址开始读出指定长度的数据

//测试写入
void Test_Write(uint32_t WriteAddr,uint16_t WriteData);
void STMFLASH_FormatWrite(uint32_t WriteAddr, uint16_t NumToWritechar, char* fmt, ...);
#endif

















