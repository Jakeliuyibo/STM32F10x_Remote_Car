/**
  ******************************************************************************
  * @file    bsp_oled.h
  * @author  LYB
  * @version V1.0.1
  * @date    2021/3/30
  * @brief   描述了底层oled通用的驱动外部接口
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

#define OLED_NUMBER_OF_PAGES                8                         /* OLED 页数       */
#define OLED_NUMBER_OF_BYTES                128                       /* OLED 每页字节数 */

#define OLED_ENABLE_DEFAULT                 ENABLE                    /* 默认 OLED 使能  */



/* typedef -------------------------------------------------------------------*/



/**  
  * @brief  定义 OLED 写操作模式
  */	
typedef enum __OLED_Write_Mode_ENUM
{
    OLED_Write_Mode_Cmd        =     0,                            /* OLED 写命令操作  */
    OLED_Write_Mode_Data       =     1                             /* OLED 写数据操作  */
}OLED_Write_Mode_ENUM;



/** 
  * @brief  定义OLED硬件结构体
  */	
typedef struct __OLEDHardware_Typedef_Struct
{
  
    GPIO_TypeDef                       *CLK_GPIO;                 /* OLED CLK  端口 */
    uint16_t                            CLK_GPIO_PIN;             /* OLED CLK  引脚 */
    GPIO_TypeDef                       *DATA_GPIO;                /* OLED DATA 端口 */ 
    uint16_t                            DATA_GPIO_PIN;            /* OLED DATA 引脚 */
    GPIO_TypeDef                       *RES_GPIO;                 /* OLED RES  端口 */
    uint16_t                            RES_GPIO_PIN;             /* OLED RES  引脚 */
    GPIO_TypeDef                       *DC_GPIO;                  /* OLED DC   端口 */   
    uint16_t                            DC_GPIO_PIN;              /* OLED DC   引脚 */
    GPIO_TypeDef                       *CS_GPIO;                  /* OLED CS   端口 */   
    uint16_t                            CS_GPIO_PIN;              /* OLED CS   引脚 */
  
}OLEDHardware_Typedef_Struct;


/** 
  * @brief  定义OLED寄存器结构体
  */	
typedef struct __OLEDRegister_Typedef_Struct
{
  
    FunctionalState                     enable_OLED;                                        /* OLED 使能      */
    uint8_t                             buffer[OLED_NUMBER_OF_BYTES][OLED_NUMBER_OF_PAGES]; /* OLED 点阵缓存  */
  
}OLEDRegister_Typedef_Struct;


/** 
  * @brief  定义OLED结构体
  */	
typedef struct __OLED_TypeDef_Struct
{
    OLEDHardware_Typedef_Struct         OLED_Hardware;        /* OLED硬件结构体 */
    OLEDRegister_Typedef_Struct         OLED_Operating;       /* OLED配置结构体 */
}OLED_TypeDef_Struct;



/** 
  * @brief  定义OLED初始化结构体
  */	
typedef struct __OLED_InitTypeDef_Struct
{
  
    FunctionalState                    enable_OLED;         /* OLED 使能      */
  
}OLED_InitTypeDef_Struct;



/* OLED BASE -----------------------------------------------------------------*/

extern  OLED_TypeDef_Struct            OLED1_BASE;    
#define OLED1                         (&OLED1_BASE)         /* OLED1          */
#define OLED1_CLK_GPIO                (GPIOG)               /* OLED1 时钟端口 */
#define OLED1_CLK_GPIO_PIN            (GPIO_Pin_4)          /* OLED1 时钟引脚 */
#define OLED1_DATA_GPIO               (GPIOG)               /* OLED1 数据端口 */
#define OLED1_DATA_GPIO_PIN           (GPIO_Pin_5)          /* OLED1 数据引脚 */
#define OLED1_RES_GPIO                (GPIOG)               /* OLED1 复位端口 */
#define OLED1_RES_GPIO_PIN            (GPIO_Pin_6)          /* OLED1 复位引脚 */
#define OLED1_DC_GPIO                 (GPIOG)               /* OLED1 控制端口 */
#define OLED1_DC_GPIO_PIN             (GPIO_Pin_7)          /* OLED1 控制引脚 */
#define OLED1_CS_GPIO                 (GPIOG)               /* OLED1 片选端口 */
#define OLED1_CS_GPIO_PIN             (GPIO_Pin_8)          /* OLED1 片选引脚 */

extern  OLED_TypeDef_Struct            OLED2_BASE;    
#define OLED2                         (&OLED2_BASE)         /* OLED2          */
#define OLED2_CLK_GPIO                (GPIOG)               /* OLED2 时钟端口 */
#define OLED2_CLK_GPIO_PIN            (GPIO_Pin_9)          /* OLED2 时钟引脚 */
#define OLED2_DATA_GPIO               (GPIOG)               /* OLED2 数据端口 */
#define OLED2_DATA_GPIO_PIN           (GPIO_Pin_10)         /* OLED2 数据引脚 */
#define OLED2_RES_GPIO                (GPIOG)               /* OLED2 复位端口 */
#define OLED2_RES_GPIO_PIN            (GPIO_Pin_11)         /* OLED2 复位引脚 */
#define OLED2_DC_GPIO                 (GPIOG)               /* OLED2 控制端口 */
#define OLED2_DC_GPIO_PIN             (GPIO_Pin_12)         /* OLED2 控制引脚 */
#define OLED2_CS_GPIO                 (GPIOG)               /* OLED2 片选端口 */
#define OLED2_CS_GPIO_PIN             (GPIO_Pin_13)         /* OLED2 片选引脚 */

/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  初始化 OLED 结构体默认配置
 * @param  OLED_InitStruct  : OLED 初始化结构体
 * @return void
 */
void BSP_OLED_InitStruct(OLED_InitTypeDef_Struct *OLED_InitStruct);


/**
 * @brief  初始化 OLED 结构体
 * @param  *OLEDx            : OLED 结构体
 *         *OLED_InitStruct  : OLED 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Init(OLED_TypeDef_Struct *OLEDx , OLED_InitTypeDef_Struct *OLED_InitStruct);


/**
 * @brief  OLED 写入数字
 * @param  *OLEDx            : OLED 结构体
 * @param  x_coordinate      : x轴坐标 0-127
 * @param  y_coordinate      : y轴坐标 0-63
 * @param  num               : 显示的数字
 * @param  len               : 数字的长度
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteNum(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u32 num);


/**
 * @brief  OLED 写入字符串
 * @param  *OLEDx            : OLED 结构体
 * @param  x_coordinate      : x轴坐标 0-127
 * @param  y_coordinate      : y轴坐标 0-63
 * @param  pchar             : 显示的字符
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteString(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u8 *pchar);


/**
 * @brief  OLED 写入字符
 * @param  *OLEDx            : OLED 结构体
 * @param  x_coordinate      : x轴坐标 0-127
 * @param  y_coordinate      : y轴坐标 0-63
 * @param  pchar             : 显示的字符
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteChar(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u8 chr);


/**
 * @brief  清屏 OLED 
 * @param  *OLEDx           : OLED结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Clear(OLED_TypeDef_Struct *OLEDx);


/**
 * @brief  更新显示 OLED 
 * @param  *OLEDx           : OLED结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Refresh(OLED_TypeDef_Struct *OLEDx);


#endif






