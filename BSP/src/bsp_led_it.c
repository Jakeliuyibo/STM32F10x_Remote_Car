/**
  ******************************************************************************
  * @file    bsp_led_it.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/6/29
  * @brief   �����˵ײ�led tim�жϵķ�����
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"





/* Public functions ----------------------------------------------------------*/




/**
 * @brief  TIM6 �жϷ����� 
 * @param  void
 * @return void
 */
void TIM6_IRQHandler(void)   
{   
    if (TIM6_IRQn == LED1->LED_Hardware.TIM_IRQn)
    {
        BSP_LED_TIM_OverFlow_IRQHandler(LED1);
    }
    else if (TIM6_IRQn == LED2->LED_Hardware.TIM_IRQn)
    {
        BSP_LED_TIM_OverFlow_IRQHandler(LED2);
    }
    else if (TIM6_IRQn == LED3->LED_Hardware.TIM_IRQn)
    {
        BSP_LED_TIM_OverFlow_IRQHandler(LED3);
    }
}


/**
 * @brief  TIM7 �жϷ����� 
 * @param  void
 * @return void
 */
void TIM7_IRQHandler(void)   
{   
    if (TIM7_IRQn == LED1->LED_Hardware.TIM_IRQn)
    {
        BSP_LED_TIM_OverFlow_IRQHandler(LED1);
    }
    else if (TIM7_IRQn == LED2->LED_Hardware.TIM_IRQn)
    {
        BSP_LED_TIM_OverFlow_IRQHandler(LED2);
    }
    else if (TIM7_IRQn == LED3->LED_Hardware.TIM_IRQn)
    {
        BSP_LED_TIM_OverFlow_IRQHandler(LED3);
    }
}

