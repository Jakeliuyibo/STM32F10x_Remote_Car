/**
  ******************************************************************************
  * @file    bsp_idwg.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   描述了底层IDWG设备的驱动实现
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_iwdg.h"


/* Global variable -----------------------------------------------------------*/
IWDG_TypeDef_Struct                 IWDG1_BASE;


/* volatile variable ---------------------------------------------------------*/



/* Private functions declaration----------------------------------------------*/


/* Public functions ----------------------------------------------------------*/


/**
 * @brief  初始化IWDG结构体默认配置
 * @param  IWDG_InitStruct : IWDG初始化结构体
 */
void BSP_IWDG_InitStruct(IWDG_InitTypeDef_Struct *IWDG_InitStruct)
{
    IWDG_InitStruct->enable     = IWDG_ENABLE_DEFAULT;
    IWDG_InitStruct->prep       = IWDG_PREP_DEFAULT;
    IWDG_InitStruct->rlr        = IWDG_RLR_DEFAULT;
}


/**
 * @brief  初始化 IWDG 结构体
 * @param  *IWDGx            : IWDG 结构体
 *         *IWDG_InitStruct  : IWDG 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_IWDG_Init(IWDG_TypeDef_Struct *IWDGx , IWDG_InitTypeDef_Struct *IWDG_InitStruct)
{
    if (IWDG_InitStruct == NULL)
    {
        return ERROR;
    }
    
    IWDGx->enable  = IWDG_InitStruct->enable;
    IWDGx->prep    = IWDG_InitStruct->prep;
    IWDGx->rlr     = IWDG_InitStruct->rlr;
    
    /* 使能对IWDG_PR IWDG_RLR 写操作 */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 
	
    /* 设置预分频系数 */
    IWDG_SetPrescaler(IWDGx->prep); 
	
    /* 设置重装载值   */
    IWDG_SetReload(IWDGx->rlr); 
    
    /* 重转载计数器   */
    IWDG_ReloadCounter(); 
	
    /* 使能IWDG       */
    IWDG_Enable(); 
    
   
    return SUCCESS;
}


/**
 * @brief  喂狗 IWDG
 * @param  void
 * @return void
 */
void BSP_IWDG_Feed(void)
{

    IWDG_ReloadCounter(); 
    
}

/* Private functions ---------------------------------------------------------*/











