/**
  ******************************************************************************
  * @file    led.h
  * @author  LYB
  * @version V1.0.1
  * @date    202/3/13
  * @brief   ������led��Ӧ�ò�Ĺ���ʵ��
  ******************************************************************************/
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"
#include "stm32f10x.h"

/* Defitions -----------------------------------------------------------------*/
#define LED_DELAY_TIMER_RCC   RCC_APB1Periph_TIM7        /* ��ʱ��ʱ��ʱ��  */
#define LED_DELAY_TIMER       TIM7                       /* ��ʱ��ʱ��      */
#define LED_DELAY_TIMER_IRQ   TIM7_IRQn                  /* ��ʱ��ʱ�ж�����*/

#define LED_DELAY_TIMER2_IRQ  0                          /* ��ʱ��ʱ��2�жϷ�����ʹ��*/
#define LED_DELAY_TIMER3_IRQ  0                          /* ��ʱ��ʱ��3�жϷ�����ʹ��*/
#define LED_DELAY_TIMER4_IRQ  0                          /* ��ʱ��ʱ��4�жϷ�����ʹ��*/
#define LED_DELAY_TIMER5_IRQ  0                          /* ��ʱ��ʱ��5�жϷ�����ʹ��*/
#define LED_DELAY_TIMER6_IRQ  0                          /* ��ʱ��ʱ��6�жϷ�����ʹ��*/
#define LED_DELAY_TIMER7_IRQ  1                          /* ��ʱ��ʱ��7�жϷ�����ʹ��*/


/* Interface declaration -----------------------------------------------------*/
void led_init(void);
void led_display(LED_TypeDef_Struct *LEDx , u32 delay_time);

#endif




