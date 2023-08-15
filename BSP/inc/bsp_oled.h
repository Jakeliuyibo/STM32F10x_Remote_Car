/**
  ******************************************************************************
  * @file    bsp_oled.h
  * @author  LYB
  * @version V1.0.1
  * @date    2021/3/30
  * @brief   �����˵ײ�oledͨ�õ������ⲿ�ӿ�
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_OLED_H
#define __BSP_OLED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"
#include "time.h"
#include "math.h"


/* Defitions -----------------------------------------------------------------*/

#define OLED_NUMBER_OF_PAGES                8                         /* OLED ҳ��       */
#define OLED_NUMBER_OF_BYTES                128                       /* OLED ÿҳ�ֽ��� */

#define OLED_ENABLE_DEFAULT                 ENABLE                    /* Ĭ�� OLED ʹ��  */



/* typedef -------------------------------------------------------------------*/



/**  
  * @brief  ���� OLED д����ģʽ
  */	
typedef enum __OLED_Write_Mode_ENUM
{
    OLED_Write_Mode_Cmd        =     0,                            /* OLED д�������  */
    OLED_Write_Mode_Data       =     1                             /* OLED д���ݲ���  */
}OLED_Write_Mode_ENUM;



/** 
  * @brief  ����OLEDӲ���ṹ��
  */	
typedef struct __OLEDHardware_Typedef_Struct
{
  
    GPIO_TypeDef                       *CLK_GPIO;                 /* OLED CLK  �˿� */
    uint16_t                            CLK_GPIO_PIN;             /* OLED CLK  ���� */
    GPIO_TypeDef                       *DATA_GPIO;                /* OLED DATA �˿� */ 
    uint16_t                            DATA_GPIO_PIN;            /* OLED DATA ���� */
    GPIO_TypeDef                       *RES_GPIO;                 /* OLED RES  �˿� */
    uint16_t                            RES_GPIO_PIN;             /* OLED RES  ���� */
    GPIO_TypeDef                       *DC_GPIO;                  /* OLED DC   �˿� */   
    uint16_t                            DC_GPIO_PIN;              /* OLED DC   ���� */
    GPIO_TypeDef                       *CS_GPIO;                  /* OLED CS   �˿� */   
    uint16_t                            CS_GPIO_PIN;              /* OLED CS   ���� */
  
}OLEDHardware_Typedef_Struct;


/** 
  * @brief  ����OLED�Ĵ����ṹ��
  */	
typedef struct __OLEDRegister_Typedef_Struct
{
  
    FunctionalState                     enable_OLED;                                        /* OLED ʹ��      */
    uint8_t                             buffer[OLED_NUMBER_OF_BYTES][OLED_NUMBER_OF_PAGES]; /* OLED ���󻺴�  */
  
}OLEDRegister_Typedef_Struct;


/** 
  * @brief  ����OLED�ṹ��
  */	
typedef struct __OLED_TypeDef_Struct
{
    OLEDHardware_Typedef_Struct         OLED_Hardware;        /* OLEDӲ���ṹ�� */
    OLEDRegister_Typedef_Struct         OLED_Operating;       /* OLED���ýṹ�� */
}OLED_TypeDef_Struct;



/** 
  * @brief  ����OLED��ʼ���ṹ��
  */	
typedef struct __OLED_InitTypeDef_Struct
{
  
    FunctionalState                    enable_OLED;         /* OLED ʹ��      */
  
}OLED_InitTypeDef_Struct;



/* OLED BASE -----------------------------------------------------------------*/

extern  OLED_TypeDef_Struct            OLED1_BASE;    
#define OLED1                         (&OLED1_BASE)         /* OLED1          */
#define OLED1_CLK_GPIO                (GPIOG)               /* OLED1 ʱ�Ӷ˿� */
#define OLED1_CLK_GPIO_PIN            (GPIO_Pin_4)          /* OLED1 ʱ������ */
#define OLED1_DATA_GPIO               (GPIOG)               /* OLED1 ���ݶ˿� */
#define OLED1_DATA_GPIO_PIN           (GPIO_Pin_5)          /* OLED1 �������� */
#define OLED1_RES_GPIO                (GPIOG)               /* OLED1 ��λ�˿� */
#define OLED1_RES_GPIO_PIN            (GPIO_Pin_6)          /* OLED1 ��λ���� */
#define OLED1_DC_GPIO                 (GPIOG)               /* OLED1 ���ƶ˿� */
#define OLED1_DC_GPIO_PIN             (GPIO_Pin_7)          /* OLED1 �������� */
#define OLED1_CS_GPIO                 (GPIOG)               /* OLED1 Ƭѡ�˿� */
#define OLED1_CS_GPIO_PIN             (GPIO_Pin_8)          /* OLED1 Ƭѡ���� */

extern  OLED_TypeDef_Struct            OLED2_BASE;    
#define OLED2                         (&OLED2_BASE)         /* OLED2          */
#define OLED2_CLK_GPIO                (GPIOG)               /* OLED2 ʱ�Ӷ˿� */
#define OLED2_CLK_GPIO_PIN            (GPIO_Pin_9)          /* OLED2 ʱ������ */
#define OLED2_DATA_GPIO               (GPIOG)               /* OLED2 ���ݶ˿� */
#define OLED2_DATA_GPIO_PIN           (GPIO_Pin_10)         /* OLED2 �������� */
#define OLED2_RES_GPIO                (GPIOG)               /* OLED2 ��λ�˿� */
#define OLED2_RES_GPIO_PIN            (GPIO_Pin_11)         /* OLED2 ��λ���� */
#define OLED2_DC_GPIO                 (GPIOG)               /* OLED2 ���ƶ˿� */
#define OLED2_DC_GPIO_PIN             (GPIO_Pin_12)         /* OLED2 �������� */
#define OLED2_CS_GPIO                 (GPIOG)               /* OLED2 Ƭѡ�˿� */
#define OLED2_CS_GPIO_PIN             (GPIO_Pin_13)         /* OLED2 Ƭѡ���� */

/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  ��ʼ�� OLED �ṹ��Ĭ������
 * @param  OLED_InitStruct  : OLED ��ʼ���ṹ��
 * @return void
 */
void BSP_OLED_InitStruct(OLED_InitTypeDef_Struct *OLED_InitStruct);


/**
 * @brief  ��ʼ�� OLED �ṹ��
 * @param  *OLEDx            : OLED �ṹ��
 *         *OLED_InitStruct  : OLED ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Init(OLED_TypeDef_Struct *OLEDx , OLED_InitTypeDef_Struct *OLED_InitStruct);


/**
 * @brief  OLED д������
 * @param  *OLEDx            : OLED �ṹ��
 * @param  x_coordinate      : x������ 0-127
 * @param  y_coordinate      : y������ 0-63
 * @param  num               : ��ʾ������
 * @param  len               : ���ֵĳ���
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteNum(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u32 num);


/**
 * @brief  OLED д���ַ���
 * @param  *OLEDx            : OLED �ṹ��
 * @param  x_coordinate      : x������ 0-127
 * @param  y_coordinate      : y������ 0-63
 * @param  pchar             : ��ʾ���ַ�
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteString(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u8 *pchar);


/**
 * @brief  OLED д���ַ�
 * @param  *OLEDx            : OLED �ṹ��
 * @param  x_coordinate      : x������ 0-127
 * @param  y_coordinate      : y������ 0-63
 * @param  pchar             : ��ʾ���ַ�
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteChar(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u8 chr);


/**
 * @brief  ���� OLED 
 * @param  *OLEDx           : OLED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Clear(OLED_TypeDef_Struct *OLEDx);


/**
 * @brief  ������ʾ OLED 
 * @param  *OLEDx           : OLED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Refresh(OLED_TypeDef_Struct *OLEDx);


#endif






