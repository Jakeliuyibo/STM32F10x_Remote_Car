/**
  ******************************************************************************
  * @file    Task_Data_output.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   描述数据输出通道的外部接口
  ******************************************************************************/
  
#ifndef _TASK_DATA_OUTPUT_H_
#define _TASK_DATA_OUTPUT_H_



/* Includes ------------------------------------------------------------------*/
#include "Common_Data_Area.h"
#include "bsp_motor.h"
#include "bsp_robotarm.h"
#include "bsp_oled.h"
#include "bsp_led.h"


/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  输出电机驱动和机械臂通道
 */
void Output_Drive_Channel(void);



/**
 * @brief  输出OLED显示数据通道
 */
void Output_OLED_Channel(void);


/**
 * @brief  输出LED通道
 */
void Output_LED_Channel(void);
  


#endif

/* ©2020 HZNU. All rights reserved. */
