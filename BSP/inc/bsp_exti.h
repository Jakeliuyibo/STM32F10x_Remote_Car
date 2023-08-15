/**
  ******************************************************************************
  * @file    bsp_exti.h
  * @author  LYB
  * @version V1.0.3
  * @date    202/5/28
  * @brief   �����˵ײ�EXTI�ⲿ�жϵ��ⲿ�ӿ�
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "string.h"



/* Defitions -----------------------------------------------------------------*/

#define      EXTI_ENABLE_DEFAULT            ENABLE                       /* Ĭ�� EXTI ʹ��         */
#define      EXTI_LINECMD_DEFAULT           ENABLE                       /* Ĭ�� EXTI �¼���ʹ��   */
  
#define      EXTI_MODE_DEFAULT              EXTI_Mode_Interrupt;         /* Ĭ�� EXTI �ж�ģʽ     */
#define      EXTI_TRIGGER_DEFAULT           EXTI_Trigger_Rising_Falling; /* Ĭ�� EXTI �жϴ�����ʽ */
    
#define      EXTI_PREPRIORINTY_DEFAULT      0x02                         /* Ĭ�� EXTI ��ռ���ȼ�   */
#define      EXTI_SUBPRIORINTY_DEFAULT      0x03                         /* Ĭ�� EXTI �����ȼ�     */




/* typedef -------------------------------------------------------------------*/


/** 
  * @brief  ���� EXTI Ӳ���ṹ��
  */
typedef struct __EXTIHardware_Typedef_Struct
{
    uint32_t                           EXTI_Line;                /* EXTI �¼���      */    
    uint8_t                            EXIT_NVIC_IRQn;           /* EXTI �ж�Դ      */    
  
    GPIO_TypeDef                      *EXTI_GPIO;                /* EXTI GPIO �˿�   */
    uint16_t                           EXTI_GPIO_PIN;            /* EXTI GPIO ����   */
      
    uint8_t                            EXTI_PortSource;          /* EXTI �˿�Դ      */
    uint8_t                            EXTI_PinSource;           /* EXTI ����Դ      */
  
}EXTIHardware_Typedef_Struct;


/** 
  * @brief  ���� EXTI �Ĵ����ṹ��
  */
typedef struct __EXTIRegister_Typedef_Struct
{
    FunctionalState                    enable_EXTI;              /* EXTI ʹ��         */
    FunctionalState                    EXTI_LineCmd;             /* EXTI �ж�Դʹ��   */
  
    FlagStatus                         risingFlag;               /* EXTI �����ر�־λ */
    FlagStatus                         fallingFlag;              /* EXTI �½��ر�־λ */
  
    EXTIMode_TypeDef                   EXTI_Mode;                /* EXTI �ж�ģʽ     */
    EXTITrigger_TypeDef                EXTI_Trigger;             /* EXTI �жϴ�����ʽ */
    
    uint8_t                            EXTI_PrePriorinty;        /* EXTI ��ռ���ȼ�   */
    uint8_t                            EXTI_SubPriorinty;        /* EXTI �����ȼ�     */

}EXTIRegister_Typedef_Struct;


/** 
  * @brief  ���� EXTI �ṹ��
  */
typedef struct __EXTI_TypeDef_Struct
{
    EXTIHardware_Typedef_Struct        EXTI_Hardware;            /* EXTIӲ���ṹ��    */
    EXTIRegister_Typedef_Struct        EXTI_Operating;           /* EXTI���ýṹ��    */
}EXTI_TypeDef_Struct;





/** 
  * @brief  ���� EXTI ��ʼ���Ĵ����ṹ��
  */
typedef struct __EXTI_InitTypedef_Struct
{
    FunctionalState                   enable_EXTI;               /* EXTI ʹ��         */
    FunctionalState                   EXTI_LineCmd;              /* EXTI �¼���ʹ��   */
  
    EXTIMode_TypeDef                  EXTI_Mode;                 /* EXTI �ж�ģʽ     */
    EXTITrigger_TypeDef               EXTI_Trigger;              /* EXTI �жϴ�����ʽ */
    
    uint8_t                           EXTI_PrePriorinty;         /* EXTI ��ռ���ȼ�   */
    uint8_t                           EXTI_SubPriorinty;         /* EXTI �����ȼ�     */
  
}EXTI_InitTypedef_Struct;





/* EXTI BASE -----------------------------------------------------------------*/
 
extern  EXTI_TypeDef_Struct             EXTI1_BASE;
#define EXTI1                          (&EXTI1_BASE)            /* EXTI1 select    */
#define EXTI1_LINE                     (EXTI_Line0)             /* EXTI1 �¼���    */
#define EXTI1_NVIC_IRQn                (EXTI0_IRQn)             /* EXTI1 �ж�Դ    */
#define EXTI1_GPIO                     (GPIOA)                  /* EXTI1 GPIO �˿� */
#define EXTI1_GPIO_PIN                 (GPIO_Pin_0)             /* EXTI1 GPIO ���� */
#define EXTI1_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI1 �˿�Դ    */
#define EXTI1_Pin_Source               (GPIO_PinSource0)        /* EXTI1 ����Դ    */


extern  EXTI_TypeDef_Struct             EXTI2_BASE;
#define EXTI2                          (&EXTI2_BASE)            /* EXTI2 select    */
#define EXTI2_LINE                     (EXTI_Line1)             /* EXTI2 �¼���    */
#define EXTI2_NVIC_IRQn                (EXTI1_IRQn)             /* EXTI2 �ж�Դ    */
#define EXTI2_GPIO                     (GPIOA)                  /* EXTI2 GPIO �˿� */
#define EXTI2_GPIO_PIN                 (GPIO_Pin_1)             /* EXTI2 GPIO ���� */
#define EXTI2_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI2 �˿�Դ    */
#define EXTI2_Pin_Source               (GPIO_PinSource1)        /* EXTI2 ����Դ    */


extern  EXTI_TypeDef_Struct             EXTI3_BASE;
#define EXTI3                          (&EXTI3_BASE)            /* EXTI3 select    */
#define EXTI3_LINE                     (EXTI_Line2)             /* EXTI3 �¼���    */
#define EXTI3_NVIC_IRQn                (EXTI2_IRQn)             /* EXTI3 �ж�Դ    */
#define EXTI3_GPIO                     (GPIOA)                  /* EXTI3 GPIO �˿� */
#define EXTI3_GPIO_PIN                 (GPIO_Pin_2)             /* EXTI3 GPIO ���� */
#define EXTI3_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI3 �˿�Դ    */
#define EXTI3_Pin_Source               (GPIO_PinSource2)        /* EXTI3 ����Դ    */

extern  EXTI_TypeDef_Struct             EXTI4_BASE;
#define EXTI4                          (&EXTI4_BASE)            /* EXTI4 select    */
#define EXTI4_LINE                     (EXTI_Line3)             /* EXTI4 �¼���    */
#define EXTI4_NVIC_IRQn                (EXTI3_IRQn)             /* EXTI4 �ж�Դ    */
#define EXTI4_GPIO                     (GPIOA)                  /* EXTI4 GPIO �˿� */
#define EXTI4_GPIO_PIN                 (GPIO_Pin_3)             /* EXTI4 GPIO ���� */
#define EXTI4_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI4 �˿�Դ    */
#define EXTI4_Pin_Source               (GPIO_PinSource3)        /* EXTI4 ����Դ    */

extern  EXTI_TypeDef_Struct             EXTI5_BASE;
#define EXTI5                          (&EXTI5_BASE)            /* EXTI5 select    */
#define EXTI5_LINE                     (EXTI_Line4)             /* EXTI5 �¼���    */
#define EXTI5_NVIC_IRQn                (EXTI4_IRQn)             /* EXTI5 �ж�Դ    */
#define EXTI5_GPIO                     (GPIOA)                  /* EXTI5 GPIO �˿� */
#define EXTI5_GPIO_PIN                 (GPIO_Pin_4)             /* EXTI5 GPIO ���� */
#define EXTI5_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI5 �˿�Դ    */
#define EXTI5_Pin_Source               (GPIO_PinSource4)        /* EXTI5 ����Դ    */

extern  EXTI_TypeDef_Struct             EXTI6_BASE;
#define EXTI6                          (&EXTI6_BASE)            /* EXTI6 select    */
#define EXTI6_LINE                     (EXTI_Line5)             /* EXTI6 �¼���    */
#define EXTI6_NVIC_IRQn                (EXTI9_5_IRQn)           /* EXTI6 �ж�Դ    */
#define EXTI6_GPIO                     (GPIOA)                  /* EXTI6 GPIO �˿� */
#define EXTI6_GPIO_PIN                 (GPIO_Pin_5)             /* EXTI6 GPIO ���� */
#define EXTI6_Port_Source              (GPIO_PortSourceGPIOA)   /* EXTI6 �˿�Դ    */
#define EXTI6_Pin_Source               (GPIO_PinSource5)        /* EXTI6 ����Դ    */

/* Interface declaration -----------------------------------------------------*/




/**
 * @brief  ��ʼ��EXTI�ṹ��Ĭ������
 * @param  EXTI_InitStruct : EXTI��ʼ���ṹ��
 */
void BSP_EXTI_InitStruct(EXTI_InitTypedef_Struct *EXTI_InitStruct);


/**
 * @brief  ��ʼ��EXTI�ṹ��
 * @param  *EXTIx            : EXTI�ṹ��
 *         *EXTI_InitStruct  : EXTI��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_Init(EXTI_TypeDef_Struct *EXTIx , EXTI_InitTypedef_Struct *EXTI_InitStruct);


/**
 * @brief  �� EXTI ͨ��
 * @param  *EXTIx            : EXTI�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus EXTI_Open(EXTI_TypeDef_Struct *EXTIx);


/**
 * @brief  �ر� EXTI ͨ��
 * @param  *EXTIx            : EXTI�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus EXTI_Close(EXTI_TypeDef_Struct *EXTIx);


/**
 * @brief  EXTI �жϷ�����
 * @param  *EXTIx            : EXTI�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_IRQHandler(EXTI_TypeDef_Struct *EXTIx);


#endif







