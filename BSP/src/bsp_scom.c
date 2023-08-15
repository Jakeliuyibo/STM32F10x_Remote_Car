/**
  ******************************************************************************
  * @file    bsp_scom.c
  * @author  LYB
  * @version V1.0.3
  * @date    202/5/17
  * @brief   描述了底层SCOM设备的驱动实现
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_scom.h"




/* Global variable -----------------------------------------------------------*/



/* Struct base ---------------------------------------------------------------*/
SCOM_TypeDef_Struct SCOM1_BASE,SCOM2_BASE,SCOM3_BASE;


/* Interrupt variable --------------------------------------------------------*/
static  uint32_t           __SCOM_CPU_PRIMASK_REG_SAVE_VALUE;


	
/* Cache declaration ---------------------------------------------------------*/
SCOM_RX_Buffer_Struct      SCOM1_RXDataBuffer;
SCOM_TX_Buffer_Struct      SCOM1_TXDataBuffer;

SCOM_RX_Buffer_Struct      SCOM2_RXDataBuffer;
SCOM_TX_Buffer_Struct      SCOM2_TXDataBuffer;

SCOM_RX_Buffer_Struct      SCOM3_RXDataBuffer;
SCOM_TX_Buffer_Struct      SCOM3_TXDataBuffer;




/* Private functions declaration----------------------------------------------*/
static __INLINE void __SCOM_Disable_IRQ(void);
static __INLINE void __SCOM_Restore_IRQ(void);

ErrorStatus BSP_SCOM_RCC_Config(SCOM_TypeDef_Struct *SCOMx);
ErrorStatus BSP_SCOM_GPIO_Config(SCOM_TypeDef_Struct *SCOMx);
void BSP_SCOM_DMA_Config(SCOM_TypeDef_Struct *SCOMx);
void BSP_SCOM_NVIC_Config(SCOM_TypeDef_Struct *SCOMx);
ErrorStatus SCOM_USART_SendData(SCOM_TypeDef_Struct *SCOMx);




/* Public functions ----------------------------------------------------------*/



/**
 * @brief  初始化SCOM结构体默认配置
 * @param  SCOM_InitStruct : LORA初始化结构体
 */
void BSP_SCOM_InitStruct(SCOM_InitTypedef_Struct *SCOM_InitStruct)
{ 
    SCOM_InitStruct->enable_SCOM = SCOM_ENABLE_DEFAULT    ;       /* SCOM     默认使能     */
    SCOM_InitStruct->enable_DMA  = SCOM_ENABLE_DMA_DEFAULT;       /* SCOM DMA 默认使能     */
  
    /*  SCOM 串口默认配置参数   */
    SCOM_InitStruct->usartParm.USART_BaudRate             =  SCOM_BAUDRATE_DEFAULT  ;
    SCOM_InitStruct->usartParm.USART_Parity               =  SCOM_PARITY_DEFAULT    ;
    SCOM_InitStruct->usartParm.USART_WordLength           =  SCOM_WORDLENGTH_DEFAULT;
    SCOM_InitStruct->usartParm.USART_StopBits             =  SCOM_STOPBITS_DEFAULT  ;
    SCOM_InitStruct->usartParm.USART_Mode                 =  SCOM_MODE_DEFAULT      ;
    SCOM_InitStruct->usartParm.USART_HardwareFlowControl  =  SCOM_HARDWARE_FLOWCONTROL_DEFAULT;
    
    SCOM_InitStruct->SCOM_PrePriorinty = SCOM_SCOMPREPRIORINTY_DEFAULT;     /* SCOM 默认抢占优先级  */
    SCOM_InitStruct->SCOM_SubPriorinty = SCOM_SCOMSUBPRIORINTY_DEFAULT;     /* SCOM 默认子优先级    */
    SCOM_InitStruct->DMA_PrePriorinty  = SCOM_DMAPREPRIORINTY_DEFAULT ;     /* DMA  默认抢占优先级  */
    SCOM_InitStruct->DMA_SubPriorinty  = SCOM_DMASUBPRIORINTY_DEFAULT ;     /* DMA  默认子优先级    */
   
    SCOM_InitStruct->TX_callbackFun = SCOM_TX_CALLBACKFUN_DEFAULT;          /* SCOM TX 默认回调函数 */
    SCOM_InitStruct->RX_callbackFun = SCOM_RX_CALLBACKFUN_DEFAULT;          /* SCOM RX 默认回调函数 */
}




/**
 * @brief  初始化SCOM结构体
 * @param  *SCOMx            : SCOM结构体
 *         *SCOM_InitStruct  : SCOM初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SCOM_Init(SCOM_TypeDef_Struct *SCOMx , SCOM_InitTypedef_Struct *SCOM_InitStruct)
{
    if ( (SCOMx == NULL) || (SCOM_InitStruct == NULL) )
    {
        return ERROR;
    }
    
    /*  SCOM 使能      */
    SCOMx->SCOM_Operating.enable_SCOM = SCOM_InitStruct->enable_SCOM ;
      
    /*  SCOM 硬件和RX TX缓存区指明  */
    if (SCOMx == SCOM1)
    {
        SCOM1_BASE.SCOM_Hardware.USARTx      = SCOM1_USART       ;
        SCOM1_BASE.SCOM_Hardware.USARTx_IRQn = SCOM1_USART_IRQn  ;
        SCOM1_BASE.SCOM_Hardware.TX_GPIO     = SCOM1_TX_GPIO     ;
        SCOM1_BASE.SCOM_Hardware.TX_GPIO_PIN = SCOM1_TX_GPIO_Pin ;
        SCOM1_BASE.SCOM_Hardware.RX_GPIO     = SCOM1_RX_GPIO     ;
        SCOM1_BASE.SCOM_Hardware.RX_GPIO_PIN = SCOM1_RX_GPIO_Pin ;
        SCOM1_BASE.SCOM_Hardware.TX_DMAy_Channelx      = SCOM1_TX_DMA_Channel     ;
        SCOM1_BASE.SCOM_Hardware.TX_DMAy_Channelx_IRQn = SCOM1_TX_DMA_Channel_IRQn;
        SCOM1_BASE.SCOM_Hardware.RX_DMAy_Channelx      = SCOM1_RX_DMA_Channel     ;
        SCOM1_BASE.SCOM_Hardware.RX_DMAy_Channelx_IRQn = SCOM1_RX_DMA_Channel_IRQn;
      
        SCOMx->SCOM_Operating.RX_Buffer = &SCOM1_RXDataBuffer;
        SCOMx->SCOM_Operating.TX_Buffer = &SCOM1_TXDataBuffer; 
    }
    else if (SCOMx == SCOM2)
    {
        SCOM2_BASE.SCOM_Hardware.USARTx      = SCOM2_USART       ;
        SCOM2_BASE.SCOM_Hardware.USARTx_IRQn = SCOM2_USART_IRQn  ;
        SCOM2_BASE.SCOM_Hardware.TX_GPIO     = SCOM2_TX_GPIO     ;
        SCOM2_BASE.SCOM_Hardware.TX_GPIO_PIN = SCOM2_TX_GPIO_Pin ;
        SCOM2_BASE.SCOM_Hardware.RX_GPIO     = SCOM2_RX_GPIO     ;
        SCOM2_BASE.SCOM_Hardware.RX_GPIO_PIN = SCOM2_RX_GPIO_Pin ;
        SCOM2_BASE.SCOM_Hardware.TX_DMAy_Channelx      = SCOM2_TX_DMA_Channel     ;
        SCOM2_BASE.SCOM_Hardware.TX_DMAy_Channelx_IRQn = SCOM2_TX_DMA_Channel_IRQn;
        SCOM2_BASE.SCOM_Hardware.RX_DMAy_Channelx      = SCOM2_RX_DMA_Channel     ;
        SCOM2_BASE.SCOM_Hardware.RX_DMAy_Channelx_IRQn = SCOM2_RX_DMA_Channel_IRQn;
      
        SCOMx->SCOM_Operating.RX_Buffer = &SCOM2_RXDataBuffer;
        SCOMx->SCOM_Operating.TX_Buffer = &SCOM2_TXDataBuffer; 
    }
    else if (SCOMx == SCOM3)
    {
        SCOM3_BASE.SCOM_Hardware.USARTx      = SCOM3_USART       ;
        SCOM3_BASE.SCOM_Hardware.USARTx_IRQn = SCOM3_USART_IRQn  ;
        SCOM3_BASE.SCOM_Hardware.TX_GPIO     = SCOM3_TX_GPIO     ;
        SCOM3_BASE.SCOM_Hardware.TX_GPIO_PIN = SCOM3_TX_GPIO_Pin ;
        SCOM3_BASE.SCOM_Hardware.RX_GPIO     = SCOM3_RX_GPIO     ;
        SCOM3_BASE.SCOM_Hardware.RX_GPIO_PIN = SCOM3_RX_GPIO_Pin ;
        SCOM3_BASE.SCOM_Hardware.TX_DMAy_Channelx      = SCOM3_TX_DMA_Channel     ;
        SCOM3_BASE.SCOM_Hardware.TX_DMAy_Channelx_IRQn = SCOM3_TX_DMA_Channel_IRQn;
        SCOM3_BASE.SCOM_Hardware.RX_DMAy_Channelx      = SCOM3_RX_DMA_Channel     ;
        SCOM3_BASE.SCOM_Hardware.RX_DMAy_Channelx_IRQn = SCOM3_RX_DMA_Channel_IRQn;
      
        SCOMx->SCOM_Operating.RX_Buffer = &SCOM3_RXDataBuffer;
        SCOMx->SCOM_Operating.TX_Buffer = &SCOM3_TXDataBuffer; 
    }
    else 
    {
        return ERROR;
    }

    /*  SCOM DMA使能   */
    if ( (SCOMx->SCOM_Hardware.TX_DMAy_Channelx == NULL) || (SCOMx->SCOM_Hardware.RX_DMAy_Channelx == NULL) )
    {
        SCOMx->SCOM_Operating.enable_DMA = DISABLE;
    }
		else
    {
        SCOMx->SCOM_Operating.enable_DMA = SCOM_InitStruct->enable_DMA;
    }
    
    
    /*  SCOM 数据缓存器操作      */
    SCOMx->SCOM_Operating.RX_Buffer->len              =  0    ;
    SCOMx->SCOM_Operating.USART_txAllowFlag           =  SET  ;
    SCOMx->SCOM_Operating.USART_rxEndFlag             =  RESET; 
    
//    /*  SCOM 数据帧赋值          */
//		SCOMx->SCOM_Operating.Frame_Data.FrameByteFresh   =  RESET;
//		SCOMx->SCOM_Operating.Frame_Data.FrameByteNum     =  0    ;	

    /*  SCOM 回调函数赋值        */
    SCOMx->SCOM_Operating.TX_callbackFun              =  SCOM_InitStruct->TX_callbackFun;
		SCOMx->SCOM_Operating.RX_callbackFun              =  SCOM_InitStruct->RX_callbackFun;
  
    /*  SCOM 串口 寄存器赋值     */
    SCOMx->SCOM_Operating.usartParm.USART_BaudRate    =  SCOM_InitStruct->usartParm.USART_BaudRate   ;
    SCOMx->SCOM_Operating.usartParm.USART_Parity      =  SCOM_InitStruct->usartParm.USART_Parity     ;
    SCOMx->SCOM_Operating.usartParm.USART_WordLength  =  SCOM_InitStruct->usartParm.USART_WordLength ;     
    SCOMx->SCOM_Operating.usartParm.USART_StopBits    =  SCOM_InitStruct->usartParm.USART_StopBits   ;     
    SCOMx->SCOM_Operating.usartParm.USART_Mode        =  SCOM_InitStruct->usartParm.USART_Mode       ;      
    SCOMx->SCOM_Operating.usartParm.USART_HardwareFlowControl = SCOM_InitStruct->usartParm.USART_HardwareFlowControl;
    
    /*  SCOM DMA 中断优先级赋值  */
    SCOMx->SCOM_Operating.SCOM_PrePriorinty = SCOM_InitStruct->SCOM_PrePriorinty;
    SCOMx->SCOM_Operating.SCOM_SubPriorinty = SCOM_InitStruct->SCOM_SubPriorinty;
    SCOMx->SCOM_Operating.DMA_PrePriorinty  = SCOM_InitStruct->DMA_PrePriorinty ;
    SCOMx->SCOM_Operating.DMA_SubPriorinty  = SCOM_InitStruct->DMA_SubPriorinty ;
    
    /*  初始化SCOM GPIO RCC 时钟 */
    if ( BSP_SCOM_RCC_Config(SCOMx) == ERROR )
    {
        return ERROR;
    } 
    
    /*  初始化SCOM GPIO  */
    if ( BSP_SCOM_GPIO_Config(SCOMx) == ERROR )
    {
        return ERROR;
    } 

    /*  初始化USART       */
    USART_Init(SCOMx->SCOM_Hardware.USARTx , &SCOMx->SCOM_Operating.usartParm);
    
    /*  SCOM DMA中断设置  */
    if ( SCOMx->SCOM_Operating.enable_DMA == DISABLE )
		{
				USART_ITConfig(SCOMx->SCOM_Hardware.USARTx , USART_IT_RXNE , ENABLE);
  			USART_ITConfig(SCOMx->SCOM_Hardware.USARTx , USART_IT_TC , ENABLE); 			
		}
		else
		{         
        if ( (SCOMx->SCOM_Hardware.RX_DMAy_Channelx != NULL) & (SCOMx->SCOM_Hardware.TX_DMAy_Channelx != NULL) )
        {
            USART_DMACmd(SCOMx->SCOM_Hardware.USARTx , USART_DMAReq_Rx | USART_DMAReq_Tx , ENABLE);
        }          
		}
    
    /*  使能  USART 中断      */
    USART_ITConfig(SCOMx->SCOM_Hardware.USARTx , USART_IT_IDLE , ENABLE);
    
    /*  初始化 SCOM DMA  配置 */
    BSP_SCOM_DMA_Config(SCOMx);
    
    /*  初始化 SCOM NVIC 中断 */   
    BSP_SCOM_NVIC_Config(SCOMx);
    
    /*  使能SCOM DMA RX TX    */
    if (  (SCOMx->SCOM_Hardware.RX_DMAy_Channelx != NULL) 
        & (SCOMx->SCOM_Hardware.TX_DMAy_Channelx != NULL)  )
		{
	      if (SCOMx->SCOM_Operating.enable_DMA == ENABLE)
			  {
			      DMA_Cmd(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , ENABLE);		
			      DMA_Cmd(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , ENABLE);			
			  }
			  else 
			  {
			      DMA_Cmd(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , DISABLE);		
			      DMA_Cmd(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , DISABLE);			
			  }
	  }
    
		USART_Cmd(SCOMx->SCOM_Hardware.USARTx , ENABLE);	
		USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx , USART_FLAG_TC);

		return SUCCESS;
}



/**
 * @brief  读取SCOM数据
 * @param  *SCOMx           : SCOM结构体
 * @param  *pRead           : 存储SCOM数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_ReadData(SCOM_TypeDef_Struct *SCOMx , SCOM_READ_DATA_Struct *pRead)
{
    if ( (SCOMx == NULL) || (pRead == NULL) )
    {
        return ERROR;
    }
    
    if (SCOMx->SCOM_Operating.USART_rxEndFlag == SET)
    {
      
        if (SCOM1 == SCOMx)
        {
            __SCOM_Disable_IRQ();
            pRead->Fresh = SET;                                           /* 更新标志位 */
            pRead->len = SCOM1_RXDataBuffer.len;
            memcpy(pRead->data , SCOM1_RXDataBuffer.data , pRead->len);
            SCOMx->SCOM_Operating.USART_rxEndFlag = RESET;
            __SCOM_Restore_IRQ();
        }
        else if (SCOM2 == SCOMx)
        {
            __SCOM_Disable_IRQ();
            pRead->Fresh = SET;                                           /* 更新标志位 */
            pRead->len = SCOM2_RXDataBuffer.len;
            memcpy(pRead->data , SCOM2_RXDataBuffer.data , pRead->len);
            SCOMx->SCOM_Operating.USART_rxEndFlag = RESET;
            __SCOM_Restore_IRQ();
        }
        else if (SCOM3 == SCOMx)
        {
            __SCOM_Disable_IRQ();
            pRead->Fresh = SET;                                           /* 更新标志位 */
            pRead->len = SCOM3_RXDataBuffer.len;
            memcpy(pRead->data , SCOM3_RXDataBuffer.data , pRead->len);
            SCOMx->SCOM_Operating.USART_rxEndFlag = RESET;
            __SCOM_Restore_IRQ();
        }
        else
        {
            return ERROR;
        }
    }
    else
    {
        return ERROR;
    }
    
    return SUCCESS;
}




/**
 * @brief  写入SCOM数据
 * @param  *SCOMx           : SCOM结构体
 * @param  *pWrite          : 存储SCOM数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_WriteData(SCOM_TypeDef_Struct *SCOMx , SCOM_WRITE_DATA_Struct *pWrite)
{
    if ( (SCOMx == NULL) || (pWrite == NULL) )
    {
        return ERROR;
    }
    
    SCOMx->SCOM_Operating.TX_Buffer->len = pWrite->len;
    memcpy(SCOMx->SCOM_Operating.TX_Buffer->data , pWrite->data , pWrite->len);
    
    /* 检测TX允许发送标志位     */
		if (SCOMx->SCOM_Operating.USART_txAllowFlag == SET)	
    {
        /* 清除TX允许发送标志位 */
        SCOMx->SCOM_Operating.USART_txAllowFlag = RESET;	
      
        if(SCOMx->SCOM_Operating.enable_DMA == ENABLE) /*  DMA模式下，DMA发送数据   */ 
        {  		
            DMA_Cmd(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , DISABLE);
            DMA_SetCurrDataCounter(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , (uint16_t)SCOMx->SCOM_Operating.TX_Buffer->len);
            DMA_Cmd(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , ENABLE);									
        }
        else                                           /*  非DMA模式下，发送数据   */ 
        {
			
            SCOM_USART_SendData(SCOMx);		
        }
    
    }
    else 
    {
        return ERROR;
    }

    
    return SUCCESS;
}



/**  
 * @brief  使能 SCOM
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_Open(SCOM_TypeDef_Struct *SCOMx)
{
    if (SCOMx == NULL)
    {
        return ERROR; 
    }

    USART_Cmd(SCOMx->SCOM_Hardware.USARTx , ENABLE);
	
    if (   (SCOMx->SCOM_Hardware.RX_DMAy_Channelx != NULL) 
        && (SCOMx->SCOM_Hardware.TX_DMAy_Channelx != NULL)
	      && (SCOMx->SCOM_Operating.enable_DMA != DISABLE   ) )
    {
        DMA_Cmd(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , ENABLE);	
        DMA_Cmd(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , ENABLE);
    }

	 return SUCCESS;
}


/**
 * @brief  失能 SCOM
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_Close(SCOM_TypeDef_Struct *SCOMx)
{
    if (SCOMx == NULL)
    {
        return ERROR; 
    }
   
    USART_Cmd(SCOMx->SCOM_Hardware.USARTx , DISABLE);
		
		if (SCOMx->SCOM_Operating.enable_DMA == ENABLE)
		{
        DMA_Cmd(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , DISABLE);				
        DMA_Cmd(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , DISABLE);
		}
    
	  return SUCCESS;
}




/* Interrupt functions -------------------------------------------------------*/


/**
 * @brief  SCOM 串口中断服务函数
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SCOM_USART_IRQHandler(SCOM_TypeDef_Struct *SCOMx)
{
		static	uint8_t SCOM1_ByteNum  = 0;
		static	uint8_t SCOM2_ByteNum  = 0;
		static	uint8_t SCOM3_ByteNum  = 0;
	  uint16_t        clear;
	
    if(SCOMx == NULL)
    {
        return ERROR; 
    }
    
			
    /* 未使能DMA */
    if(SCOMx->SCOM_Operating.enable_DMA != ENABLE )
    {
    
        /*  USART串口 接收完成中断标注位  */ 
        if(USART_GetFlagStatus(SCOMx->SCOM_Hardware.USARTx ,USART_IT_RXNE) == SET)
        {
            if(SCOMx == SCOM1)
            {	
                SCOMx->SCOM_Operating.RX_Buffer->data[SCOM1_ByteNum] = USART_ReceiveData(SCOMx->SCOM_Hardware.USARTx);
                USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_IT_RXNE);   /* TCIE,TE,RE */
                SCOM1_ByteNum++;
            }
            else if(SCOMx == SCOM2)
            {	
                SCOMx->SCOM_Operating.RX_Buffer->data[SCOM2_ByteNum] = USART_ReceiveData(SCOMx->SCOM_Hardware.USARTx);
                USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_IT_RXNE);   /* TCIE,TE,RE */
                SCOM2_ByteNum++;
            }
            else if(SCOMx == SCOM3)
            {	
                SCOMx->SCOM_Operating.RX_Buffer->data[SCOM3_ByteNum] = USART_ReceiveData(SCOMx->SCOM_Hardware.USARTx);
                USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx,USART_IT_RXNE);   /* TCIE,TE,RE */
                SCOM3_ByteNum++;
            }
        }
    
    
        /*  USART串口发送完成标志位 */ 
        if(USART_GetFlagStatus(SCOMx->SCOM_Hardware.USARTx , USART_FLAG_TC) == SET)
        {
            USART_ClearFlag(SCOMx->SCOM_Hardware.USARTx , USART_FLAG_TC);    /* TCIE,TE,RE */
            SCOM_USART_SendData(SCOMx);
        }

    }


    if(USART_GetFlagStatus(SCOMx->SCOM_Hardware.USARTx,USART_FLAG_IDLE) == SET)	
		{ 
//        SCOMx->SCOM_Operating.Frame_Data.FrameByteFresh = SET;
			  SCOMx->SCOM_Operating.USART_rxEndFlag           = SET;
				if(SCOMx->SCOM_Operating.enable_DMA == ENABLE)
				{
            DMA_Cmd(SCOMx->SCOM_Hardware.RX_DMAy_Channelx,DISABLE);

            if(SCOMx == SCOM1)
            {
                SCOM1_ByteNum = RX_BUFFER_MAX_SIZE - DMA_GetCurrDataCounter(SCOMx->SCOM_Hardware.RX_DMAy_Channelx);
            }					
            else if(SCOMx == SCOM2)
            {
                SCOM2_ByteNum = RX_BUFFER_MAX_SIZE - DMA_GetCurrDataCounter(SCOMx->SCOM_Hardware.RX_DMAy_Channelx);
            }
            else if(SCOMx == SCOM3)
            {
                SCOM3_ByteNum = RX_BUFFER_MAX_SIZE - DMA_GetCurrDataCounter(SCOMx->SCOM_Hardware.RX_DMAy_Channelx);
            }

            SCOMx->SCOM_Hardware.RX_DMAy_Channelx->CMAR =(u32) (SCOMx->SCOM_Operating.RX_Buffer->data);  
            DMA_SetCurrDataCounter(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , RX_BUFFER_MAX_SIZE);
            DMA_Cmd(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , ENABLE);
        }			
						
			  if (SCOMx == SCOM1)
				{
//            SCOM1_BASE.SCOM_Operating.Frame_Data.FrameByteNum  = SCOM1_ByteNum;
            SCOM1_RXDataBuffer.len                             = SCOM1_ByteNum;
            SCOM1_ByteNum = 0 ;
        }					
				else if (SCOMx == SCOM2)
				{
//            SCOM2_BASE.SCOM_Operating.Frame_Data.FrameByteNum  = SCOM2_ByteNum;
            SCOM2_RXDataBuffer.len                             = SCOM2_ByteNum;
            SCOM2_ByteNum = 0 ;
        }
        else if (SCOMx == SCOM3)
        {
//            SCOM3_BASE.SCOM_Operating.Frame_Data.FrameByteNum  = SCOM3_ByteNum;
            SCOM3_RXDataBuffer.len                             = SCOM3_ByteNum;
            SCOM3_ByteNum = 0 ;
        }


				if(SCOMx->SCOM_Operating.RX_callbackFun != NULL)
        { 
            (*SCOMx->SCOM_Operating.RX_callbackFun)();	
				}
        
				clear = SCOMx->SCOM_Hardware.USARTx->SR;
				clear = SCOMx->SCOM_Hardware.USARTx->DR;
				clear = clear;
    }					

	  return SUCCESS;
}



/**
 * @brief  SCOM 串口发送DMA中断服务函数
 * @param  *SCOMx           : SCOM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus	SCOM_TX_DMA_IRQHandler(SCOM_TypeDef_Struct *SCOMx)	
{
    uint32_t DMAy_IT;
	  uint32_t DMAy_FLAG;
  
    if (SCOMx == NULL)
    {
        return ERROR; 
    }
  
	  if (SCOMx->SCOM_Hardware.TX_DMAy_Channelx == DMA1_Channel2)
		{
        DMAy_IT   = DMA1_IT_TC2;
        DMAy_FLAG = DMA1_FLAG_TC2;
		}
	  else if (SCOMx->SCOM_Hardware.TX_DMAy_Channelx == DMA1_Channel4)
		{
        DMAy_IT   = DMA1_IT_TC4;
        DMAy_FLAG = DMA1_FLAG_TC4;
		}
	  else if (SCOMx->SCOM_Hardware.TX_DMAy_Channelx == DMA1_Channel7)
		{
        DMAy_IT   = DMA1_IT_TC7;
        DMAy_FLAG = DMA1_FLAG_TC7;
		}		
    else
		{
        return ERROR;
		}		
		
		if (DMA_GetITStatus(DMAy_IT) == SET)
		{
        DMA_ClearFlag(DMAy_FLAG);   /* TCIE,TE,RE	*/
			  DMA_Cmd(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , DISABLE);
			  SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
				if (SCOMx->SCOM_Operating.TX_callbackFun != NULL)
        {
            (*SCOMx->SCOM_Operating.TX_callbackFun)();
        }
		}
    
	  return SUCCESS;
}





/* Private functions ---------------------------------------------------------*/



/**
 * @brief  关中断
 * @param  void
 * @return void
 */
static __INLINE void __SCOM_Disable_IRQ(void)
{
    __SCOM_CPU_PRIMASK_REG_SAVE_VALUE = __get_PRIMASK();
	  __disable_irq();
}



/**
 * @brief  开中断
 * @param  void
 * @return void
 */
static __INLINE void __SCOM_Restore_IRQ(void)
{
    __set_PRIMASK(__SCOM_CPU_PRIMASK_REG_SAVE_VALUE) ;
}




/**
 * @brief  初始化 SCOM RCC 寄存器
 * @param  *SCOMx        : SCOM结构体 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_SCOM_RCC_Config(SCOM_TypeDef_Struct *SCOMx)
{
  
    if ( (SCOMx == NULL) || (SCOMx->SCOM_Hardware.TX_GPIO == NULL)
                         || (SCOMx->SCOM_Hardware.RX_GPIO == NULL) )
    {
        return ERROR;
    }
    
    if ( SCOMx->SCOM_Operating.enable_DMA == ENABLE )	
    {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
		}	
    
		if ( (SCOMx->SCOM_Hardware.RX_GPIO == GPIOA) || (SCOMx->SCOM_Hardware.TX_GPIO == GPIOA) )
		{
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);		
		}

		if ( (SCOMx->SCOM_Hardware.RX_GPIO == GPIOB) || (SCOMx->SCOM_Hardware.TX_GPIO== GPIOB) )
		{
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);	
		}
		
		if ( (SCOMx->SCOM_Hardware.RX_GPIO == GPIOC) || (SCOMx->SCOM_Hardware.TX_GPIO == GPIOC) )
		{
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);	
		}
		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		
    
    return SUCCESS;
}




/**
 * @brief  初始化 SCOM GPIO 寄存器
 * @param  *SCOMx        : SCOM结构体 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_SCOM_GPIO_Config(SCOM_TypeDef_Struct *SCOMx)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  
    if ( (SCOMx == NULL) || (SCOMx->SCOM_Hardware.TX_GPIO == NULL)
                         || (SCOMx->SCOM_Hardware.RX_GPIO == NULL) )
    {
        return ERROR;
    }
    
    GPIO_StructInit(&GPIO_InitStructure);
    
    /*  TX : AF_PP  RX : IN_FLOATING  */
    GPIO_InitStructure.GPIO_Pin   = SCOMx->SCOM_Hardware.TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(SCOMx->SCOM_Hardware.TX_GPIO , &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = SCOMx->SCOM_Hardware.RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SCOMx->SCOM_Hardware.RX_GPIO , &GPIO_InitStructure);   
    
    return SUCCESS;
}



/**
 * @brief  初始化 SCOM DMA 及中断配置
 * @param  *SCOMx        : SCOM结构体 
 * @return void     
 */
void BSP_SCOM_DMA_Config(SCOM_TypeDef_Struct *SCOMx)
{
    DMA_InitTypeDef      DMA_InitStructure;
  
    if((SCOMx->SCOM_Hardware.RX_DMAy_Channelx != NULL) & (SCOMx->SCOM_Hardware.TX_DMAy_Channelx != NULL))
		{
				if ( SCOMx->SCOM_Operating.enable_DMA == ENABLE )
				{   
            /*  使能 SCOM RX DMA  */
						DMA_DeInit(SCOMx->SCOM_Hardware.RX_DMAy_Channelx);
						DMA_InitStructure.DMA_PeripheralBaseAddr 	= (u32)(&SCOMx->SCOM_Hardware.USARTx->DR);
			    	DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32) (SCOMx->SCOM_Operating.RX_Buffer->data);
  					DMA_InitStructure.DMA_DIR 								= DMA_DIR_PeripheralSRC;
						DMA_InitStructure.DMA_BufferSize 					= RX_BUFFER_MAX_SIZE;
						DMA_InitStructure.DMA_PeripheralInc 			= DMA_PeripheralInc_Disable;
						DMA_InitStructure.DMA_MemoryInc 					= DMA_MemoryInc_Enable;
						DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
						DMA_InitStructure.DMA_MemoryDataSize 			= DMA_MemoryDataSize_Byte;
						DMA_InitStructure.DMA_Mode 								= DMA_Mode_Normal;
						DMA_InitStructure.DMA_Priority 						= DMA_Priority_VeryHigh;
						DMA_InitStructure.DMA_M2M 								= DMA_M2M_Disable;
          
						DMA_Init(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , &DMA_InitStructure);								
						DMA_SetCurrDataCounter(SCOMx->SCOM_Hardware.RX_DMAy_Channelx , RX_BUFFER_MAX_SIZE);
           
            /*  使能 SCOM TX DMA  */
						DMA_DeInit(SCOMx->SCOM_Hardware.TX_DMAy_Channelx);
				    DMA_InitStructure.DMA_MemoryBaseAddr 			= (u32)(SCOMx->SCOM_Operating.TX_Buffer->data); 
						DMA_InitStructure.DMA_DIR 								= DMA_DIR_PeripheralDST;
						DMA_InitStructure.DMA_BufferSize 					= TX_BUFFER_MAX_SIZE;
						DMA_Init(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , &DMA_InitStructure);
						
						DMA_ITConfig(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , DMA_IT_TC,ENABLE);						 
						DMA_SetCurrDataCounter(SCOMx->SCOM_Hardware.TX_DMAy_Channelx , 0);
            
				}
	  }
}




/**
 * @brief  初始化 SCOM NVIC 配置及中断
 * @param  *SCOMx        : SCOM结构体 
 * @return void     
 */
void BSP_SCOM_NVIC_Config(SCOM_TypeDef_Struct *SCOMx)
{
    NVIC_InitTypeDef     NVIC_InitStructure;
  
    NVIC_InitStructure.NVIC_IRQChannel                        = SCOMx->SCOM_Hardware.USARTx_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority      = SCOMx->SCOM_Operating.SCOM_PrePriorinty;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority             = SCOMx->SCOM_Operating.SCOM_SubPriorinty;
		NVIC_InitStructure.NVIC_IRQChannelCmd                     = ENABLE; 
		NVIC_Init(&NVIC_InitStructure); 
  
    if ( SCOMx->SCOM_Operating.enable_DMA == ENABLE )
		{   
        NVIC_InitStructure.NVIC_IRQChannel 										 = SCOMx->SCOM_Hardware.TX_DMAy_Channelx_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority   = SCOMx->SCOM_Operating.DMA_PrePriorinty;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority          = SCOMx->SCOM_Operating.DMA_SubPriorinty;
        NVIC_InitStructure.NVIC_IRQChannelCmd 								 = ENABLE;
        NVIC_Init(&NVIC_InitStructure);		
		}

}




/**
 * @brief  非DMA模式下，SCOM 发送数据
 * @param  *SCOMx        : SCOM结构体 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus SCOM_USART_SendData(SCOM_TypeDef_Struct *SCOMx)
{
    static uint8_t  cnt[3] = {0};
	
    if(SCOMx->SCOM_Operating.TX_Buffer == NULL)
    {
        return ERROR;  
    }

    if(SCOMx == SCOM1)
		{			
				if(cnt[0]< SCOMx->SCOM_Operating.TX_Buffer->len)
				{
					 USART_SendData(SCOMx->SCOM_Hardware.USARTx , (uint16_t)SCOMx->SCOM_Operating.TX_Buffer->data[cnt[0]]);
					 cnt[0] ++;
				}
				else 
				{
					 if (SCOMx->SCOM_Operating.TX_callbackFun != NULL)
							 (*SCOMx->SCOM_Operating.TX_callbackFun)();
					 SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
					 cnt[0] = 0;
				}
	  }
    else if(SCOMx == SCOM2)
		{			
				if(cnt[1]< SCOMx->SCOM_Operating.TX_Buffer->len)
				{
					 USART_SendData(SCOMx->SCOM_Hardware.USARTx , (uint16_t)SCOMx->SCOM_Operating.TX_Buffer->data[cnt[1]]);
					 cnt[1] ++;
				}
				else 
				{
					 if (SCOMx->SCOM_Operating.TX_callbackFun != NULL)
							 (*SCOMx->SCOM_Operating.TX_callbackFun)();
					 SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
					 cnt[1] = 0;
				}
	  }		
    else if(SCOMx == SCOM3)
		{			
				if(cnt[2]< SCOMx->SCOM_Operating.TX_Buffer->len)
				{
					 USART_SendData(SCOMx->SCOM_Hardware.USARTx , (uint16_t)SCOMx->SCOM_Operating.TX_Buffer->data[cnt[2]]);
					 cnt[2] ++;
				}
				else 
				{
					 if (SCOMx->SCOM_Operating.TX_callbackFun != NULL)
							 (*SCOMx->SCOM_Operating.TX_callbackFun)();
					 SCOMx->SCOM_Operating.USART_txAllowFlag = SET;
					 cnt[2] = 0;
				}
	  }			
    else 
    {
        return ERROR;			
    }

		
		return SUCCESS;		
}	









///**
// * @brief  从串口读取一帧数据的有效长度，单位:字节                 
// * @param  *SCOMx           : SCOM结构体
// * @param  FrameByteNum     : 存储取回的一帧串口数据长度 
// * @return ErrorStatus: ERROR or SUCCESS   
// */
//ErrorStatus SCOM_Read_FrameByteNum(SCOM_TypeDef_Struct*SCOMx , SCOM_FrameByte_Struct* FrameByteNum)
//{
//    if (SCOMx == NULL) 
//    {
//        return ERROR;
//    }
//    
//    if  (SCOMx->SCOM_Operating.Frame_Data.FrameByteFresh == SET)
//		{
//        __SCOM_Disable_IRQ();
//        FrameByteNum->FrameByteFresh   = SET;
//        FrameByteNum->FrameByteNum     = SCOMx->SCOM_Operating.Frame_Data.FrameByteNum;
//        SCOMx->SCOM_Operating.Frame_Data.FrameByteFresh = RESET;
//        SCOMx->SCOM_Operating.Frame_Data.FrameByteNum  = 0;
//        __SCOM_Restore_IRQ();
//		}
//		else
//		{
//        __SCOM_Disable_IRQ();
//        FrameByteNum->FrameByteFresh  = RESET;
//        FrameByteNum->FrameByteNum    = 0;
//        __SCOM_Restore_IRQ();
//    }

//    return SUCCESS;
//}


