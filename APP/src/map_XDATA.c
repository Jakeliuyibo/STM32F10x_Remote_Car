/**
  ******************************************************************************
  * @file    map_XDATA.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/1
  * @brief   描述了数据协议转换的功能实现
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "map_XDATA.h"

/* Global variable -----------------------------------------------------------*/
XDATA_TypeDef_Struct    XDATA1_BASE,XDATA2_BASE,XDATA3_BASE;




/* Private functions declaration----------------------------------------------*/




/* Public functions ----------------------------------------------------------*/



/**
 * @brief  初始化XDATA结构体默认配置
 * @param  *XDATA_InitStruct  : XDATA初始化结构体
 * @return void  
 */
void MAP_XDATA_InitStruct(XDATA_InitTypeDef_Struct *XDATA_InitStruct)
{
    LORA_InitTypedef_Struct   LORA_InitStruct;
  
    XDATA_InitStruct->enable_XDATA    = XDATA_ENABLE_DEFAULT;    /* XDATA 使能      */
    XDATA_InitStruct->XDATA_TransMode = XDATA_TRANSMODE_DEFAULT; /* XDATA 传输模式  */
    
    /* 初始化 LORA INIT 结构体  */
    BSP_LORA_InitStruct(&LORA_InitStruct);
  
    XDATA_InitStruct->LORA_InitStruct = LORA_InitStruct;         /* XDATA LORA INIT */

}



/**
 * @brief  初始化XDATA结构体
 * @param  *XDATAx           : XDATA结构体
 *         *XDATA_InitStruct : XDATA初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_XDATA_Init(XDATA_TypeDef_Struct *XDATAx , XDATA_InitTypeDef_Struct *XDATA_InitStruct)
{
    if ( (XDATAx == NULL) || (XDATA_InitStruct == NULL) )
    {
        return ERROR;
    }
    
    /*  XDATA 寄存器赋值        */
    XDATAx->XDATA_Operating.enable_XDATA    = XDATA_InitStruct->enable_XDATA ;
    XDATAx->XDATA_Operating.TransMode       = XDATA_InitStruct->XDATA_TransMode;
    XDATAx->XDATA_Operating.LORA_InitStruct = XDATA_InitStruct->LORA_InitStruct;
    
    
    
    /*  XDATA 硬件赋值          */
    if (XDATAx == XDATA1) 
    {
        XDATA1_BASE.XDATA_Hardware.LORAx  = XDATA1_LORA;   /* XDATA1 LORA     */
      
//        XDATAx->XDATA_Operating.RX_Buffer = XDATA1_LORA->LORA_Operating.LoraRxdata;
//        XDATAx->XDATA_Operating.TX_Buffer = XDATA1_LORA->LORA_Operating.LoraTxdata;
    }
    else if (XDATAx == XDATA2)
    {
        XDATA2_BASE.XDATA_Hardware.LORAx  = XDATA2_LORA;   /* XDATA2 LORA     */
    }
    else if (XDATAx == XDATA3)
    {
        XDATA3_BASE.XDATA_Hardware.LORAx  = XDATA3_LORA;   /* XDATA3 LORA     */
    }  
    else 
    {
        return ERROR;
    }

    BSP_LORA_Init(XDATAx->XDATA_Hardware.LORAx , &XDATAx->XDATA_Operating.LORA_InitStruct);

    return SUCCESS;
}


/**
 * @brief  读出XDATA数据
 * @param  XDATAx： 需要读出数据的XDATA结构体指针
 * @param  Xdata ： XDATA协议数据结构体指针
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_ReadData(XDATA_TypeDef_Struct *XDATAx , XDATA_READ_DATA_Struct *pRead)
{
  
    if ((XDATAx == NULL) || (pRead == NULL))
    {
        return ERROR;
    }
    
    /*  接收到新的数据   */
    if ( (SUCCESS == LORA_ReadData(XDATAx->XDATA_Hardware.LORAx , &XDATAx->XDATA_Operating.RX_Buffer))
      && (XDATAx->XDATA_Operating.RX_Buffer.Fresh == SET) )
    {
        pRead->Fresh = SET;
      
        /*  数组长度为25 */
        if (XDATAx->XDATA_Operating.RX_Buffer.len != 25)
        {
            return ERROR;
        }
        
        if (ERROR == MAP_SCOMtoSBUS(XDATAx->XDATA_Operating.RX_Buffer.data , &pRead->RXData))
        {
            return ERROR;
        }
        
        XDATAx->XDATA_Hardware.LORAx->LORA_Operating.LoraRxdata.Fresh = RESET;
    }
    else
    {
        return ERROR;
    }
    
    
    return SUCCESS;
}



/**
 * @brief  写入SBUS数据
 * @param  XDATAx  ： 写入数据的XDATA结构体指针
 * @param  SBUSdata： SBUS数据存储指针,数组长度16byte 11bit
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_WriteData(XDATA_TypeDef_Struct *XDATAx , XDATA_WRITE_DATA_Struct *pWrite)
{
    if ((XDATAx == NULL) || (pWrite == NULL))
    {
        return ERROR;
    }
    
    /*  将pWrite 从SBUS转化为SCOM  */
    if (ERROR == MAP_SBUStoSCOM(pWrite , XDATAx->XDATA_Operating.TX_Buffer.data))
    {
        return ERROR;
    }
    
    XDATAx->XDATA_Operating.TX_Buffer.len = 25;
    
    /*  将数据从XDATA TX 缓存，发送给LORA */
    if (ERROR == LORA_WriteData(XDATAx->XDATA_Hardware.LORAx , &XDATAx->XDATA_Operating.TX_Buffer))
    {
        return ERROR;
    }
    
    
    return SUCCESS;
}





/**
 * @brief  打开 XDATA 通道
 * @param  XDATAx： 需要打开的 XDATA 通道
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_Open(XDATA_TypeDef_Struct *XDATAx)
{
    if (XDATAx == NULL)
    {
        return ERROR;
    }
    
    XDATAx->XDATA_Operating.enable_XDATA = ENABLE;
    
    LORA_Open(XDATAx->XDATA_Hardware.LORAx);
    
    return SUCCESS;
}




/**
 * @brief  关闭 XDATA 通道
 * @param  XDATAx： 需要关闭的 XDATA 通道
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_Close(XDATA_TypeDef_Struct *XDATAx)
{
    if (XDATAx == NULL)
    {
        return ERROR;
    }
    
    XDATAx->XDATA_Operating.enable_XDATA = DISABLE;
    
    LORA_Close(XDATAx->XDATA_Hardware.LORAx);
    
    return SUCCESS;
}


