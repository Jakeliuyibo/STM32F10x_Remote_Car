/**
  ******************************************************************************
  * @file    Task_Data_input.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   描述数据输入级的外部接口
  ******************************************************************************/
  
  
#ifndef _TASK_DATA_INPUT_H_
#define _TASK_DATA_INPUT_H_   


/* Includes ------------------------------------------------------------------*/

#include "Common_Data_Area.h"
#include "bsp_ultrasonic.h"


/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  输入遥控数据通道
 */
void Input_Remote_Channel(void);



/**
 * @brief  输入超声波数据通道
 */
void Input_Sonic_Channel(void);
  


/**
 * @brief  输入超声波使能
 */
void Input_Sonic_Start(void);

#endif
