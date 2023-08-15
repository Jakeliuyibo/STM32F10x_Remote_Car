/**
  ******************************************************************************
  * @file    bsp_idwg.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   描述了底层gpio通用的驱动外部接口
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_IDWG_H
#define __BSP_IDWG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"
#include "stm32f10x_iwdg.h"

/* Defitions -----------------------------------------------------------------*/
#define           IWDG_ENABLE_DEFAULT           ENABLE          /* 默认 IWDG 使能配置   */
#define           IWDG_PREP_DEFAULT             4               /* 默认 IWDG 预分频系数 */
#define           IWDG_RLR_DEFAULT              625             /* 默认 IWDG 重装载值   */


/* typedef -------------------------------------------------------------------*/





/** 
  * @brief  定义 IWDG 结构体  Tout=((4 * 2^prer) * rlr) / 40 (ms).
  */	
typedef struct __IWDG_TypeDef_Struct
{
  
    FunctionalState              enable;                  /* IWDG 使能              */
    uint8_t                      prep;                    /* IWDG 预分频系数 0~7    */
    uint16_t                     rlr;                     /* IWDG 重装载值   0~2047 */
  
}IWDG_TypeDef_Struct;


/** 
  * @brief  定义 IWDG 初始化结构体 Tout=((4 * 2^prer) * rlr) / 40 (ms).
  */	
typedef struct __IWDG_InitTypeDef_Struct
{
  
    FunctionalState              enable;                  /* IWDG 使能              */
    uint8_t                      prep;                    /* IWDG 预分频系数 0~7    */
    uint16_t                     rlr;                     /* IWDG 重装载值   0~2047 */
  
}IWDG_InitTypeDef_Struct;


/* IWDG BASE -----------------------------------------------------------------*/

extern  IWDG_TypeDef_Struct         IWDG1_BASE;    
#define IWDG1                       (&IWDG1_BASE)         /* IWDG1               */




/* Interface declaration -----------------------------------------------------*/

/**
 * @brief  初始化IWDG结构体默认配置
 * @param  IWDG_InitStruct : IWDG初始化结构体
 */
void BSP_IWDG_InitStruct(IWDG_InitTypeDef_Struct *IWDG_InitStruct);


/**
 * @brief  初始化 IWDG 结构体
 * @param  *IWDGx            : IWDG 结构体
 *         *IWDG_InitStruct  : IWDG 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_IWDG_Init(IWDG_TypeDef_Struct *IWDGx , IWDG_InitTypeDef_Struct *IWDG_InitStruct);


/**
 * @brief  喂狗 IWDG
 * @param  void
 * @return void
 */
void BSP_IWDG_Feed(void);




#endif

