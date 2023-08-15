/**
  ******************************************************************************
  * @file    led.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   描述了led的应用层的功能实现
  ******************************************************************************/
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"
#include "stm32f10x.h"

/* Defitions -----------------------------------------------------------------*/
#define LED_DELAY_TIMER_RCC   RCC_APB1Periph_TIM7        /* 延时定时器时钟  */
#define LED_DELAY_TIMER       TIM7                       /* 延时定时器      */
#define LED_DELAY_TIMER_IRQ   TIM7_IRQn                  /* 延时定时中断向量*/

#define LED_DELAY_TIMER2_IRQ  0                          /* 延时定时器2中断服务函数使能*/
#define LED_DELAY_TIMER3_IRQ  0                          /* 延时定时器3中断服务函数使能*/
#define LED_DELAY_TIMER4_IRQ  0                          /* 延时定时器4中断服务函数使能*/
#define LED_DELAY_TIMER5_IRQ  0                          /* 延时定时器5中断服务函数使能*/
#define LED_DELAY_TIMER6_IRQ  0                          /* 延时定时器6中断服务函数使能*/
#define LED_DELAY_TIMER7_IRQ  1                          /* 延时定时器7中断服务函数使能*/


/* Interface declaration -----------------------------------------------------*/
void led_init(void);
void led_display(LED_TypeDef_Struct *LEDx , u32 delay_time);

#endif




