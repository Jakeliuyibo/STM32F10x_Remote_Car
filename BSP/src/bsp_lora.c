/**
  ******************************************************************************
  * @file    bsp_lora.c
  * @author  LYB
  * @version V1.0.2
  * @date    202/4/3
  * @brief   描述了底层lora设备的驱动实现
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_lora.h"

/* Global variable -----------------------------------------------------------*/
LORA_TypeDef_Struct  LORA1_BASE , LORA2_BASE , LORA3_BASE;


/* 中断  存储变量 ----------------------------------------------------------- */
static  uint32_t          __Lora_CPU_PRIMASK_REG_SAVE_VALUE;


/* Private functions declaration----------------------------------------------*/
static __INLINE void __LORA_Disable_IRQ(void);
static __INLINE void __LORA_Restore_IRQ(void);

ErrorStatus BSP_LORA_GPIO_Config(LORA_TypeDef_Struct *LORAx);
ErrorStatus LORA_ReceiveData(LORA_TypeDef_Struct *LORAx);
ErrorStatus LORA_SendData(LORA_TypeDef_Struct *LORAx);

void LORA1_ReceiveData_Callback(void);
void LORA2_ReceiveData_Callback(void);
void LORA3_ReceiveData_Callback(void);
void LORA1_SendData_Callback(void);
void LORA2_SendData_Callback(void);
void LORA3_SendData_Callback(void);


/* Public functions ----------------------------------------------------------*/

/**
 * @brief  初始化LORA结构体默认配置
 * @param  LORA_InitStruct : LORA初始化结构体
 */
void BSP_LORA_InitStruct(LORA_InitTypedef_Struct *LORA_InitStruct)
{ 
 
    LORA_InitStruct->enable_LORA    = LORA_ENABLE_DEFAULT     ;      /* LORA 默认使能       */
    LORA_InitStruct->enable_DMA     = LORA_ENABLE_DMA_DEFAULT ;      /* LORA DMA默认使能    */
  
    LORA_InitStruct->TransMode      = LORA_TRANSMODE_DEFAULT  ;      /* LORA 默认传输模式   */
    LORA_InitStruct->UsartMode      = LORA_USARTMODE_DEFAULT  ;      /* LORA 默认串口模式   */
  
    LORA_InitStruct->TX_callbackFun = LORA_TX_CALLBACKFUN_DEFAULT ;  /* LORA 默认TX回调函数 */
    LORA_InitStruct->RX_callbackFun = LORA_RX_CALLBACKFUN_DEFAULT ;  /* LORA 默认RX回调函数 */
  
    LORA_InitStruct->LORA_SCOM_PrePriorinty = LORA_SCOMPREPRIORINTY_DEFAULT ; /* LORA SCOM抢占级 */
    LORA_InitStruct->LORA_SCOM_SubPriorinty = LORA_SCOMSUBPRIORINTY_DEFAULT ; /* LORA SCOM子级   */
    LORA_InitStruct->LORA_DMA_PrePriorinty  = LORA_DMAPREPRIORINTY_DEFAULT  ; /* LORA DMA抢占级  */
    LORA_InitStruct->LORA_DMA_SubPriorinty  = LORA_DMASUBPRIORINTY_DEFAULT  ; /* LORA DMA子级    */

    LORA_InitStruct->LORA_SCOM_BaudRate = LORA_BAUDRATE_DEFAULT;        /* LORA SCOM 波特率      */
    LORA_InitStruct->LORA_SCOM_Parity = LORA_PARITY_DEFAULT;            /* LORA SCOM 串口校验位  */
    LORA_InitStruct->LORA_SCOM_WordLength = LORA_WORDLENGTH_DEFAULT;    /* LORA SCOM 串口字长    */
    LORA_InitStruct->LORA_SCOM_StopBits = LORA_STOPBITS_DEFAULT;        /* LORA SCOM 串口停止位  */
    LORA_InitStruct->LORA_SCOM_HardwareFlowControl = LORA_HARDWARE_FLOWCONTROL_DEFAULT; /* LORA SCOM 硬件控制流 */

    LORA_InitStruct->Address     = LORA_ADDRESS_DEFAULT    ;         /* LORA 默认地址       */
    LORA_InitStruct->Com_Channel = LORA_COMCHANNEL_DEFAULT ;         /* LORA 默认串口通道   */
}



/**
 * @brief  初始化LORA结构体
 * @param  *LORAx            : LORA结构体
 *         *LORA_InitStruct  : LORA初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LORA_Init(LORA_TypeDef_Struct *LORAx , LORA_InitTypedef_Struct *LORA_InitStruct)
{
    
    if ( (LORA_InitStruct == NULL) || (LORA_InitStruct == NULL) )
    {
        return ERROR;
    }
    
    /*  LORA 寄存器赋值        */
    LORAx->LORA_Operating.enable_LORA    = LORA_InitStruct->enable_LORA;
    LORAx->LORA_Operating.TransMode      = LORA_InitStruct->TransMode;
    LORAx->LORA_Operating.UsartMode      = LORA_InitStruct->UsartMode;
    LORAx->LORA_Operating.Address        = LORA_InitStruct->Address;
    LORAx->LORA_Operating.Com_Channel    = LORA_InitStruct->Com_Channel;
    
    LORAx->LORA_Operating.TX_callbackFun = LORA_InitStruct->TX_callbackFun;
    LORAx->LORA_Operating.RX_callbackFun = LORA_InitStruct->RX_callbackFun;


    /*  LORA SCOM 初始化       */
    BSP_SCOM_InitStruct(&LORAx->LORA_Operating.SCOM_InitStruct);
    
    if( LORAx->LORA_Operating.enable_LORA == ENABLE )
    {
        LORAx->LORA_Operating.SCOM_InitStruct.enable_SCOM = ENABLE;
        LORAx->LORA_Operating.SCOM_InitStruct.enable_DMA  = LORA_InitStruct->enable_DMA;
    }
    else
    {
        LORAx->LORA_Operating.SCOM_InitStruct.enable_SCOM = DISABLE;
        LORAx->LORA_Operating.SCOM_InitStruct.enable_DMA  = DISABLE;     
    }
    

    /*  LORA SCOM 中断优先级    */
    LORAx->LORA_Operating.SCOM_InitStruct.SCOM_PrePriorinty = LORA_InitStruct->LORA_SCOM_PrePriorinty ;
    LORAx->LORA_Operating.SCOM_InitStruct.SCOM_SubPriorinty = LORA_InitStruct->LORA_SCOM_SubPriorinty ;
    LORAx->LORA_Operating.SCOM_InitStruct.DMA_PrePriorinty  = LORA_InitStruct->LORA_DMA_PrePriorinty  ;
    LORAx->LORA_Operating.SCOM_InitStruct.DMA_SubPriorinty  = LORA_InitStruct->LORA_DMA_SubPriorinty  ;
    
    /*  LORA SCOM 串口配置      */
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_BaudRate   = LORA_BAUDRATE_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_Parity     = LORA_PARITY_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_WordLength = LORA_WORDLENGTH_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_StopBits   = LORA_STOPBITS_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_HardwareFlowControl = LORA_HARDWARE_FLOWCONTROL_DEFAULT;  
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_Mode       = LORA_InitStruct->UsartMode;

    /*  LORA 硬件及回调函数配置  */
    if (LORAx == LORA1)
    {
        LORA1_BASE.LORA_Hardware.SCOMx        = LORA1_SCOM;           /* LORA1 SCOM     */
        LORA1_BASE.LORA_Hardware.MD0_GPIO     = LORA1_MD0_GPIO;       /* LORA1 MD0 端口 */
        LORA1_BASE.LORA_Hardware.MD0_GPIO_PIN = LORA1_MD0_GPIO_PIN;   /* LORA1 MD0 引脚 */
        LORA1_BASE.LORA_Hardware.MD1_GPIO     = LORA1_MD1_GPIO;       /* LORA1 MD1 端口 */
        LORA1_BASE.LORA_Hardware.MD1_GPIO_PIN = LORA1_MD1_GPIO_PIN;   /* LORA1 MD1 引脚 */
        LORA1_BASE.LORA_Hardware.AUX_GPIO     = LORA1_AUX_GPIO;       /* LORA1 AUX 端口 */
        LORA1_BASE.LORA_Hardware.AUX_GPIO_PIN = LORA1_AUX_GPIO_PIN;   /* LORA1 AUX 引脚 */

        LORAx->LORA_Operating.SCOM_InitStruct.TX_callbackFun = LORA1_SendData_Callback ;
        LORAx->LORA_Operating.SCOM_InitStruct.RX_callbackFun = LORA1_ReceiveData_Callback ;    
    }
    else if (LORAx == LORA2)
    {
        LORA2_BASE.LORA_Hardware.SCOMx        = LORA2_SCOM;           /* LORA2 SCOM     */
        LORA2_BASE.LORA_Hardware.MD0_GPIO     = LORA2_MD0_GPIO;       /* LORA2 MD0 端口 */
        LORA2_BASE.LORA_Hardware.MD0_GPIO_PIN = LORA2_MD0_GPIO_PIN;   /* LORA2 MD0 引脚 */
        LORA2_BASE.LORA_Hardware.MD1_GPIO     = LORA2_MD1_GPIO;       /* LORA2 MD1 端口 */
        LORA2_BASE.LORA_Hardware.MD1_GPIO_PIN = LORA2_MD1_GPIO_PIN;   /* LORA2 MD1 引脚 */
        LORA2_BASE.LORA_Hardware.AUX_GPIO     = LORA2_AUX_GPIO;       /* LORA2 AUX 端口 */
        LORA2_BASE.LORA_Hardware.AUX_GPIO_PIN = LORA2_AUX_GPIO_PIN;   /* LORA2 AUX 引脚 */

        LORAx->LORA_Operating.SCOM_InitStruct.TX_callbackFun = LORA2_SendData_Callback ;
        LORAx->LORA_Operating.SCOM_InitStruct.RX_callbackFun = LORA2_ReceiveData_Callback ;    
    }
    else if (LORAx == LORA3)
    {
        LORA3_BASE.LORA_Hardware.SCOMx        = LORA3_SCOM;           /* LORA2 SCOM     */
        LORA3_BASE.LORA_Hardware.MD0_GPIO     = LORA3_MD0_GPIO;       /* LORA2 MD0 端口 */
        LORA3_BASE.LORA_Hardware.MD0_GPIO_PIN = LORA3_MD0_GPIO_PIN;   /* LORA2 MD0 引脚 */
        LORA3_BASE.LORA_Hardware.MD1_GPIO     = LORA3_MD1_GPIO;       /* LORA2 MD1 端口 */
        LORA3_BASE.LORA_Hardware.MD1_GPIO_PIN = LORA3_MD1_GPIO_PIN;   /* LORA2 MD1 引脚 */
        LORA3_BASE.LORA_Hardware.AUX_GPIO     = LORA3_AUX_GPIO;       /* LORA2 AUX 端口 */
        LORA3_BASE.LORA_Hardware.AUX_GPIO_PIN = LORA3_AUX_GPIO_PIN;   /* LORA2 AUX 引脚 */

        LORAx->LORA_Operating.SCOM_InitStruct.TX_callbackFun = LORA3_SendData_Callback ;
        LORAx->LORA_Operating.SCOM_InitStruct.RX_callbackFun = LORA3_ReceiveData_Callback ;    
    }

    
    /*  初始化LORA GPIO寄存器  */
    if (ERROR == BSP_LORA_GPIO_Config(LORAx))
    {
        return ERROR;
    }
    
    BSP_SCOM_Init(LORAx->LORA_Hardware.SCOMx , &LORAx->LORA_Operating.SCOM_InitStruct);
    
    LORAx->LORA_Operating.LoraRxdata.Fresh = RESET;		
    
    return SUCCESS;
  
}



/**
 * @brief  使能LORA
 * @param  *LORAx           : LORA结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_Open(LORA_TypeDef_Struct *LORAx)
{
    if ( LORAx == NULL )
    {
        return ERROR;
    }
    
    LORAx->LORA_Operating.enable_LORA = ENABLE;
    SCOM_Open(LORAx->LORA_Hardware.SCOMx);
    
    return SUCCESS;
}


/**
 * @brief  失能LORA
 * @param  *LORAx           : LORA结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_Close(LORA_TypeDef_Struct *LORAx)
{
    if ( LORAx == NULL )
    {
        return ERROR;
    }
    
    LORAx->LORA_Operating.enable_LORA = DISABLE;
    SCOM_Close(LORAx->LORA_Hardware.SCOMx);
    
    return SUCCESS;
}





/**
 * @brief  读取LORA数据
 * @param  *LORAx           : LORA结构体
 * @param  *pRead           : 存储LORA数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_ReadData(LORA_TypeDef_Struct *LORAx , LORA_READ_DATA_Struct *pRead)
{

    if((LORAx == NULL) || (LORAx->LORA_Operating.enable_LORA == DISABLE)
			                 || (LORAx->LORA_Operating.UsartMode   == USART_Mode_Tx) )
		{
        return ERROR;
    }
     
    if(SET == LORAx->LORA_Operating.LoraRxdata.Fresh)
		{
        __LORA_Disable_IRQ();			
        pRead->Fresh = SET;
			  pRead->len   = LORAx->LORA_Operating.LoraRxdata.len;
			  memcpy(pRead->data , LORAx->LORA_Operating.LoraRxdata.data , pRead->len);
			  LORAx->LORA_Operating.LoraRxdata.Fresh = RESET;
			  __LORA_Restore_IRQ();
    }
    else 
		{
        return ERROR;	
		}	
    
    return SUCCESS;
}




/**
 * @brief  写入LORA数据
 * @param  *LORAx           : LORA结构体
 * @param  *pWrite          : 存储LORA数据结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LORA_WriteData(LORA_TypeDef_Struct *LORAx , LORA_WRITE_DATA_Struct *pWrite)
{
	  SCOM_WRITE_DATA_Struct      LoraWriteData;
	
  	if ((LORAx ==NULL) || (pWrite == NULL) 
                       || (LORAx->LORA_Operating.enable_LORA == DISABLE)
			                 || (LORAx->LORA_Operating.UsartMode   == USART_Mode_Rx) )
		{
        return ERROR;
    }
    
		if(LORAx->LORA_Operating.TransMode == LORA_Transparent_Trans)    		/*  透传      */
		{
				LoraWriteData.len = pWrite->len;
				memcpy(LoraWriteData.data , &pWrite->data , pWrite->len);				
		}
		else if(LORAx->LORA_Operating.TransMode == LORA_Fixed_Transfer)    	/*  定点传输  */
		{
				LoraWriteData.len = pWrite->len + 3;
				LoraWriteData.data[0] = (LORAx->LORA_Operating.Address >>8);
				LoraWriteData.data[1] =  LORAx->LORA_Operating.Address;
				LoraWriteData.data[2] =  LORAx->LORA_Operating.Com_Channel;					
				memcpy(&LoraWriteData.data[3] , &pWrite->data , pWrite->len);									
		}	
    else
    {
        return ERROR;
    }
    
		if (SUCCESS == SCOM_WriteData(LORAx->LORA_Hardware.SCOMx , &LoraWriteData))
		{
				return SUCCESS;
		}
		else
		{			
				return ERROR;	
		}		

}





/* Private functions ---------------------------------------------------------*/


/**
 * @brief  LORA 关中断
 */
static __INLINE void __LORA_Disable_IRQ(void)
{
    __Lora_CPU_PRIMASK_REG_SAVE_VALUE = __get_PRIMASK();
	  __disable_irq();
}

/**
 * @brief  LORA 开中断
 */
static __INLINE void __LORA_Restore_IRQ(void)
{
    __set_PRIMASK(__Lora_CPU_PRIMASK_REG_SAVE_VALUE) ;
}



/*
  例：当Lora1 串口接收到完整数据帧时会调用Lora1_ReceiveData_Callback()函数，
  进而调用Lora_ReceiveData(Lorax1)，
  Lora_ReceiveData(Lora1)的功能就是从串口读取数据存入Lora1-> LoraRxdata   
  存储完成后如果Lora1也定义的回调函数，则执行该回调函数             */

/**
 * @brief  供回调函数调用的接收数据
 * @param  *LORAx        : LORA结构体 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus  LORA_ReceiveData(LORA_TypeDef_Struct *LORAx)
{
    if((LORAx == NULL) || (LORAx->LORA_Operating.enable_LORA == DISABLE))
		{
        return ERROR;
    }
    
		if(SCOM_ReadData(LORAx->LORA_Hardware.SCOMx , &LORAx->LORA_Operating.LoraRxdata) == SUCCESS)
		{			
        if(LORAx->LORA_Operating.RX_callbackFun != NULL)
        {
              LORAx->LORA_Operating.RX_callbackFun();        
        }
        return SUCCESS;
		}
		else
		{
				return  ERROR;; 
		}  
}


/**
 * @brief  供回调函数调用的发送数据
 * @param  *LORAx        : LORA结构体 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus  LORA_SendData(LORA_TypeDef_Struct *LORAx)
{
    if((LORAx == NULL) || (LORAx->LORA_Operating.enable_LORA == DISABLE))
		{
        return ERROR;
    }
    
		if(SCOM_WriteData(LORAx->LORA_Hardware.SCOMx, &LORAx->LORA_Operating.LoraTxdata) == SUCCESS)
		{			
        if(LORAx->LORA_Operating.TX_callbackFun != NULL)
        {
            LORAx->LORA_Operating.TX_callbackFun();     
        }
        return SUCCESS;
		}
		else
		{
				return  ERROR;; 
		} 
}



/**
 * @brief  LORA 接受回调函数定义
 * @param  void 
 * @return void
 */
void LORA1_ReceiveData_Callback(void)
{
    LORA_ReceiveData(LORA1);
}

void LORA2_ReceiveData_Callback(void)
{
    LORA_ReceiveData(LORA2);
}

void LORA3_ReceiveData_Callback(void)
{
    LORA_ReceiveData(LORA3);
}


/**
 * @brief  LORA 发送回调函数定义
 * @param  void
 * @return void
 */
void LORA1_SendData_Callback(void)
{
    LORA_SendData(LORA1);
}

void LORA2_SendData_Callback(void)
{
    LORA_SendData(LORA2);
}

void LORA3_SendData_Callback(void)
{
    LORA_SendData(LORA3);
}



/**
 * @brief  初始化LORA GPIO寄存器
 * @param  *LORAx        : LORA结构体 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_LORA_GPIO_Config(LORA_TypeDef_Struct *LORAx)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  
    if ((LORAx == NULL) || (LORAx->LORA_Hardware.MD0_GPIO == NULL) || (LORAx->LORA_Hardware.MD0_GPIO_PIN  == NULL)
                        || (LORAx->LORA_Hardware.MD1_GPIO == NULL) || (LORAx->LORA_Hardware.MD1_GPIO_PIN  == NULL)
                        || (LORAx->LORA_Hardware.AUX_GPIO == NULL) || (LORAx->LORA_Hardware.AUX_GPIO_PIN  == NULL) )
    {
        return ERROR;
    }
    
    GPIO_InitStructure.GPIO_Pin   = LORAx->LORA_Hardware.MD0_GPIO_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz             ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP              ;
    GPIO_Init(LORAx->LORA_Hardware.MD0_GPIO , &GPIO_InitStructure) ;
    GPIO_ResetBits(LORAx->LORA_Hardware.MD0_GPIO , LORAx->LORA_Hardware.MD0_GPIO_PIN);		
    
    GPIO_InitStructure.GPIO_Pin   = LORAx->LORA_Hardware.MD1_GPIO_PIN ;
    GPIO_Init(LORAx->LORA_Hardware.MD1_GPIO , &GPIO_InitStructure) ;
    GPIO_ResetBits(LORAx->LORA_Hardware.MD1_GPIO , LORAx->LORA_Hardware.MD1_GPIO_PIN);		
    
    GPIO_InitStructure.GPIO_Pin   = LORAx->LORA_Hardware.AUX_GPIO_PIN ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING        ;
    GPIO_Init(LORAx->LORA_Hardware.AUX_GPIO , &GPIO_InitStructure) ;

    return SUCCESS;
}





