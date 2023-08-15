/**
  ******************************************************************************
  * @file    bsp_pwm.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/24
  * @brief   描述了底层PWM的驱动实现
  ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_pwm.h"

/* Global variable -----------------------------------------------------------*/
PWM_TypeDef_Struct   PWM1_BASE,PWM2_BASE,PWM3_BASE,PWM4_BASE;
PWM_TypeDef_Struct   PWM5_BASE,PWM6_BASE,PWM7_BASE,PWM8_BASE;
PWM_TypeDef_Struct   PWM9_BASE,PWM10_BASE,PWM11_BASE,PWM12_BASE;


/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_PWM_GPIO_Config(PWM_TypeDef_Struct *PWMx);



/* Public functions ----------------------------------------------------------*/

/**
 * @brief  初始化 PWM 结构体默认配置
 * @param  PWM_InitStruct  : PWM初始化结构体
 * @return void
 */
void BSP_PWM_InitStruct(PWM_InitTypedef_Struct *PWM_InitStruct)
{
    PWM_InitStruct->enable_PWM                = PWM_ENABLE_DEFAULT;               /* PWM 使能                */
  
    PWM_InitStruct->PWM_TIM_Prescaler         = PWM_TIM_PRESCALER_DEFAULT;        /* PWM TIM 时基 分频系数   */
    PWM_InitStruct->PWM_TIM_Period            = PWM_TIM_PERIOD_DEFAULT;           /* PWM TIM 时基 预转载值   */
  
    PWM_InitStruct->PWM_TIM_OCMode            = PWM_TIM_OCMODE_DEFAULT;           /* PWM TIM OC 输出模式     */
    PWM_InitStruct->PWM_TIM_OutputState       = PWM_TIM_OUTPUTSTATE_DEFAULT;      /* PWM TIM OC 比较输出状态 */
    PWM_InitStruct->PWM_TIM_OutputNState      = PWM_TIM_OUTPUTNSTATE_DEFAULT;     /* PWM TIM OC 互补输出状态 */
    PWM_InitStruct->PWM_TIM_Pulse             = PWM_TIM_PULSE_DEFAULT;            /* PWM TIM OC 占空比       */
    PWM_InitStruct->PWM_TIM_OCPolarity        = PWM_TIM_OCPOLARITY_DEFAULT;       /* PWM TIM OC 输出比较极性 */
    PWM_InitStruct->PWM_TIM_OCNPolarity       = PWM_TIM_OCNPOLARITY_DEFAULT;      /* PWM TIM OC 输出互补极性 */
    PWM_InitStruct->PWM_TIM_OCIdleState       = PWM_TIM_OCIDLESTATE_DEFAULT;      /* PWM TIM OC 空闲输出状态 */
    PWM_InitStruct->PWM_TIM_OCNIdleState      = PWM_TIM_OCNIDLESTATE_DEFAULT;     /* PWM TIM OC 空闲互补状态 */ 
                  
}



/**
 * @brief  初始化 PWM 结构体
 * @param  *PWMx           : PWM结构体
 *         *PWM_InitStruct : PWM初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_PWM_Init(PWM_TypeDef_Struct *PWMx , PWM_InitTypedef_Struct *PWM_InitStruct)
{
    if ( (PWMx == NULL) || (PWM_InitStruct == NULL) )
    {
        return ERROR;
    }
  
    /*  PWM 寄存器赋值   */
    PWMx->PWM_Operating.enable_PWM                       = PWM_InitStruct->enable_PWM; 
   
    PWMx->PWM_Operating.TIM_TimeBaseInit.TIM_Prescaler   = PWM_InitStruct->PWM_TIM_Prescaler; 
    PWMx->PWM_Operating.TIM_TimeBaseInit.TIM_Period      = PWM_InitStruct->PWM_TIM_Period;     
   
    PWMx->PWM_Operating.TIM_OCInit.TIM_OCMode            = PWM_InitStruct->PWM_TIM_OCMode;
    PWMx->PWM_Operating.TIM_OCInit.TIM_OutputState       = PWM_InitStruct->PWM_TIM_OutputState;
    PWMx->PWM_Operating.TIM_OCInit.TIM_OutputNState      = PWM_InitStruct->PWM_TIM_OutputNState;  
    PWMx->PWM_Operating.TIM_OCInit.TIM_Pulse             = PWM_InitStruct->PWM_TIM_Pulse;     
    PWMx->PWM_Operating.TIM_OCInit.TIM_OCPolarity        = PWM_InitStruct->PWM_TIM_OCPolarity;  
    PWMx->PWM_Operating.TIM_OCInit.TIM_OCNPolarity       = PWM_InitStruct->PWM_TIM_OCNPolarity;
    PWMx->PWM_Operating.TIM_OCInit.TIM_OCIdleState       = PWM_InitStruct->PWM_TIM_OCIdleState; 
    PWMx->PWM_Operating.TIM_OCInit.TIM_OCNIdleState      = PWM_InitStruct->PWM_TIM_OCNIdleState; 


    /*  PWM 硬件赋值  */
    if (PWMx == PWM1)
    {
        PWM1_BASE.PWM_Hardware.TIMx              = PWM1_TIMER;
        PWM1_BASE.PWM_Hardware.TIM_Channel       = PWM1_TIM_CHANNEL;
        PWM1_BASE.PWM_Hardware.TIM_Channel_Remap = PWM1_TIM_CHANNEL_REMAP;
        PWM1_BASE.PWM_Hardware.PWM_GPIO          = PWM1_GPIO;
        PWM1_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM1_GPIO_PIN;
    }
    else if (PWMx == PWM2)
    {
        PWM2_BASE.PWM_Hardware.TIMx              = PWM2_TIMER;
        PWM2_BASE.PWM_Hardware.TIM_Channel       = PWM2_TIM_CHANNEL;
        PWM2_BASE.PWM_Hardware.TIM_Channel_Remap = PWM2_TIM_CHANNEL_REMAP;
        PWM2_BASE.PWM_Hardware.PWM_GPIO          = PWM2_GPIO;
        PWM2_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM2_GPIO_PIN;
    }
    else if (PWMx == PWM3)
    {
        PWM3_BASE.PWM_Hardware.TIMx              = PWM3_TIMER;
        PWM3_BASE.PWM_Hardware.TIM_Channel       = PWM3_TIM_CHANNEL;
        PWM3_BASE.PWM_Hardware.TIM_Channel_Remap = PWM3_TIM_CHANNEL_REMAP;
        PWM3_BASE.PWM_Hardware.PWM_GPIO          = PWM3_GPIO;
        PWM3_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM3_GPIO_PIN;
    }
    else if (PWMx == PWM4)
    {
        PWM4_BASE.PWM_Hardware.TIMx              = PWM4_TIMER;
        PWM4_BASE.PWM_Hardware.TIM_Channel       = PWM4_TIM_CHANNEL;
        PWM4_BASE.PWM_Hardware.TIM_Channel_Remap = PWM4_TIM_CHANNEL_REMAP;
        PWM4_BASE.PWM_Hardware.PWM_GPIO          = PWM4_GPIO;
        PWM4_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM4_GPIO_PIN;
    }
    else if (PWMx == PWM5)
    {
        PWM5_BASE.PWM_Hardware.TIMx              = PWM5_TIMER;
        PWM5_BASE.PWM_Hardware.TIM_Channel       = PWM5_TIM_CHANNEL;
        PWM5_BASE.PWM_Hardware.TIM_Channel_Remap = PWM5_TIM_CHANNEL_REMAP;
        PWM5_BASE.PWM_Hardware.PWM_GPIO          = PWM5_GPIO;
        PWM5_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM5_GPIO_PIN;
    }
    else if (PWMx == PWM6)
    {
        PWM6_BASE.PWM_Hardware.TIMx              = PWM6_TIMER;
        PWM6_BASE.PWM_Hardware.TIM_Channel       = PWM6_TIM_CHANNEL;
        PWM6_BASE.PWM_Hardware.TIM_Channel_Remap = PWM6_TIM_CHANNEL_REMAP;
        PWM6_BASE.PWM_Hardware.PWM_GPIO          = PWM6_GPIO;
        PWM6_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM6_GPIO_PIN;
    }
    else if (PWMx == PWM7)
    {
        PWM7_BASE.PWM_Hardware.TIMx              = PWM7_TIMER;
        PWM7_BASE.PWM_Hardware.TIM_Channel       = PWM7_TIM_CHANNEL;
        PWM7_BASE.PWM_Hardware.TIM_Channel_Remap = PWM7_TIM_CHANNEL_REMAP;
        PWM7_BASE.PWM_Hardware.PWM_GPIO          = PWM7_GPIO;
        PWM7_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM7_GPIO_PIN;
    }
    else if (PWMx == PWM8)
    {
        PWM8_BASE.PWM_Hardware.TIMx              = PWM8_TIMER;
        PWM8_BASE.PWM_Hardware.TIM_Channel       = PWM8_TIM_CHANNEL;
        PWM8_BASE.PWM_Hardware.TIM_Channel_Remap = PWM8_TIM_CHANNEL_REMAP;
        PWM8_BASE.PWM_Hardware.PWM_GPIO          = PWM8_GPIO;
        PWM8_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM8_GPIO_PIN;
    }
    else if (PWMx == PWM9)
    {
        PWM9_BASE.PWM_Hardware.TIMx              = PWM9_TIMER;
        PWM9_BASE.PWM_Hardware.TIM_Channel       = PWM9_TIM_CHANNEL;
        PWM9_BASE.PWM_Hardware.TIM_Channel_Remap = PWM9_TIM_CHANNEL_REMAP;
        PWM9_BASE.PWM_Hardware.PWM_GPIO          = PWM9_GPIO;
        PWM9_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM9_GPIO_PIN;
    }
    else if (PWMx == PWM10)
    {
        PWM10_BASE.PWM_Hardware.TIMx              = PWM10_TIMER;
        PWM10_BASE.PWM_Hardware.TIM_Channel       = PWM10_TIM_CHANNEL;
        PWM10_BASE.PWM_Hardware.TIM_Channel_Remap = PWM10_TIM_CHANNEL_REMAP;
        PWM10_BASE.PWM_Hardware.PWM_GPIO          = PWM10_GPIO;
        PWM10_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM10_GPIO_PIN;
    }
    else if (PWMx == PWM11)
    {
        PWM11_BASE.PWM_Hardware.TIMx              = PWM11_TIMER;
        PWM11_BASE.PWM_Hardware.TIM_Channel       = PWM11_TIM_CHANNEL;
        PWM11_BASE.PWM_Hardware.TIM_Channel_Remap = PWM11_TIM_CHANNEL_REMAP;
        PWM11_BASE.PWM_Hardware.PWM_GPIO          = PWM11_GPIO;
        PWM11_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM11_GPIO_PIN;
    }
    else if (PWMx == PWM12)
    {
        PWM12_BASE.PWM_Hardware.TIMx              = PWM12_TIMER;
        PWM12_BASE.PWM_Hardware.TIM_Channel       = PWM12_TIM_CHANNEL;
        PWM12_BASE.PWM_Hardware.TIM_Channel_Remap = PWM12_TIM_CHANNEL_REMAP;
        PWM12_BASE.PWM_Hardware.PWM_GPIO          = PWM12_GPIO;
        PWM12_BASE.PWM_Hardware.PWM_GPIO_PIN      = PWM12_GPIO_PIN;
    }
    else
    {
        return ERROR;
    }
    
    
    /*  初始化PWM GPIO          */
    if (ERROR == BSP_PWM_GPIO_Config(PWMx))
    {
        return ERROR;
    }
    
    PWMx->PWM_Operating.TIM_TimeBaseInit.TIM_CounterMode       = TIM_CounterMode_Up;
    PWMx->PWM_Operating.TIM_TimeBaseInit.TIM_ClockDivision     = 0;
    PWMx->PWM_Operating.TIM_TimeBaseInit.TIM_RepetitionCounter = 0;
    
    /*  初始化 PWM TIM 时基      */
    TIM_TimeBaseInit(PWMx->PWM_Hardware.TIMx , &PWMx->PWM_Operating.TIM_TimeBaseInit);
    
    
    /*  配置 PWM TIM 输出比较  */   
    if (PWMx->PWM_Hardware.TIM_Channel == 1)
    {
        TIM_OC1Init(PWMx->PWM_Hardware.TIMx , &PWMx->PWM_Operating.TIM_OCInit);
        TIM_OC1PreloadConfig(PWMx->PWM_Hardware.TIMx , TIM_OCPreload_Enable);
    }
    else if (PWMx->PWM_Hardware.TIM_Channel == 2)
    {
        TIM_OC2Init(PWMx->PWM_Hardware.TIMx , &PWMx->PWM_Operating.TIM_OCInit);
        TIM_OC2PreloadConfig(PWMx->PWM_Hardware.TIMx , TIM_OCPreload_Enable);
    }
    else if (PWMx->PWM_Hardware.TIM_Channel == 3)
    {
        TIM_OC3Init(PWMx->PWM_Hardware.TIMx , &PWMx->PWM_Operating.TIM_OCInit);
        TIM_OC3PreloadConfig(PWMx->PWM_Hardware.TIMx , TIM_OCPreload_Enable);
    }
    else if (PWMx->PWM_Hardware.TIM_Channel == 4)
    {
        TIM_OC4Init(PWMx->PWM_Hardware.TIMx , &PWMx->PWM_Operating.TIM_OCInit);
        TIM_OC4PreloadConfig(PWMx->PWM_Hardware.TIMx , TIM_OCPreload_Enable);
    }
    else
    {
        return ERROR;
    }
        
    /*  设置 PWM 占空比  */
    PWMx->PWM_Operating.pwm_duty  = (float)((float)(PWMx->PWM_Operating.TIM_OCInit.TIM_Pulse )
                                          / (float)(PWMx->PWM_Operating.TIM_TimeBaseInit.TIM_Period + 1));
    
    /*  使能定时器ARR预装载寄存器  */
    TIM_ARRPreloadConfig(PWMx->PWM_Hardware.TIMx , ENABLE);
    
    /*  使能定时器                 */
    TIM_Cmd(PWMx->PWM_Hardware.TIMx , ENABLE);
    
    /*  使能定时器输出PWM          */
    TIM_CtrlPWMOutputs(PWMx->PWM_Hardware.TIMx , ENABLE); 
    
    return SUCCESS;
}




/**
 * @brief  使能 PWM 结构体
 * @param  *PWMx           : PWM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PWM_Open(PWM_TypeDef_Struct *PWMx)
{
    if (PWMx == NULL)
    {
        return ERROR;
    }
    
    PWMx->PWM_Operating.enable_PWM = ENABLE;
    
    /*  使能定时器                 */
    TIM_Cmd(PWMx->PWM_Hardware.TIMx , ENABLE);
    
    /*  使能定时器输出PWM          */
    TIM_CtrlPWMOutputs(PWMx->PWM_Hardware.TIMx , ENABLE); 

    return SUCCESS;
}


/**
 * @brief  失能 PWM 结构体
 * @param  *PWMx           : PWM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PWM_Close(PWM_TypeDef_Struct *PWMx)
{
    if (PWMx == NULL)
    {
        return ERROR;
    }
    
    PWMx->PWM_Operating.enable_PWM = DISABLE;
    
    /*  失能定时器输出PWM          */
    TIM_CtrlPWMOutputs(PWMx->PWM_Hardware.TIMx , DISABLE); 
    
    /*  失能定时器                 */
    TIM_Cmd(PWMx->PWM_Hardware.TIMx , DISABLE);
    
    return SUCCESS;
}




/**
 * @brief  设置 PWM 通道占空比
 * @param  *PWMx           : PWM 结构体
 * @param  duty            : 占空比，取值0-1
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PWM_Set_Duty(PWM_TypeDef_Struct *PWMx , float duty)
{
    uint16_t     compare = 0;
  
    if (PWMx == NULL)
    {
        return ERROR;
    }
    
    /* 输出限幅                */
    if (duty > PWM_OUTPUT_AMP_MAX_LIMIT)
    {
        PWMx->PWM_Operating.pwm_duty = PWM_OUTPUT_AMP_MAX_LIMIT;
    }
    else if (duty < PWM_OUTPUT_AMP_MIN_LIMIT)
    {
        PWMx->PWM_Operating.pwm_duty = 0;
    }
    else
    {
        PWMx->PWM_Operating.pwm_duty = duty;
    }
 
    compare = (uint16_t)(PWMx->PWM_Operating.pwm_duty * (PWMx->PWM_Operating.TIM_TimeBaseInit.TIM_Period + 1));
    
    /*  配置 PWM TIM 输出比较  */   
    if (PWMx->PWM_Hardware.TIM_Channel == 1)
    {
        TIM_SetCompare1(PWMx->PWM_Hardware.TIMx , compare);
    }
    else if (PWMx->PWM_Hardware.TIM_Channel == 2)
    {
        TIM_SetCompare2(PWMx->PWM_Hardware.TIMx , compare);
    }
    else if (PWMx->PWM_Hardware.TIM_Channel == 3)
    {
        TIM_SetCompare3(PWMx->PWM_Hardware.TIMx , compare);
    }
    else if (PWMx->PWM_Hardware.TIM_Channel == 4)
    {
        TIM_SetCompare4(PWMx->PWM_Hardware.TIMx , compare);
    }
    else
    {
        return ERROR;
    }
    
    return SUCCESS;
}




/* Private functions ---------------------------------------------------------*/



/**
 * @brief  初始化 PWM GPIO 配置
 * @param  *PWMx           : PWM结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_PWM_GPIO_Config(PWM_TypeDef_Struct *PWMx)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
  
    if ( (PWMx == NULL) || (PWMx->PWM_Hardware.PWM_GPIO     == NULL) 
                        || (PWMx->PWM_Hardware.PWM_GPIO_PIN == NULL) )
    {
        return ERROR;
    }
    
    if (PWMx->PWM_Hardware.TIM_Channel_Remap != NULL)
    {
        GPIO_PinRemapConfig(PWMx->PWM_Hardware.TIM_Channel_Remap , ENABLE);
    }

    GPIO_InitStructure.GPIO_Pin   = PWMx->PWM_Hardware.PWM_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(PWMx->PWM_Hardware.PWM_GPIO , &GPIO_InitStructure);
    
    
    return SUCCESS;
}

