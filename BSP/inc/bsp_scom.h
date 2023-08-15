/**
  ******************************************************************************
  * @file    bsp_scom.h
  * @author  LYB
  * @version V1.0.3
  * @date    202/3/31
  * @brief   �����˵ײ�scomͨ�õ������ⲿ�ӿ�
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

#define   SCOM_ENABLE_DEFAULT                ENABLE                         /* Ĭ��SCOM ʹ��       */
#define   SCOM_ENABLE_DMA_DEFAULT            ENABLE                         /* Ĭ��SCOM DMAʹ��    */

#define   SCOM_SCOMPREPRIORINTY_DEFAULT      3                              /* Ĭ��SCOM��ռ���ȼ�  */
#define   SCOM_SCOMSUBPRIORINTY_DEFAULT      3                              /* Ĭ��SCOM�����ȼ�    */
#define   SCOM_DMAPREPRIORINTY_DEFAULT       0                              /* Ĭ��DMA��ռ���ȼ�   */
#define   SCOM_DMASUBPRIORINTY_DEFAULT       0                              /* Ĭ��DMA�����ȼ�     */

#define   SCOM_TX_CALLBACKFUN_DEFAULT        NULL                           /* Ĭ��SCOM TX�ص����� */
#define   SCOM_RX_CALLBACKFUN_DEFAULT        NULL                           /* Ĭ��SCOM RX�ص����� */

#define   SCOM_BAUDRATE_DEFAULT              115200                        /* Ĭ�ϴ��ڲ�����     */
#define   SCOM_PARITY_DEFAULT                USART_Parity_No                /* Ĭ�ϴ���У��λ     */
#define   SCOM_WORDLENGTH_DEFAULT            USART_WordLength_8b            /* Ĭ�ϴ����ֳ�       */
#define   SCOM_STOPBITS_DEFAULT              USART_StopBits_1               /* Ĭ�ϴ���ֹͣλ     */
#define   SCOM_MODE_DEFAULT                  USART_Mode_Rx | USART_Mode_Tx  /* Ĭ�ϴ���ģʽ       */
#define   SCOM_HARDWARE_FLOWCONTROL_DEFAULT  USART_HardwareFlowControl_None /* Ĭ�ϴ���Ӳ�������� */



/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  SCOM �ص���������
  */
typedef void (*SCOM_Callback_Function)(); 


/** 
  * @brief  ���� SCOM �������ݽṹ��
  */
typedef struct __SCOM_READ_DATA_Struct
{  
	 FlagStatus     Fresh;                      /*�������ݸ��±�־*/
	 uint8_t        len;                        /*���ڶ������ݵ���Ч����*/
   uint8_t        data[RX_BUFFER_MAX_SIZE];   /*���ڶ�������*/
}SCOM_READ_DATA_Struct;


/** 
  * @brief  ���� SCOM д�����ݽṹ��
  */
typedef struct __SCOM_WRITE_DATA_Struct
{  
	 uint8_t        len;                         /*����д�����ݵ���Ч����*/
   uint8_t        data[TX_BUFFER_MAX_SIZE];    /*����д������*/
}SCOM_WRITE_DATA_Struct;


/** 
  * @brief  ���� SCOM��RX����ṹ��
  */
typedef struct __SCOM_RX_Buffer_Struct
{  
	 uint8_t        len;                           /*���ڽ��ջ������ݵ���Ч����*/ 
   uint8_t        data[RX_BUFFER_MAX_SIZE];      /*���ڽ��ջ�������*/
}SCOM_RX_Buffer_Struct;


/** 
  * @brief  ���� SCOM��TX����ṹ��
  */
typedef struct __SCOM_TX_Buffer_Struct
{  
	 uint8_t        len;                          /*���ڷ��ͻ������ݵ���Ч����*/ 
   uint8_t        data[TX_BUFFER_MAX_SIZE];     /*���ڷ��ͻ�������*/
}SCOM_TX_Buffer_Struct;


/** 
  * @brief  ���� SCOM���������ݱ�־�ṹ��
  */
typedef struct __SCOM_FrameByte_Struct
{   
	 FlagStatus     FrameByteFresh;            /*�������ݽ������ ��Ч���ݳ��ȸ��±�־*/ 
   uint8_t        FrameByteNum;              /*�������ݽ������ ����֡��Ч���ݳ��� ��λ���ֽ�*/ 
}SCOM_FrameByte_Struct;


/** 
  * @brief  ���� SCOM Ӳ���ṹ��
  */
typedef struct __SCOMHardware_Typedef_Struct
{
    USART_TypeDef              *USARTx;                  /* ����         */
    uint8_t                     USARTx_IRQn;             /* �����ж�ͨ�� */
    GPIO_TypeDef               *TX_GPIO;                 /* TX�˿�       */
    uint16_t                    TX_GPIO_PIN;             /* TX����       */
    GPIO_TypeDef               *RX_GPIO;                 /* RX�˿�       */
    uint16_t                    RX_GPIO_PIN;             /* RX����       */ 
  	
    DMA_Channel_TypeDef        *TX_DMAy_Channelx;        /* DMAͨ��      */
		uint8_t                     TX_DMAy_Channelx_IRQn;	 /* DMA�ж�ͨ��  */
		DMA_Channel_TypeDef        *RX_DMAy_Channelx;        /* DMAͨ��      */
		uint8_t                     RX_DMAy_Channelx_IRQn;	 /* DMA�ж�ͨ��  */
}SCOMHardware_Typedef_Struct;


/** 
  * @brief  ���� SCOM �Ĵ����ṹ��
  */
typedef struct __SCOMRegister_Typedef_Struct
{
    FunctionalState             enable_SCOM;             /* SCOMʹ��     */
    FunctionalState             enable_DMA;              /* DMAʹ��      */
  
    SCOM_TX_Buffer_Struct      *TX_Buffer;               /* TX����       */
    SCOM_RX_Buffer_Struct      *RX_Buffer;			         /* RX����       */
   	FlagStatus                  USART_txAllowFlag;       /* TX�����־   */
    FlagStatus                  USART_rxEndFlag;         /* RX������־   */
  
		USART_InitTypeDef           usartParm;				       /* ��������     */
    SCOM_Callback_Function      TX_callbackFun;	         /* TX�ص�����   */
    SCOM_Callback_Function      RX_callbackFun;      		 /* RX�ص�����   */
//    SCOM_FrameByte_Struct       Frame_Data;	             /* ���ݸ��±�־ */
    
    uint8_t                     SCOM_PrePriorinty;        /* SCOM��ռ���ȼ� */
    uint8_t                     SCOM_SubPriorinty;        /* SCOM�����ȼ�   */
    uint8_t                     DMA_PrePriorinty;         /* DMA��ռ���ȼ�  */
    uint8_t                     DMA_SubPriorinty;         /* DMA�����ȼ�    */
  
}SCOMRegister_Typedef_Struct;


/** 
  * @brief  ���� SCOM �ṹ��
  */
typedef struct __SCOM_TypeDef_Struct
{
    SCOMHardware_Typedef_Struct        SCOM_Hardware;      /* SCOMӲ���ṹ�� */
    SCOMRegister_Typedef_Struct        SCOM_Operating;     /* SCOM���ýṹ�� */
}SCOM_TypeDef_Struct;


/** 
  * @brief  ���� SCOM ��ʼ���Ĵ����ṹ��
  */
typedef struct __SCOM_InitTypedef_Struct
{
  
    FunctionalState                    enable_SCOM;              /* SCOMʹ��     */
    FunctionalState                    enable_DMA;               /* DMAʹ��      */
  
    SCOM_Callback_Function             TX_callbackFun;	         /* TX�ص�����   */
    SCOM_Callback_Function             RX_callbackFun;      		 /* RX�ص�����   */
   
    USART_InitTypeDef                  usartParm;				         /* ��������     */
  
    uint8_t                            SCOM_PrePriorinty;        /* SCOM��ռ���ȼ� */
    uint8_t                            SCOM_SubPriorinty;        /* SCOM�����ȼ�   */
    uint8_t                            DMA_PrePriorinty;         /* DMA��ռ���ȼ�  */
    uint8_t                            DMA_SubPriorinty;         /* DMA�����ȼ�    */
  
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
 * @brief  ��ʼ��SCOM�ṹ��Ĭ������
 * @param  SCOM_InitStruct : SCOM��ʼ���ṹ��
 */
void BSP_SCOM_InitStruct(SCOM_InitTypedef_Struct *SCOM_InitStruct);


/**
 * @brief  ��ʼ��SCOM�ṹ��
 * @param  *SCOMx            : SCOM�ṹ��
 *         *SCOM_InitStruct  : SCOM��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SCOM_Init(SCOM_TypeDef_Struct *SCOMx , SCOM_InitTypedef_Struct *SCOM_InitStruct);

/**
 * @brief  ʹ��SCOM
 * @param  *SCOMx           : SCOM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_Open(SCOM_TypeDef_Struct *SCOMx);


/**
 * @brief  ʧ��SCOM
 * @param  *SCOMx           : SCOM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_Close(SCOM_TypeDef_Struct *SCOMx);


/**
 * @brief  ��ȡSCOM����
 * @param  *SCOMx           : SCOM�ṹ��
 * @param  *pRead           : �洢SCOM���ݽṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_ReadData(SCOM_TypeDef_Struct *SCOMx , SCOM_READ_DATA_Struct *pRead);


/**
 * @brief  д��SCOM����
 * @param  *SCOMx           : SCOM�ṹ��
 * @param  *pWrite          : �洢SCOM���ݽṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_WriteData(SCOM_TypeDef_Struct *SCOMx , SCOM_WRITE_DATA_Struct *pWrite);


///**
// * @brief  �Ӵ��ڶ�ȡһ֡���ݵ���Ч���ȣ���λ:�ֽ�                 
// * @param  *SCOMx           : SCOM�ṹ��
// * @param  FrameByteNum     : �洢ȡ�ص�һ֡�������ݳ��� 
// * @return ErrorStatus: ERROR or SUCCESS   
// */
//ErrorStatus SCOM_Read_FrameByteNum(SCOM_TypeDef_Struct*SCOMx , SCOM_FrameByte_Struct* FrameByteNum);


/**
 * @brief  SCOM�����жϷ�����
 * @param  *SCOMx           : SCOM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_USART_IRQHandler(SCOM_TypeDef_Struct* SCOMx);


/**
 * @brief  SCOM���ڷ���DMA�жϷ�����
 * @param  *SCOMx           : SCOM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus	SCOM_TX_DMA_IRQHandler(SCOM_TypeDef_Struct *SCOMx);	



#endif







