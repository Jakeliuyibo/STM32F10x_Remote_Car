/**
  ******************************************************************************
  * @file    bsp_ultrasonic.c
  * @author  LYB
  * @version V1.0.3
  * @date    202/6/6
  * @brief   �����˵ײ㳬�������ģ��Ĺ���ʵ��
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_ultrasonic.h"




/* Global variable -----------------------------------------------------------*/



/* Struct base ---------------------------------------------------------------*/
SONIC_TypeDef_Struct          SONIC1_BASE,SONIC2_BASE,SONIC3_BASE;




/* Interrupt variable --------------------------------------------------------*/




/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_SONIC_GPIO_Config(SONIC_TypeDef_Struct *SONICx);
ErrorStatus BSP_SONIC_TIM_Config(SONIC_TypeDef_Struct *SONICx);
ErrorStatus BSP_SONIC_TIM_NVIC_Config(SONIC_TypeDef_Struct *SONICx);



/* Public functions ----------------------------------------------------------*/


/**
 * @brief  ��ʼ��SONIC�ṹ��Ĭ������
 * @param  SONIC_InitStruct : SONIC��ʼ���ṹ��
 * @return void
 */
void BSP_SONIC_InitStruct(SONIC_InitTypedef_Struct *SONIC_InitStruct)
{
    SONIC_InitStruct->enable_SONIC            = ENABLE_SONIC_DEFAULT; 
    SONIC_InitStruct->enable_EXTI             = ENABLE_EXTI_DEFAULT;

    SONIC_InitStruct->SONIC_EXTI_PrePriorinty = SONIC_EXTI_PREPRIORINTY_DEFAULT;
    SONIC_InitStruct->SONIC_EXTI_SubPriorinty = SONIC_EXTI_SUBPRIORINTY_DEFAULT;
  
    SONIC_InitStruct->SONIC_TIM_Prescaler     = SONIC_TIM_PRESCALER_DEFAULT;
    SONIC_InitStruct->SONIC_TIM_Period        = SONIC_TIM_PERIOD_DEFAULT;
  
    SONIC_InitStruct->SONIC_TIM_PrePriorinty  = SONIC_TIM_PREPRIORINTY_DEFAULT;
    SONIC_InitStruct->SONIC_TIM_SubPriorinty  = SONIC_TIM_SUBPRIORINTY_DEFAULT;
}


/**
 * @brief  ��ʼ��ULTRASONIC�ṹ��
 * @param  *SONICx            : SONIC�ṹ��
 *         *SONIC_InitStruct  : SONIC��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_Init(SONIC_TypeDef_Struct *SONICx , SONIC_InitTypedef_Struct *SONIC_InitStruct)
{
    if ((SONICx == NULL) || (SONIC_InitStruct == NULL))
    {
        return ERROR;
    }
    
    /* SONIC �Ĵ�������     */
    SONICx->SONIC_Operating.enable_SONIC                      = SONIC_InitStruct->enable_SONIC;
    SONICx->SONIC_Operating.EXTI_InitStruct.enable_EXTI       = SONIC_InitStruct->enable_EXTI;

    SONICx->SONIC_Operating.EXTI_InitStruct.EXTI_PrePriorinty = SONIC_InitStruct->SONIC_EXTI_PrePriorinty;
    SONICx->SONIC_Operating.EXTI_InitStruct.EXTI_SubPriorinty = SONIC_InitStruct->SONIC_EXTI_SubPriorinty;
    
    SONICx->SONIC_Operating.TIM_TimeBaseInit.TIM_Prescaler    = SONIC_InitStruct->SONIC_TIM_Prescaler;
    SONICx->SONIC_Operating.TIM_TimeBaseInit.TIM_Period       = SONIC_InitStruct->SONIC_TIM_Period;

    SONICx->SONIC_Operating.TIM_PrePriorinty                  =  SONIC_InitStruct->SONIC_TIM_PrePriorinty;
    SONICx->SONIC_Operating.TIM_SubPriorinty                  =  SONIC_InitStruct->SONIC_TIM_SubPriorinty;
    
    SONICx->SONIC_Operating.overFlow                          =  0;   
    SONICx->SONIC_Operating.time                              =  0;
    SONICx->SONIC_Operating.updateFlag                        =  RESET;
    SONICx->SONIC_Operating.startFlag                         =  RESET;
    
    /* SONIC Ӳ������      */
    if (SONICx == SONIC1)
    {
        SONICx->SONIC_Hardware.EXTIx           = SONIC1_EXTI;
        SONICx->SONIC_Hardware.TIMx            = SONIC1_TIMER;
        SONICx->SONIC_Hardware.TIM_IRQn        = SONIC1_TIMER_IRQ;
        SONICx->SONIC_Hardware.SONIC_TRIG_GPIO = SONIC1_TRIG_GPIO;
        SONICx->SONIC_Hardware.SONIC_TRIG_PIN  = SONIC1_TRIG_GPIO_PIN;
    }
    else if (SONICx == SONIC2)
    {
        SONICx->SONIC_Hardware.EXTIx           = SONIC2_EXTI;
        SONICx->SONIC_Hardware.TIMx            = SONIC2_TIMER;
        SONICx->SONIC_Hardware.TIM_IRQn        = SONIC2_TIMER_IRQ;
        SONICx->SONIC_Hardware.SONIC_TRIG_GPIO = SONIC2_TRIG_GPIO;
        SONICx->SONIC_Hardware.SONIC_TRIG_PIN  = SONIC2_TRIG_GPIO_PIN;
    }
    else 
    {
        return ERROR;
    }
    
    /*  ��ʼ�� SONIC GPIO ����       */
    if (ERROR == BSP_SONIC_GPIO_Config(SONICx))
    {
        return ERROR;
    } 

    /* ��ʼ��SONIC TIM ����          */
    if (ERROR == BSP_SONIC_TIM_Config(SONICx))
    {
        return ERROR;
    }
    
    /* ��ʼ��SONIC TIM �ж�����      */
    if (ERROR == BSP_SONIC_TIM_NVIC_Config(SONICx))
    {
        return ERROR;
    }
    
    SONICx->SONIC_Operating.EXTI_InitStruct.EXTI_LineCmd      = ENABLE;
    SONICx->SONIC_Operating.EXTI_InitStruct.EXTI_Mode         = EXTI_Mode_Interrupt;
    SONICx->SONIC_Operating.EXTI_InitStruct.EXTI_Trigger      = EXTI_Trigger_Rising_Falling;
    
    /* ��ʼ�� SONIC EXTI ����        */
    BSP_EXTI_Init(SONICx->SONIC_Hardware.EXTIx , &SONICx->SONIC_Operating.EXTI_InitStruct);    

    
    return SUCCESS;
}




/**
 * @brief  �� SONICx ͨ��
 * @param  *SONICx            : SONIC�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Open(SONIC_TypeDef_Struct *SONICx)
{
    if (SONICx == NULL)
    {
        return ERROR;
    }
    
    SONICx->SONIC_Operating.enable_SONIC  = ENABLE;
    EXTI_Open(SONICx->SONIC_Hardware.EXTIx);

    return SUCCESS;
}


/**
 * @brief  �ر� SONICx ͨ��
 * @param  *SONICx            : ULTRASONIC�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Close(SONIC_TypeDef_Struct *SONICx)
{
    if (SONICx == NULL)
    {
        return ERROR;
    }
    
    SONICx->SONIC_Operating.enable_SONIC  = DISABLE;
    EXTI_Close(SONICx->SONIC_Hardware.EXTIx);

    return SUCCESS;
}


/**
 * @brief  ���� SONICx ͨ������
 * @param  *SONICx            : SONIC �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus SONIC_Start(SONIC_TypeDef_Struct *SONICx)
{
    if (SONICx == NULL)
    {
        return ERROR;
    }
    
    GPIO_SetBits(SONICx->SONIC_Hardware.SONIC_TRIG_GPIO , SONICx->SONIC_Hardware.SONIC_TRIG_PIN);
    Delay_us(10);
    GPIO_ResetBits(SONICx->SONIC_Hardware.SONIC_TRIG_GPIO , SONICx->SONIC_Hardware.SONIC_TRIG_PIN);
    
    SONICx->SONIC_Operating.startFlag = SET;
    
    return SUCCESS;
}




/**
 * @brief  SONICx �жϷ����� ״̬����������
 *         s0: �ж��Ƿ���ȷ�Ĵ��� ���������ȷ��Ϊ����������ת��s1 ���� ��һ״̬Ϊs0 
 *         s1: ��ղ��򿪶�ʱ����ʱ                                     ��һ״̬Ϊs2                                     
 *         s2: �ж��Ƿ�Ϊ�½���   �����ȷ�������ߵ�ƽʱ�� ���±�־λ ��һ״̬Ϊs0  
 * @param  *SONICx            : SONIC �ṹ�� 
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_EXTI_IRQHandler(SONIC_TypeDef_Struct *SONICx)
{
    EXTI_TypeDef_Struct *pEXTIx = SONICx->SONIC_Hardware.EXTIx;
  
    static uint8_t state_machine = 0;
  
    if (SONICx == NULL)
    {
        return ERROR;
    }

    switch (state_machine)
    {
        case 0: 
            if ((SONICx->SONIC_Operating.startFlag == SET) && (pEXTIx->EXTI_Operating.risingFlag == SET))
            {                    
                /* �����־λ                      */
                pEXTIx->EXTI_Operating.risingFlag = RESET;
                
                /* ����break ��ת��ִ��s1          */           
                state_machine = 1;
            }
            else
            {
                state_machine = 0;
                break;
            }
          
        case 1: 
            /* ��ղ�������ʱ��                    */
            SONICx->SONIC_Operating.overFlow = 0;
            TIM_SetCounter(SONICx->SONIC_Hardware.TIMx , 0);                          
            TIM_Cmd(SONICx->SONIC_Hardware.TIMx , ENABLE);
            state_machine = 2;
            break;
        
        case 2:
          
            /* �رն�ʱ��                          */
            TIM_Cmd(SONICx->SONIC_Hardware.TIMx , DISABLE);
        
            if (pEXTIx->EXTI_Operating.fallingFlag == SET)      /* ����Ϊ�½���   */
            {
                /* �����־λ                      */
                pEXTIx->EXTI_Operating.fallingFlag = RESET;
              
                /* ����ߵ�ƽ����ʱ��              */
                SONICx->SONIC_Operating.time = TIM_GetCounter(SONICx->SONIC_Hardware.TIMx)
                + SONICx->SONIC_Operating.overFlow * (SONICx->SONIC_Operating.TIM_TimeBaseInit.TIM_Period + 1);
                
                /* ���¸ߵ�ƽ����ʱ���־λ        */
                SONICx->SONIC_Operating.updateFlag = SET;  
              
                /* ִ����һ��ѭ�� ���������־λ   */
                SONICx->SONIC_Operating.startFlag = RESET;
            }      
            state_machine = 0;
            break;
          
        default:
            state_machine = 0;
            break;
    
    }
    
    /* ��������ر�־λ                */
    pEXTIx->EXTI_Operating.risingFlag = RESET;

    /* ����½��ر�־λ                */
    pEXTIx->EXTI_Operating.fallingFlag = RESET;

    return SUCCESS;

}


/**
 * @brief  SONICx TIM ����жϷ�����
 * @param  *SONICx            : SONIC �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_TIM_OverFlow_IRQHandler(SONIC_TypeDef_Struct *SONICx)
{
    if (SONICx == NULL)
    {
        return ERROR;
    }
    
    if (TIM_GetITStatus(SONICx->SONIC_Hardware.TIMx , TIM_IT_Update) != RESET)  
    { 
        /*  ��������жϱ�־ */
        TIM_ClearITPendingBit(SONICx->SONIC_Hardware.TIMx , TIM_IT_Update);
        SONICx->SONIC_Operating.overFlow++;
		}
 
    return SUCCESS;

}



/* Private functions ---------------------------------------------------------*/

/**
 * @brief  ��ʼ�� SONIC GPIO �Ĵ���
 * @param  *SONICx       : SONIC �ṹ�� 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_GPIO_Config(SONIC_TypeDef_Struct *SONICx)
{   
    GPIO_InitTypeDef    GPIO_InitStructure;
  
    if (SONICx == NULL)
    {
        return ERROR;
    }
    
    GPIO_InitStructure.GPIO_Pin   = SONICx->SONIC_Hardware.SONIC_TRIG_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SONICx->SONIC_Hardware.SONIC_TRIG_GPIO , &GPIO_InitStructure);
    
    GPIO_ResetBits(SONICx->SONIC_Hardware.SONIC_TRIG_GPIO ,SONICx->SONIC_Hardware.SONIC_TRIG_PIN);
    
    return SUCCESS;
}


/**
 * @brief  ��ʼ�� SONIC TIM �Ĵ���
 * @param  *SONICx       : SONIC �ṹ�� 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_TIM_Config(SONIC_TypeDef_Struct *SONICx)
{   
    if (SONICx == NULL)
    {
        return ERROR;
    }
    
    SONICx->SONIC_Operating.TIM_TimeBaseInit.TIM_CounterMode       = TIM_CounterMode_Up;
    SONICx->SONIC_Operating.TIM_TimeBaseInit.TIM_ClockDivision     = 0;
    SONICx->SONIC_Operating.TIM_TimeBaseInit.TIM_RepetitionCounter = 0;
    
    /*  ��ʼ�� SONIC TIM ʱ������    */
    TIM_DeInit(SONICx->SONIC_Hardware.TIMx);
    TIM_TimeBaseInit(SONICx->SONIC_Hardware.TIMx , &SONICx->SONIC_Operating.TIM_TimeBaseInit);
    
    /* ��������ж�                  */
    TIM_ClearFlag(SONICx->SONIC_Hardware.TIMx , TIM_FLAG_Update);   
    
    /* ʹ�� SONIC TIM �ж�           */
    TIM_ITConfig(SONICx->SONIC_Hardware.TIMx , TIM_IT_Update , ENABLE);
    
    /* ʧ�� SONIC TIM ��ʱ��         */                     
    TIM_Cmd(SONICx->SONIC_Hardware.TIMx , DISABLE);
    
    return SUCCESS;  
}




/**
 * @brief  ��ʼ�� SONIC TIM NVIC �Ĵ���
 * @param  *SONICx       : SONIC �ṹ�� 
 * @return ErrorStatus   : ERROR or SUCCESS   
 */
ErrorStatus BSP_SONIC_TIM_NVIC_Config(SONIC_TypeDef_Struct *SONICx)
{   
    NVIC_InitTypeDef     NVIC_InitStructure;
  
    if (SONICx == NULL)
    {
        return ERROR;
    }
    
    NVIC_InitStructure.NVIC_IRQChannel                    = SONICx->SONIC_Hardware.TIM_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = SONICx->SONIC_Operating.TIM_PrePriorinty;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = SONICx->SONIC_Operating.TIM_SubPriorinty;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);

    return SUCCESS;  
}




