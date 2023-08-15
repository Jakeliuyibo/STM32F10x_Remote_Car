/**
  ******************************************************************************
  * @file    led.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/3/13
  * @brief   ������led��Ӧ�ò�Ĺ���ʵ��
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
 * @brief  ��ʼ��LED
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
 * @brief  led����ʱdelay_time��˸
 * @param  **LEDx           : LED�ṹ��
 *         *delay_time      : ��Ҫ��˸�ļ��
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
 * @brief  ��ʱ����ʱ�жϳ�ʼ��
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

    TIM_ITConfig(LED_DELAY_TIMER, TIM_IT_Update, ENABLE); // �������ʱ�����ж�
    TIM_Cmd(LED_DELAY_TIMER, DISABLE);
  
    NVIC_InitStructure.NVIC_IRQChannel = LED_DELAY_TIMER_IRQ;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���		 
}


#if LED_DELAY_TIMER2_IRQ
void TIM2_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //���TIMx�����жϷ������
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		}
}
#endif


#if LED_DELAY_TIMER3_IRQ
void TIM3_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //���TIMx�����жϷ������
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		}
}
#endif


#if LED_DELAY_TIMER4_IRQ
void TIM4_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //���TIMx�����жϷ������
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		}
}
#endif

#if LED_DELAY_TIMER5_IRQ
void TIM5_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //���TIMx�����жϷ������
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		}
}
#endif

#if LED_DELAY_TIMER6_IRQ
void TIM6_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //���TIMx�����жϷ������
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		}
}
#endif

#if LED_DELAY_TIMER7_IRQ
void TIM7_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //���TIMx�����жϷ������
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		}
}
#endif

#if LED_DELAY_TIMER8_IRQ
void TIM8_IRQHandler(void)   
{
    if (TIM_GetITStatus(LED_DELAY_TIMER, TIM_IT_Update) != RESET)  //���TIMx�����жϷ������
    { 
        gTimer++;
        TIM_ClearITPendingBit(LED_DELAY_TIMER, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		}
}
#endif






