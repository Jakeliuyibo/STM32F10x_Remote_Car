/**
  ******************************************************************************
  * @file    map_SCOMandSBUS.h
  * @author  LYB
  * @version V1.0.0
  * @date    202/4/18
  * @brief   描述了SCOM数据协议转换SBUS的功能实现
  ******************************************************************************/
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __MAP_SCOMANDSBUS_H
#define __MAP_SCOMANDSBUS_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"


/* Defitions -----------------------------------------------------------------*/



/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  定义SBUS数据结构体
  */
typedef struct __SBUSData_Struct
{
    uint16_t           Channel[16];       /* 通道   */
    uint8_t            FlagByte;          /* 标志位 */
}SBUSData_Struct;



/* Interface declaration -----------------------------------------------------*/



/**
 * @brief  将SCOM协议数据转化为SBUS协议
 * @param  *SCOMdata： SCOM数据指针，数组长度25byte   8bit     
 *            * SCOMdata[0]               首字节      0x0F           
 *            * SCOMdata[1]-SCOMdata[22]  用户数据    
 *            * SCOMdata[23]              标志字节    0x00     
 *            * SCOMdata[24]              尾字节      0x00      
 * @param  *SBUSdata： SBUS数据存储指针,数组长度16byte 11bit
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_SCOMtoSBUS(uint8_t *SCOMdata , SBUSData_Struct *SBUSdata);


/**
 * @brief  将SBUS协议数据转化为SCOM协议
 * @param  *SBUSdata： SBUS数据存储指针,数组长度16byte  11bit
 * @param  *SCOMdata： 串口数据指针，要求数组长度25byte 8bit     
 *            * SCOMdata[0]               首字节        0x0F           
 *            * SCOMdata[1]-SCOMdata[22]  用户数据    
 *            * SCOMdata[23]              标志字节      0x00     
 *            * SCOMdata[24]              尾字节        0x00      
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_SBUStoSCOM(SBUSData_Struct *SBUSdata , uint8_t *SCOMdata);







#endif





