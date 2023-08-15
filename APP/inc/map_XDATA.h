/**
  ******************************************************************************
  * @file    map_XDATA.h
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/1
  * @brief   ����������Э��ת���Ĺ���ʵ��
  ******************************************************************************/
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __MAP_XDATA_H
#define __MAP_XDATA_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "map_SCOMandSBUS.h"
#include "bsp_lora.h"
#include "string.h"


/* Defitions -----------------------------------------------------------------*/

#define   XDATA_ENABLE_DEFAULT                ENABLE                        /* Ĭ��XDATA ʹ��       */
#define   XDATA_TRANSMODE_DEFAULT             XDATA_Trans_Read_Mode         /* Ĭ��XDATA ����ģʽ   */


/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  ���� XDATA д�����ݽṹ��
  */	
typedef SBUSData_Struct           XDATA_WRITE_DATA_Struct; 


/** 
  * @brief  ���� XDATA ����ģʽö������
  */	
typedef enum __XDATA_TransMode_ENUM
{
    XDATA_Trans_Read_Mode      =     USART_Mode_Rx,      /* XDATA��ȡģʽ */
    XDATA_Trans_Weite_Mode     =     USART_Mode_Tx,      /* XDATAд��ģʽ */
}XDATA_TransMode_ENUM;



/** 
  * @brief  ���� XDATA ��ȡ���ݽṹ��
  */
typedef struct __XDATA_READ_DATA_Struct
{
    SBUSData_Struct             RXData;            /* RX���ݽṹ��     */
    FlagStatus                  Fresh;             /* �������ݸ��±�־ */
}XDATA_READ_DATA_Struct;



/** 
  * @brief  ���� XDATA Ӳ���ṹ��
  */
typedef struct __XDATAHardware_Typedef_Struct
{
  
    LORA_TypeDef_Struct        *LORAx;             /* XDATA LORA */
  
}XDATAHardware_Typedef_Struct;


/** 
  * @brief  ���� XDATA �Ĵ����ṹ��
  */
typedef struct __XDATARegister_Typedef_Struct
{
    FunctionalState             enable_XDATA;      /* XDATA ʹ��              */
    XDATA_TransMode_ENUM        TransMode;         /* XDATA ����ģʽ          */
    LORA_InitTypedef_Struct     LORA_InitStruct;   /* XDATA LORA��ʼ���ṹ��  */
  
    LORA_READ_DATA_Struct       RX_Buffer;         /* XDATA LORA RX ���ݻ���  */
    LORA_WRITE_DATA_Struct      TX_Buffer;         /* XDATA LORA TX ���ݻ���  */

}XDATARegister_Typedef_Struct;




/** 
  * @brief  ���� XDATA �ṹ��
  */
typedef struct __XDATA_TypeDef_Struct
{
    XDATAHardware_Typedef_Struct     XDATA_Hardware;    /* LORAӲ���ṹ�� */
    XDATARegister_Typedef_Struct     XDATA_Operating;   /* LORA���ýṹ�� */
}XDATA_TypeDef_Struct;



/** 
  * @brief  ����XDATA��ʼ���ṹ��
  */
typedef struct __XDATA_InitTypeDef_Struct
{
  
    FunctionalState                  enable_XDATA;      /* XDATA ʹ��             */
    XDATA_TransMode_ENUM             XDATA_TransMode;   /* XDATA ����ģʽ         */
    LORA_InitTypedef_Struct          LORA_InitStruct;   /* XDATA LORA��ʼ���ṹ�� */
  
}XDATA_InitTypeDef_Struct;



/* XDATA BASE ----------------------------------------------------------------*/


extern XDATA_TypeDef_Struct            XDATA1_BASE;
#define XDATA1                        (&XDATA1_BASE)    /* LORA1 selected */
#define XDATA1_LORA                   (LORA1)           /* XDATA LORA     */

 
extern XDATA_TypeDef_Struct            XDATA2_BASE;
#define XDATA2                        (&XDATA2_BASE)    /* LORA1 selected */
#define XDATA2_LORA                   (LORA2)           /* XDATA LORA     */


extern XDATA_TypeDef_Struct            XDATA3_BASE;
#define XDATA3                        (&XDATA3_BASE)    /* LORA1 selected */
#define XDATA3_LORA                   (LORA3)           /* XDATA LORA     */




/* Interface declaration -----------------------------------------------------*/

/**
 * @brief  ��ʼ��XDATA�ṹ��Ĭ������
 * @param  *XDATA_InitStruct  : XDATA��ʼ���ṹ��
 * @return void  
 */
void MAP_XDATA_InitStruct(XDATA_InitTypeDef_Struct *XDATA_InitStruct);


/**
 * @brief  ��ʼ��XDATA�ṹ��
 * @param  *XDATAx           : XDATA�ṹ��
 *         *XDATA_InitStruct : XDATA��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_XDATA_Init(XDATA_TypeDef_Struct *XDATAx , XDATA_InitTypeDef_Struct *XDATA_InitStruct);


/**
 * @brief  �� XDATA ͨ��
 * @param  XDATAx�� ��Ҫ�򿪵� XDATA ͨ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_Open(XDATA_TypeDef_Struct *XDATAx);


/**
 * @brief  �ر� XDATA ͨ��
 * @param  XDATAx�� ��Ҫ�رյ� XDATA ͨ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_Close(XDATA_TypeDef_Struct *XDATAx);


/**
 * @brief  ����XDATA����
 * @param  XDATAx�� ��Ҫ�������ݵ�XDATA�ṹ��ָ��
 * @param  Xdata �� XDATAЭ�����ݽṹ��ָ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_ReadData(XDATA_TypeDef_Struct *XDATAx , XDATA_READ_DATA_Struct *pRead);


/**
 * @brief  д��SBUS����
 * @param  XDATAx  �� д�����ݵ�XDATA�ṹ��ָ��
 * @param  SBUSdata�� SBUS���ݴ洢ָ��,���鳤��16byte 11bit
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_WriteData(XDATA_TypeDef_Struct *XDATAx , XDATA_WRITE_DATA_Struct *pWrite);



#endif




