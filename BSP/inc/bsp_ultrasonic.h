/**
  ******************************************************************************
  * @file    bsp_ultrasonic.h
  * @author  LYB
  * @version V1.0.3
  * @date    202/6/6
  * @brief   �����˵ײ㳬�������ģ����ⲿ�ӿ�
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

#define       ENABLE_SONIC_DEFAULT                  ENABLE                      /* Ĭ�� SONIC ʹ��                */
#define       ENABLE_EXTI_DEFAULT                   ENABLE                      /* Ĭ�� SONIC EXTI ʹ��           */
  
#define       SONIC_EXTI_PREPRIORINTY_DEFAULT       0x01                       /* Ĭ�� SONIC EXTI ��ռ���ȼ�     */
#define       SONIC_EXTI_SUBPRIORINTY_DEFAULT       0x01                       /* Ĭ�� SONIC EXTI �����ȼ�       */
  
#define       SONIC_TIM_PRESCALER_DEFAULT           (72 - 1)                   /* Ĭ�� SONIC TIM ʱ�� ��Ƶϵ��   */
#define       SONIC_TIM_PERIOD_DEFAULT              (1000 - 1)                 /* Ĭ�� SONIC TIM ʱ�� Ԥת��ֵ   */

#define       SONIC_TIM_PREPRIORINTY_DEFAULT        0x00                       /* Ĭ�� SONIC TIM ��ռ���ȼ�      */
#define       SONIC_TIM_SUBPRIORINTY_DEFAULT        0x00                       /* Ĭ�� SONIC TIM �����ȼ�        */



/* typedef -------------------------------------------------------------------*/


/** 
  * @brief  ���� ULTRASONIC Ӳ���ṹ��
  */
typedef struct __SONICHardware_Typedef_Struct
{
    EXTI_TypeDef_Struct          *EXTIx;                     /* SONIC EXTI �ⲿ�ж�    */
  
    TIM_TypeDef                  *TIMx;                      /* SONIC TIM  ��ʱ��      */
    uint16_t                      TIM_IRQn;                  /* SONIC TIM  �ж�ͨ��    */
  
    GPIO_TypeDef                 *SONIC_TRIG_GPIO;           /* SONIC TRIG GPIO �˿�   */
    uint16_t                      SONIC_TRIG_PIN;            /* SONIC TRIG GPIO ����   */
  
}SONICHardware_Typedef_Struct;


/** 
  * @brief  ���� ULTRASONIC �Ĵ����ṹ��
  */
typedef struct __SONICRegister_Typedef_Struct
{
    FunctionalState               enable_SONIC;              /* SONIC ʹ��               */
  
    EXTI_InitTypedef_Struct       EXTI_InitStruct;           /* SONIC EXTI ��ʼ��        */
 
    TIM_TimeBaseInitTypeDef       TIM_TimeBaseInit;          /* SONIC TIM ʱ��           */ 
    uint8_t                       TIM_PrePriorinty;          /* SONIC TIM ��ռ���ȼ�     */
    uint8_t                       TIM_SubPriorinty;          /* SONIC TIM �����ȼ�       */
  
    uint16_t                      overFlow;                  /* SONIC TIM �������       */
    uint16_t                      time;                      /* SONIC �ߵ�ƽ����ʱ��     */
  
    FlagStatus                    updateFlag;                /* SONIC �ߵ�ƽ���±�־λ   */
    FlagStatus                    startFlag;                 /* SONIC ������־λ         */
 
}SONICRegister_Typedef_Struct;


/** 
  * @brief  ���� ULTRASONIC �ṹ��
  */
typedef struct __SONIC_TypeDef_Struct
{
    SONICHardware_Typedef_Struct        SONIC_Hardware;      /* SONIC Ӳ���ṹ�� */
    SONICRegister_Typedef_Struct        SONIC_Operating;     /* SONIC ���ýṹ�� */
}SONIC_TypeDef_Struct;





/** 
  * @brief  ���� ULTRASONIC ��ʼ���Ĵ����ṹ��
  */
typedef struct __SONIC_InitTypedef_Struct
{
    FunctionalState       enable_SONIC;                      /* SONIC ʹ��                */
    FunctionalState       enable_EXTI;                       /* SONIC EXTI ʹ��           */

    uint8_t               SONIC_EXTI_PrePriorinty;           /* SONIC EXTI ��ռ���ȼ�     */
    uint8_t               SONIC_EXTI_SubPriorinty;           /* SONIC EXTI �����ȼ�       */
  
    uint16_t              SONIC_TIM_Prescaler;               /* SONIC TIM ʱ�� ��Ƶϵ��   */
    uint16_t              SONIC_TIM_Period;                  /* SONIC TIM ʱ�� Ԥת��ֵ   */
  
    uint8_t               SONIC_TIM_PrePriorinty;            /* SONIC TIM ��ռ���ȼ�      */
    uint8_t               SONIC_TIM_SubPriorinty;            /* SONIC TIM �����ȼ�        */
  
}SONIC_InitTypedef_Struct;




/* ULTRASONIC BASE -----------------------------------------------------------------*/

extern SONIC_TypeDef_Struct                   SONIC1_BASE;
#define SONIC1                               (&SONIC1_BASE)           /* SONIC1 select         */
#define SONIC1_EXTI                          (EXTI1)                  /* SONIC1 EXTI  �ⲿ�ж� */
#define SONIC1_TIMER                         (TIM5)                   /* SONIC1 TIMER ��ʱ��   */
#define SONIC1_TIMER_IRQ                     (TIM5_IRQn)              /* SONIC1 TIMER �ж�     */
#define SONIC1_TRIG_GPIO                     (GPIOA)                  /* SONIC1 TRIG GPIO �˿� */
#define SONIC1_TRIG_GPIO_PIN                 (GPIO_Pin_1)             /* SONIC1 TRIG GPIO ���� */


extern SONIC_TypeDef_Struct                   SONIC2_BASE;
#define SONIC2                               (&SONIC2_BASE)           /* SONIC2 select         */
#define SONIC2_EXTI                          (EXTI2)                  /* SONIC2 EXTI  �ⲿ�ж� */
#define SONIC2_TIMER                         (TIM6)                   /* SONIC2 TIMER ��ʱ��   */
#define SONIC2_TIMER_IRQ                     (TIM6_IRQn)              /* SONIC2 TIMER �ж�     */
#define SONIC2_TRIG_GPIO                     (GPIOA)                  /* SONIC2 TRIG GPIO �˿� */
#define SONIC2_TRIG_GPIO_PIN                 (GPIO_Pin_1)             /* SONIC2 TRIG GPIO ���� */


/* Interface declaration -----------------------------------------------------*/




/**
 * @brief  ��ʼ�� SONIC_InitStruct �ṹ��Ĭ������
 * @param  SONIC_InitStruct : SONIC ��ʼ���ṹ��
 * @return void
 */
void BSP_SONIC_InitStruct(SONIC_InitTypedef_Struct *SONIC_InitStruct);


/**
 * @brief  ��ʼ�� SONICx �ṹ��
 * @param  *SONICx            : SONIC �ṹ��
 *         *SONIC_InitStruct  : SONIC ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_Init(SONIC_TypeDef_Struct *SONICx , SONIC_InitTypedef_Struct *SONIC_InitStruct);


/**
 * @brief  �� SONICx ͨ��
 * @param  *SONICx            : SONIC �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Open(SONIC_TypeDef_Struct *SONICx);


/**
 * @brief  �ر� SONICx ͨ��
 * @param  *SONICx            : SONIC �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Close(SONIC_TypeDef_Struct *SONICx);


/**
 * @brief  ���� SONICx ͨ������
 * @param  *SONICx            : SONIC �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Start(SONIC_TypeDef_Struct *SONICx);


/**
 * @brief  SONICx �жϷ�����
 * @param  *SONICx            : SONIC �ṹ��
 * @param  *EXTIx             : EXTIx �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_EXTI_IRQHandler(SONIC_TypeDef_Struct *SONICx);



/**
 * @brief  SONICx TIM ����жϷ�����
 * @param  *SONICx            : SONIC �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_TIM_OverFlow_IRQHandler(SONIC_TypeDef_Struct *SONICx);




#endif







