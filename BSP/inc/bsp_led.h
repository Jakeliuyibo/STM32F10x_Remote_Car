/**
  ******************************************************************************
  * @file    bsp_led.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   描述了底层gpio通用的驱动外部接口
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_LED_H
#define __BSP_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"
#include "stm32f10x_tim.h"

/* Defitions -----------------------------------------------------------------*/

#define   LED_ENABLE_DEFAULT                  ENABLE                  /* 默认 LED 使能                */
#define   LED_POL_DEFAULT                     LED_OCPolarity_Low      /* 默认 LED 驱动电平            */       
#define   LED_DELAY_TIME                      1000                    /* 默认 LED 延时时间            */

#define   LED_TIM_PRESCALER_DEFAULT           (7200 - 1)             /* 默认 LED TIM 时基 分频系数   */
#define   LED_TIM_PERIOD_DEFAULT              (10000 - 1)            /* 默认 LED TIM 时基 预转载值   */

#define   LED_TIM_PREPRIORINTY_DEFAULT        0x00                    /* 默认 LED TIM 抢占优先级      */
#define   LED_TIM_SUBPRIORINTY_DEFAULT        0x00                    /* 默认 LED TIM 子优先级        */  



/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  定义LED初始极性枚举类型
  */	
typedef enum __LED_Polarity_ENUM
{
    LED_OCPolarity_High   =   1,          /* LED 高电平极性 */
    LED_OCPolarity_Low    =   0           /* LED 低电平极性 */
}LED_Polarity_ENUM;


/** 
  * @brief  定义LED硬件结构体
  */	
typedef struct __LEDHardware_Typedef_Struct
{
  
    GPIO_TypeDef                *LED_GPIO;                /* LED IO 端口        */
    uint8_t                      LED_PIN;                 /* LED IO 引脚        */
  
    TIM_TypeDef                 *TIMx;                    /* LED TIM            */
    uint16_t                     TIM_IRQn;                /* LED TIM 中断通道   */
  
}LEDHardware_Typedef_Struct;


/** 
  * @brief  定义LED寄存器结构体
  */	
typedef struct __LEDRegister_Typedef_Struct
{
  
    FunctionalState              enable;                  /* LED 使能           */
    LED_Polarity_ENUM            pol;                     /* LED 极性           */
    FlagStatus                   state;                   /* LED 状态           */
    uint16_t                     delay_time;              /* LED 延时时间       */
  
    TIM_TimeBaseInitTypeDef      TIM_TimeBaseInit;        /* LED TIM 时基       */
    uint8_t                      TIM_PrePriorinty;        /* LED TIM 抢占优先级 */
    uint8_t                      TIM_SubPriorinty;        /* LED TIM 子优先级   */
  
}LEDRegister_Typedef_Struct;


/** 
  * @brief  定义LED结构体
  */	
typedef struct __LED_TypeDef_Struct
{
    LEDHardware_Typedef_Struct       LED_Hardware;        /* LED硬件结构体 */
    LEDRegister_Typedef_Struct       LED_Operating;       /* LED配置结构体 */
}LED_TypeDef_Struct;

/** 
  * @brief  定义LED初始化结构体
  */	
typedef struct __LED_InitTypeDef_Struct
{
  
    FunctionalState              enable;                    /* LED 使能                */
    LED_Polarity_ENUM            pol;                       /* LED 极性                */
//    FlagStatus                   state;                     /* LED 状态                */
    uint16_t                     delay_time;                /* LED 延时时间       */
  
    uint16_t                     LED_TIM_Prescaler;         /* LED TIM 时基 分频系数   */
//    uint16_t                     LED_TIM_CounterMode;       /* LED TIM 时基 计数模式   */
    uint16_t                     LED_TIM_Period;            /* LED TIM 时基 预转载值   */
//    uint16_t                     LED_TIM_ClockDivision;     /* LED TIM 时基 时钟分割   */
//    uint8_t                      LED_TIM_RepetitionCounter; /* LED TIM 时基 重复计数   */
  
    uint8_t                      LED_TIM_PrePriorinty;      /* LED TIM 抢占优先级      */
    uint8_t                      LED_TIM_SubPriorinty;      /* LED TIM 子优先级        */
  
}LED_InitTypeDef_Struct;


/* LED BASE ------------------------------------------------------------------*/
extern  LED_TypeDef_Struct         LED1_BASE;    
#define LED1                      (&LED1_BASE)        /* LED1          */
#define LED1_GPIO                 (GPIOA)             /* LED1 端口     */
#define LED1_PIN                  (GPIO_Pin_2)        /* LED1 引脚     */
#define LED1_TIMER                (TIM7)              /* LED1 TIM      */
#define LED1_TIMER_IRQ            (TIM7_IRQn)         /* LED1 TIM 中断 */


extern  LED_TypeDef_Struct         LED2_BASE;        
#define LED2                      (&LED2_BASE)        /* LED2          */
#define LED2_GPIO                 (GPIOA)             /* LED2 端口     */
#define LED2_PIN                  (GPIO_Pin_3)        /* LED2 引脚     */
#define LED2_TIMER                (TIM6)              /* LED2 TIM      */
#define LED2_TIMER_IRQ            (TIM6_IRQn)         /* LED2 TIM 中断 */


extern  LED_TypeDef_Struct         LED3_BASE;         
#define LED3                      (&LED3_BASE)        /* LED3          */
#define LED3_GPIO                 (GPIOA)             /* LED3 端口     */
#define LED3_PIN                  (GPIO_Pin_4)        /* LED3 引脚     */
#define LED3_TIMER                (TIM7)              /* LED3 TIM      */
#define LED3_TIMER_IRQ            (TIM7_IRQn)         /* LED3 TIM 中断 */





/* Interface declaration -----------------------------------------------------*/

/**
 * @brief  初始化LED结构体默认配置
 * @param  LED_InitStruct : LED初始化结构体
 */
void BSP_LED_InitStruct(LED_InitTypeDef_Struct *LED_InitStruct);


/**
 * @brief  初始化LED结构体
 * @param  *LEDx            : LED结构体
 *         *LED_InitStruct  : LED初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_Init(LED_TypeDef_Struct *LEDx , LED_InitTypeDef_Struct *LED_InitStruct);


/**
 * @brief  根据默认的LED极性,点灯
 * @param  *LEDx           : LED结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Open(LED_TypeDef_Struct *LEDx);


/**
 * @brief  根据默认的LED极性,关灯
 * @param  *LEDx           : LED结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Close(LED_TypeDef_Struct *LEDx);


/**
 * @brief  设置 LED 电平翻转的周期
 * @param  *LEDx           : LED 结构体
 * @param  delay           : 设置 LED 翻转周期 1~1000ms
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Set_Duty(LED_TypeDef_Struct *LEDx , u16 delay);


/**
 * @brief  LEDx TIM 溢出中断服务函数
 * @param  *LEDx            : LED 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_TIM_OverFlow_IRQHandler(LED_TypeDef_Struct *LEDx);




#endif

