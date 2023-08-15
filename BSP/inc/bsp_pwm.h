/**
  ******************************************************************************
  * @file    bsp_pwm.h
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/24
  * @brief   描述了底层PWM的外部接口
  ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_PWM_H
#define __BSP_PWM_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "string.h"

/* Defitions -----------------------------------------------------------------*/

#define    PWM_ENABLE_DEFAULT                 ENABLE;                        /* 默认 PWM 使能                */
  
#define    PWM_TIM_PRESCALER_DEFAULT          0                              /* 默认 PWM TIM 时基 分频系数   */
#define    PWM_TIM_PERIOD_DEFAULT             9999                          /* 默认 PWM TIM 时基 预转载值   */

#define    PWM_TIM_OCMODE_DEFAULT             TIM_OCMode_PWM1                /* 默认 PWM TIM OC 输出模式     */
#define    PWM_TIM_OUTPUTSTATE_DEFAULT        TIM_OutputState_Enable         /* 默认 PWM TIM OC 比较输出状态 */
#define    PWM_TIM_OUTPUTNSTATE_DEFAULT       TIM_OutputNState_Disable       /* 默认 PWM TIM OC 互补输出状态 */
#define    PWM_TIM_PULSE_DEFAULT              (PWM_TIM_PERIOD_DEFAULT + 1)/2 /* 默认 PWM TIM OC 占空比       */
#define    PWM_TIM_OCPOLARITY_DEFAULT         TIM_OCPolarity_High            /* 默认 PWM TIM OC 输出比较极性 */
#define    PWM_TIM_OCNPOLARITY_DEFAULT        TIM_OCPolarity_High            /* 默认 PWM TIM OC 输出互补极性 */
#define    PWM_TIM_OCIDLESTATE_DEFAULT        TIM_OCIdleState_Reset          /* 默认 PWM TIM OC 空闲输出状态 */
#define    PWM_TIM_OCNIDLESTATE_DEFAULT       TIM_OCNIdleState_Reset         /* 默认 PWM TIM OC 空闲互补状态 */

         
#define    PWM_OUTPUT_AMP_MAX_LIMIT           0.95f                          /* PWM 最大输出限幅            */
#define    PWM_OUTPUT_AMP_MIN_LIMIT           0.05f                          /* PWM 最小输出限幅            */

    
/* typedef -------------------------------------------------------------------*/




/** 
  * @brief  定义 PWM 硬件结构体
  */
typedef struct __PWMHardware_Typedef_Struct
{
    TIM_TypeDef                  *TIMx;                         /* 定时器TIM              */
    uint16_t                      TIM_Channel;                  /* 定时器通道             */
    uint32_t                      TIM_Channel_Remap;            /* 定时器通道映射         */
  
    GPIO_TypeDef                 *PWM_GPIO;                     /* PWM 端口               */
    uint16_t                      PWM_GPIO_PIN;                 /* PWM 引脚               */ 
}PWMHardware_Typedef_Struct;



/** 
  * @brief  定义 PWM 寄存器结构体
  */
typedef struct __PWMRegister_Typedef_Struct
{
  
    FunctionalState               enable_PWM;                   /* PWM 使能               */
  
    TIM_TimeBaseInitTypeDef       TIM_TimeBaseInit;             /* PWM TIM时基            */
    TIM_OCInitTypeDef             TIM_OCInit;                   /* PWM TIM输出比较        */
  
    float                         pwm_duty;                     /* PWM 占空比             */

}PWMRegister_Typedef_Struct;



/** 
  * @brief  定义 PWM 结构体
  */
typedef struct __PWM_TypeDef_Struct
{
    PWMHardware_Typedef_Struct    PWM_Hardware;                 /* PWM 硬件结构体          */
    PWMRegister_Typedef_Struct    PWM_Operating;                /* PWM 配置结构体          */
}PWM_TypeDef_Struct;


/** 
  * @brief  定义 PWM 初始化寄存器结构体
  */
typedef struct __PWM_InitTypedef_Struct
{
    FunctionalState               enable_PWM;                   /* PWM 使能                */
  
    uint16_t                      PWM_TIM_Prescaler;            /* PWM TIM 时基 分频系数   */
    uint16_t                      PWM_TIM_Period;               /* PWM TIM 时基 预转载值   */
  
    uint16_t                      PWM_TIM_OCMode;               /* PWM TIM OC 输出模式     */
    uint16_t                      PWM_TIM_OutputState;          /* PWM TIM OC 比较输出状态 */
    uint16_t                      PWM_TIM_OutputNState;         /* PWM TIM OC 互补输出状态 */
    uint16_t                      PWM_TIM_Pulse;                /* PWM TIM OC 占空比       */
    uint16_t                      PWM_TIM_OCPolarity;           /* PWM TIM OC 输出比较极性 */
    uint16_t                      PWM_TIM_OCNPolarity;          /* PWM TIM OC 输出互补极性 */
    uint16_t                      PWM_TIM_OCIdleState;          /* PWM TIM OC 空闲输出状态 */
    uint16_t                      PWM_TIM_OCNIdleState;         /* PWM TIM OC 空闲互补状态 */
    
}PWM_InitTypedef_Struct;


/* MOTOR BASE ----------------------------------------------------------------*/

extern  PWM_TypeDef_Struct                   PWM1_BASE;
#define PWM1                                 (&PWM1_BASE         )   /* PWM1 selected          */
#define PWM1_TIMER                           (TIM3               )   /* PWM1 TIMER             */
#define PWM1_TIM_CHANNEL                     (1                  )   /* PWM1 TIM CHANNEL       */
#define PWM1_TIM_CHANNEL_REMAP               (NULL               )   /* PWM1 TIM CHANNEL REMAP */
#define PWM1_GPIO                            (GPIOA              )   /* PWM1 GPIO              */
#define PWM1_GPIO_PIN                        (GPIO_Pin_6         )   /* PWM1 GPIO PIN          */

extern  PWM_TypeDef_Struct                   PWM2_BASE;
#define PWM2                                 (&PWM2_BASE         )   /* PWM2 selected          */
#define PWM2_TIMER                           (TIM3               )   /* PWM2 TIMER             */
#define PWM2_TIM_CHANNEL                     (2                  )   /* PWM2 TIM CHANNEL       */
#define PWM2_TIM_CHANNEL_REMAP               (NULL               )   /* PWM2 TIM CHANNEL REMAP */
#define PWM2_GPIO                            (GPIOA              )   /* PWM2 GPIO              */
#define PWM2_GPIO_PIN                        (GPIO_Pin_7         )   /* PWM2 GPIO PIN          */

extern  PWM_TypeDef_Struct                   PWM3_BASE;
#define PWM3                                 (&PWM3_BASE         )   /* PWM3 selected          */
#define PWM3_TIMER                           (TIM3               )   /* PWM3 TIMER             */
#define PWM3_TIM_CHANNEL                     (3                  )   /* PWM3 TIM CHANNEL       */
#define PWM3_TIM_CHANNEL_REMAP               (NULL               )   /* PWM3 TIM CHANNEL REMAP */
#define PWM3_GPIO                            (GPIOB              )   /* PWM3 GPIO              */
#define PWM3_GPIO_PIN                        (GPIO_Pin_0         )   /* PWM3 GPIO PIN          */

extern  PWM_TypeDef_Struct                   PWM4_BASE;
#define PWM4                                 (&PWM4_BASE         )   /* PWM4 selected          */
#define PWM4_TIMER                           (TIM3               )   /* PWM4 TIMER             */
#define PWM4_TIM_CHANNEL                     (4                  )   /* PWM4 TIM CHANNEL       */
#define PWM4_TIM_CHANNEL_REMAP               (NULL               )   /* PWM4 TIM CHANNEL REMAP */
#define PWM4_GPIO                            (GPIOB              )   /* PWM4 GPIO              */
#define PWM4_GPIO_PIN                        (GPIO_Pin_1         )   /* PWM4 GPIO PIN          */


extern  PWM_TypeDef_Struct                   PWM5_BASE;
#define PWM5                                 (&PWM5_BASE         )   /* PWM5 selected          */
#define PWM5_TIMER                           (TIM1               )   /* PWM5 TIMER             */
#define PWM5_TIM_CHANNEL                     (1                  )   /* PWM5 TIM CHANNEL       */
#define PWM5_TIM_CHANNEL_REMAP               (GPIO_FullRemap_TIM1)   /* PWM5 TIM CHANNEL REMAP */
#define PWM5_GPIO                            (GPIOE              )   /* PWM5 GPIO              */
#define PWM5_GPIO_PIN                        (GPIO_Pin_9         )   /* PWM5 GPIO PIN          */

extern  PWM_TypeDef_Struct                   PWM6_BASE;
#define PWM6                                 (&PWM6_BASE         )   /* PWM6 selected          */
#define PWM6_TIMER                           (TIM1               )   /* PWM6 TIMER             */
#define PWM6_TIM_CHANNEL                     (2                  )   /* PWM6 TIM CHANNEL       */
#define PWM6_TIM_CHANNEL_REMAP               (GPIO_FullRemap_TIM1)   /* PWM6 TIM CHANNEL REMAP */
#define PWM6_GPIO                            (GPIOE              )   /* PWM6 GPIO              */
#define PWM6_GPIO_PIN                        (GPIO_Pin_11        )   /* PWM6 GPIO PIN          */

extern  PWM_TypeDef_Struct                   PWM7_BASE;
#define PWM7                                 (&PWM7_BASE         )   /* PWM7 selected          */
#define PWM7_TIMER                           (TIM1               )   /* PWM7 TIMER             */
#define PWM7_TIM_CHANNEL                     (3                  )   /* PWM7 TIM CHANNEL       */
#define PWM7_TIM_CHANNEL_REMAP               (GPIO_FullRemap_TIM1)   /* PWM7 TIM CHANNEL REMAP */
#define PWM7_GPIO                            (GPIOE              )   /* PWM7 GPIO              */
#define PWM7_GPIO_PIN                        (GPIO_Pin_13        )   /* PWM7 GPIO PIN          */

extern  PWM_TypeDef_Struct                   PWM8_BASE;
#define PWM8                                 (&PWM8_BASE         )   /* PWM8 selected          */
#define PWM8_TIMER                           (TIM1               )   /* PWM8 TIMER             */
#define PWM8_TIM_CHANNEL                     (4                  )   /* PWM8 TIM CHANNEL       */
#define PWM8_TIM_CHANNEL_REMAP               (GPIO_FullRemap_TIM1)   /* PWM8 TIM CHANNEL REMAP */
#define PWM8_GPIO                            (GPIOE              )   /* PWM8 GPIO              */
#define PWM8_GPIO_PIN                        (GPIO_Pin_14        )   /* PWM8 GPIO PIN          */


extern  PWM_TypeDef_Struct                   PWM9_BASE;
#define PWM9                                 (&PWM9_BASE         )   /* PWM9 selected          */
#define PWM9_TIMER                           (TIM4               )   /* PWM9 TIMER             */
#define PWM9_TIM_CHANNEL                     (1                  )   /* PWM9 TIM CHANNEL       */
#define PWM9_TIM_CHANNEL_REMAP               (GPIO_Remap_TIM4    )   /* PWM9 TIM CHANNEL REMAP */
#define PWM9_GPIO                            (GPIOD              )   /* PWM9 GPIO              */
#define PWM9_GPIO_PIN                        (GPIO_Pin_12        )   /* PWM9 GPIO PIN          */

extern  PWM_TypeDef_Struct                   PWM10_BASE;
#define PWM10                                (&PWM10_BASE        )   /* PWM10 selected          */
#define PWM10_TIMER                          (TIM4               )   /* PWM10 TIMER             */
#define PWM10_TIM_CHANNEL                    (2                  )   /* PWM10 TIM CHANNEL       */
#define PWM10_TIM_CHANNEL_REMAP              (GPIO_Remap_TIM4    )   /* PWM10 TIM CHANNEL REMAP */
#define PWM10_GPIO                           (GPIOD              )   /* PWM10 GPIO              */
#define PWM10_GPIO_PIN                       (GPIO_Pin_13        )   /* PWM10 GPIO PIN          */

extern  PWM_TypeDef_Struct                    PWM11_BASE;
#define PWM11                                (&PWM11_BASE        )   /* PWM11 selected          */
#define PWM11_TIMER                          (TIM4               )   /* PWM11 TIMER             */
#define PWM11_TIM_CHANNEL                    (3                  )   /* PWM11 TIM CHANNEL       */
#define PWM11_TIM_CHANNEL_REMAP              (GPIO_Remap_TIM4    )   /* PWM11 TIM CHANNEL REMAP */
#define PWM11_GPIO                           (GPIOD              )   /* PWM11 GPIO              */
#define PWM11_GPIO_PIN                       (GPIO_Pin_14        )   /* PWM11 GPIO PIN          */

extern  PWM_TypeDef_Struct                    PWM12_BASE;
#define PWM12                                (&PWM12_BASE        )   /* PWM12 selected          */
#define PWM12_TIMER                          (TIM4               )   /* PWM12 TIMER             */
#define PWM12_TIM_CHANNEL                    (4                  )   /* PWM12 TIM CHANNEL       */
#define PWM12_TIM_CHANNEL_REMAP              (GPIO_Remap_TIM4    )   /* PWM12 TIM CHANNEL REMAP */
#define PWM12_GPIO                           (GPIOD              )   /* PWM12 GPIO              */
#define PWM12_GPIO_PIN                       (GPIO_Pin_15        )   /* PWM12 GPIO PIN          */



/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  初始化 PWM 结构体默认配置
 * @param  PWM_InitStruct  : PWM 初始化结构体
 * @return void
 */
void BSP_PWM_InitStruct(PWM_InitTypedef_Struct *PWM_InitStruct);



/**
 * @brief  初始化 PWM 结构体
 * @param  *PWMx           : PWM 结构体
 *         *PWM_InitStruct : PWM 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_PWM_Init(PWM_TypeDef_Struct *PWMx , PWM_InitTypedef_Struct *PWM_InitStruct);



/**
 * @brief  使能 PWM 通道
 * @param  *PWMx           : PWM 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PWM_Open(PWM_TypeDef_Struct *PWMx);



/**
 * @brief  失能 PWM 通道
 * @param  *PWMx           : PWM 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PWM_Close(PWM_TypeDef_Struct *PWMx);



/**
 * @brief  设置 PWM 通道占空比
 * @param  *PWMx           : PWM 结构体
 * @param  duty            : 占空比，取值0-1
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PWM_Set_Duty(PWM_TypeDef_Struct *PWMx , float duty);


#endif






