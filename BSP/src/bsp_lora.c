/**
  ******************************************************************************
  * @file    bsp_lora.c
  * @author  LYB
  * @version V1.0.2
  * @date    202/4/3
  * @brief   �����˵ײ�lora�豸������ʵ��
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_lora.h"

/* Global variable -----------------------------------------------------------*/
LORA_TypeDef_Struct  LORA1_BASE , LORA2_BASE , LORA3_BASE;


/* �ж�  �洢���� ----------------------------------------------------------- */
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
 * @brief  ��ʼ��LORA�ṹ��Ĭ������
 * @param  LORA_InitStruct : LORA��ʼ���ṹ��
 */
void BSP_LORA_InitStruct(LORA_InitTypedef_Struct *LORA_InitStruct)
{ 
 
    LORA_InitStruct->enable_LORA    = LORA_ENABLE_DEFAULT     ;      /* LORA Ĭ��ʹ��       */
    LORA_InitStruct->enable_DMA     = LORA_ENABLE_DMA_DEFAULT ;      /* LORA DMAĬ��ʹ��    */
  
    LORA_InitStruct->TransMode      = LORA_TRANSMODE_DEFAULT  ;      /* LORA Ĭ�ϴ���ģʽ   */
    LORA_InitStruct->UsartMode      = LORA_USARTMODE_DEFAULT  ;      /* LORA Ĭ�ϴ���ģʽ   */
  
    LORA_InitStruct->TX_callbackFun = LORA_TX_CALLBACKFUN_DEFAULT ;  /* LORA Ĭ��TX�ص����� */
    LORA_InitStruct->RX_callbackFun = LORA_RX_CALLBACKFUN_DEFAULT ;  /* LORA Ĭ��RX�ص����� */
  
    LORA_InitStruct->LORA_SCOM_PrePriorinty = LORA_SCOMPREPRIORINTY_DEFAULT ; /* LORA SCOM��ռ�� */
    LORA_InitStruct->LORA_SCOM_SubPriorinty = LORA_SCOMSUBPRIORINTY_DEFAULT ; /* LORA SCOM�Ӽ�   */
    LORA_InitStruct->LORA_DMA_PrePriorinty  = LORA_DMAPREPRIORINTY_DEFAULT  ; /* LORA DMA��ռ��  */
    LORA_InitStruct->LORA_DMA_SubPriorinty  = LORA_DMASUBPRIORINTY_DEFAULT  ; /* LORA DMA�Ӽ�    */

    LORA_InitStruct->LORA_SCOM_BaudRate = LORA_BAUDRATE_DEFAULT;        /* LORA SCOM ������      */
    LORA_InitStruct->LORA_SCOM_Parity = LORA_PARITY_DEFAULT;            /* LORA SCOM ����У��λ  */
    LORA_InitStruct->LORA_SCOM_WordLength = LORA_WORDLENGTH_DEFAULT;    /* LORA SCOM �����ֳ�    */
    LORA_InitStruct->LORA_SCOM_StopBits = LORA_STOPBITS_DEFAULT;        /* LORA SCOM ����ֹͣλ  */
    LORA_InitStruct->LORA_SCOM_HardwareFlowControl = LORA_HARDWARE_FLOWCONTROL_DEFAULT; /* LORA SCOM Ӳ�������� */

    LORA_InitStruct->Address     = LORA_ADDRESS_DEFAULT    ;         /* LORA Ĭ�ϵ�ַ       */
    LORA_InitStruct->Com_Channel = LORA_COMCHANNEL_DEFAULT ;         /* LORA Ĭ�ϴ���ͨ��   */
}



/**
 * @brief  ��ʼ��LORA�ṹ��
 * @param  *LORAx            : LORA�ṹ��
 *         *LORA_InitStruct  : LORA��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LORA_Init(LORA_TypeDef_Struct *LORAx , LORA_InitTypedef_Struct *LORA_InitStruct)
{
    
    if ( (LORA_InitStruct == NULL) || (LORA_InitStruct == NULL) )
    {
        return ERROR;
    }
    
    /*  LORA �Ĵ�����ֵ        */
    LORAx->LORA_Operating.enable_LORA    = LORA_InitStruct->enable_LORA;
    LORAx->LORA_Operating.TransMode      = LORA_InitStruct->TransMode;
    LORAx->LORA_Operating.UsartMode      = LORA_InitStruct->UsartMode;
    LORAx->LORA_Operating.Address        = LORA_InitStruct->Address;
    LORAx->LORA_Operating.Com_Channel    = LORA_InitStruct->Com_Channel;
    
    LORAx->LORA_Operating.TX_callbackFun = LORA_InitStruct->TX_callbackFun;
    LORAx->LORA_Operating.RX_callbackFun = LORA_InitStruct->RX_callbackFun;


    /*  LORA SCOM ��ʼ��       */
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
    

    /*  LORA SCOM �ж����ȼ�    */
    LORAx->LORA_Operating.SCOM_InitStruct.SCOM_PrePriorinty = LORA_InitStruct->LORA_SCOM_PrePriorinty ;
    LORAx->LORA_Operating.SCOM_InitStruct.SCOM_SubPriorinty = LORA_InitStruct->LORA_SCOM_SubPriorinty ;
    LORAx->LORA_Operating.SCOM_InitStruct.DMA_PrePriorinty  = LORA_InitStruct->LORA_DMA_PrePriorinty  ;
    LORAx->LORA_Operating.SCOM_InitStruct.DMA_SubPriorinty  = LORA_InitStruct->LORA_DMA_SubPriorinty  ;
    
    /*  LORA SCOM ��������      */
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_BaudRate   = LORA_BAUDRATE_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_Parity     = LORA_PARITY_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_WordLength = LORA_WORDLENGTH_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_StopBits   = LORA_STOPBITS_DEFAULT;
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_HardwareFlowControl = LORA_HARDWARE_FLOWCONTROL_DEFAULT;  
    LORAx->LORA_Operating.SCOM_InitStruct.usartParm.USART_Mode       = LORA_InitStruct->UsartMode;

    /*  LORA Ӳ�����ص���������  */
    if (LORAx == LORA1)
    {
        LORA1_BASE.LORA_Hardware.SCOMx        = LORA1_SCOM;           /* LORA1 SCOM     */
        LORA1_BASE.LORA_Hardware.MD0_GPIO     = LORA1_MD0_GPIO;       /* LORA1 MD0 �˿� */
        LORA1_BASE.LORA_Hardware.MD0_GPIO_PIN = LORA1_MD0_GPIO_PIN;   /* LORA1 MD0 ���� */
        LORA1_BASE.LORA_Hardware.MD1_GPIO     = LORA1_MD1_GPIO;       /* LORA1 MD1 �˿� */
        LORA1_BASE.LORA_Hardware.MD1_GPIO_PIN = LORA1_MD1_GPIO_PIN;   /* LORA1 MD1 ���� */
        LORA1_BASE.LORA_Hardware.AUX_GPIO     = LORA1_AUX_GPIO;       /* LORA1 AUX �˿� */
        LORA1_BASE.LORA_Hardware.AUX_GPIO_PIN = LORA1_AUX_GPIO_PIN;   /* LORA1 AUX ���� */

        LORAx->LORA_Operating.SCOM_InitStruct.TX_callbackFun = LORA1_SendData_Callback ;
        LORAx->LORA_Operating.SCOM_InitStruct.RX_callbackFun = LORA1_ReceiveData_Callback ;    
    }
    else if (LORAx == LORA2)
    {
        LORA2_BASE.LORA_Hardware.SCOMx        = LORA2_SCOM;           /* LORA2 SCOM     */
        LORA2_BASE.LORA_Hardware.MD0_GPIO     = LORA2_MD0_GPIO;       /* LORA2 MD0 �˿� */
        LORA2_BASE.LORA_Hardware.MD0_GPIO_PIN = LORA2_MD0_GPIO_PIN;   /* LORA2 MD0 ���� */
        LORA2_BASE.LORA_Hardware.MD1_GPIO     = LORA2_MD1_GPIO;       /* LORA2 MD1 �˿� */
        LORA2_BASE.LORA_Hardware.MD1_GPIO_PIN = LORA2_MD1_GPIO_PIN;   /* LORA2 MD1 ���� */
        LORA2_BASE.LORA_Hardware.AUX_GPIO     = LORA2_AUX_GPIO;       /* LORA2 AUX �˿� */
        LORA2_BASE.LORA_Hardware.AUX_GPIO_PIN = LORA2_AUX_GPIO_PIN;   /* LORA2 AUX ���� */

        LORAx->LORA_Operating.SCOM_InitStruct.TX_callbackFun = LORA2_SendData_Callback ;
        LORAx->LORA_Operating.SCOM_InitStruct.RX_callbackFun = LORA2_ReceiveData_Callback ;    
    }
    else if (LORAx == LORA3)
    {
        LORA3_BASE.LORA_Hardware.SCOMx        = LORA3_SCOM;           /* LORA2 SCOM     */
        LORA3_BASE.LORA_Hardware.MD0_GPIO     = LORA3_MD0_GPIO;       /* LORA2 MD0 �˿� */
        LORA3_BASE.LORA_Hardware.MD0_GPIO_PIN = LORA3_MD0_GPIO_PIN;   /* LORA2 MD0 ���� */
        LORA3_BASE.LORA_Hardware.MD1_GPIO     = LORA3_MD1_GPIO;       /* LORA2 MD1 �˿� */
        LORA3_BASE.LORA_Hardware.MD1_GPIO_PIN = LORA3_MD1_GPIO_PIN;   /* LORA2 MD1 ���� */
        LORA3_BASE.LORA_Hardware.AUX_GPIO     = LORA3_AUX_GPIO;       /* LORA2 AUX �˿� */
        LORA3_BASE.LORA_Hardware.AUX_GPIO_PIN = LORA3_AUX_GPIO_PIN;   /* LORA2 AUX ���� */

        LORAx->LORA_Operating.SCOM_InitStruct.TX_callbackFun = LORA3_SendData_Callback ;
        LORAx->LORA_Operating.SCOM_InitStruct.RX_callbackFun = LORA3_ReceiveData_Callback ;    
    }

    
    /*  ��ʼ��LORA GPIO�Ĵ���  */
    if (ERROR == BSP_LORA_GPIO_Config(LORAx))
    {
        return ERROR;
    }
    
    BSP_SCOM_Init(LORAx->LORA_Hardware.SCOMx , &LORAx->LORA_Operating.SCOM_InitStruct);
    
    LORAx->LORA_Operating.LoraRxdata.Fresh = RESET;		
    
    return SUCCESS;
  
}



/**
 * @brief  ʹ��LORA
 * @param  *LORAx           : LORA�ṹ��
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
 * @brief  ʧ��LORA
 * @param  *LORAx           : LORA�ṹ��
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
 * @brief  ��ȡLORA����
 * @param  *LORAx           : LORA�ṹ��
 * @param  *pRead           : �洢LORA���ݽṹ��
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
 * @brief  д��LORA����
 * @param  *LORAx           : LORA�ṹ��
 * @param  *pWrite          : �洢LORA���ݽṹ��
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
    
		if(LORAx->LORA_Operating.TransMode == LORA_Transparent_Trans)    		/*  ͸��      */
		{
				LoraWriteData.len = pWrite->len;
				memcpy(LoraWriteData.data , &pWrite->data , pWrite->len);				
		}
		else if(LORAx->LORA_Operating.TransMode == LORA_Fixed_Transfer)    	/*  ���㴫��  */
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
 * @brief  LORA ���ж�
 */
static __INLINE void __LORA_Disable_IRQ(void)
{
    __Lora_CPU_PRIMASK_REG_SAVE_VALUE = __get_PRIMASK();
	  __disable_irq();
}

/**
 * @brief  LORA ���ж�
 */
static __INLINE void __LORA_Restore_IRQ(void)
{
    __set_PRIMASK(__Lora_CPU_PRIMASK_REG_SAVE_VALUE) ;
}



/*
  ������Lora1 ���ڽ��յ���������֡ʱ�����Lora1_ReceiveData_Callback()������
  ��������Lora_ReceiveData(Lorax1)��
  Lora_ReceiveData(Lora1)�Ĺ��ܾ��ǴӴ��ڶ�ȡ���ݴ���Lora1-> LoraRxdata   
  �洢��ɺ����Lora1Ҳ����Ļص���������ִ�иûص�����             */

/**
 * @brief  ���ص��������õĽ�������
 * @param  *LORAx        : LORA�ṹ�� 
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
 * @brief  ���ص��������õķ�������
 * @param  *LORAx        : LORA�ṹ�� 
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
 * @brief  LORA ���ܻص���������
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
 * @brief  LORA ���ͻص���������
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
 * @brief  ��ʼ��LORA GPIO�Ĵ���
 * @param  *LORAx        : LORA�ṹ�� 
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





