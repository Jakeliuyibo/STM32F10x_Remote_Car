/**
  ******************************************************************************
  * @file    bsp_lora.h
  * @author  LYB
  * @version V1.0.2
  * @date    202/4/3
  * @brief   描述了底层lora通用的驱动外部接口
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_LORA_H
#define __BSP_LORA_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_scom.h"
#include "string.h"

/* Defitions -----------------------------------------------------------------*/

#define   LORA_ENABLE_DEFAULT                ENABLE                        /* 默认LORA 使能       */
#define   LORA_ENABLE_DMA_DEFAULT            ENABLE                        /* 默认LORA DMA使能    */

#define   LORA_TRANSMODE_DEFAULT             LORA_Transparent_Trans        /* 默认LORA传输模式    */     
#define   LORA_USARTMODE_DEFAULT             LORA_Usart_Mode_RX            /* 默认LORA串口模式    */

#define   LORA_SCOMPREPRIORINTY_DEFAULT      3                             /* 默认SCOM抢占优先级  */
#define   LORA_SCOMSUBPRIORINTY_DEFAULT      3                             /* 默认SCOM子优先级    */
#define   LORA_DMAPREPRIORINTY_DEFAULT       0                             /* 默认DMA抢占优先级   */
#define   LORA_DMASUBPRIORINTY_DEFAULT       0                             /* 默认DMA子优先级     */

#define   LORA_TX_CALLBACKFUN_DEFAULT        NULL                          /* 默认LORA TX回调函数 */
#define   LORA_RX_CALLBACKFUN_DEFAULT        NULL                          /* 默认LORA RX回调函数 */

#define   LORA_ADDRESS_DEFAULT               0X1234                       /* 默认LORA地址       */
#define   LORA_COMCHANNEL_DEFAULT	           0X17                          /* 默认LORA串口通道   */

#define   LORA_BAUDRATE_DEFAULT              115200                        /* 默认串口波特率  */
#define   LORA_PARITY_DEFAULT                USART_Parity_No                /* 默认串口校验位  */
#define   LORA_WORDLENGTH_DEFAULT            USART_WordLength_8b            /* 默认串口字长    */
#define   LORA_STOPBITS_DEFAULT              USART_StopBits_1               /* 默认串口停止位  */
#define   LORA_HARDWARE_FLOWCONTROL_DEFAULT  USART_HardwareFlowControl_None /* 默认串口硬件控制流 */

/* typedef -------------------------------------------------------------------*/

typedef SCOM_READ_DATA_Struct     LORA_READ_DATA_Struct ;    /* LORA读取数据结构体 */
typedef SCOM_WRITE_DATA_Struct    LORA_WRITE_DATA_Struct;    /* LORA写入数据结构体 */


/** 
  * @brief  LORA回调函数声明
  */
typedef void (*LORA_Callback_Function)();


/**  
  * @brief  定义 LORA 传输模式枚举类型
  */	
typedef enum __LORA_TransMode_ENUM
{
    LORA_Transparent_Trans    =     0,                  /* LORA透明传输 */
    LORA_Fixed_Transfer       =     1                   /* LORA定点传输 */
//    LORA_Radio_Listening      =     2,                /* LORA广播监听 */
//    LORA_Air_Wakeup           =     3,                /* LORA空中唤醒 */
//    LORA_Low_Power            =     4                 /* LORA低功耗   */ 
}LORA_TransMode_ENUM;


/** 
  * @brief  定义 LORA 串口模式枚举类型
  */	
typedef enum __LORA_UsartMode_ENUM
{
    LORA_Usart_Mode_RX    =   USART_Mode_Rx,            /* LORA串口接受模式 */
    LORA_Usart_Mode_TX    =   USART_Mode_Tx,            /* LORA串口发送模式 */
}LORA_UsartMode_ENUM;


/** 
  * @brief  定义 LORA 硬件结构体
  */
typedef struct __LORAHardware_Typedef_Struct
{
    SCOM_TypeDef_Struct        *SCOMx;                   /* SCOM         */

    GPIO_TypeDef               *MD0_GPIO;                /* MD0端口      */
    uint16_t                    MD0_GPIO_PIN;            /* MD0引脚      */
    GPIO_TypeDef               *MD1_GPIO;                /* MD1端口      */
    uint16_t                    MD1_GPIO_PIN;            /* MD1引脚      */
    GPIO_TypeDef               *AUX_GPIO;                /* AUX端口      */
    uint16_t                    AUX_GPIO_PIN;            /* AUX引脚      */
  
}LORAHardware_Typedef_Struct;


/** 
  * @brief  定义LORA寄存器结构体
  */
typedef struct __LORARegister_Typedef_Struct
{
    FunctionalState             enable_LORA;             /* LORA 使能      */
  
    LORA_READ_DATA_Struct       LoraRxdata;              /* LORA RX 数据   */
    LORA_WRITE_DATA_Struct      LoraTxdata;              /* LORA TX 数据   */
  
    LORA_TransMode_ENUM         TransMode;               /* LORA 传输模式  */
    LORA_UsartMode_ENUM         UsartMode;               /* LORA 串口模式  */
    LORA_Callback_Function      RX_callbackFun;          /* LORA RX 回调   */
    LORA_Callback_Function      TX_callbackFun;          /* LORA TX 回调   */
  
    SCOM_InitTypedef_Struct     SCOM_InitStruct;         /* SCOM 初始化    */ 
  
    uint16_t                    Address;                 /* LORA 地址      */
    uint16_t                    Com_Channel;	           /* LORA 串口通道  */

}LORARegister_Typedef_Struct;


/** 
  * @brief  定义LORA结构体
  */
typedef struct __LORA_TypeDef_Struct
{
    LORAHardware_Typedef_Struct       LORA_Hardware;     /* LORA硬件结构体 */
    LORARegister_Typedef_Struct       LORA_Operating;    /* LORA配置结构体 */
}LORA_TypeDef_Struct;


/** 
  * @brief  定义LORA初始化寄存器结构体
  */
typedef struct __LORA_InitTypedef_Struct
{
    FunctionalState             enable_LORA;             /* LORA 使能      */
    FunctionalState             enable_DMA;              /* DMA  使能      */
  
    LORA_TransMode_ENUM         TransMode;               /* LORA 传输模式  */
    LORA_UsartMode_ENUM         UsartMode;               /* LORA 串口模式  */
    LORA_Callback_Function      RX_callbackFun;          /* LORA RX 回调   */
    LORA_Callback_Function      TX_callbackFun;          /* LORA TX 回调   */
  
    uint8_t                     LORA_SCOM_PrePriorinty;  /* SCOM抢占优先级 */
    uint8_t                     LORA_SCOM_SubPriorinty;  /* SCOM子优先级   */
    uint8_t                     LORA_DMA_PrePriorinty;   /* DMA抢占优先级  */
    uint8_t                     LORA_DMA_SubPriorinty;   /* DMA子优先级    */
  
    uint32_t                    LORA_SCOM_BaudRate; 	   /* LORA SCOM 波特率      */
    uint16_t                    LORA_SCOM_Parity;        /* LORA SCOM 串口校验位  */
    uint16_t                    LORA_SCOM_WordLength;	   /* LORA SCOM 串口字长    */
	  uint16_t                    LORA_SCOM_StopBits;      /* LORA SCOM 串口停止位  */
    uint16_t                    LORA_SCOM_HardwareFlowControl; /* LORA SCOM 硬件控制流 */
    
    uint16_t                    Address;                 /* LORA 地址      */
    uint16_t                    Com_Channel;	           /* LORA 串口通道  */
  
}LORA_InitTypedef_Struct;



/* LORA BASE -----------------------------------------------------------------*/

extern LORA_TypeDef_Struct            LORA1_BASE;
#define LORA1                         (&LORA1_BASE)      /* LORA1 selected */
#define LORA1_SCOM                    (SCOM3      )      /* LORA1 SCOM     */
#define LORA1_MD0_GPIO                (GPIOB      )      /* LORA1 MD0 端口 */
#define LORA1_MD0_GPIO_PIN            (GPIO_Pin_8 )      /* LORA1 MD0 引脚 */
#define LORA1_MD1_GPIO                (GPIOB      )      /* LORA1 MD1 端口 */
#define LORA1_MD1_GPIO_PIN            (GPIO_Pin_9 )      /* LORA1 MD1 引脚 */
#define LORA1_AUX_GPIO                (GPIOB      )      /* LORA1 AUX 端口 */
#define LORA1_AUX_GPIO_PIN            (GPIO_Pin_7 )      /* LORA1 AUX 引脚 */
 
extern LORA_TypeDef_Struct            LORA2_BASE;
#define LORA2                         (&LORA2_BASE)      /* LORA2 selected */    
#define LORA2_SCOM                    (SCOM2      )      /* LORA2 SCOM     */
#define LORA2_MD0_GPIO                (GPIOA      )      /* LORA2 MD0 端口 */
#define LORA2_MD0_GPIO_PIN            (GPIO_Pin_11)      /* LORA2 MD0 引脚 */
#define LORA2_MD1_GPIO                (GPIOA      )      /* LORA2 MD1 端口 */
#define LORA2_MD1_GPIO_PIN            (GPIO_Pin_12)      /* LORA2 MD1 引脚 */
#define LORA2_AUX_GPIO                (GPIOA      )      /* LORA2 AUX 端口 */
#define LORA2_AUX_GPIO_PIN            (GPIO_Pin_13)      /* LORA2 AUX 引脚 */

extern LORA_TypeDef_Struct            LORA3_BASE;
#define LORA3                         (&LORA3_BASE)      /* LORA3 selected */
#define LORA3_SCOM                    (SCOM1      )      /* LORA3 SCOM     */
#define LORA3_MD0_GPIO                (GPIOC      )      /* LORA3 MD0 端口 */
#define LORA3_MD0_GPIO_PIN            (GPIO_Pin_11)      /* LORA3 MD0 引脚 */
#define LORA3_MD1_GPIO                (GPIOC      )      /* LORA3 MD1 端口 */
#define LORA3_MD1_GPIO_PIN            (GPIO_Pin_12)      /* LORA3 MD1 引脚 */
#define LORA3_AUX_GPIO                (GPIOC      )      /* LORA3 AUX 端口 */
#define LORA3_AUX_GPIO_PIN            (GPIO_Pin_13)      /* LORA3 AUX 引脚 */



/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  初始化LORA结构体默认配置
 * @param  LORA_InitStruct  : LORA初始化结构体
 */
void BSP_LORA_InitStruct(LORA_InitTypedef_Struct *LORA_InitStruct);


/**
 * @brief  初始化LORA结构体
 * @param  *LORAx           : LORA结构体
 *         *LORA_InitStruct : LORA初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LORA_Init(LORA_TypeDef_Struct *LORAx , LORA_InitTypedef_Struct *LORA_InitStruct);

/**
 * @brief  使能LORA
 * @param  *LORAx           : LORA结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_Open(LORA_TypeDef_Struct *LORAx);


/**
 * @brief  失能LORA
 * @param  *LORAx           : LORA结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_Close(LORA_TypeDef_Struct *LORAx);

/**
 * @brief  读取LORA数据
 * @param  *LORAx           : LORA结构体
 * @param  *pRead           : 存储LORA数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_ReadData(LORA_TypeDef_Struct *LORAx , LORA_READ_DATA_Struct *pRead);


/**
 * @brief  写入LORA数据
 * @param  *LORAx           : LORA结构体
 * @param  *pWrite          : 存储LORA数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_WriteData(LORA_TypeDef_Struct *LORAx , LORA_WRITE_DATA_Struct *pWrite);


#endif







