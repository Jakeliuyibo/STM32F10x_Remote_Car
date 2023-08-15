/**
  ******************************************************************************
  * @file    algorithm_PID.c
  * @author  LYB
  * @version V1.0.0
  * @date    2021/3/29
  * @brief   描述PID功能模块
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "algorithm_PID.h"


/* Global variable -----------------------------------------------------------*/

/* Private functions declaration----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  初始化PID结构体默认配置
 * @param  *PIDx           : PID 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
void Algorithm_PID_InitStruct(PIDControl_InitTypedef_Struct *PID_InitStruct)
{

    PID_InitStruct->Kp            = PID_CONTROL_KP_DEFAULT;                  /* PID 比例系数 */
    PID_InitStruct->Ki            = PID_CONTROL_KI_DEFAULT;                  /* PID 积分系数 */
    PID_InitStruct->Kd            = PID_CONTROL_KD_DEFAULT;                  /* PID 微分系数 */
    PID_InitStruct->Output_limit  = PID_CONTROL_OUTPUT_LIMIT_DEFAULT;        /* PID 输出限幅 */

}



/**
 * @brief  初始化PID结构体
 * @param  *PIDx           : PID 变量结构体
 * @param  *PID_InitStruct : PID 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Algorithm_PID_Init(PIDControl_Typedef_Struct *PID , PIDControl_InitTypedef_Struct *PID_InitStruct)
{
    if ( (PID == NULL) || (PID_InitStruct == NULL))
    {
        return ERROR;
    }
  
    PID->Kp                       = PID_InitStruct->Kp;
    PID->Ki                       = PID_InitStruct->Ki;
    PID->Kd                       = PID_InitStruct->Kd;    
    PID->Output_limit             = PID_InitStruct->Output_limit;
    
    PID->Ek                       = 0;
    PID->Ek1                      = 0;   
    PID->Ek2                      = 0;    
    PID->Inc                      = 0;     
    
  
    return SUCCESS;
}



/**
 * @brief  PID 控制环
 * @param  *PIDx           : PID 变量结构体
 * @param  SetVal          : 设置速度
 * @param  ActualVal       : 实际速度
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PID_Adjustable_Ring(PIDControl_Typedef_Struct *PID , float SetVal , float ActualVal)
{
    if ( (PID == ERROR) || (SetVal < 0) || (SetVal > 1) ||  (ActualVal < 0) ||  (ActualVal > 1) )
    {
        return ERROR;
    }
    
    PID->Ek = SetVal - ActualVal;
    
//    PID->Inc =   PID->Ek  * (PID->Kp + PID->Ki + PID->Kd) 
//                - PID->Ek1 * (PID->Kp + 2 * PID->Kd) 
//                + PID->Ek2 * PID->Kd;
    PID->Inc =    PID->Ek  * PID->Kp 
                - PID->Ek1 * PID->Ki
                + PID->Ek2 * PID->Kd;   
    
    PID->Ek2 = PID->Ek1;
    PID->Ek1 = PID->Ek;
    
    
    /* PID环 输出限幅 */
    if ( (SetVal + PID->Inc) > PID->Output_limit )
    {
        PID->Inc = PID->Output_limit - SetVal;
    }
  
    return SUCCESS;
}













