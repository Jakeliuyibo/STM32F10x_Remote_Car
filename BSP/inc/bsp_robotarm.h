/**
  ******************************************************************************
  * @file    bsp_robotarm.h
  * @author  LYB
  * @version V1.0.1
  * @date    2021/4/06
  * @brief   �����˵ײ��е�۵��ⲿ�ӿ�
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_ROBOTARM_H
#define __BSP_ROBOTARM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_scom.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "time.h"

/* Defitions -----------------------------------------------------------------*/

#define   ARM_ENABLE_DEFAULT                ENABLE                         /* Ĭ�� ARM ʹ��       */
#define   ARM_ENABLE_DMA_DEFAULT            ENABLE                         /* Ĭ�� ARM DMAʹ��    */

#define   ARM_BAUDRATE_DEFAULT              115200                        /* Ĭ�ϴ��ڲ�����      */
#define   ARM_PARITY_DEFAULT                USART_Parity_No                /* Ĭ�ϴ���У��λ      */
#define   ARM_WORDLENGTH_DEFAULT            USART_WordLength_8b            /* Ĭ�ϴ����ֳ�        */
#define   ARM_STOPBITS_DEFAULT              USART_StopBits_1               /* Ĭ�ϴ���ֹͣλ      */
#define   ARM_HARDWARE_FLOWCONTROL_DEFAULT  USART_HardwareFlowControl_None /* Ĭ�ϴ���Ӳ��������  */

#define   ARM_SCOMPREPRIORINTY_DEFAULT      3                              /* Ĭ��SCOM��ռ���ȼ�  */
#define   ARM_SCOMSUBPRIORINTY_DEFAULT      3                              /* Ĭ��SCOM�����ȼ�    */
#define   ARM_DMAPREPRIORINTY_DEFAULT       3                              /* Ĭ��DMA��ռ���ȼ�   */
#define   ARM_DMASUBPRIORINTY_DEFAULT       3                              /* Ĭ��DMA�����ȼ�     */

#define   ARM_OUTPUT_MAX_LIMIT              2500                           /* ARM ��������Ƕ�  */
#define   ARM_OUTPUT_MIN_LIMIT              500                            /* ARM �������С�Ƕ�  */


/* typedef -------------------------------------------------------------------*/


typedef  SCOM_WRITE_DATA_Struct             ARM_WRITE_DATA_Struct;         /* ARM д�����ݽṹ�� */


/** 
  * @brief  ���� ARM Ӳ���ṹ��
  */	
typedef struct __ARMHardware_Typedef_Struct
{
    SCOM_TypeDef_Struct                    *SCOM;                          /* SCOM               */
  
}ARMHardware_Typedef_Struct;


/** 
  * @brief  ���� ARM �Ĵ����ṹ��
  */	
typedef struct __ARMRegister_Typedef_Struct
{
    FunctionalState                         enable_ARM;                    /* ARM ʹ��              */
    
    uint16_t                                Channel_data[6];               /* ARM 6��ͨ���Ļ���     */
    ARM_WRITE_DATA_Struct                   Tx_data;                       /* ARM TX ��������       */
  
    SCOM_InitTypedef_Struct                 SCOM_InitStruct;               /* ARM SCOM ����         */ 

}ARMRegister_Typedef_Struct;


/** 
  * @brief  ���� ARM �ṹ��
  */	
typedef struct __ARM_TypeDef_Struct
{
    ARMHardware_Typedef_Struct              ARM_Hardware;                  /* ARM Ӳ���ṹ��        */
    ARMRegister_Typedef_Struct              ARM_Operating;                 /* ARM ���ýṹ��        */
}ARM_TypeDef_Struct;

/** 
  * @brief  ���� ARM ��ʼ���ṹ��
  */	
typedef struct __ARM_InitTypeDef_Struct
{
    FunctionalState                         enable_ARM;                    /* ARM ʹ��              */
    FunctionalState                         enable_DMA;                    /* ARM SCOM DMA  ʹ��    */
  
    uint32_t                                ARM_SCOM_BaudRate; 	           /* ARM SCOM ������       */
    uint16_t                                ARM_SCOM_Parity;               /* ARM SCOM ����У��λ   */
    uint16_t                                ARM_SCOM_WordLength;	         /* ARM SCOM �����ֳ�     */
	  uint16_t                                ARM_SCOM_StopBits;             /* ARM SCOM ����ֹͣλ   */
    uint16_t                                ARM_SCOM_HardwareFlowControl;  /* ARM SCOM Ӳ��������   */
  
    uint8_t                                 ARM_SCOM_PrePriorinty;         /* ARM SCOM��ռ���ȼ�    */
    uint8_t                                 ARM_SCOM_SubPriorinty;         /* ARM SCOM�����ȼ�      */
    uint8_t                                 ARM_DMA_PrePriorinty;          /* ARM DMA��ռ���ȼ�     */
    uint8_t                                 ARM_DMA_SubPriorinty;          /* ARM DMA�����ȼ�       */

}ARM_InitTypeDef_Struct;


/* ARM BASE ------------------------------------------------------------------*/

extern ARM_TypeDef_Struct                   ARM1_BASE;
#define ARM1                                (&ARM1_BASE)                   /* ARM1 selected */
#define ARM1_SCOM                           (SCOM1      )                  /* ARM1 SCOM     */


extern ARM_TypeDef_Struct                   ARM2_BASE;
#define ARM2                                (&ARM2_BASE)                   /* ARM1 selected */
#define ARM2_SCOM                           (SCOM2      )                  /* ARM1 SCOM     */

/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  ��ʼ��ARM�ṹ��Ĭ������
 * @param  ARM_InitStruct  : ARM��ʼ���ṹ��
 * @return void
 */
void BSP_ARM_InitStruct(ARM_InitTypeDef_Struct *ARM_InitStruct);


/**
 * @brief  ��ʼ��LORA�ṹ��
 * @param  *ARMx           : ARMx�ṹ��
 *         *ARM_InitStruct : ARM��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Init(ARM_TypeDef_Struct *ARMx , ARM_InitTypeDef_Struct *ARM_InitStruct);

/**
 * @brief  ʹ��ARM
 * @param  *ARMx           : ARM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Open(ARM_TypeDef_Struct *ARMx);


/**
 * @brief  ʧ��ARM
 * @param  *ARMx           : ARM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Close(ARM_TypeDef_Struct *ARMx);


/**
 * @brief  ARM ��е������
 * @param  *ARMx           : ARM�ṹ��
 * @param  channel         : ������ͨ��
 * @param  data            : ����������
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Drive(ARM_TypeDef_Struct *ARMx , uint8_t channel, float data);

#endif

