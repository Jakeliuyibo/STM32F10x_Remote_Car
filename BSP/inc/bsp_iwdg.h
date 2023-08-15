/**
  ******************************************************************************
  * @file    bsp_idwg.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   �����˵ײ�gpioͨ�õ������ⲿ�ӿ�
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_IDWG_H
#define __BSP_IDWG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"
#include "stm32f10x_iwdg.h"

/* Defitions -----------------------------------------------------------------*/
#define           IWDG_ENABLE_DEFAULT           ENABLE          /* Ĭ�� IWDG ʹ������   */
#define           IWDG_PREP_DEFAULT             4               /* Ĭ�� IWDG Ԥ��Ƶϵ�� */
#define           IWDG_RLR_DEFAULT              625             /* Ĭ�� IWDG ��װ��ֵ   */


/* typedef -------------------------------------------------------------------*/





/** 
  * @brief  ���� IWDG �ṹ��  Tout=((4 * 2^prer) * rlr) / 40 (ms).
  */	
typedef struct __IWDG_TypeDef_Struct
{
  
    FunctionalState              enable;                  /* IWDG ʹ��              */
    uint8_t                      prep;                    /* IWDG Ԥ��Ƶϵ�� 0~7    */
    uint16_t                     rlr;                     /* IWDG ��װ��ֵ   0~2047 */
  
}IWDG_TypeDef_Struct;


/** 
  * @brief  ���� IWDG ��ʼ���ṹ�� Tout=((4 * 2^prer) * rlr) / 40 (ms).
  */	
typedef struct __IWDG_InitTypeDef_Struct
{
  
    FunctionalState              enable;                  /* IWDG ʹ��              */
    uint8_t                      prep;                    /* IWDG Ԥ��Ƶϵ�� 0~7    */
    uint16_t                     rlr;                     /* IWDG ��װ��ֵ   0~2047 */
  
}IWDG_InitTypeDef_Struct;


/* IWDG BASE -----------------------------------------------------------------*/

extern  IWDG_TypeDef_Struct         IWDG1_BASE;    
#define IWDG1                       (&IWDG1_BASE)         /* IWDG1               */




/* Interface declaration -----------------------------------------------------*/

/**
 * @brief  ��ʼ��IWDG�ṹ��Ĭ������
 * @param  IWDG_InitStruct : IWDG��ʼ���ṹ��
 */
void BSP_IWDG_InitStruct(IWDG_InitTypeDef_Struct *IWDG_InitStruct);


/**
 * @brief  ��ʼ�� IWDG �ṹ��
 * @param  *IWDGx            : IWDG �ṹ��
 *         *IWDG_InitStruct  : IWDG ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_IWDG_Init(IWDG_TypeDef_Struct *IWDGx , IWDG_InitTypeDef_Struct *IWDG_InitStruct);


/**
 * @brief  ι�� IWDG
 * @param  void
 * @return void
 */
void BSP_IWDG_Feed(void);




#endif

