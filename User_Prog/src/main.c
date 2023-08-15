/********************************************************************************
  * @file     main.c
  * @author   W.Dong
  * @version  V1.0.0
  * @date     28/01/2020
  * @brief    This file provides main functions.
  ******************************************************************************/


#include "init.h"
#include "scheduler.h"
#include "Task_Data_input.h"
#include "Task_Data_output.h"
#include "Task_Data_Remap.h"

void RCC_Configuration(void);

void task_1ms(void){}
  
void task_10ms(void){}
  
void task_30ms(void)
{
    Input_Remote_Channel();
	  Remap_Remote_Channel();

}

void task_50ms(void)
{
    Output_Drive_Channel();
}

void task_100ms(void)
{
    Input_Sonic_Start();
    Input_Sonic_Channel();
    Remap_Sonic_Channel();
}
  
void task_200ms(void)
{
    Output_OLED_Channel();
}

void task_500ms(void)
{
    Output_LED_Channel();
}
 

/*----------------------------------------------------------------------------
 *        Main: Initialize and Start scheduler
 *---------------------------------------------------------------------------*/
int main (void) 
{

    SCHEDULER_TASKS_Struct allTasks;	
	
	  RCC_Configuration();
    /* Init  */
	  Car_System_Init();
	
	  /* write all pointers of tasks's funtion to scheduler */
		allTasks.pDuty_1ms    = task_1ms;
		allTasks.pDuty_10ms   = task_10ms;	
		allTasks.pDuty_30ms   = task_30ms;
		allTasks.pDuty_50ms   = task_50ms;
		allTasks.pDuty_100ms  = task_100ms;
    allTasks.pDuty_200ms  = task_200ms;
    allTasks.pDuty_500ms  = task_500ms;

		Scheduler_Init(allTasks);
	
	  /* start shecduler to excute tasks */	
		Scheduler_Start();
	
	  while(1)
		{
//        BSP_IWDG_Feed();
        Scheduler_Main_Loop();
    }		 
}

//////////ต๗สิ/////////////////////

//void int2string(char * fmt,...)
//{
//    u8 buf[100];
//    SCOM_WRITE_DATA_Struct pWrite;
//  
//    va_list ap; 
//    va_start(ap,fmt);
//    vsprintf((char*)buf,fmt,ap);
//    va_end(ap);
//    pWrite.len = strlen((const char *)buf);
//    memcpy(pWrite.data , buf , pWrite.len);
//    SCOM_WriteData(SCOM1 , &pWrite);
//}

//int main(void){
//  
//    SCOM_InitTypedef_Struct SCOM_InitStruct;
//    SCOM_WRITE_DATA_Struct pWrite;
//    char buf1[] = "#1P1000T100\r\n";
//    char buf2[] = "#1P1500T100\r\n";
//    char buf3[] = "#1P2000T100\r\n";
//    u8 delay = 1000;
//  
//    RCC_Configuration();
//    SysTick_Configuration();	
//  
//    BSP_SCOM_InitStruct(&SCOM_InitStruct);
//    BSP_SCOM_Init(SCOM1 , &SCOM_InitStruct);
//  
//    while(1)
//    {
//    int2string("#1P%dT10\r\n", 1000);Delay_ms(delay);
//    int2string("#1P%dT10\r\n", 1500);Delay_ms(delay);
//    int2string("#1P%dT10\r\n", 2000);Delay_ms(delay); 
//    int2string("#1P%dT10\r\n", 1500);Delay_ms(delay); 
//      
//    int2string("#2P%dT10\r\n", 1000);Delay_ms(delay);
//    int2string("#2P%dT10\r\n", 1500);Delay_ms(delay);
//    int2string("#2P%dT10\r\n", 2000);Delay_ms(delay);
//    int2string("#2P%dT10\r\n", 1500);Delay_ms(delay);
//      
//    int2string("#3P%dT10\r\n", 1000);Delay_ms(delay);
//    int2string("#3P%dT10\r\n", 1500);Delay_ms(delay);
//    int2string("#3P%dT10\r\n", 2000);Delay_ms(delay);
//    int2string("#3P%dT10\r\n", 1500);Delay_ms(delay);
//      
//    int2string("#4P%dT10\r\n", 1000);Delay_ms(delay);
//    int2string("#4P%dT10\r\n", 1500);Delay_ms(delay);
//    int2string("#4P%dT10\r\n", 2000);Delay_ms(delay);
//    int2string("#4P%dT10\r\n", 1500);Delay_ms(delay);
//      
//    int2string("#5P%dT10\r\n", 1000);Delay_ms(delay);
//    int2string("#5P%dT10\r\n", 1500);Delay_ms(delay);
//    int2string("#5P%dT10\r\n", 2000);Delay_ms(delay);
//    int2string("#5P%dT10\r\n", 1500);Delay_ms(delay);
//    
//    int2string("#6P%dT10\r\n", 1000);Delay_ms(delay);
//    int2string("#6P%dT10\r\n", 1500);Delay_ms(delay);
//    int2string("#6P%dT10\r\n", 2000);Delay_ms(delay);
//    int2string("#6P%dT10\r\n", 1500);Delay_ms(delay);
//    
////    pWrite.len = 13;
////    memcpy(pWrite.data , buf1 , pWrite.len);
////    SCOM_WriteData(SCOM1 , &pWrite);
////    Delay_ms(1000);    Delay_ms(1000);
////      
////    pWrite.len = 13;
////    memcpy(pWrite.data , buf2 , pWrite.len);
////    SCOM_WriteData(SCOM1 , &pWrite);
////    Delay_ms(1000);    Delay_ms(1000);

////    pWrite.len = 13;
////    memcpy(pWrite.data , buf3 , pWrite.len);
////    SCOM_WriteData(SCOM1 , &pWrite);
////    Delay_ms(1000);      Delay_ms(1000);   
////      
////    u3_printf("%s",buf1);	
////    Delay_ms(1000);
////    Delay_ms(1000);
////      
////    u3_printf("%s",buf2);	
////    Delay_ms(1000);
////    Delay_ms(1000);
////      
////    u3_printf("%s",buf3);	
////    Delay_ms(1000);  
////    Delay_ms(1000);
////      
//    }
//  
//  
//}



/**
  * @brief  Configing  Configuring RCC of CPU's hardware
  * 
  * @param:   void
  * @retval : void
  */

void RCC_Configuration(void)
{
	ErrorStatus              HSEStartUpStatus;
	
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/16 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }
	// next two lines should move to initial code, and add low OS at Hardware!! 
 	  RCC_LSICmd(ENABLE);
  	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);		
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);			
}


void HardFault_Handler()
{
    return ;
}







/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/


