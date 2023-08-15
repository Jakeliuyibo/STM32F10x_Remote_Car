/**
  ******************************************************************************
  * @file    bsp_ultrasonic.h
  * @author  LYB
  * @version V1.0.3
  * @date    202/6/6
  * @brief   描述了底层超声波测距模块的外部接口
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_ULTRASONIC_H
#define __BSP_ULTRASONIC_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "bsp_exti.h"
#include "string.h"
#include "time.h"


/* Defitions -----------------------------------------------------------------*/

#define       ENABLE_SONIC_DEFAULT                  ENABLE                      /* 默认 SONIC 使能                */
#define       ENABLE_EXTI_DEFAULT                   ENABLE                      /* 默认 SONIC EXTI 使能           */
  
#define       SONIC_EXTI_PREPRIORINTY_DEFAULT       0x01                       /* 默认 SONIC EXTI 抢占优先级     */
#define       SONIC_EXTI_SUBPRIORINTY_DEFAULT       0x01                       /* 默认 SONIC EXTI 子优先级       */
  
#define       SONIC_TIM_PRESCALER_DEFAULT           (72 - 1)                   /* 默认 SONIC TIM 时基 分频系数   */
#define       SONIC_TIM_PERIOD_DEFAULT              (1000 - 1)                 /* 默认 SONIC TIM 时基 预转载值   */

#define       SONIC_TIM_PREPRIORINTY_DEFAULT        0x00                       /* 默认 SONIC TIM 抢占优先级      */
#define       SONIC_TIM_SUBPRIORINTY_DEFAULT        0x00                       /* 默认 SONIC TIM 子优先级        */



/* typedef -------------------------------------------------------------------*/


/** 
  * @brief  定义 ULTRASONIC 硬件结构体
  */
typedef struct __SONICHardware_Typedef_Struct
{
    EXTI_TypeDef_Struct          *EXTIx;                     /* SONIC EXTI 外部中断    */
  
    TIM_TypeDef                  *TIMx;                      /* SONIC TIM  定时器      */
    uint16_t                      TIM_IRQn;                  /* SONIC TIM  中断通道    */
  
    GPIO_TypeDef                 *SONIC_TRIG_GPIO;           /* SONIC TRIG GPIO 端口   */
    uint16_t                      SONIC_TRIG_PIN;            /* SONIC TRIG GPIO 引脚   */
  
}SONICHardware_Typedef_Struct;


/** 
  * @brief  定义 ULTRASONIC 寄存器结构体
  */
typedef struct __SONICRegister_Typedef_Struct
{
    FunctionalState               enable_SONIC;              /* SONIC 使能               */
  
    EXTI_InitTypedef_Struct       EXTI_InitStruct;           /* SONIC EXTI 初始化        */
 
    TIM_TimeBaseInitTypeDef       TIM_TimeBaseInit;          /* SONIC TIM 时基           */ 
    uint8_t                       TIM_PrePriorinty;          /* SONIC TIM 抢占优先级     */
    uint8_t                       TIM_SubPriorinty;          /* SONIC TIM 子优先级       */
  
    uint16_t                      overFlow;                  /* SONIC TIM 溢出次数       */
    uint16_t                      time;                      /* SONIC 高电平持续时间     */
  
    FlagStatus                    updateFlag;                /* SONIC 高电平更新标志位   */
    FlagStatus                    startFlag;                 /* SONIC 触发标志位         */
 
}SONICRegister_Typedef_Struct;


/** 
  * @brief  定义 ULTRASONIC 结构体
  */
typedef struct __SONIC_TypeDef_Struct
{
    SONICHardware_Typedef_Struct        SONIC_Hardware;      /* SONIC 硬件结构体 */
    SONICRegister_Typedef_Struct        SONIC_Operating;     /* SONIC 配置结构体 */
}SONIC_TypeDef_Struct;





/** 
  * @brief  定义 ULTRASONIC 初始化寄存器结构体
  */
typedef struct __SONIC_InitTypedef_Struct
{
    FunctionalState       enable_SONIC;                      /* SONIC 使能                */
    FunctionalState       enable_EXTI;                       /* SONIC EXTI 使能           */

    uint8_t               SONIC_EXTI_PrePriorinty;           /* SONIC EXTI 抢占优先级     */
    uint8_t               SONIC_EXTI_SubPriorinty;           /* SONIC EXTI 子优先级       */
  
    uint16_t              SONIC_TIM_Prescaler;               /* SONIC TIM 时基 分频系数   */
    uint16_t              SONIC_TIM_Period;                  /* SONIC TIM 时基 预转载值   */
  
    uint8_t               SONIC_TIM_PrePriorinty;            /* SONIC TIM 抢占优先级      */
    uint8_t               SONIC_TIM_SubPriorinty;            /* SONIC TIM 子优先级        */
  
}SONIC_InitTypedef_Struct;




/* ULTRASONIC BASE -----------------------------------------------------------------*/

extern SONIC_TypeDef_Struct                   SONIC1_BASE;
#define SONIC1                               (&SONIC1_BASE)           /* SONIC1 select         */
#define SONIC1_EXTI                          (EXTI1)                  /* SONIC1 EXTI  外部中断 */
#define SONIC1_TIMER                         (TIM5)                   /* SONIC1 TIMER 定时器   */
#define SONIC1_TIMER_IRQ                     (TIM5_IRQn)              /* SONIC1 TIMER 中断     */
#define SONIC1_TRIG_GPIO                     (GPIOA)                  /* SONIC1 TRIG GPIO 端口 */
#define SONIC1_TRIG_GPIO_PIN                 (GPIO_Pin_1)             /* SONIC1 TRIG GPIO 引脚 */


extern SONIC_TypeDef_Struct                   SONIC2_BASE;
#define SONIC2                               (&SONIC2_BASE)           /* SONIC2 select         */
#define SONIC2_EXTI                          (EXTI2)                  /* SONIC2 EXTI  外部中断 */
#define SONIC2_TIMER                         (TIM6)                   /* SONIC2 TIMER 定时器   */
#define SONIC2_TIMER_IRQ                     (TIM6_IRQn)              /* SONIC2 TIMER 中断     */
#define SONIC2_TRIG_GPIO                     (GPIOA)                  /* SONIC2 TRIG GPIO 端口 */
#define SONIC2_TRIG_GPIO_PIN                 (GPIO_Pin_1)             /* SONIC2 TRIG GPIO 引脚 */


/* Interface declaration -----------------------------------------------------*/




/**
 * @brief  初始化 SONIC_InitStruct 结构体默认配置
 * @param  SONIC_InitStruct : SONIC 初始化结构体
 * @return void
 */
void BSP_SONIC_InitStruct(SONIC_InitTypedef_Struct *SONIC_InitStruct);


/**
 * @brief  初始化 SONICx 结构体
 * @param  *SONICx            : SONIC 结构体
 *         *SONIC_InitStruct  : SONIC 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_Init(SONIC_TypeDef_Struct *SONICx , SONIC_InitTypedef_Struct *SONIC_InitStruct);


/**
 * @brief  打开 SONICx 通道
 * @param  *SONICx            : SONIC 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Open(SONIC_TypeDef_Struct *SONICx);


/**
 * @brief  关闭 SONICx 通道
 * @param  *SONICx            : SONIC 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Close(SONIC_TypeDef_Struct *SONICx);


/**
 * @brief  开启 SONICx 通道测量
 * @param  *SONICx            : SONIC 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Start(SONIC_TypeDef_Struct *SONICx);


/**
 * @brief  SONICx 中断服务函数
 * @param  *SONICx            : SONIC 结构体
 * @param  *EXTIx             : EXTIx 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_EXTI_IRQHandler(SONIC_TypeDef_Struct *SONICx);



/**
 * @brief  SONICx TIM 溢出中断服务函数
 * @param  *SONICx            : SONIC 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_TIM_OverFlow_IRQHandler(SONIC_TypeDef_Struct *SONICx);




#endif







