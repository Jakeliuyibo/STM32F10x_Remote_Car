/**
  ******************************************************************************
  * @file    algorithm_PID.h
  * @author  LYB
  * @version V1.0.0
  * @date    2021/3/29
  * @brief   描述PID功能模块的外部调用
  ******************************************************************************/
  
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __ALGORITHM_PID_H
#define __ALGORITHM_PID_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"


/* Defitions -----------------------------------------------------------------*/
  
#define             PID_CONTROL_KP_DEFAULT                 0.7              /* PID 默认比例系数 */
#define             PID_CONTROL_KI_DEFAULT                 0.1              /* PID 默认积分系数 */
#define             PID_CONTROL_KD_DEFAULT                 0.2              /* PID 默认微分系数 */
#define             PID_CONTROL_OUTPUT_LIMIT_DEFAULT       0.9              /* PID 默认输出限幅 */


/* Typedef -------------------------------------------------------------------*/


/**
  * @brief  定义PID控制结构体
  */
typedef struct  __PIDControl_InitTypedef_Struct
{
  
    float           Kp;               /*  PID 比例系数  */
    float           Ki;               /*  PID 积分系数  */
    float           Kd;               /*  PID 微分系数  */
    float           Output_limit;     /*  PID 输出限幅  */
  
}PIDControl_InitTypedef_Struct;


/**
  * @brief  定义PID控制结构体
  */
typedef struct  __PIDControl_Typedef_Struct
{
  
    float           Kp;               /*  PID 比例系数  */
    float           Ki;               /*  PID 积分系数  */
    float           Kd;               /*  PID 微分系数  */
    float           Ek;               /*  PID 差值      */
    float           Ek1;              /*  PID 前差值    */
    float           Ek2;              /*  PID 前前差值  */
    float           Inc;              /*  PID 计算增量  */
    float           Output_limit;     /*  PID 输出限幅  */
  
}PIDControl_Typedef_Struct;



/* PID BASE ------------------------------------------------------------------*/




/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  初始化PID结构体默认配置
 * @param  *PID_InitStruct : PID 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
void Algorithm_PID_InitStruct(PIDControl_InitTypedef_Struct *PID_InitStruct);



/**
 * @brief  初始化PID结构体
 * @param  *PID            : PID 变量结构体
 * @param  *PID_InitStruct : PID 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Algorithm_PID_Init(PIDControl_Typedef_Struct *PID , PIDControl_InitTypedef_Struct *PID_InitStruct);



/**
 * @brief  PID 控制环
 * @param  *PID            : PID 变量结构体
 * @param  SetVal          : 设置速度
 * @param  ActualVal       : 实际速度
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PID_Adjustable_Ring(PIDControl_Typedef_Struct *PID , float SetVal , float ActualVal);












#endif

