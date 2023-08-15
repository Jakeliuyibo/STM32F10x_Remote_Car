/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  LYB
  * @version V1.0.3
  * @date    202/5/28
  * @brief   �����˵ײ�EXTI�ⲿ�жϵ�����ʵ��
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_exti.h"



/* Global variable -----------------------------------------------------------*/


/* Struct base ---------------------------------------------------------------*/
EXTI_TypeDef_Struct         EXTI1_BASE,EXTI2_BASE,EXTI3_BASE,EXTI4_BASE,EXTI5_BASE,EXTI6_BASE;


/* Interrupt variable --------------------------------------------------------*/



/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_EXTI_GPIO_Config(EXTI_TypeDef_Struct *EXTIx);
ErrorStatus BSP_EXTI_NVIC_Config(EXTI_TypeDef_Struct *EXTIx);



/* Public functions ----------------------------------------------------------*/

/**
 * @brief  ��ʼ��EXTI�ṹ��Ĭ������
 * @param  EXTI_InitStruct : EXTI��ʼ���ṹ��
 */
void BSP_EXTI_InitStruct(EXTI_InitTypedef_Struct *EXTI_InitStruct)
{
  
    EXTI_InitStruct->enable_EXTI       = EXTI_ENABLE_DEFAULT;        /* Ĭ�� EXTI ʹ��         */
    EXTI_InitStruct->EXTI_LineCmd      = EXTI_LINECMD_DEFAULT;       /* Ĭ�� EXTI �ж�Դʹ��   */
    EXTI_InitStruct->EXTI_Mode         = EXTI_MODE_DEFAULT;          /* Ĭ�� EXTI �ж�ģʽ     */
    EXTI_InitStruct->EXTI_Trigger      = EXTI_TRIGGER_DEFAULT;       /* Ĭ�� EXTI �жϴ�����ʽ */
    EXTI_InitStruct->EXTI_PrePriorinty = EXTI_PREPRIORINTY_DEFAULT;  /* Ĭ�� EXTI ��ռ���ȼ�   */
    EXTI_InitStruct->EXTI_SubPriorinty = EXTI_SUBPRIORINTY_DEFAULT;  /* Ĭ�� EXTI �����ȼ�     */           
}


/**
 * @brief  ��ʼ��EXTI�ṹ��
 * @param  *EXTIx            : EXTI�ṹ��
 *         *EXTI_InitStruct  : EXTI��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_Init(EXTI_TypeDef_Struct *EXTIx , EXTI_InitTypedef_Struct *EXTI_InitStruct)
{
    EXTI_InitTypeDef    EXTI_InitStructure;
  
    if ((EXTIx == NULL) || (EXTI_InitStruct == NULL))
    {
        return ERROR;
    }
    
    /*  EXTI ��������   */
    EXTIx->EXTI_Operating.enable_EXTI         = EXTI_InitStruct->enable_EXTI;
    EXTIx->EXTI_Operating.EXTI_LineCmd        = EXTI_InitStruct->EXTI_LineCmd;
    EXTIx->EXTI_Operating.EXTI_Mode           = EXTI_InitStruct->EXTI_Mode;
    EXTIx->EXTI_Operating.EXTI_Trigger        = EXTI_InitStruct->EXTI_Trigger;
    EXTIx->EXTI_Operating.EXTI_PrePriorinty   = EXTI_InitStruct->EXTI_PrePriorinty;
    EXTIx->EXTI_Operating.EXTI_SubPriorinty   = EXTI_InitStruct->EXTI_SubPriorinty;
    
    /*  EXTI ��λ��־   */
    EXTIx->EXTI_Operating.risingFlag          = RESET;    
    EXTIx->EXTI_Operating.fallingFlag         = RESET;

    /*  EXTI Ӳ����ֵ   */
    if (EXTIx == EXTI1)
    {
        EXTI1_BASE.EXTI_Hardware.EXTI_Line       =  EXTI1_LINE;
        EXTI1_BASE.EXTI_Hardware.EXIT_NVIC_IRQn  =  EXTI1_NVIC_IRQn;
        EXTI1_BASE.EXTI_Hardware.EXTI_GPIO       =  EXTI1_GPIO;
        EXTI1_BASE.EXTI_Hardware.EXTI_GPIO_PIN   =  EXTI1_GPIO_PIN;
        EXTI1_BASE.EXTI_Hardware.EXTI_PortSource =  EXTI1_Port_Source;
        EXTI1_BASE.EXTI_Hardware.EXTI_PinSource  =  EXTI1_Pin_Source;
    }
    else if (EXTIx == EXTI2)
    {
        EXTI2_BASE.EXTI_Hardware.EXTI_Line       =  EXTI2_LINE;
        EXTI2_BASE.EXTI_Hardware.EXIT_NVIC_IRQn  =  EXTI2_NVIC_IRQn;
        EXTI2_BASE.EXTI_Hardware.EXTI_GPIO       =  EXTI2_GPIO;
        EXTI2_BASE.EXTI_Hardware.EXTI_GPIO_PIN   =  EXTI2_GPIO_PIN;
        EXTI2_BASE.EXTI_Hardware.EXTI_PortSource =  EXTI2_Port_Source;
        EXTI2_BASE.EXTI_Hardware.EXTI_PinSource  =  EXTI2_Pin_Source;
    }
    else if (EXTIx == EXTI3)
    {
        EXTI3_BASE.EXTI_Hardware.EXTI_Line       =  EXTI3_LINE;
        EXTI3_BASE.EXTI_Hardware.EXIT_NVIC_IRQn  =  EXTI3_NVIC_IRQn;
        EXTI3_BASE.EXTI_Hardware.EXTI_GPIO       =  EXTI3_GPIO;
        EXTI3_BASE.EXTI_Hardware.EXTI_GPIO_PIN   =  EXTI3_GPIO_PIN;
        EXTI3_BASE.EXTI_Hardware.EXTI_PortSource =  EXTI3_Port_Source;
        EXTI3_BASE.EXTI_Hardware.EXTI_PinSource  =  EXTI3_Pin_Source;
    }
    else if (EXTIx == EXTI4)
    {
        EXTI4_BASE.EXTI_Hardware.EXTI_Line       =  EXTI4_LINE;
        EXTI4_BASE.EXTI_Hardware.EXIT_NVIC_IRQn  =  EXTI4_NVIC_IRQn;
        EXTI4_BASE.EXTI_Hardware.EXTI_GPIO       =  EXTI4_GPIO;
        EXTI4_BASE.EXTI_Hardware.EXTI_GPIO_PIN   =  EXTI4_GPIO_PIN;
        EXTI4_BASE.EXTI_Hardware.EXTI_PortSource =  EXTI4_Port_Source;
        EXTI4_BASE.EXTI_Hardware.EXTI_PinSource  =  EXTI4_Pin_Source;
    }
    else if (EXTIx == EXTI5)
    {
        EXTI5_BASE.EXTI_Hardware.EXTI_Line       =  EXTI5_LINE;
        EXTI5_BASE.EXTI_Hardware.EXIT_NVIC_IRQn  =  EXTI5_NVIC_IRQn;
        EXTI5_BASE.EXTI_Hardware.EXTI_GPIO       =  EXTI5_GPIO;
        EXTI5_BASE.EXTI_Hardware.EXTI_GPIO_PIN   =  EXTI5_GPIO_PIN;
        EXTI5_BASE.EXTI_Hardware.EXTI_PortSource =  EXTI5_Port_Source;
        EXTI5_BASE.EXTI_Hardware.EXTI_PinSource  =  EXTI5_Pin_Source;
    }
    else if (EXTIx == EXTI6)
    {
        EXTI6_BASE.EXTI_Hardware.EXTI_Line       =  EXTI6_LINE;
        EXTI6_BASE.EXTI_Hardware.EXIT_NVIC_IRQn  =  EXTI6_NVIC_IRQn;
        EXTI6_BASE.EXTI_Hardware.EXTI_GPIO       =  EXTI6_GPIO;
        EXTI6_BASE.EXTI_Hardware.EXTI_GPIO_PIN   =  EXTI6_GPIO_PIN;
        EXTI6_BASE.EXTI_Hardware.EXTI_PortSource =  EXTI6_Port_Source;
        EXTI6_BASE.EXTI_Hardware.EXTI_PinSource  =  EXTI6_Pin_Source;
    }
    else 
    {
        return ERROR;
    }
    
    /*  ��ʼ�� EXTI GPIO ����*/
    if (ERROR == BSP_EXTI_GPIO_Config(EXTIx))
    {
        return ERROR;
    }
    
    EXTI_InitStructure.EXTI_LineCmd   = EXTIx->EXTI_Operating.EXTI_LineCmd;
    EXTI_InitStructure.EXTI_Line      = EXTIx->EXTI_Hardware.EXTI_Line;
    EXTI_InitStructure.EXTI_Mode      = EXTIx->EXTI_Operating.EXTI_Mode;
    EXTI_InitStructure.EXTI_Trigger   = EXTIx->EXTI_Operating.EXTI_Trigger;
    
    EXTI_Init(&EXTI_InitStructure);

    
    /*  ��ʼ�� EXTI NVIC ����*/
    if (ERROR == BSP_EXTI_NVIC_Config(EXTIx))
    {
        return ERROR;
    }
    
    
    
    return SUCCESS;
}



/**
 * @brief  �� EXTI ͨ��
 * @param  *EXTIx            : EXTI�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus EXTI_Open(EXTI_TypeDef_Struct *EXTIx)
{
    if (EXTIx == NULL)
    {
        return ERROR;
    }
    
    EXTIx->EXTI_Operating.enable_EXTI = ENABLE;
    
    EXTIx->EXTI_Operating.EXTI_LineCmd = ENABLE;
    
    return SUCCESS;
}


/**
 * @brief  �ر� EXTI ͨ��
 * @param  *EXTIx            : EXTI�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus EXTI_Close(EXTI_TypeDef_Struct *EXTIx)
{
    if (EXTIx == NULL)
    {
        return ERROR;
    }
    
    EXTIx->EXTI_Operating.enable_EXTI = DISABLE;
    
    EXTIx->EXTI_Operating.EXTI_LineCmd = DISABLE;
    
    return SUCCESS;
}


/**
 * @brief  EXTI �жϷ�����
 * @param  *EXTIx            : EXTI�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_IRQHandler(EXTI_TypeDef_Struct *EXTIx)
{
  
    if (EXTIx == NULL)
    {
        return ERROR;
    }
    
    if (EXTI_GetFlagStatus(EXTIx->EXTI_Hardware.EXTI_Line) == SET)
    {
      
        /* ����Ϊ������   */
        if (GPIO_ReadInputDataBit(EXTIx->EXTI_Hardware.EXTI_GPIO , EXTIx->EXTI_Hardware.EXTI_GPIO_PIN))
        {
            EXTIx->EXTI_Operating.risingFlag = SET;
        }
        else /* �½��� */
        {
            EXTIx->EXTI_Operating.fallingFlag = SET;
        }
        
        EXTI_ClearFlag(EXTIx->EXTI_Hardware.EXTI_Line);
    }
    else
    {
        return ERROR;
    }
    
    
    return SUCCESS;
}



/* Private functions ---------------------------------------------------------*/







/**
 * @brief  ��ʼ�� EXTI GPIO �Ĵ���
 * @param  *EXTIx        : EXTI �ṹ�� 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_GPIO_Config(EXTI_TypeDef_Struct *EXTIx)
{   
    GPIO_InitTypeDef    GPIO_InitStructure;
  
    if (EXTIx == NULL)
    {
        return ERROR;
    }
    
    GPIO_InitStructure.GPIO_Pin   = EXTIx->EXTI_Hardware.EXTI_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(EXTIx->EXTI_Hardware.EXTI_GPIO , &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(EXTIx->EXTI_Hardware.EXTI_PortSource , EXTIx->EXTI_Hardware.EXTI_PinSource);
    
    return SUCCESS;
    
}


/**
 * @brief  ��ʼ�� EXTI NVIC �Ĵ���
 * @param  *EXTIx        : EXTI �ṹ�� 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_EXTI_NVIC_Config(EXTI_TypeDef_Struct *EXTIx)
{
    NVIC_InitTypeDef     NVIC_InitStructure;
  
    if (EXTIx == NULL)
    {
        return ERROR;
    }

    NVIC_InitStructure.NVIC_IRQChannel                    = EXTIx->EXTI_Hardware.EXIT_NVIC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = EXTIx->EXTI_Operating.EXTI_PrePriorinty;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = EXTIx->EXTI_Operating.EXTI_SubPriorinty;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);
    
    return SUCCESS;
}

