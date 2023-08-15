/**
  ******************************************************************************
  * @file    map_XDATA.h
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/1
  * @brief   描述了数据协议转换的功能实现
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

#define   XDATA_ENABLE_DEFAULT                ENABLE                        /* 默认XDATA 使能       */
#define   XDATA_TRANSMODE_DEFAULT             XDATA_Trans_Read_Mode         /* 默认XDATA 传输模式   */


/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  定义 XDATA 写入数据结构体
  */	
typedef SBUSData_Struct           XDATA_WRITE_DATA_Struct; 


/** 
  * @brief  定义 XDATA 传输模式枚举类型
  */	
typedef enum __XDATA_TransMode_ENUM
{
    XDATA_Trans_Read_Mode      =     USART_Mode_Rx,      /* XDATA读取模式 */
    XDATA_Trans_Weite_Mode     =     USART_Mode_Tx,      /* XDATA写入模式 */
}XDATA_TransMode_ENUM;



/** 
  * @brief  定义 XDATA 读取数据结构体
  */
typedef struct __XDATA_READ_DATA_Struct
{
    SBUSData_Struct             RXData;            /* RX数据结构体     */
    FlagStatus                  Fresh;             /* 接收数据更新标志 */
}XDATA_READ_DATA_Struct;



/** 
  * @brief  定义 XDATA 硬件结构体
  */
typedef struct __XDATAHardware_Typedef_Struct
{
  
    LORA_TypeDef_Struct        *LORAx;             /* XDATA LORA */
  
}XDATAHardware_Typedef_Struct;


/** 
  * @brief  定义 XDATA 寄存器结构体
  */
typedef struct __XDATARegister_Typedef_Struct
{
    FunctionalState             enable_XDATA;      /* XDATA 使能              */
    XDATA_TransMode_ENUM        TransMode;         /* XDATA 传输模式          */
    LORA_InitTypedef_Struct     LORA_InitStruct;   /* XDATA LORA初始化结构体  */
  
    LORA_READ_DATA_Struct       RX_Buffer;         /* XDATA LORA RX 数据缓存  */
    LORA_WRITE_DATA_Struct      TX_Buffer;         /* XDATA LORA TX 数据缓存  */

}XDATARegister_Typedef_Struct;




/** 
  * @brief  定义 XDATA 结构体
  */
typedef struct __XDATA_TypeDef_Struct
{
    XDATAHardware_Typedef_Struct     XDATA_Hardware;    /* LORA硬件结构体 */
    XDATARegister_Typedef_Struct     XDATA_Operating;   /* LORA配置结构体 */
}XDATA_TypeDef_Struct;



/** 
  * @brief  定义XDATA初始化结构体
  */
typedef struct __XDATA_InitTypeDef_Struct
{
  
    FunctionalState                  enable_XDATA;      /* XDATA 使能             */
    XDATA_TransMode_ENUM             XDATA_TransMode;   /* XDATA 传输模式         */
    LORA_InitTypedef_Struct          LORA_InitStruct;   /* XDATA LORA初始化结构体 */
  
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
 * @brief  初始化XDATA结构体默认配置
 * @param  *XDATA_InitStruct  : XDATA初始化结构体
 * @return void  
 */
void MAP_XDATA_InitStruct(XDATA_InitTypeDef_Struct *XDATA_InitStruct);


/**
 * @brief  初始化XDATA结构体
 * @param  *XDATAx           : XDATA结构体
 *         *XDATA_InitStruct : XDATA初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_XDATA_Init(XDATA_TypeDef_Struct *XDATAx , XDATA_InitTypeDef_Struct *XDATA_InitStruct);


/**
 * @brief  打开 XDATA 通道
 * @param  XDATAx： 需要打开的 XDATA 通道
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_Open(XDATA_TypeDef_Struct *XDATAx);


/**
 * @brief  关闭 XDATA 通道
 * @param  XDATAx： 需要关闭的 XDATA 通道
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_Close(XDATA_TypeDef_Struct *XDATAx);


/**
 * @brief  读出XDATA数据
 * @param  XDATAx： 需要读出数据的XDATA结构体指针
 * @param  Xdata ： XDATA协议数据结构体指针
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_ReadData(XDATA_TypeDef_Struct *XDATAx , XDATA_READ_DATA_Struct *pRead);


/**
 * @brief  写入SBUS数据
 * @param  XDATAx  ： 写入数据的XDATA结构体指针
 * @param  SBUSdata： SBUS数据存储指针,数组长度16byte 11bit
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_WriteData(XDATA_TypeDef_Struct *XDATAx , XDATA_WRITE_DATA_Struct *pWrite);



#endif




