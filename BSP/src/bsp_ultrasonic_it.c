/**
  ******************************************************************************
  * @file    bsp_ultrasonic_it.c
  * @author  LYB
  * @version V1.0.3
  * @date    202/6/6
  * @brief   描述了底层ultrasonic外部中断的服务函数
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_exti.h"
#include "bsp_ultrasonic.h"





/* Public functions ----------------------------------------------------------*/

/**
 * @brief  EXTI0 中断服务函数 
 * @param  void
 * @return void
 */
void EXTI0_IRQHandler(void)
{
    if (EXTI0_IRQn == EXTI1->EXTI_Hardware.EXIT_NVIC_IRQn)
    {
        BSP_EXTI_IRQHandler(EXTI1);
      
        if (EXTI1 == SONIC1->SONIC_Hardware.EXTIx)
        {
            BSP_SONIC_EXTI_IRQHandler(SONIC1);
        }
        else if(EXTI1 == SONIC2->SONIC_Hardware.EXTIx)
        {
            BSP_SONIC_EXTI_IRQHandler(SONIC2);
        }
    }
}


/**
 * @brief  EXTI4 中断服务函数 
 * @param  void
 * @return void
 */
void EXTI9_5_IRQHandler(void)
{
    if (EXTI9_5_IRQn == EXTI6->EXTI_Hardware.EXIT_NVIC_IRQn)
    {
        BSP_EXTI_IRQHandler(EXTI6);
      
        if (EXTI6 == SONIC1->SONIC_Hardware.EXTIx)
        {
            BSP_SONIC_EXTI_IRQHandler(SONIC1);
        }
        else if(EXTI6 == SONIC2->SONIC_Hardware.EXTIx)
        {
            BSP_SONIC_EXTI_IRQHandler(SONIC2);
        }
    }
}




/**
 * @brief  TIMER5 中断服务函数 
 * @param  void
 * @return void
 */
void TIM5_IRQHandler(void)   
{   
    if (TIM5_IRQn == SONIC1->SONIC_Hardware.TIM_IRQn)
    {
        BSP_SONIC_TIM_OverFlow_IRQHandler(SONIC1);
    }
    else if (TIM5_IRQn == SONIC2->SONIC_Hardware.TIM_IRQn)
    {
        BSP_SONIC_TIM_OverFlow_IRQHandler(SONIC2);
    }

}


