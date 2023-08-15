/**
  ******************************************************************************
  * @file    Task_Data_Remap.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   描述数据转化与映射的外部接口
  ******************************************************************************/
  
#ifndef _TASK_DATA_REMAP_H_
#define _TASK_DATA_REMAP_H_


/* Includes ------------------------------------------------------------------*/

#include "Common_Data_Area.h"



/* Interface declaration -----------------------------------------------------*/

/**
 * @brief  遥控数据转化与映射
 */
void  Remap_Remote_Channel(void);


/**
 * @brief 超声波数据转化
 */
void Remap_Sonic_Channel(void);

#endif

