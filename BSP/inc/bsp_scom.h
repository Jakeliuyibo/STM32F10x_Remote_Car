/**
  ******************************************************************************
  * @file    bsp_scom.h
  * @author  LYB
  * @version V1.0.3
  * @date    202/3/31
  * @brief   描述了底层scom通用的驱动外部接口
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_SCOM_H
#define __BSP_SCOM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_usart.h"
#include "string.h"

/* Defitions -----------------------------------------------------------------*/
#define   RX_BUFFER_MAX_SIZE                 32
#define   TX_BUFFER_MAX_SIZE                 32	

#define   SCOM_ENABLE_DEFAULT                ENABLE                         /* 默认SCOM 使能       */
#define   SCOM_ENABLE_DMA_DEFAULT            ENABLE                         /* 默认SCOM DMA使能    */

#define   SCOM_SCOMPREPRIORINTY_DEFAULT      3                              /* 默认SCOM抢占优先级  */
#define   SCOM_SCOMSUBPRIORINTY_DEFAULT      3                              /* 默认SCOM子优先级    */
#define   SCOM_DMAPREPRIORINTY_DEFAULT       0                              /* 默认DMA抢占优先级   */
#define   SCOM_DMASUBPRIORINTY_DEFAULT       0                              /* 默认DMA子优先级     */

#define   SCOM_TX_CALLBACKFUN_DEFAULT        NULL                           /* 默认SCOM TX回调函数 */
#define   SCOM_RX_CALLBACKFUN_DEFAULT        NULL                           /* 默认SCOM RX回调函数 */

#define   SCOM_BAUDRATE_DEFAULT              115200                        /* 默认串口波特率     */
#define   SCOM_PARITY_DEFAULT                USART_Parity_No                /* 默认串口校验位     */
#define   SCOM_WORDLENGTH_DEFAULT            USART_WordLength_8b            /* 默认串口字长       */
#define   SCOM_STOPBITS_DEFAULT              USART_StopBits_1               /* 默认串口停止位     */
#define   SCOM_MODE_DEFAULT                  USART_Mode_Rx | USART_Mode_Tx  /* 默认串口模式       */
#define   SCOM_HARDWARE_FLOWCONTROL_DEFAULT  USART_HardwareFlowControl_None /* 默认串口硬件控制流 */



/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  SCOM 回调函数声明
  */
typedef void (*SCOM_Callback_Function)(); 


/** 
  * @brief  定义 SCOM 读出数据结构体
  */
typedef struct __SCOM_READ_DATA_Struct
{  
	 FlagStatus     Fresh;                      /*接收数据更新标志*/
	 uint8_t        len;                        /*串口读入数据的有效长度*/
   uint8_t        data[RX_BUFFER_MAX_SIZE];   /*串口读入数据*/
}SCOM_READ_DATA_Struct;


/** 
  * @brief  定义 SCOM 写入数据结构体
  */
typedef struct __SCOM_WRITE_DATA_Struct
{  
	 uint8_t        len;                         /*串口写入数据的有效长度*/
   uint8_t        data[TX_BUFFER_MAX_SIZE];    /*串口写入数据*/
}SCOM_WRITE_DATA_Struct;


/** 
  * @brief  定义 SCOM，RX缓存结构体
  */
typedef struct __SCOM_RX_Buffer_Struct
{  
	 uint8_t        len;                           /*串口接收缓存数据的有效长度*/ 
   uint8_t        data[RX_BUFFER_MAX_SIZE];      /*串口接收缓存数据*/
}SCOM_RX_Buffer_Struct;


/** 
  * @brief  定义 SCOM，TX缓存结构体
  */
typedef struct __SCOM_TX_Buffer_Struct
{  
	 uint8_t        len;                          /*串口发送缓存数据的有效长度*/ 
   uint8_t        data[TX_BUFFER_MAX_SIZE];     /*串口发送缓存数据*/
}SCOM_TX_Buffer_Struct;


/** 
  * @brief  定义 SCOM，接受数据标志结构体
  */
typedef struct __SCOM_FrameByte_Struct
{   
	 FlagStatus     FrameByteFresh;            /*串口数据接收完毕 有效数据长度更新标志*/ 
   uint8_t        FrameByteNum;              /*串口数据接收完毕 数据帧有效数据长度 单位：字节*/ 
}SCOM_FrameByte_Struct;


/** 
  * @brief  定义 SCOM 硬件结构体
  */
typedef struct __SCOMHardware_Typedef_Struct
{
    USART_TypeDef              *USARTx;                  /* 串口         */
    uint8_t                     USARTx_IRQn;             /* 串口中断通道 */
    GPIO_TypeDef               *TX_GPIO;                 /* TX端口       */
    uint16_t                    TX_GPIO_PIN;             /* TX引脚       */
    GPIO_TypeDef               *RX_GPIO;                 /* RX端口       */
    uint16_t                    RX_GPIO_PIN;             /* RX引脚       */ 
  	
    DMA_Channel_TypeDef        *TX_DMAy_Channelx;        /* DMA通道      */
		uint8_t                     TX_DMAy_Channelx_IRQn;	 /* DMA中断通道  */
		DMA_Channel_TypeDef        *RX_DMAy_Channelx;        /* DMA通道      */
		uint8_t                     RX_DMAy_Channelx_IRQn;	 /* DMA中断通道  */
}SCOMHardware_Typedef_Struct;


/** 
  * @brief  定义 SCOM 寄存器结构体
  */
typedef struct __SCOMRegister_Typedef_Struct
{
    FunctionalState             enable_SCOM;             /* SCOM使能     */
    FunctionalState             enable_DMA;              /* DMA使能      */
  
    SCOM_TX_Buffer_Struct      *TX_Buffer;               /* TX缓存       */
    SCOM_RX_Buffer_Struct      *RX_Buffer;			         /* RX缓存       */
   	FlagStatus                  USART_txAllowFlag;       /* TX允许标志   */
    FlagStatus                  USART_rxEndFlag;         /* RX结束标志   */
  
		USART_InitTypeDef           usartParm;				       /* 串口配置     */
    SCOM_Callback_Function      TX_callbackFun;	         /* TX回调函数   */
    SCOM_Callback_Function      RX_callbackFun;      		 /* RX回调函数   */
//    SCOM_FrameByte_Struct       Frame_Data;	             /* 数据更新标志 */
    
    uint8_t                     SCOM_PrePriorinty;        /* SCOM抢占优先级 */
    uint8_t                     SCOM_SubPriorinty;        /* SCOM子优先级   */
    uint8_t                     DMA_PrePriorinty;         /* DMA抢占优先级  */
    uint8_t                     DMA_SubPriorinty;         /* DMA子优先级    */
  
}SCOMRegister_Typedef_Struct;


/** 
  * @brief  定义 SCOM 结构体
  */
typedef struct __SCOM_TypeDef_Struct
{
    SCOMHardware_Typedef_Struct        SCOM_Hardware;      /* SCOM硬件结构体 */
    SCOMRegister_Typedef_Struct        SCOM_Operating;     /* SCOM配置结构体 */
}SCOM_TypeDef_Struct;


/** 
  * @brief  定义 SCOM 初始化寄存器结构体
  */
typedef struct __SCOM_InitTypedef_Struct
{
  
    FunctionalState                    enable_SCOM;              /* SCOM使能     */
    FunctionalState                    enable_DMA;               /* DMA使能      */
  
    SCOM_Callback_Function             TX_callbackFun;	         /* TX回调函数   */
    SCOM_Callback_Function             RX_callbackFun;      		 /* RX回调函数   */
   
    USART_InitTypeDef                  usartParm;				         /* 串口配置     */
  
    uint8_t                            SCOM_PrePriorinty;        /* SCOM抢占优先级 */
    uint8_t                            SCOM_SubPriorinty;        /* SCOM子优先级   */
    uint8_t                            DMA_PrePriorinty;         /* DMA抢占优先级  */
    uint8_t                            DMA_SubPriorinty;         /* DMA子优先级    */
  
}SCOM_InitTypedef_Struct;


/* SCOM BASE -----------------------------------------------------------------*/

extern SCOM_TypeDef_Struct             SCOM1_BASE;
#define SCOM1                          (&SCOM1_BASE  )     /* SCOM1 selected */
#define SCOM1_USART                    (USART3       )
#define SCOM1_USART_IRQn		           39  
#define SCOM1_TX_GPIO                  (GPIOB        )
#define SCOM1_TX_GPIO_Pin	             (GPIO_Pin_10  )
#define SCOM1_RX_GPIO                  (GPIOB        )
#define SCOM1_RX_GPIO_Pin              (GPIO_Pin_11  )
#define SCOM1_TX_DMA_Channel           (DMA1_Channel2)
#define SCOM1_TX_DMA_Channel_IRQn      12    
#define SCOM1_RX_DMA_Channel           (DMA1_Channel3)
#define SCOM1_RX_DMA_Channel_IRQn      13  	
      

extern SCOM_TypeDef_Struct             SCOM2_BASE;
#define SCOM2                          (&SCOM2_BASE  )      /* SCOM2 selected */
#define SCOM2_USART                    (USART2       )
#define SCOM2_USART_IRQn		           38   
#define SCOM2_TX_GPIO                  (GPIOA        )
#define SCOM2_TX_GPIO_Pin	             (GPIO_Pin_2   )
#define SCOM2_RX_GPIO                  (GPIOA        )
#define SCOM2_RX_GPIO_Pin              (GPIO_Pin_3   )
#define SCOM2_TX_DMA_Channel           (DMA1_Channel7)
#define SCOM2_TX_DMA_Channel_IRQn      17  
#define SCOM2_RX_DMA_Channel           (DMA1_Channel6)
#define SCOM2_RX_DMA_Channel_IRQn      16  	


extern SCOM_TypeDef_Struct             SCOM3_BASE;
#define SCOM3                          (&SCOM3_BASE  )      /* SCOM3 selected */
#define SCOM3_USART                    (USART1       )
#define SCOM3_USART_IRQn		           37  
#define SCOM3_TX_GPIO                  (GPIOA        )
#define SCOM3_TX_GPIO_Pin	             (GPIO_Pin_9   )
#define SCOM3_RX_GPIO                  (GPIOA        )
#define SCOM3_RX_GPIO_Pin              (GPIO_Pin_10  )
#define SCOM3_TX_DMA_Channel           (DMA1_Channel4)
#define SCOM3_TX_DMA_Channel_IRQn      14  
#define SCOM3_RX_DMA_Channel           (DMA1_Channel5)
#define SCOM3_RX_DMA_Channel_IRQn      15  	


/* Interface declaration -----------------------------------------------------*/

/**
 * @brief  初始化SCOM结构体默认配置
 * @param  SCOM_InitStruct : SCOM初始化结构体
 */
void BSP_SCOM_InitStruct(SCOM_InitTypedef_Struct *SCOM_InitStruct);


/**
 * @brief  初始化SCOM结构体
 * @param  *SCOMx            : SCOM结构体
 *         *SCOM_InitStruct  : SCOM初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SCOM_Init(SCOM_TypeDef_Struct *SCOMx , SCOM_InitTypedef_Struct *SCOM_InitStruct);

/**
 * @brief  使能SCOM
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_Open(SCOM_TypeDef_Struct *SCOMx);


/**
 * @brief  失能SCOM
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_Close(SCOM_TypeDef_Struct *SCOMx);


/**
 * @brief  读取SCOM数据
 * @param  *SCOMx           : SCOM结构体
 * @param  *pRead           : 存储SCOM数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_ReadData(SCOM_TypeDef_Struct *SCOMx , SCOM_READ_DATA_Struct *pRead);


/**
 * @brief  写入SCOM数据
 * @param  *SCOMx           : SCOM结构体
 * @param  *pWrite          : 存储SCOM数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_WriteData(SCOM_TypeDef_Struct *SCOMx , SCOM_WRITE_DATA_Struct *pWrite);


///**
// * @brief  从串口读取一帧数据的有效长度，单位:字节                 
// * @param  *SCOMx           : SCOM结构体
// * @param  FrameByteNum     : 存储取回的一帧串口数据长度 
// * @return ErrorStatus: ERROR or SUCCESS   
// */
//ErrorStatus SCOM_Read_FrameByteNum(SCOM_TypeDef_Struct*SCOMx , SCOM_FrameByte_Struct* FrameByteNum);


/**
 * @brief  SCOM串口中断服务函数
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_USART_IRQHandler(SCOM_TypeDef_Struct* SCOMx);


/**
 * @brief  SCOM串口发送DMA中断服务函数
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus	SCOM_TX_DMA_IRQHandler(SCOM_TypeDef_Struct *SCOMx);	



#endif







