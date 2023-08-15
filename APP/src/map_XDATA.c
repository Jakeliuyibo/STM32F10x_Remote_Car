/**
  ******************************************************************************
  * @file    map_XDATA.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/1
  * @brief   ����������Э��ת���Ĺ���ʵ��
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "map_XDATA.h"

/* Global variable -----------------------------------------------------------*/
XDATA_TypeDef_Struct    XDATA1_BASE,XDATA2_BASE,XDATA3_BASE;




/* Private functions declaration----------------------------------------------*/




/* Public functions ----------------------------------------------------------*/



/**
 * @brief  ��ʼ��XDATA�ṹ��Ĭ������
 * @param  *XDATA_InitStruct  : XDATA��ʼ���ṹ��
 * @return void  
 */
void MAP_XDATA_InitStruct(XDATA_InitTypeDef_Struct *XDATA_InitStruct)
{
    LORA_InitTypedef_Struct   LORA_InitStruct;
  
    XDATA_InitStruct->enable_XDATA    = XDATA_ENABLE_DEFAULT;    /* XDATA ʹ��      */
    XDATA_InitStruct->XDATA_TransMode = XDATA_TRANSMODE_DEFAULT; /* XDATA ����ģʽ  */
    
    /* ��ʼ�� LORA INIT �ṹ��  */
    BSP_LORA_InitStruct(&LORA_InitStruct);
  
    XDATA_InitStruct->LORA_InitStruct = LORA_InitStruct;         /* XDATA LORA INIT */

}



/**
 * @brief  ��ʼ��XDATA�ṹ��
 * @param  *XDATAx           : XDATA�ṹ��
 *         *XDATA_InitStruct : XDATA��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_XDATA_Init(XDATA_TypeDef_Struct *XDATAx , XDATA_InitTypeDef_Struct *XDATA_InitStruct)
{
    if ( (XDATAx == NULL) || (XDATA_InitStruct == NULL) )
    {
        return ERROR;
    }
    
    /*  XDATA �Ĵ�����ֵ        */
    XDATAx->XDATA_Operating.enable_XDATA    = XDATA_InitStruct->enable_XDATA ;
    XDATAx->XDATA_Operating.TransMode       = XDATA_InitStruct->XDATA_TransMode;
    XDATAx->XDATA_Operating.LORA_InitStruct = XDATA_InitStruct->LORA_InitStruct;
    
    
    
    /*  XDATA Ӳ����ֵ          */
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
 * @brief  ����XDATA����
 * @param  XDATAx�� ��Ҫ�������ݵ�XDATA�ṹ��ָ��
 * @param  Xdata �� XDATAЭ�����ݽṹ��ָ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_ReadData(XDATA_TypeDef_Struct *XDATAx , XDATA_READ_DATA_Struct *pRead)
{
  
    if ((XDATAx == NULL) || (pRead == NULL))
    {
        return ERROR;
    }
    
    /*  ���յ��µ�����   */
    if ( (SUCCESS == LORA_ReadData(XDATAx->XDATA_Hardware.LORAx , &XDATAx->XDATA_Operating.RX_Buffer))
      && (XDATAx->XDATA_Operating.RX_Buffer.Fresh == SET) )
    {
        pRead->Fresh = SET;
      
        /*  ���鳤��Ϊ25 */
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
 * @brief  д��SBUS����
 * @param  XDATAx  �� д�����ݵ�XDATA�ṹ��ָ��
 * @param  SBUSdata�� SBUS���ݴ洢ָ��,���鳤��16byte 11bit
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus XDATA_WriteData(XDATA_TypeDef_Struct *XDATAx , XDATA_WRITE_DATA_Struct *pWrite)
{
    if ((XDATAx == NULL) || (pWrite == NULL))
    {
        return ERROR;
    }
    
    /*  ��pWrite ��SBUSת��ΪSCOM  */
    if (ERROR == MAP_SBUStoSCOM(pWrite , XDATAx->XDATA_Operating.TX_Buffer.data))
    {
        return ERROR;
    }
    
    XDATAx->XDATA_Operating.TX_Buffer.len = 25;
    
    /*  �����ݴ�XDATA TX ���棬���͸�LORA */
    if (ERROR == LORA_WriteData(XDATAx->XDATA_Hardware.LORAx , &XDATAx->XDATA_Operating.TX_Buffer))
    {
        return ERROR;
    }
    
    
    return SUCCESS;
}





/**
 * @brief  �� XDATA ͨ��
 * @param  XDATAx�� ��Ҫ�򿪵� XDATA ͨ��
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
 * @brief  �ر� XDATA ͨ��
 * @param  XDATAx�� ��Ҫ�رյ� XDATA ͨ��
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


