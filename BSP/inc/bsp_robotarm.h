/**
  ******************************************************************************
  * @file    bsp_robotarm.h
  * @author  LYB
  * @version V1.0.1
  * @date    2021/4/06
  * @brief   描述了底层机械臂的外部接口
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

#define   ARM_ENABLE_DEFAULT                ENABLE                         /* 默认 ARM 使能       */
#define   ARM_ENABLE_DMA_DEFAULT            ENABLE                         /* 默认 ARM DMA使能    */

#define   ARM_BAUDRATE_DEFAULT              115200                        /* 默认串口波特率      */
#define   ARM_PARITY_DEFAULT                USART_Parity_No                /* 默认串口校验位      */
#define   ARM_WORDLENGTH_DEFAULT            USART_WordLength_8b            /* 默认串口字长        */
#define   ARM_STOPBITS_DEFAULT              USART_StopBits_1               /* 默认串口停止位      */
#define   ARM_HARDWARE_FLOWCONTROL_DEFAULT  USART_HardwareFlowControl_None /* 默认串口硬件控制流  */

#define   ARM_SCOMPREPRIORINTY_DEFAULT      3                              /* 默认SCOM抢占优先级  */
#define   ARM_SCOMSUBPRIORINTY_DEFAULT      3                              /* 默认SCOM子优先级    */
#define   ARM_DMAPREPRIORINTY_DEFAULT       3                              /* 默认DMA抢占优先级   */
#define   ARM_DMASUBPRIORINTY_DEFAULT       3                              /* 默认DMA子优先级     */

#define   ARM_OUTPUT_MAX_LIMIT              2500                           /* ARM 输出的最大角度  */
#define   ARM_OUTPUT_MIN_LIMIT              500                            /* ARM 输出的最小角度  */


/* typedef -------------------------------------------------------------------*/


typedef  SCOM_WRITE_DATA_Struct             ARM_WRITE_DATA_Struct;         /* ARM 写入数据结构体 */


/** 
  * @brief  定义 ARM 硬件结构体
  */	
typedef struct __ARMHardware_Typedef_Struct
{
    SCOM_TypeDef_Struct                    *SCOM;                          /* SCOM               */
  
}ARMHardware_Typedef_Struct;


/** 
  * @brief  定义 ARM 寄存器结构体
  */	
typedef struct __ARMRegister_Typedef_Struct
{
    FunctionalState                         enable_ARM;                    /* ARM 使能              */
    
    uint16_t                                Channel_data[6];               /* ARM 6个通道的缓存     */
    ARM_WRITE_DATA_Struct                   Tx_data;                       /* ARM TX 发送数据       */
  
    SCOM_InitTypedef_Struct                 SCOM_InitStruct;               /* ARM SCOM 配置         */ 

}ARMRegister_Typedef_Struct;


/** 
  * @brief  定义 ARM 结构体
  */	
typedef struct __ARM_TypeDef_Struct
{
    ARMHardware_Typedef_Struct              ARM_Hardware;                  /* ARM 硬件结构体        */
    ARMRegister_Typedef_Struct              ARM_Operating;                 /* ARM 配置结构体        */
}ARM_TypeDef_Struct;

/** 
  * @brief  定义 ARM 初始化结构体
  */	
typedef struct __ARM_InitTypeDef_Struct
{
    FunctionalState                         enable_ARM;                    /* ARM 使能              */
    FunctionalState                         enable_DMA;                    /* ARM SCOM DMA  使能    */
  
    uint32_t                                ARM_SCOM_BaudRate; 	           /* ARM SCOM 波特率       */
    uint16_t                                ARM_SCOM_Parity;               /* ARM SCOM 串口校验位   */
    uint16_t                                ARM_SCOM_WordLength;	         /* ARM SCOM 串口字长     */
	  uint16_t                                ARM_SCOM_StopBits;             /* ARM SCOM 串口停止位   */
    uint16_t                                ARM_SCOM_HardwareFlowControl;  /* ARM SCOM 硬件控制流   */
  
    uint8_t                                 ARM_SCOM_PrePriorinty;         /* ARM SCOM抢占优先级    */
    uint8_t                                 ARM_SCOM_SubPriorinty;         /* ARM SCOM子优先级      */
    uint8_t                                 ARM_DMA_PrePriorinty;          /* ARM DMA抢占优先级     */
    uint8_t                                 ARM_DMA_SubPriorinty;          /* ARM DMA子优先级       */

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
 * @brief  初始化ARM结构体默认配置
 * @param  ARM_InitStruct  : ARM初始化结构体
 * @return void
 */
void BSP_ARM_InitStruct(ARM_InitTypeDef_Struct *ARM_InitStruct);


/**
 * @brief  初始化LORA结构体
 * @param  *ARMx           : ARMx结构体
 *         *ARM_InitStruct : ARM初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Init(ARM_TypeDef_Struct *ARMx , ARM_InitTypeDef_Struct *ARM_InitStruct);

/**
 * @brief  使能ARM
 * @param  *ARMx           : ARM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Open(ARM_TypeDef_Struct *ARMx);


/**
 * @brief  失能ARM
 * @param  *ARMx           : ARM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Close(ARM_TypeDef_Struct *ARMx);


/**
 * @brief  ARM 机械臂驱动
 * @param  *ARMx           : ARM结构体
 * @param  channel         : 驱动的通道
 * @param  data            : 驱动的数据
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Drive(ARM_TypeDef_Struct *ARMx , uint8_t channel, float data);

#endif

