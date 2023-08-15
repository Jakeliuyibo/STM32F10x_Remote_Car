/**
  ******************************************************************************
  * @file    init.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   描述小车功能初始化的外部接口
  ******************************************************************************/
  
#ifndef __INIT_H
#define __INIT_H



/* Includes ------------------------------------------------------------------*/

#include "Common_Data_Area.h"
#include "map_XDATA.h"
#include "bsp_motor.h"
#include "bsp_robotarm.h"
#include "bsp_ultrasonic.h"
#include "bsp_led.h"
#include "bsp_iwdg.h"
#include "bsp_oled.h"


/* Interface declaration -----------------------------------------------------*/



/**
 * @brief  初始化小车模块
 * @param  void
 * @return void
 */
void Car_System_Init(void);

#endif
