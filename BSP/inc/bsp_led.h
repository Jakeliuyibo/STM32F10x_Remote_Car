/**
  ******************************************************************************
  * @file    bsp_led.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   �����˵ײ�gpioͨ�õ������ⲿ�ӿ�
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_LED_H
#define __BSP_LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"
#include "stm32f10x_tim.h"

/* Defitions -----------------------------------------------------------------*/

#define   LED_ENABLE_DEFAULT                  ENABLE                  /* Ĭ�� LED ʹ��                */
#define   LED_POL_DEFAULT                     LED_OCPolarity_Low      /* Ĭ�� LED ������ƽ            */       
#define   LED_DELAY_TIME                      1000                    /* Ĭ�� LED ��ʱʱ��            */

#define   LED_TIM_PRESCALER_DEFAULT           (7200 - 1)             /* Ĭ�� LED TIM ʱ�� ��Ƶϵ��   */
#define   LED_TIM_PERIOD_DEFAULT              (10000 - 1)            /* Ĭ�� LED TIM ʱ�� Ԥת��ֵ   */

#define   LED_TIM_PREPRIORINTY_DEFAULT        0x00                    /* Ĭ�� LED TIM ��ռ���ȼ�      */
#define   LED_TIM_SUBPRIORINTY_DEFAULT        0x00                    /* Ĭ�� LED TIM �����ȼ�        */  



/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  ����LED��ʼ����ö������
  */	
typedef enum __LED_Polarity_ENUM
{
    LED_OCPolarity_High   =   1,          /* LED �ߵ�ƽ���� */
    LED_OCPolarity_Low    =   0           /* LED �͵�ƽ���� */
}LED_Polarity_ENUM;


/** 
  * @brief  ����LEDӲ���ṹ��
  */	
typedef struct __LEDHardware_Typedef_Struct
{
  
    GPIO_TypeDef                *LED_GPIO;                /* LED IO �˿�        */
    uint8_t                      LED_PIN;                 /* LED IO ����        */
  
    TIM_TypeDef                 *TIMx;                    /* LED TIM            */
    uint16_t                     TIM_IRQn;                /* LED TIM �ж�ͨ��   */
  
}LEDHardware_Typedef_Struct;


/** 
  * @brief  ����LED�Ĵ����ṹ��
  */	
typedef struct __LEDRegister_Typedef_Struct
{
  
    FunctionalState              enable;                  /* LED ʹ��           */
    LED_Polarity_ENUM            pol;                     /* LED ����           */
    FlagStatus                   state;                   /* LED ״̬           */
    uint16_t                     delay_time;              /* LED ��ʱʱ��       */
  
    TIM_TimeBaseInitTypeDef      TIM_TimeBaseInit;        /* LED TIM ʱ��       */
    uint8_t                      TIM_PrePriorinty;        /* LED TIM ��ռ���ȼ� */
    uint8_t                      TIM_SubPriorinty;        /* LED TIM �����ȼ�   */
  
}LEDRegister_Typedef_Struct;


/** 
  * @brief  ����LED�ṹ��
  */	
typedef struct __LED_TypeDef_Struct
{
    LEDHardware_Typedef_Struct       LED_Hardware;        /* LEDӲ���ṹ�� */
    LEDRegister_Typedef_Struct       LED_Operating;       /* LED���ýṹ�� */
}LED_TypeDef_Struct;

/** 
  * @brief  ����LED��ʼ���ṹ��
  */	
typedef struct __LED_InitTypeDef_Struct
{
  
    FunctionalState              enable;                    /* LED ʹ��                */
    LED_Polarity_ENUM            pol;                       /* LED ����                */
//    FlagStatus                   state;                     /* LED ״̬                */
    uint16_t                     delay_time;                /* LED ��ʱʱ��       */
  
    uint16_t                     LED_TIM_Prescaler;         /* LED TIM ʱ�� ��Ƶϵ��   */
//    uint16_t                     LED_TIM_CounterMode;       /* LED TIM ʱ�� ����ģʽ   */
    uint16_t                     LED_TIM_Period;            /* LED TIM ʱ�� Ԥת��ֵ   */
//    uint16_t                     LED_TIM_ClockDivision;     /* LED TIM ʱ�� ʱ�ӷָ�   */
//    uint8_t                      LED_TIM_RepetitionCounter; /* LED TIM ʱ�� �ظ�����   */
  
    uint8_t                      LED_TIM_PrePriorinty;      /* LED TIM ��ռ���ȼ�      */
    uint8_t                      LED_TIM_SubPriorinty;      /* LED TIM �����ȼ�        */
  
}LED_InitTypeDef_Struct;


/* LED BASE ------------------------------------------------------------------*/
extern  LED_TypeDef_Struct         LED1_BASE;    
#define LED1                      (&LED1_BASE)        /* LED1          */
#define LED1_GPIO                 (GPIOA)             /* LED1 �˿�     */
#define LED1_PIN                  (GPIO_Pin_2)        /* LED1 ����     */
#define LED1_TIMER                (TIM7)              /* LED1 TIM      */
#define LED1_TIMER_IRQ            (TIM7_IRQn)         /* LED1 TIM �ж� */


extern  LED_TypeDef_Struct         LED2_BASE;        
#define LED2                      (&LED2_BASE)        /* LED2          */
#define LED2_GPIO                 (GPIOA)             /* LED2 �˿�     */
#define LED2_PIN                  (GPIO_Pin_3)        /* LED2 ����     */
#define LED2_TIMER                (TIM6)              /* LED2 TIM      */
#define LED2_TIMER_IRQ            (TIM6_IRQn)         /* LED2 TIM �ж� */


extern  LED_TypeDef_Struct         LED3_BASE;         
#define LED3                      (&LED3_BASE)        /* LED3          */
#define LED3_GPIO                 (GPIOA)             /* LED3 �˿�     */
#define LED3_PIN                  (GPIO_Pin_4)        /* LED3 ����     */
#define LED3_TIMER                (TIM7)              /* LED3 TIM      */
#define LED3_TIMER_IRQ            (TIM7_IRQn)         /* LED3 TIM �ж� */





/* Interface declaration -----------------------------------------------------*/

/**
 * @brief  ��ʼ��LED�ṹ��Ĭ������
 * @param  LED_InitStruct : LED��ʼ���ṹ��
 */
void BSP_LED_InitStruct(LED_InitTypeDef_Struct *LED_InitStruct);


/**
 * @brief  ��ʼ��LED�ṹ��
 * @param  *LEDx            : LED�ṹ��
 *         *LED_InitStruct  : LED��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_Init(LED_TypeDef_Struct *LEDx , LED_InitTypeDef_Struct *LED_InitStruct);


/**
 * @brief  ����Ĭ�ϵ�LED����,���
 * @param  *LEDx           : LED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Open(LED_TypeDef_Struct *LEDx);


/**
 * @brief  ����Ĭ�ϵ�LED����,�ص�
 * @param  *LEDx           : LED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Close(LED_TypeDef_Struct *LEDx);


/**
 * @brief  ���� LED ��ƽ��ת������
 * @param  *LEDx           : LED �ṹ��
 * @param  delay           : ���� LED ��ת���� 1~1000ms
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Set_Duty(LED_TypeDef_Struct *LEDx , u16 delay);


/**
 * @brief  LEDx TIM ����жϷ�����
 * @param  *LEDx            : LED �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_TIM_OverFlow_IRQHandler(LED_TypeDef_Struct *LEDx);




#endif

