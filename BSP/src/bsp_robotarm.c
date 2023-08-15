/**
  ******************************************************************************
  * @file    bsp_robotarm.c
  * @author  LYB
  * @version V1.0.1
  * @date    2021/4/06
  * @brief   描述了底层机械臂的驱动实现
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_robotarm.h"


/* Global variable -----------------------------------------------------------*/
ARM_TypeDef_Struct                      ARM1_BASE , ARM2_BASE;

const uint16_t ARM_INITIAL_POSITION[] = {1500,2100,2400,2050,1500,1000};      /* ARM 机械臂初始位置  */


/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_ARM_WriteData(ARM_TypeDef_Struct *ARMx , char * fmt , ...);


/* Public functions ----------------------------------------------------------*/


/**
 * @brief  初始化ARM结构体默认配置
 * @param  ARM_InitStruct  : ARM初始化结构体
 * @return void
 */
void BSP_ARM_InitStruct(ARM_InitTypeDef_Struct *ARM_InitStruct)
{
  
    ARM_InitStruct->enable_ARM                    = ARM_ENABLE_DEFAULT;               /* ARM 默认 使能           */
    ARM_InitStruct->enable_DMA                    = ARM_ENABLE_DMA_DEFAULT;           /* ARM 默认 DMA使能        */
  
    ARM_InitStruct->ARM_SCOM_BaudRate             = ARM_BAUDRATE_DEFAULT;             /* ARM 默认串口波特率      */
    ARM_InitStruct->ARM_SCOM_Parity               = ARM_PARITY_DEFAULT;               /* ARM 默认串口校验位      */
    ARM_InitStruct->ARM_SCOM_WordLength           = ARM_WORDLENGTH_DEFAULT;           /* ARM 默认串口字长        */
    ARM_InitStruct->ARM_SCOM_StopBits             = ARM_STOPBITS_DEFAULT;             /* ARM 默认串口停止位      */
    ARM_InitStruct->ARM_SCOM_HardwareFlowControl  = ARM_HARDWARE_FLOWCONTROL_DEFAULT; /* ARM 默认串口硬件控制流  */
  
    ARM_InitStruct->ARM_SCOM_PrePriorinty         = ARM_SCOMPREPRIORINTY_DEFAULT;     /* ARM 默认SCOM抢占优先级  */
    ARM_InitStruct->ARM_SCOM_SubPriorinty         = ARM_SCOMSUBPRIORINTY_DEFAULT;     /* ARM 默认SCOM子优先级    */
    ARM_InitStruct->ARM_DMA_PrePriorinty          = ARM_DMAPREPRIORINTY_DEFAULT ;     /* ARM 默认DMA抢占优先级   */
    ARM_InitStruct->ARM_DMA_SubPriorinty          = ARM_DMASUBPRIORINTY_DEFAULT ;     /* ARM 默认DMA子优先级     */                         
}


/**
 * @brief  初始化LORA结构体
 * @param  *ARMx           : ARMx结构体
 *         *ARM_InitStruct : ARM初始化结构体
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
   
    /* ARM TX 清空数据BUF      */
    ARMx->ARM_Operating.Tx_data.len  = 0;
    for (ii = 0; ii < TX_BUFFER_MAX_SIZE; ii++)
    {
        ARMx->ARM_Operating.Tx_data.data[ii] = 0;
    }
     
    /*  ARM SCOM 初始化配置    */
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
    
    
    /*  ARM SCOM 中断优先级    */
    ARMx->ARM_Operating.SCOM_InitStruct.SCOM_PrePriorinty = ARM_InitStruct->ARM_SCOM_PrePriorinty;
    ARMx->ARM_Operating.SCOM_InitStruct.SCOM_SubPriorinty = ARM_InitStruct->ARM_SCOM_SubPriorinty;
    ARMx->ARM_Operating.SCOM_InitStruct.DMA_PrePriorinty  = ARM_InitStruct->ARM_DMA_PrePriorinty;
    ARMx->ARM_Operating.SCOM_InitStruct.DMA_SubPriorinty  = ARM_InitStruct->ARM_DMA_SubPriorinty;
      
    /*  ARM SCOM 串口配置      */
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_Mode                = USART_Mode_Tx;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_BaudRate            = ARM_InitStruct->ARM_SCOM_BaudRate;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_Parity              = ARM_InitStruct->ARM_SCOM_Parity;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_WordLength          = ARM_InitStruct->ARM_SCOM_WordLength;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_StopBits            = ARM_InitStruct->ARM_SCOM_StopBits;
    ARMx->ARM_Operating.SCOM_InitStruct.usartParm.USART_HardwareFlowControl = ARM_InitStruct->ARM_SCOM_HardwareFlowControl;
    
    
    /* ARM 硬件配置            */
    if (ARMx == ARM1)
    {
        ARMx->ARM_Hardware.SCOM = ARM1_SCOM;
    }
    else if (ARMx == ARM2)
    {
        ARMx->ARM_Hardware.SCOM = ARM2_SCOM;
    }
    
    /* ARM SCOM 初始化         */
    BSP_SCOM_Init(ARMx->ARM_Hardware.SCOM , &ARMx->ARM_Operating.SCOM_InitStruct);
    
    
    /* ARM Channel 通道设置为初始位置 */
    for (ii = 0; ii < 6; ii++)
    {
        ARMx->ARM_Operating.Channel_data[ii] = ARM_INITIAL_POSITION[ii];
        BSP_ARM_WriteData(ARMx, "#%dP%dT10\r\n", (ii+1), ARMx->ARM_Operating.Channel_data[ii]); 
        Delay_ms(100);
    }

    
    return SUCCESS;
}




/**
 * @brief  使能 ARM
 * @param  *ARMx           : ARM结构体
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
 * @brief  失能 ARM
 * @param  *ARMx           : ARM结构体
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
 * @brief  ARM 机械臂驱动
 * @param  *ARMx           : ARM结构体
 * @param  channel         : 驱动的通道0~5
 * @param  data            : 驱动的数据
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
    
    /* 输出限幅 */
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
 * @brief  ARM 机械臂写入数据
 * @param  *ARMx           : ARM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_ARM_WriteData(ARM_TypeDef_Struct *ARMx , char * fmt , ...)
{
    uint8_t buf[30];       /* 字符串缓存 */
    va_list ap; 

    if (ARMx == NULL)
    {
        return ERROR;
    }
    
    va_start(ap,fmt);
    vsprintf((char*)buf,fmt,ap);
    va_end(ap);
    
    /* 计算字符串长度         */
    ARMx->ARM_Operating.Tx_data.len = strlen((const char *)buf);
    
    /* 将缓存数据拷贝到ARMx中 */
    memcpy(ARMx->ARM_Operating.Tx_data.data , buf ,  ARMx->ARM_Operating.Tx_data.len);
    
    /* 将数据写入SCOM         */
    SCOM_WriteData(ARMx->ARM_Hardware.SCOM , &ARMx->ARM_Operating.Tx_data);
  

    return SUCCESS;

}






