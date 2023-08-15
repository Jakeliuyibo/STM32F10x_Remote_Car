/**
  ******************************************************************************
  * @file    bsp_lora.h
  * @author  LYB
  * @version V1.0.2
  * @date    202/4/3
  * @brief   �����˵ײ�loraͨ�õ������ⲿ�ӿ�
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_LORA_H
#define __BSP_LORA_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_scom.h"
#include "string.h"

/* Defitions -----------------------------------------------------------------*/

#define   LORA_ENABLE_DEFAULT                ENABLE                        /* Ĭ��LORA ʹ��       */
#define   LORA_ENABLE_DMA_DEFAULT            ENABLE                        /* Ĭ��LORA DMAʹ��    */

#define   LORA_TRANSMODE_DEFAULT             LORA_Transparent_Trans        /* Ĭ��LORA����ģʽ    */     
#define   LORA_USARTMODE_DEFAULT             LORA_Usart_Mode_RX            /* Ĭ��LORA����ģʽ    */

#define   LORA_SCOMPREPRIORINTY_DEFAULT      3                             /* Ĭ��SCOM��ռ���ȼ�  */
#define   LORA_SCOMSUBPRIORINTY_DEFAULT      3                             /* Ĭ��SCOM�����ȼ�    */
#define   LORA_DMAPREPRIORINTY_DEFAULT       0                             /* Ĭ��DMA��ռ���ȼ�   */
#define   LORA_DMASUBPRIORINTY_DEFAULT       0                             /* Ĭ��DMA�����ȼ�     */

#define   LORA_TX_CALLBACKFUN_DEFAULT        NULL                          /* Ĭ��LORA TX�ص����� */
#define   LORA_RX_CALLBACKFUN_DEFAULT        NULL                          /* Ĭ��LORA RX�ص����� */

#define   LORA_ADDRESS_DEFAULT               0X1234                       /* Ĭ��LORA��ַ       */
#define   LORA_COMCHANNEL_DEFAULT	           0X17                          /* Ĭ��LORA����ͨ��   */

#define   LORA_BAUDRATE_DEFAULT              115200                        /* Ĭ�ϴ��ڲ�����  */
#define   LORA_PARITY_DEFAULT                USART_Parity_No                /* Ĭ�ϴ���У��λ  */
#define   LORA_WORDLENGTH_DEFAULT            USART_WordLength_8b            /* Ĭ�ϴ����ֳ�    */
#define   LORA_STOPBITS_DEFAULT              USART_StopBits_1               /* Ĭ�ϴ���ֹͣλ  */
#define   LORA_HARDWARE_FLOWCONTROL_DEFAULT  USART_HardwareFlowControl_None /* Ĭ�ϴ���Ӳ�������� */

/* typedef -------------------------------------------------------------------*/

typedef SCOM_READ_DATA_Struct     LORA_READ_DATA_Struct ;    /* LORA��ȡ���ݽṹ�� */
typedef SCOM_WRITE_DATA_Struct    LORA_WRITE_DATA_Struct;    /* LORAд�����ݽṹ�� */


/** 
  * @brief  LORA�ص���������
  */
typedef void (*LORA_Callback_Function)();


/**  
  * @brief  ���� LORA ����ģʽö������
  */	
typedef enum __LORA_TransMode_ENUM
{
    LORA_Transparent_Trans    =     0,                  /* LORA͸������ */
    LORA_Fixed_Transfer       =     1                   /* LORA���㴫�� */
//    LORA_Radio_Listening      =     2,                /* LORA�㲥���� */
//    LORA_Air_Wakeup           =     3,                /* LORA���л��� */
//    LORA_Low_Power            =     4                 /* LORA�͹���   */ 
}LORA_TransMode_ENUM;


/** 
  * @brief  ���� LORA ����ģʽö������
  */	
typedef enum __LORA_UsartMode_ENUM
{
    LORA_Usart_Mode_RX    =   USART_Mode_Rx,            /* LORA���ڽ���ģʽ */
    LORA_Usart_Mode_TX    =   USART_Mode_Tx,            /* LORA���ڷ���ģʽ */
}LORA_UsartMode_ENUM;


/** 
  * @brief  ���� LORA Ӳ���ṹ��
  */
typedef struct __LORAHardware_Typedef_Struct
{
    SCOM_TypeDef_Struct        *SCOMx;                   /* SCOM         */

    GPIO_TypeDef               *MD0_GPIO;                /* MD0�˿�      */
    uint16_t                    MD0_GPIO_PIN;            /* MD0����      */
    GPIO_TypeDef               *MD1_GPIO;                /* MD1�˿�      */
    uint16_t                    MD1_GPIO_PIN;            /* MD1����      */
    GPIO_TypeDef               *AUX_GPIO;                /* AUX�˿�      */
    uint16_t                    AUX_GPIO_PIN;            /* AUX����      */
  
}LORAHardware_Typedef_Struct;


/** 
  * @brief  ����LORA�Ĵ����ṹ��
  */
typedef struct __LORARegister_Typedef_Struct
{
    FunctionalState             enable_LORA;             /* LORA ʹ��      */
  
    LORA_READ_DATA_Struct       LoraRxdata;              /* LORA RX ����   */
    LORA_WRITE_DATA_Struct      LoraTxdata;              /* LORA TX ����   */
  
    LORA_TransMode_ENUM         TransMode;               /* LORA ����ģʽ  */
    LORA_UsartMode_ENUM         UsartMode;               /* LORA ����ģʽ  */
    LORA_Callback_Function      RX_callbackFun;          /* LORA RX �ص�   */
    LORA_Callback_Function      TX_callbackFun;          /* LORA TX �ص�   */
  
    SCOM_InitTypedef_Struct     SCOM_InitStruct;         /* SCOM ��ʼ��    */ 
  
    uint16_t                    Address;                 /* LORA ��ַ      */
    uint16_t                    Com_Channel;	           /* LORA ����ͨ��  */

}LORARegister_Typedef_Struct;


/** 
  * @brief  ����LORA�ṹ��
  */
typedef struct __LORA_TypeDef_Struct
{
    LORAHardware_Typedef_Struct       LORA_Hardware;     /* LORAӲ���ṹ�� */
    LORARegister_Typedef_Struct       LORA_Operating;    /* LORA���ýṹ�� */
}LORA_TypeDef_Struct;


/** 
  * @brief  ����LORA��ʼ���Ĵ����ṹ��
  */
typedef struct __LORA_InitTypedef_Struct
{
    FunctionalState             enable_LORA;             /* LORA ʹ��      */
    FunctionalState             enable_DMA;              /* DMA  ʹ��      */
  
    LORA_TransMode_ENUM         TransMode;               /* LORA ����ģʽ  */
    LORA_UsartMode_ENUM         UsartMode;               /* LORA ����ģʽ  */
    LORA_Callback_Function      RX_callbackFun;          /* LORA RX �ص�   */
    LORA_Callback_Function      TX_callbackFun;          /* LORA TX �ص�   */
  
    uint8_t                     LORA_SCOM_PrePriorinty;  /* SCOM��ռ���ȼ� */
    uint8_t                     LORA_SCOM_SubPriorinty;  /* SCOM�����ȼ�   */
    uint8_t                     LORA_DMA_PrePriorinty;   /* DMA��ռ���ȼ�  */
    uint8_t                     LORA_DMA_SubPriorinty;   /* DMA�����ȼ�    */
  
    uint32_t                    LORA_SCOM_BaudRate; 	   /* LORA SCOM ������      */
    uint16_t                    LORA_SCOM_Parity;        /* LORA SCOM ����У��λ  */
    uint16_t                    LORA_SCOM_WordLength;	   /* LORA SCOM �����ֳ�    */
	  uint16_t                    LORA_SCOM_StopBits;      /* LORA SCOM ����ֹͣλ  */
    uint16_t                    LORA_SCOM_HardwareFlowControl; /* LORA SCOM Ӳ�������� */
    
    uint16_t                    Address;                 /* LORA ��ַ      */
    uint16_t                    Com_Channel;	           /* LORA ����ͨ��  */
  
}LORA_InitTypedef_Struct;



/* LORA BASE -----------------------------------------------------------------*/

extern LORA_TypeDef_Struct            LORA1_BASE;
#define LORA1                         (&LORA1_BASE)      /* LORA1 selected */
#define LORA1_SCOM                    (SCOM3      )      /* LORA1 SCOM     */
#define LORA1_MD0_GPIO                (GPIOB      )      /* LORA1 MD0 �˿� */
#define LORA1_MD0_GPIO_PIN            (GPIO_Pin_8 )      /* LORA1 MD0 ���� */
#define LORA1_MD1_GPIO                (GPIOB      )      /* LORA1 MD1 �˿� */
#define LORA1_MD1_GPIO_PIN            (GPIO_Pin_9 )      /* LORA1 MD1 ���� */
#define LORA1_AUX_GPIO                (GPIOB      )      /* LORA1 AUX �˿� */
#define LORA1_AUX_GPIO_PIN            (GPIO_Pin_7 )      /* LORA1 AUX ���� */
 
extern LORA_TypeDef_Struct            LORA2_BASE;
#define LORA2                         (&LORA2_BASE)      /* LORA2 selected */    
#define LORA2_SCOM                    (SCOM2      )      /* LORA2 SCOM     */
#define LORA2_MD0_GPIO                (GPIOA      )      /* LORA2 MD0 �˿� */
#define LORA2_MD0_GPIO_PIN            (GPIO_Pin_11)      /* LORA2 MD0 ���� */
#define LORA2_MD1_GPIO                (GPIOA      )      /* LORA2 MD1 �˿� */
#define LORA2_MD1_GPIO_PIN            (GPIO_Pin_12)      /* LORA2 MD1 ���� */
#define LORA2_AUX_GPIO                (GPIOA      )      /* LORA2 AUX �˿� */
#define LORA2_AUX_GPIO_PIN            (GPIO_Pin_13)      /* LORA2 AUX ���� */

extern LORA_TypeDef_Struct            LORA3_BASE;
#define LORA3                         (&LORA3_BASE)      /* LORA3 selected */
#define LORA3_SCOM                    (SCOM1      )      /* LORA3 SCOM     */
#define LORA3_MD0_GPIO                (GPIOC      )      /* LORA3 MD0 �˿� */
#define LORA3_MD0_GPIO_PIN            (GPIO_Pin_11)      /* LORA3 MD0 ���� */
#define LORA3_MD1_GPIO                (GPIOC      )      /* LORA3 MD1 �˿� */
#define LORA3_MD1_GPIO_PIN            (GPIO_Pin_12)      /* LORA3 MD1 ���� */
#define LORA3_AUX_GPIO                (GPIOC      )      /* LORA3 AUX �˿� */
#define LORA3_AUX_GPIO_PIN            (GPIO_Pin_13)      /* LORA3 AUX ���� */



/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  ��ʼ��LORA�ṹ��Ĭ������
 * @param  LORA_InitStruct  : LORA��ʼ���ṹ��
 */
void BSP_LORA_InitStruct(LORA_InitTypedef_Struct *LORA_InitStruct);


/**
 * @brief  ��ʼ��LORA�ṹ��
 * @param  *LORAx           : LORA�ṹ��
 *         *LORA_InitStruct : LORA��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LORA_Init(LORA_TypeDef_Struct *LORAx , LORA_InitTypedef_Struct *LORA_InitStruct);

/**
 * @brief  ʹ��LORA
 * @param  *LORAx           : LORA�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_Open(LORA_TypeDef_Struct *LORAx);


/**
 * @brief  ʧ��LORA
 * @param  *LORAx           : LORA�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_Close(LORA_TypeDef_Struct *LORAx);

/**
 * @brief  ��ȡLORA����
 * @param  *LORAx           : LORA�ṹ��
 * @param  *pRead           : �洢LORA���ݽṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_ReadData(LORA_TypeDef_Struct *LORAx , LORA_READ_DATA_Struct *pRead);


/**
 * @brief  д��LORA����
 * @param  *LORAx           : LORA�ṹ��
 * @param  *pWrite          : �洢LORA���ݽṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_WriteData(LORA_TypeDef_Struct *LORAx , LORA_WRITE_DATA_Struct *pWrite);


#endif







