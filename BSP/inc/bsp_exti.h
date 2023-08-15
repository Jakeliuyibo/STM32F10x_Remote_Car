/**
  ******************************************************************************
  * @file    bsp_exti.h
  * @author  LYB
  * @version V1.0.3
  * @date    202/5/28
  * @brief   描述了底层EXTI外部中断的外部接口
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "string.h"



/* Defitions -----------------------------------------------------------------*/

#define      EXTI_ENABLE_DEFAULT            ENABLE                       /* 默认 EXTI 使能         */
#define      EXTI_LINECMD_DEFAULT           ENABLE                       /* 默认 EXTI 事件线使能   */
  
#define      EXTI_MODE_DEFAULT              EXTI_Mode_Interrupt;         /* 默认 EXTI 中断模式     */
#define      EXTI_TRIGGER_DEFAULT           EXTI_Trigger_Rising_Falling; /* 默认 EXTI 中断触发方式 */
    
#define      EXTI_PREPRIORINTY_DEFAULT      0x02                         /* 默认 EXTI 抢占优先级   */
#define      EXTI_SUBPRIORINTY_DEFAULT      0x03                         /* 默认 EXTI 子优先级     */




/* typedef -------------------------------------------------------------------*/


/** 
  * @brief  定义 EXTI 硬件结构体
  */
typedef struct __EXTIHardware_Typedef_Struct
{
    uint32_t                           EXTI_Line;                /* EXTI 事件线      */    
    uint8_t                            EXIT_NVIC_IRQn;           /* EXTI 中断源      */    
  
    GPIO_TypeDef                      *EXTI_GPIO;                /* EXTI GPIO 端口   */
    uint16_t                           EXTI_GPIO_PIN;            /* EXTI GPIO 引脚   */
      
    uint8_t                            EXTI_PortSource;          /* EXTI 端口源      */
    uint8_t                            EXTI_PinSource;           /* EXTI 引脚源      */
  
}EXTIHardware_Typedef_Struct;


/** 
  * @brief  定义 EXTI 寄存器结构体
  */
typedef struct __EXTIRegister_Typedef_Struct
{
    FunctionalState                    enable_EXTI;              /* EXTI 使能         */
    FunctionalState                    EXTI_LineCmd;             /* EXTI 中断源使能   */
  
    FlagStatus                         risingFlag;               /* EXTI 上升沿标志位 */
    FlagStatus                         fallingFlag;              /* EXTI 下降沿标志位 */
  
    EXTIMode_TypeDef                   EXTI_Mode;                /* EXTI 中断模式     */
    EXTITrigger_TypeDef                EXTI_Trigger;             /* EXTI 中断触发方式 */
    
    uint8_t                            EXTI_PrePriorinty;        /* EXTI 抢占优先级   */
    uint8_t                            EXTI_SubPriorinty;        /* EXTI 子优先级     */

}EXTIRegister_Typedef_Struct;


/** 
  * @brief  定义 EXTI 结构体
  */
typedef struct __EXTI_TypeDef_Struct
{
    EXTIHardware_Typedef_Struct        EXTI_Hardware;            /* EXTI硬件结构体    */
    EXTIRegister_Typedef_Struct        EXTI_Operating;           /* EXTI配置结构体    */
}EXTI_TypeDef_Struct;





/** 
  * @brief  定义 EXTI 初始化寄存器结构体
  */
typedef struct __EXTI_InitTypedef_Struct
{
    FunctionalState                   enable_EXTI;               /* EXTI 使能         */
    FunctionalState                   EXTI_LineCmd;              /* EXTI 事件线使能   */
  
    EXTIMode_TypeDef                  EXTI_Mode;                 /* EXTI 中断模式     */
    EXTITrigger_TypeDef               EXTI_Trigger;              /* EXTI 中断触发方式 */
    
    uint8_t                           EXTI_PrePriorinty;         /* EXTI 抢占优先级   */
    uint8_t                           EXTI_SubPriorinty;         /* EXTI 子优先级     */
  
}EXTI_InitTypedef_Struct;





/* EXTI BASE -----------------------------------------------------------------*/
 
extern  EXTI_TypeDef_Struct             EXTI1_BASE;
#define EXTI1                          (&EXTI1_BASE)            /* EXTI1 select    */
#define EXTI1_LINE                     (EXTI_Line0)             /* EXTI1 事件线    */
#define EXTI1_NVIC_IRQn                (EXTI0_IRQn)             /* EXTI1 中断源    */
#define EXTI1_GPIO                     (GPIOA)                  /* EXTI1 GPIO 端口 */
#define EXTI1_GPIO_PIN                 (GPIO_Pin_0)             /* EXTI1 GPIO 引脚 */
#define EXTI1_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI1 端口源    */
#define EXTI1_Pin_Source               (GPIO_PinSource0)        /* EXTI1 引脚源    */


extern  EXTI_TypeDef_Struct             EXTI2_BASE;
#define EXTI2                          (&EXTI2_BASE)            /* EXTI2 select    */
#define EXTI2_LINE                     (EXTI_Line1)             /* EXTI2 事件线    */
#define EXTI2_NVIC_IRQn                (EXTI1_IRQn)             /* EXTI2 中断源    */
#define EXTI2_GPIO                     (GPIOA)                  /* EXTI2 GPIO 端口 */
#define EXTI2_GPIO_PIN                 (GPIO_Pin_1)             /* EXTI2 GPIO 引脚 */
#define EXTI2_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI2 端口源    */
#define EXTI2_Pin_Source               (GPIO_PinSource1)        /* EXTI2 引脚源    */


extern  EXTI_TypeDef_Struct             EXTI3_BASE;
#define EXTI3                          (&EXTI3_BASE)            /* EXTI3 select    */
#define EXTI3_LINE                     (EXTI_Line2)             /* EXTI3 事件线    */
#define EXTI3_NVIC_IRQn                (EXTI2_IRQn)             /* EXTI3 中断源    */
#define EXTI3_GPIO                     (GPIOA)                  /* EXTI3 GPIO 端口 */
#define EXTI3_GPIO_PIN                 (GPIO_Pin_2)             /* EXTI3 GPIO 引脚 */
#define EXTI3_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI3 端口源    */
#define EXTI3_Pin_Source               (GPIO_PinSource2)        /* EXTI3 引脚源    */

extern  EXTI_TypeDef_Struct             EXTI4_BASE;
#define EXTI4                          (&EXTI4_BASE)            /* EXTI4 select    */
#define EXTI4_LINE                     (EXTI_Line3)             /* EXTI4 事件线    */
#define EXTI4_NVIC_IRQn                (EXTI3_IRQn)             /* EXTI4 中断源    */
#define EXTI4_GPIO                     (GPIOA)                  /* EXTI4 GPIO 端口 */
#define EXTI4_GPIO_PIN                 (GPIO_Pin_3)             /* EXTI4 GPIO 引脚 */
#define EXTI4_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI4 端口源    */
#define EXTI4_Pin_Source               (GPIO_PinSource3)        /* EXTI4 引脚源    */

extern  EXTI_TypeDef_Struct             EXTI5_BASE;
#define EXTI5                          (&EXTI5_BASE)            /* EXTI5 select    */
#define EXTI5_LINE                     (EXTI_Line4)             /* EXTI5 事件线    */
#define EXTI5_NVIC_IRQn                (EXTI4_IRQn)             /* EXTI5 中断源    */
#define EXTI5_GPIO                     (GPIOA)                  /* EXTI5 GPIO 端口 */
#define EXTI5_GPIO_PIN                 (GPIO_Pin_4)             /* EXTI5 GPIO 引脚 */
#define EXTI5_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI5 端口源    */
#define EXTI5_Pin_Source               (GPIO_PinSource4)        /* EXTI5 引脚源    */

extern  EXTI_TypeDef_Struct             EXTI6_BASE;
#define EXTI6                          (&EXTI6_BASE)            /* EXTI6 select    */
#define EXTI6_LINE                     (EXTI_Line5)             /* EXTI6 事件线    */
#define EXTI6_NVIC_IRQn                (EXTI9_5_IRQn)           /* EXTI6 中断源    */
#define EXTI6_GPIO                     (GPIOA)                  /* EXTI6 GPIO 端口 */
#define EXTI6_GPIO_PIN                 (GPIO_Pin_5)             /* EXTI6 GPIO 引脚 */
#define EXTI6_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI6 端口源    */
#define EXTI6_Pin_Source               (GPIO_PinSource5)        /* EXTI6 引脚源    */

/* Interface declaration -----------------------------------------------------*/




/**
 * @brief  初始化EXTI结构体默认配置
 * @param  EXTI_InitStruct : EXTI初始化结构体
 */
void BSP_EXTI_InitStruct(EXTI_InitTypedef_Struct *EXTI_InitStruct);


/**
 * @brief  初始化EXTI结构体
 * @param  *EXTIx            : EXTI结构体
 *         *EXTI_InitStruct  : EXTI初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_Init(EXTI_TypeDef_Struct *EXTIx , EXTI_InitTypedef_Struct *EXTI_InitStruct);


/**
 * @brief  打开 EXTI 通道
 * @param  *EXTIx            : EXTI结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus EXTI_Open(EXTI_TypeDef_Struct *EXTIx);


/**
 * @brief  关闭 EXTI 通道
 * @param  *EXTIx            : EXTI结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus EXTI_Close(EXTI_TypeDef_Struct *EXTIx);


/**
 * @brief  EXTI 中断服务函数
 * @param  *EXTIx            : EXTI结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_IRQHandler(EXTI_TypeDef_Struct *EXTIx);


#endif







