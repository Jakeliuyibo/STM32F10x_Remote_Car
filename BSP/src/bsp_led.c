/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   描述了底层LED设备的驱动实现
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"


/* Global variable -----------------------------------------------------------*/
LED_TypeDef_Struct          LED1_BASE , LED2_BASE , LED3_BASE;


/* volatile variable ---------------------------------------------------------*/
volatile u32 gTimer = 0;


/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_LED_GPIO_Config(LED_TypeDef_Struct *LEDx);
ErrorStatus BSP_LED_TIM_RCC_Config(LED_TypeDef_Struct *LEDx);
ErrorStatus BSP_LED_TIM_Config(LED_TypeDef_Struct *LEDx);
ErrorStatus BSP_LED_TIM_NVIC_Config(LED_TypeDef_Struct *LEDx);

/* Public functions ----------------------------------------------------------*/


/**
 * @brief  初始化LED结构体默认配置
 * @param  LED_InitStruct : LED初始化结构体
 */
void BSP_LED_InitStruct(LED_InitTypeDef_Struct *LED_InitStruct)
{ 
    LED_InitStruct->enable                  = LED_ENABLE_DEFAULT ;   
    LED_InitStruct->pol                     = LED_POL_DEFAULT    ;   
    LED_InitStruct->delay_time              = LED_DELAY_TIME      ;
  
    LED_InitStruct->LED_TIM_Prescaler       = LED_TIM_PRESCALER_DEFAULT;
    LED_InitStruct->LED_TIM_Period          = LED_TIM_PERIOD_DEFAULT;

    LED_InitStruct->LED_TIM_PrePriorinty    = LED_TIM_PREPRIORINTY_DEFAULT;
    LED_InitStruct->LED_TIM_SubPriorinty    = LED_TIM_SUBPRIORINTY_DEFAULT;
 
}



/**
 * @brief  初始化LED结构体
 * @param  *LEDx            : LED结构体
 *         *LED_InitStruct  : LED初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_Init(LED_TypeDef_Struct *LEDx , LED_InitTypeDef_Struct *LED_InitStruct)
{
  
    if (LED_InitStruct == NULL)                          
    {
        return ERROR;
    }
    
    if (LEDx == LED1)
    {
        LED1_BASE.LED_Hardware.LED_GPIO = LED1_GPIO;
        LED1_BASE.LED_Hardware.LED_PIN  = LED1_PIN;
        LED1_BASE.LED_Hardware.TIMx     = LED1_TIMER;
        LED1_BASE.LED_Hardware.TIM_IRQn = LED1_TIMER_IRQ;
    }
    else if (LEDx == LED2)
    {
        LED2_BASE.LED_Hardware.LED_GPIO = LED2_GPIO;
        LED2_BASE.LED_Hardware.LED_PIN  = LED2_PIN;
        LED2_BASE.LED_Hardware.TIMx     = LED2_TIMER;
        LED2_BASE.LED_Hardware.TIM_IRQn = LED2_TIMER_IRQ;
    }
    else if (LEDx == LED3)
    {
        LED3_BASE.LED_Hardware.LED_GPIO = LED3_GPIO;
        LED3_BASE.LED_Hardware.LED_PIN  = LED3_PIN;
        LED3_BASE.LED_Hardware.TIMx     = LED3_TIMER;
        LED3_BASE.LED_Hardware.TIM_IRQn = LED3_TIMER_IRQ;
    }
    else 
    {
        return ERROR;
    }
    
    /* 寄存器赋值 */
    LEDx->LED_Operating.enable     = LED_InitStruct->enable    ;
    LEDx->LED_Operating.pol        = LED_InitStruct->pol       ;
    LEDx->LED_Operating.delay_time = LED_InitStruct->delay_time;
    
    LEDx->LED_Operating.TIM_TimeBaseInit.TIM_Prescaler          = LED_InitStruct->LED_TIM_Prescaler;
    LEDx->LED_Operating.TIM_TimeBaseInit.TIM_Period             = LED_InitStruct->LED_TIM_Period;
    
    LEDx->LED_Operating.TIM_PrePriorinty  = LED_InitStruct->LED_TIM_PrePriorinty;
    LEDx->LED_Operating.TIM_SubPriorinty  = LED_InitStruct->LED_TIM_SubPriorinty;

    LEDx->LED_Operating.state = RESET;
    
    /* 初始化GPIO寄存器 */
    if (BSP_LED_GPIO_Config(LEDx) == ERROR)
    {
        return ERROR;
    }
    
    /* 初始化LED TIM RCC */
    if (BSP_LED_TIM_RCC_Config(LEDx) == ERROR)
    {
        return ERROR;
    }
    
    /* 初始化LED TIM     */
    if (BSP_LED_TIM_Config(LEDx) == ERROR)
    {
        return ERROR;
    }
    
    /* 初始化TIM NVIC    */
    if (BSP_LED_TIM_NVIC_Config(LEDx) == ERROR)
    {
        return ERROR;
    }
    
    return SUCCESS;
}


/**
 * @brief  根据默认的LED极性,点灯
 * @param  *LEDx           : LED结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Open(LED_TypeDef_Struct *LEDx)
{
    if ((LEDx == NULL) || (LEDx->LED_Hardware.LED_GPIO == NULL) || (LEDx->LED_Hardware.LED_PIN == NULL)
                       || (LEDx->LED_Operating.enable == DISABLE))
    {
        return ERROR;
    }
    
    if (LEDx->LED_Operating.pol == LED_OCPolarity_Low)         /* 低电平点亮LED */
    {
        GPIO_ResetBits(LEDx->LED_Hardware.LED_GPIO , LEDx->LED_Hardware.LED_PIN);
    }
    else if (LEDx->LED_Operating.pol == LED_OCPolarity_High)   /* 高电平点亮LED */
    {
        GPIO_SetBits(LEDx->LED_Hardware.LED_GPIO , LEDx->LED_Hardware.LED_PIN);
    }
    
    LEDx->LED_Operating.state = SET;
    
    return SUCCESS;
}

/**
 * @brief  根据默认的LED极性,关灯
 * @param  *LEDx           : LED结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Close(LED_TypeDef_Struct *LEDx)    
{
    if ((LEDx == NULL) || (LEDx->LED_Hardware.LED_GPIO == NULL) || (LEDx->LED_Hardware.LED_PIN == NULL)
                       || (LEDx->LED_Operating.enable == DISABLE))
    {
        return ERROR;
    }
    
    if (LEDx->LED_Operating.pol == LED_OCPolarity_Low)         /* 低电平点亮LED */
    {
        GPIO_SetBits(LEDx->LED_Hardware.LED_GPIO , LEDx->LED_Hardware.LED_PIN);
    }
    else if (LEDx->LED_Operating.pol == LED_OCPolarity_High)   /* 高电平点亮LED */
    {
        GPIO_ResetBits(LEDx->LED_Hardware.LED_GPIO , LEDx->LED_Hardware.LED_PIN);
    }   

    LEDx->LED_Operating.state = RESET;
    
    return SUCCESS;
}



/**
 * @brief  设置 LED 电平翻转的周期
 * @param  *LEDx           : LED 结构体
 * @param  delay           : 设置 LED 翻转周期 1~1000ms
 * @example     F = 72 000 000 / Prescaler / Period
 *           if Prescaler = 7200 ,then F = 10 000 / Period ,thus F could select 1~10 000Hz ,on other word T = 100us~1s
 *           so if you want T ramap in 1~1000ms , you should sure that Prescaler is avaliable.
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus LED_Set_Duty(LED_TypeDef_Struct *LEDx , u16 delay)
{
    if (LEDx == NULL)
    {
        return ERROR;
    }
    
    LEDx->LED_Operating.delay_time = delay;
    
    return SUCCESS;
}


/**
 * @brief  LEDx TIM 溢出中断服务函数
 * @param  *LEDx            : LED 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_TIM_OverFlow_IRQHandler(LED_TypeDef_Struct *LEDx)
{
    u32 temp = 0;
  
    if (LEDx == NULL)
    {
        return ERROR;
    }
    

    
    if (TIM_GetITStatus(LEDx->LED_Hardware.TIMx , TIM_IT_Update) != RESET)
    { 
        gTimer++;
    
        if((gTimer % LEDx->LED_Operating.delay_time) == 0)
        {
            temp = gTimer / LEDx->LED_Operating.delay_time;
            if((temp % 2) == 0)
            {
                LED_Open(LEDx);
            }
            else 
            {
                LED_Close(LEDx);   
            }
        }
        
        TIM_ClearITPendingBit(LEDx->LED_Hardware.TIMx , TIM_IT_Update  ); 
		}
    
    
//    if (TIM_GetITStatus(LEDx->LED_Hardware.TIMx , TIM_IT_Update) != RESET)
//    { 
//        if (LEDx->LED_Operating.state == SET)
//        {
//            LED_Close(LEDx);
//        }
//        else if (LEDx->LED_Operating.state == RESET)
//        {
//            LED_Open(LEDx);
//        }
//        
//        TIM_ClearITPendingBit(LEDx->LED_Hardware.TIMx , TIM_IT_Update  ); 
//		}
    
    return SUCCESS;
}









/* Private functions ---------------------------------------------------------*/


/**
 * @brief  初始化LED寄存器
 * @param  *LEDx        : LED 结构体 
 * @return ErrorStatus  : ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_GPIO_Config(LED_TypeDef_Struct *LEDx)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  
    if ((LEDx == NULL) || (LEDx->LED_Hardware.LED_GPIO == NULL) || (LEDx->LED_Hardware.LED_PIN == NULL))
    {
        return ERROR;
    }
    
    GPIO_InitStructure.GPIO_Pin   = LEDx->LED_Hardware.LED_PIN   ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    
    GPIO_Init(LEDx->LED_Hardware.LED_GPIO , &GPIO_InitStructure);

    /* 初始化GPIO极性配置 */
    if (LEDx->LED_Operating.pol == LED_OCPolarity_High)
    {
        GPIO_ResetBits(LEDx->LED_Hardware.LED_GPIO , LEDx->LED_Hardware.LED_PIN);
    }
    else if (LEDx->LED_Operating.pol == LED_OCPolarity_Low)
    {
        GPIO_SetBits(LEDx->LED_Hardware.LED_GPIO , LEDx->LED_Hardware.LED_PIN);
    }
    else
    {
        return ERROR;
    } 

    LEDx->LED_Operating.state = RESET;
      
    return SUCCESS;
}



/**
 * @brief  初始化 LED TIM RCC 配置
 * @param  *LEDx           : LED 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_TIM_RCC_Config(LED_TypeDef_Struct *LEDx)
{
    if (LEDx == NULL)
    {
        return ERROR;
    }
    
    /*  开启定时器时钟  */
    if (LEDx->LED_Hardware.TIMx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    }
    else if (LEDx->LED_Hardware.TIMx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    }   
    else if (LEDx->LED_Hardware.TIMx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
    } 
    else if (LEDx->LED_Hardware.TIMx == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);
    }    
    else if (LEDx->LED_Hardware.TIMx == TIM1) 
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
    }
    else if (LEDx->LED_Hardware.TIMx == TIM7) 
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);
    } 
    else if (LEDx->LED_Hardware.TIMx == TIM8) 
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);
    } 
    else 
    {
        return ERROR;
    }
  
    return SUCCESS;
}



/**
 * @brief  初始化 LED TIM 配置
 * @param  *LEDx           : LED 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_TIM_Config(LED_TypeDef_Struct *LEDx)
{
    if (LEDx == NULL)
    {
        return ERROR;
    }
    
    /* 缺省TIM          */
    TIM_DeInit(LEDx->LED_Hardware.TIMx);
    
    LEDx->LED_Operating.TIM_TimeBaseInit.TIM_CounterMode        = TIM_CounterMode_Up;
    LEDx->LED_Operating.TIM_TimeBaseInit.TIM_ClockDivision      = 0;
    LEDx->LED_Operating.TIM_TimeBaseInit.TIM_RepetitionCounter  = 0;

    /* 初始化LED TIM    */
    TIM_TimeBaseInit(LEDx->LED_Hardware.TIMx , &LEDx->LED_Operating.TIM_TimeBaseInit);
    
    /* 清楚更新标志位   */
    TIM_ClearFlag(LEDx->LED_Hardware.TIMx , TIM_FLAG_Update);
    
    /* 使能定时器IT中断 */
    TIM_ITConfig(LEDx->LED_Hardware.TIMx , TIM_IT_Update , ENABLE);
    
    /* 使能  TIM        */
    TIM_Cmd(LEDx->LED_Hardware.TIMx , ENABLE);
    
    return SUCCESS;
}




/**
 * @brief  初始化 LED TIM NVIC 配置
 * @param  *LEDx           : LED 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_LED_TIM_NVIC_Config(LED_TypeDef_Struct *LEDx)
{
    NVIC_InitTypeDef NVIC_InitStructure;
  
    if (LEDx == NULL)
    {
        return ERROR;
    }
    
    NVIC_InitStructure.NVIC_IRQChannel                   = LEDx->LED_Hardware.TIM_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LEDx->LED_Operating.TIM_PrePriorinty;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = LEDx->LED_Operating.TIM_SubPriorinty;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器		
    
    return SUCCESS;
}











