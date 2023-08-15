/**
  ******************************************************************************
  * @file    init.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   描述小车功能初始化的实现
  ******************************************************************************/

#include "init.h"


/**
 * @brief  IWDG驱动初始化 , Tout=((4 * 2^prer) * rlr) / 40 (ms) = 32 * 160 / 40 = 128(ms)
 */
void IWDG_Init(void)
{
    IWDG_InitTypeDef_Struct IWDG_InitStruct;
  
    BSP_IWDG_InitStruct(&IWDG_InitStruct);
  
    IWDG_InitStruct.enable = ENABLE;
  
    IWDG_InitStruct.prep   = 3;
    IWDG_InitStruct.rlr    = 160;
  
    BSP_IWDG_Init(IWDG1 , &IWDG_InitStruct);
}



/**
 * @brief  led驱动初始化
 */
void LED_Init(void)
{
    LED_InitTypeDef_Struct  LED_InitStruct;
  
    BSP_LED_InitStruct(&LED_InitStruct);
  
    LED_InitStruct.enable  =  ENABLE;
    
    LED_InitStruct.LED_TIM_PrePriorinty = 0X04;
    LED_InitStruct.LED_TIM_SubPriorinty = 0X04;
  
    BSP_LED_Init(LED1 , &LED_InitStruct);
}


/**
 * @brief  led驱动初始化

 */
void OLED_Init(void)
{
    OLED_InitTypeDef_Struct OLED_InitStruct;
  
    OLED_InitStruct.enable_OLED = ENABLE;
  
    BSP_OLED_Init(OLED1 , &OLED_InitStruct);
  
}


/**
* @brief  机械臂初始化 串行总线驱动

 */
void RobotArm_Init(void)
{
    ARM_InitTypeDef_Struct    ARM_InitStruct;
  
    BSP_ARM_InitStruct(&ARM_InitStruct);
  
    ARM_InitStruct.enable_ARM             = ENABLE;
    ARM_InitStruct.enable_DMA             = ENABLE;
  
    ARM_InitStruct.ARM_SCOM_BaudRate      = 115200;
  
    ARM_InitStruct.ARM_SCOM_PrePriorinty  = 0X03;
    ARM_InitStruct.ARM_SCOM_SubPriorinty  = 0X03;
    ARM_InitStruct.ARM_DMA_PrePriorinty   = 0X03;
    ARM_InitStruct.ARM_DMA_SubPriorinty   = 0X03;
  
    BSP_ARM_Init(ARM1, &ARM_InitStruct);
}




/**
 * @brief  超声波驱动初始化
 */
void UltraSonic_Init(void)
{
    SONIC_InitTypedef_Struct   SONIC_InitStruct;
    
    BSP_SONIC_InitStruct(&SONIC_InitStruct);
  
    SONIC_InitStruct.enable_SONIC = ENABLE;
    SONIC_InitStruct.enable_EXTI  = ENABLE;
  
    SONIC_InitStruct.SONIC_TIM_Period       = 99;
    SONIC_InitStruct.SONIC_TIM_Prescaler    = 71;
  
    SONIC_InitStruct.SONIC_TIM_PrePriorinty = 0X00;
    SONIC_InitStruct.SONIC_TIM_SubPriorinty = 0X00;
  
    SONIC_InitStruct.SONIC_EXTI_PrePriorinty = 0X01;
    SONIC_InitStruct.SONIC_EXTI_SubPriorinty = 0X01;
  
    BSP_SONIC_Init(SONIC1 , &SONIC_InitStruct);
}


/**
 * @brief  小车驱动初始化
 */
void CarDrive_Init(void)
{
    MOTOR_InitTypedef_Struct  MOTOR_InitStruct;
  
    BSP_MOTOR_InitStruct(&MOTOR_InitStruct);
  
    MOTOR_InitStruct.enable_MOTOR = ENABLE;
  
    MOTOR_InitStruct.MOTOR_PWM_Period    = 9999;
    MOTOR_InitStruct.MOTOR_PWM_Prescaler = 0;
  
    MOTOR_InitStruct.straight_speed      = 0;
    MOTOR_InitStruct.turn_speed          = 0;
    MOTOR_InitStruct.limit_speed         = 0.9;
  
    BSP_MOTOR_Init(MOTOR1 , &MOTOR_InitStruct);

}




/**
 * @brief  遥控数据通道初始化
 */
void RemoteCtrl_Init(void)
{
    XDATA_InitTypeDef_Struct    XDATA_InitS;

    MAP_XDATA_InitStruct(&XDATA_InitS);
  
    XDATA_InitS.XDATA_TransMode             = XDATA_Trans_Read_Mode;
 
	  XDATA_InitS.LORA_InitStruct.enable_LORA = ENABLE; 	
	  XDATA_InitS.LORA_InitStruct.enable_DMA  = ENABLE;

  	XDATA_InitS.LORA_InitStruct.TransMode   = LORA_Transparent_Trans;
	  XDATA_InitS.LORA_InitStruct.UsartMode   = LORA_Usart_Mode_RX;
  
	  XDATA_InitS.LORA_InitStruct.LORA_DMA_PrePriorinty   = 2;
	  XDATA_InitS.LORA_InitStruct.LORA_DMA_SubPriorinty   = 2;
	  XDATA_InitS.LORA_InitStruct.LORA_SCOM_PrePriorinty  = 2;
	  XDATA_InitS.LORA_InitStruct.LORA_SCOM_SubPriorinty  = 2;	
  
	  XDATA_InitS.LORA_InitStruct.LORA_SCOM_BaudRate            = 115200;
	  XDATA_InitS.LORA_InitStruct.LORA_SCOM_Parity              = USART_Parity_No;	
	  XDATA_InitS.LORA_InitStruct.LORA_SCOM_HardwareFlowControl = USART_HardwareFlowControl_None;	
	  XDATA_InitS.LORA_InitStruct.LORA_SCOM_StopBits            = USART_StopBits_1;	
	  XDATA_InitS.LORA_InitStruct.LORA_SCOM_WordLength          = USART_WordLength_8b;	

	  MAP_XDATA_Init(XDATA1, &XDATA_InitS);
}





/**
 * @brief  初始化小车模块
 */
void Car_System_Init(void)
{
    SysTick_Configuration();	
		Common_Data_Area_Init();
    RemoteCtrl_Init();	
    CarDrive_Init();
    UltraSonic_Init();
    LED_Init();
    OLED_Init();
    RobotArm_Init();
//    IWDG_Init();
}



