/**
  ******************************************************************************
  * @file    bsp_idwg.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   �����˵ײ�IDWG�豸������ʵ��
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_iwdg.h"


/* Global variable -----------------------------------------------------------*/
IWDG_TypeDef_Struct                 IWDG1_BASE;


/* volatile variable ---------------------------------------------------------*/



/* Private functions declaration----------------------------------------------*/


/* Public functions ----------------------------------------------------------*/


/**
 * @brief  ��ʼ��IWDG�ṹ��Ĭ������
 * @param  IWDG_InitStruct : IWDG��ʼ���ṹ��
 */
void BSP_IWDG_InitStruct(IWDG_InitTypeDef_Struct *IWDG_InitStruct)
{
    IWDG_InitStruct->enable     = IWDG_ENABLE_DEFAULT;
    IWDG_InitStruct->prep       = IWDG_PREP_DEFAULT;
    IWDG_InitStruct->rlr        = IWDG_RLR_DEFAULT;
}


/**
 * @brief  ��ʼ�� IWDG �ṹ��
 * @param  *IWDGx            : IWDG �ṹ��
 *         *IWDG_InitStruct  : IWDG ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_IWDG_Init(IWDG_TypeDef_Struct *IWDGx , IWDG_InitTypeDef_Struct *IWDG_InitStruct)
{
    if (IWDG_InitStruct == NULL)
    {
        return ERROR;
    }
    
    IWDGx->enable  = IWDG_InitStruct->enable;
    IWDGx->prep    = IWDG_InitStruct->prep;
    IWDGx->rlr     = IWDG_InitStruct->rlr;
    
    /* ʹ�ܶ�IWDG_PR IWDG_RLR д���� */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 
	
    /* ����Ԥ��Ƶϵ�� */
    IWDG_SetPrescaler(IWDGx->prep); 
	
    /* ������װ��ֵ   */
    IWDG_SetReload(IWDGx->rlr); 
    
    /* ��ת�ؼ�����   */
    IWDG_ReloadCounter(); 
	
    /* ʹ��IWDG       */
    IWDG_Enable(); 
    
   
    return SUCCESS;
}


/**
 * @brief  ι�� IWDG
 * @param  void
 * @return void
 */
void BSP_IWDG_Feed(void)
{

    IWDG_ReloadCounter(); 
    
}

/* Private functions ---------------------------------------------------------*/











