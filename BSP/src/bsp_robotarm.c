/**
  ******************************************************************************
  * @file    bsp_robotarm.c
  * @author  LYB
  * @version V1.0.1
  * @date    2021/4/06
  * @brief   �����˵ײ��е�۵�����ʵ��
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_robotarm.h"


/* Global variable -----------------------------------------------------------*/
ARM_TypeDef_Struct                      ARM1_BASE , ARM2_BASE;

const uint16_t ARM_INITIAL_POSITION[] = {1500,2100,2400,2050,1500,1000};      /* ARM ��е�۳�ʼλ��  */


/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_ARM_WriteData(ARM_TypeDef_Struct *ARMx , char * fmt , ...);


/* Public functions ----------------------------------------------------------*/


/**
 * @brief  ��ʼ��ARM�ṹ��Ĭ������
 * @param  ARM_InitStruct  : ARM��ʼ���ṹ��
 * @return void
 */
void BSP_ARM_InitStruct(ARM_InitTypeDef_Struct *ARM_InitStruct)
{
  
    ARM_InitStruct->enable_ARM                    = ARM_ENABLE_DEFAULT;               /* ARM Ĭ�� ʹ��           */
    ARM_InitStruct->enable_DMA                    = ARM_ENABLE_DMA_DEFAULT;           /* ARM Ĭ�� DMAʹ��        */
  
    ARM_InitStruct->ARM_SCOM_BaudRate             = ARM_BAUDRATE_DEFAULT;             /* ARM Ĭ�ϴ��ڲ�����      */
    ARM_InitStruct->ARM_SCOM_Parity               = ARM_PARITY_DEFAULT;               /* ARM Ĭ�ϴ���У��λ      */
    ARM_InitStruct->ARM_SCOM_WordLength           = ARM_WORDLENGTH_DEFAULT;           /* ARM Ĭ�ϴ����ֳ�        */
    ARM_InitStruct->ARM_SCOM_StopBits             = ARM_STOPBITS_DEFAULT;             /* ARM Ĭ�ϴ���ֹͣλ      */
    ARM_InitStruct->ARM_SCOM_HardwareFlowControl  = ARM_HARDWARE_FLOWCONTROL_DEFAULT; /* ARM Ĭ�ϴ���Ӳ��������  */
  
    ARM_InitStruct->ARM_SCOM_PrePriorinty         = ARM_SCOMPREPRIORINTY_DEFAULT;     /* ARM Ĭ��SCOM��ռ���ȼ�  */
    ARM_InitStruct->ARM_SCOM_SubPriorinty         = ARM_SCOMSUBPRIORINTY_DEFAULT;     /* ARM Ĭ��SCOM�����ȼ�    */
    ARM_InitStruct->ARM_DMA_PrePriorinty          = ARM_DMAPREPRIORINTY_DEFAULT ;     /* ARM Ĭ��DMA��ռ���ȼ�   */
    ARM_InitStruct->ARM_DMA_SubPriorinty          = ARM_DMASUBPRIORINTY_DEFAULT ;     /* ARM Ĭ��DMA�����ȼ�     */                         
}


/**
 * @brief  ��ʼ��LORA�ṹ��
 * @param  *ARMx           : ARMx�ṹ��
 *         *ARM_InitStruct : ARM��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Init(ARM_TypeDef_Struct *ARMx , ARM_InitTypeDef_Struct *ARM_InitStruct)
{
    uint8_t ii = 0;
  
    if ((ARMx == NULL) || (ARM_InitStruct == NULL))
    {
        return ERROR;
    }
    
    ARMx->ARM_Operating.enable_ARM      = ARM_InitStruct->enable_ARM;
   
    /* ARM TX �������BUF      */
    ARMx->ARM_Operating.Tx_data.len  = 0;
    for (ii = 0; ii < TX_BUFFER_MAX_SIZE; ii++)
    {
        ARMx->ARM_Operating.Tx_data.data[ii] = 0;
    }
     
    /*  ARM SCOM ��ʼ������    */
    BSP_SCOM_InitStruct(&ARMx->ARM_Operating.SCOM_InitStruct);
    
    if (ARMx->ARM_Operating.enable_ARM == ENABLE)
    {
        ARMx->ARM_Operating.SCOM_InitStruct.enable_SCOM = ENABLE;
        ARMx->ARM_Operating.SCOM_InitStruct.enable_DMA  = ARM_InitStruct->enable_DMA;
    }
    else
    {
        ARMx->ARM_Operating.SCOM_InitStruct.enable_SCOM = DISABLE;
        ARMx->ARM_Operating.SCOM_InitStruct.enable_DMA  = DISABLE;
    }
    
    
    /*  ARM SCOM �ж����ȼ�    */
    ARMx->ARM_Operating.SCOM_InitStruct.SCOM_PrePriorinty = ARM_InitStruct->ARM_SCOM_PrePriorinty;
    ARMx->ARM_Operating.SCOM_InitStruct.SCOM_SubPriorinty = ARM_InitStruct->ARM_SCOM_SubPriorinty;
    ARMx->ARM_Operating.SCOM_InitStruct.DMA_PrePriorinty  = ARM_InitStruct->ARM_DMA_PrePriorinty;
    ARMx->ARM_Operating.SCOM_InitStruct.DMA_SubPriorinty  = ARM_InitStruct->ARM_DMA_SubPriorinty;
      
    /*  ARM SCOM ��������      */
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_Mode                = USART_Mode_Tx;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_BaudRate            = ARM_InitStruct->ARM_SCOM_BaudRate;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_Parity              = ARM_InitStruct->ARM_SCOM_Parity;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_WordLength          = ARM_InitStruct->ARM_SCOM_WordLength;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_StopBits            = ARM_InitStruct->ARM_SCOM_StopBits;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_HardwareFlowControl = ARM_InitStruct->ARM_SCOM_HardwareFlowControl;
    
    
    /* ARM Ӳ������            */
    if (ARMx == ARM1)
    {
        ARMx->ARM_Hardware.SCOM = ARM1_SCOM;
    }
    else if (ARMx == ARM2)
    {
        ARMx->ARM_Hardware.SCOM = ARM2_SCOM;
    }
    
    /* ARM SCOM ��ʼ��         */
    BSP_SCOM_Init(ARMx->ARM_Hardware.SCOM , &ARMx->ARM_Operating.SCOM_InitStruct);
    
    
    /* ARM Channel ͨ������Ϊ��ʼλ�� */
    for (ii = 0; ii < 6; ii++)
    {
        ARMx->ARM_Operating.Channel_data[ii] = ARM_INITIAL_POSITION[ii];
        BSP_ARM_WriteData(ARMx, "#%dP%dT10\r\n", (ii+1), ARMx->ARM_Operating.Channel_data[ii]); 
        Delay_ms(100);
    }

    
    return SUCCESS;
}




/**
 * @brief  ʹ�� ARM
 * @param  *ARMx           : ARM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Open(ARM_TypeDef_Struct *ARMx)
{
    if (ARMx == NULL)
    {
        return ERROR;
    }
    
    ARMx->ARM_Operating.enable_ARM = ENABLE;
    SCOM_Open(ARMx->ARM_Hardware.SCOM);

    return SUCCESS;
}


/**
 * @brief  ʧ�� ARM
 * @param  *ARMx           : ARM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Close(ARM_TypeDef_Struct *ARMx)
{
    if (ARMx == NULL)
    {
        return ERROR;
    }
    
    ARMx->ARM_Operating.enable_ARM = DISABLE;
    SCOM_Close(ARMx->ARM_Hardware.SCOM);
    
    return SUCCESS;
}


/**
 * @brief  ARM ��е������
 * @param  *ARMx           : ARM�ṹ��
 * @param  channel         : ������ͨ��0~5
 * @param  data            : ����������
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_Drive(ARM_TypeDef_Struct *ARMx , uint8_t channel, float data)
{

    if (ARMx == NULL)
    {
        return ERROR;
    }
    
    if (data > 0.05)
    {
        ARMx->ARM_Operating.Channel_data[channel] = ARMx->ARM_Operating.Channel_data[channel] + 50;
      
    }
    else if (data < -0.05)
    {
        ARMx->ARM_Operating.Channel_data[channel] = ARMx->ARM_Operating.Channel_data[channel] - 50;
    }
    else
    {
        ARMx->ARM_Operating.Channel_data[channel] = ARMx->ARM_Operating.Channel_data[channel];
    }
    
    /* ����޷� */
    if (ARMx->ARM_Operating.Channel_data[channel] > ARM_OUTPUT_MAX_LIMIT)
    {
        ARMx->ARM_Operating.Channel_data[channel] = ARM_OUTPUT_MAX_LIMIT;
    }
    if (ARMx->ARM_Operating.Channel_data[channel] < ARM_OUTPUT_MIN_LIMIT)
    {
        ARMx->ARM_Operating.Channel_data[channel] = ARM_OUTPUT_MIN_LIMIT;
    }    
    
    if (data != 0)
    {
        BSP_ARM_WriteData(ARMx, "#%dP%dT10\r\n", (channel+1), ARMx->ARM_Operating.Channel_data[channel]);
    }

    

    return SUCCESS;
}




/* Private functions ---------------------------------------------------------*/


/**
 * @brief  ARM ��е��д������
 * @param  *ARMx           : ARM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_WriteData(ARM_TypeDef_Struct *ARMx , char * fmt , ...)
{
    uint8_t buf[30];       /* �ַ������� */
    va_list ap; 

    if (ARMx == NULL)
    {
        return ERROR;
    }
    
    va_start(ap,fmt);
    vsprintf((char*)buf,fmt,ap);
    va_end(ap);
    
    /* �����ַ�������         */
    ARMx->ARM_Operating.Tx_data.len = strlen((const char *)buf);
    
    /* ���������ݿ�����ARMx�� */
    memcpy(ARMx->ARM_Operating.Tx_data.data , buf ,  ARMx->ARM_Operating.Tx_data.len);
    
    /* ������д��SCOM         */
    SCOM_WriteData(ARMx->ARM_Hardware.SCOM , &ARMx->ARM_Operating.Tx_data);
  

    return SUCCESS;

}






