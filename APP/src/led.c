/**
  ******************************************************************************
  * @file    led.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/3/13
  * @brief   描述了led的应用层的功能实现
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "led.h"
#include "stdlib.h"

/* volatile variable ---------------------------------------------------------*/
volatile u32 gTimer = 0;

/* Private functions declaration----------------------------------------------*/
static void TIM_delay_Init(void);

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  初始化LED
 */
void led_init(void)
{
    LED_InitTypeDef_Struct LED_InitStruct;

    BSP_LED_InitStruct(&LED_InitStruct);

    LED_InitStruct.LED_Hardware.LED_GPIO = LED1_GPIO;
    LED_InitStruct.LED_Hardware.LED_PIN  = LED1_PIN;
    BSP_LED_Init(LED1,&LED_InitStruct);
  
//    LED_InitStruct.LED_Hardware.LED_GPIO = LED2_GPIO;
//    LED_InitStruct.LED_Hardware.LED_PIN  = LED2_PIN;
//    BSP_LED_Init(LED2,&LED_InitStruct);
  
    TIM_delay_Init();
    TIM_Cmd(LED_DELAY_TIMER, ENABLE);
}


/**
 * @brief  led灯延时delay_time闪烁
 * @param  **LEDx           : LED结构体
 *         *delay_time      : 需要闪烁的间隔
 */
void led_display(LED_TypeDef_Struct *LEDx , u32 delay_time)
{
    u32 temp = 0;
  
    if((gTimer % delay_time) == 0)
    {
        temp = gTimer / delay_time;
        if((temp % 2) == 0)
        {
            LED_Open(LEDx);
        }
        else 
        {
            LED_Close(LEDx);   
        }
    }
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  定时器延时中断初始化
 */
static void TIM_delay_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(LED_DELAY_TIMER_RCC, ENABLE); 

    TIM_DeInit(LED_DELAY_TIMER);
    TIM_TimeBaseStructure.TIM_Period=1;
    TIM_TimeBaseStructure.TIM_Prescaler=(36000-1);
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(LED_DELAY_TIMER,&TIM_TimeBaseStructure);
    TIM_ClearFlag(LED_DELAY_TIMER,TIM_FLAG_Update);
    TIM_ITConfig(LED_DELAY_TIMER,TIM_IT_Update,ENABLE);
    TIM_Cmd(LED_DELAY_TIMER,DISABLE);

    TIM_ITConfig(LED_DELAY_TIMER, TIM_IT_Update, ENABLE); // 计数溢出时触发中断
    TIM_Cmd(LED_DELAY_TIMER, DISABLE);
  
    NVIC_InitStructure.NVIC_IRQChannel = LED_DELAY_TIMER_IRQ;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器		 
}


#if LED_DELAY_TIMER2_IRQ
void TIM2_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //检查TIMx更新中断发生与否
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}
#endif


#if LED_DELAY_TIMER3_IRQ
void TIM3_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //检查TIMx更新中断发生与否
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}
#endif


#if LED_DELAY_TIMER4_IRQ
void TIM4_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //检查TIMx更新中断发生与否
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}
#endif

#if LED_DELAY_TIMER5_IRQ
void TIM5_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //检查TIMx更新中断发生与否
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}
#endif

#if LED_DELAY_TIMER6_IRQ
void TIM6_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //检查TIMx更新中断发生与否
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}
#endif

#if LED_DELAY_TIMER7_IRQ
void TIM7_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //检查TIMx更新中断发生与否
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}
#endif

#if LED_DELAY_TIMER8_IRQ
void TIM8_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //检查TIMx更新中断发生与否
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //清除TIMx更新中断标志 
		}
}
#endif






