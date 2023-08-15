/**
  ******************************************************************************
  * @file    Task_Data_output.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   描述数据输出通道功能的实现
  ******************************************************************************/
  
  
/* Includes ------------------------------------------------------------------*/

#include "Task_Data_output.h"


/* Public functions ----------------------------------------------------------*/



/**
 * @brief  输出电机驱动和机械臂通道
 */
void Output_Drive_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;
 
    data_type = CDA_DataType_MotorArmDrive;
  
    if ( (SUCCESS == Read_CDA_DataIRQ(data_type , &uData)) && (uData.Drive.updateFlag == SET) )
    {

        if (uData.Drive.mode == MODE_Car_Motor_Drive)                  /* 模式：电机驱动        */
        {
            /* 输出电机驱动      */
            BSP_MOTOR_Drive(MOTOR1 , uData.Drive.channel[0] , uData.Drive.channel[1] , uData.Drive.channel[2]);
        }
        else if (uData.Drive.mode == MODE_Car_RobotArm_12)             /* 模式：机械臂P1P2      */
        {
            BSP_ARM_Drive(ARM1, 0, uData.Drive.channel[0]);
            BSP_ARM_Drive(ARM1, 1, uData.Drive.channel[1]);     
        }
        else if (uData.Drive.mode == MODE_Car_RobotArm_34)             /* 模式：机械臂P3P4      */
        {
            BSP_ARM_Drive(ARM1, 2, uData.Drive.channel[0]);
            BSP_ARM_Drive(ARM1, 3, uData.Drive.channel[1]);  
        }    
        else if (uData.Drive.mode == MODE_Car_RobotArm_56)             /* 模式：机械臂P5P6      */
        {
            BSP_ARM_Drive(ARM1, 4, uData.Drive.channel[0]);
            BSP_ARM_Drive(ARM1, 5, uData.Drive.channel[1]);  
        }    
        else
        {
        
        }
            
        /* 清除更新标志位    */
        uData.Drive.updateFlag = RESET;
        data_type = CDA_DataType_MotorArmDrive;
        Write_CDA_DataIRQ(data_type , &uData);
    }

}




/**
 * @brief  输出OLED显示数据通道
 */
void Output_OLED_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;
    float                            flaot_distance = 0;
    u32                              u32_distance = 0;
  

    data_type = CDA_DataType_MotorArmDrive;
  
    /* 读取遥控的数据    */
    if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
    {   
        BSP_OLED_Clear(OLED1);
        BSP_OLED_WriteString(OLED1, 5,  0, "mode"    );
        BSP_OLED_WriteString(OLED1, 5, 14, "ch0" );
        BSP_OLED_WriteString(OLED1, 5, 30, "ch1"    );
        BSP_OLED_WriteString(OLED1, 5, 46, "dist");
      
        BSP_OLED_WriteNum(OLED1, 60,  0,  uData.Drive.mode                              );
        BSP_OLED_WriteNum(OLED1, 60, 14, (uint16_t)((uData.Drive.channel[0] + 1) * 1024) );
        BSP_OLED_WriteNum(OLED1, 60, 30, (uint16_t)((uData.Drive.channel[1] + 1) * 1024) );
    }
    
    
    data_type = CDA_DataType_UltraSonic;
    
    /* 读取超声波的数据  */
    if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
    {
//        flaot_distance = uData.Sonic.distance;
//        u32_distance   = flaot_distance;
//        flaot_distance = 100 * (flaot_distance - u32_distance); /* 保留两位小数 */
        
        BSP_OLED_WriteNum(OLED1, 60, 46, (u32)uData.Sonic.distance);
        BSP_OLED_WriteString(OLED1, 84, 46, ".");
        BSP_OLED_WriteNum(OLED1, 92, 46, (u32)(100 * (uData.Sonic.distance - (u32)uData.Sonic.distance)));   
        BSP_OLED_Refresh(OLED1);
    }

}




/**
 * @brief  输出LED通道
 */
void Output_LED_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;
  
    
    data_type = CDA_DataType_MotorArmDrive;
    
    /* 读取超声波的数据  */
    if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
    {
        LED_Set_Duty(LED1 , (uint16_t)((1000 * uData.Drive.channel[2]) + 100)); 
    }

}






