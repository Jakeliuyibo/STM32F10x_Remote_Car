/**
  ******************************************************************************
  * @file    bsp_scom_it.c
  * @author  LYB
  * @version V1.0.3
  * @date    202/5/17
  * @brief   �����˵ײ�SCOM �жϷ�������ʵ��
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_scom.h"




/* Public functions ----------------------------------------------------------*/


/**
 * @brief  USART1�жϷ����� 
 * @param  void
 * @return void
 */
void USART1_IRQHandler(void) 
{
  
#if(SCOM1_USART_IRQn == 37)
    SCOM_USART_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_USART_IRQn == 37)
    SCOM_USART_IRQHandler(SCOM2);
#endif
	
#if(SCOM3_USART_IRQn == 37)
    SCOM_USART_IRQHandler(SCOM3);
#endif	
	
}



/**
 * @brief  USART2�жϷ����� 
 * @param  void
 * @return void
 */
void USART2_IRQHandler(void) 
{
#if(SCOM1_USART_IRQn == 38)	
    SCOM_USART_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_USART_IRQn == 38)	
    SCOM_USART_IRQHandler(SCOM2);
#endif
	
#if(SCOM3_USART_IRQn == 38)	
    SCOM_USART_IRQHandler(SCOM3);
#endif

}


/**
 * @brief  USART3�жϷ����� 
 * @param  void
 * @return void
 */
void USART3_IRQHandler(void) 
{
#if(SCOM1_USART_IRQn == 39)	
    SCOM_USART_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_USART_IRQn == 39)	
    SCOM_USART_IRQHandler(SCOM2);
#endif
	
#if(SCOM3_USART_IRQn == 39)	
    SCOM_USART_IRQHandler(SCOM3);
#endif	
	
}




/**
 * @brief  DMA1 ͨ��12 �жϷ����� 
 * @param  void
 * @return void
 */
void DMA1_Channel2_IRQHandler(void)
{
#if(SCOM1_TX_DMA_Channel_IRQn == 12)	
    SCOM_TX_DMA_IRQHandler(SCOM1);
#endif	

#if(SCOM2_TX_DMA_Channel_IRQn == 12)	
    SCOM_TX_DMA_IRQHandler(SCOM2);	
#endif

#if(SCOM3_TX_DMA_Channel_IRQn == 12)	
	  SCOM_TX_DMA_IRQHandler(SCOM3);	
#endif

}


/**
 * @brief  DMA1 ͨ��14 �жϷ����� 
 * @param  void
 * @return void
 */
void DMA1_Channel4_IRQHandler(void)
{
#if(SCOM1_tx_DMA_Channel_IRQn == 14)	
    SCOM_TX_DMA_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_tx_DMA_Channel_IRQn == 14)	
    SCOM_TX_DMA_IRQHandler(SCOM2);	
#endif
	
#if(SCOM3_tx_DMA_Channel_IRQn == 14)	
    SCOM_TX_DMA_IRQHandler(SCOM3);	
#endif		

}


/**
 * @brief  DMA1 ͨ��17 �жϷ����� 
 * @param  void
 * @return void
 */
void DMA1_Channel7_IRQHandler(void)
{
#if(SCOM1_tx_DMA_Channel_IRQn == 17)	
    SCOM_TX_DMA_IRQHandler(SCOM1);
#endif	
	
#if(SCOM2_tx_DMA_Channel_IRQn == 17)	
    SCOM_TX_DMA_IRQHandler(SCOM2);	
#endif
	
#if(SCOM3_tx_DMA_Channel_IRQn == 17)	
    SCOM_TX_DMA_IRQHandler(SCOM3);	
#endif

}




