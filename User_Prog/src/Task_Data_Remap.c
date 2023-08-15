/**
  ******************************************************************************
  * @file    Task_Data_Remap.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   描述数据转化与映射的功能实现
  ******************************************************************************/
  
  
/* Includes ------------------------------------------------------------------*/

#include "Task_Data_Remap.h"





/* Private Defitions ---------------------------------------------------------*/


#define  SONIC_SAFETY_DISTANCE               100         /*  防碰撞安全距离 40cm */
#define  SONIC_WARNING_DISTANCE              30          /*  警报距离       20cm */



/**
 * @brief  遥控数据转化与映射
 */
void  Remap_Remote_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;

    uint16_t                         uint16_straight = 0;
    uint16_t                         uint16_turn     = 0;
    uint16_t                         uint16_key[4];
    static uint8_t                   uint8_cnt = 0;
		
    data_type = CDA_DataType_RemoteCtrl;
    
    /*  从公共数据区读出遥控数据  */
    if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
    {  
        if (uData.Remote.Fresh == RESET)
        {
            uint8_cnt++;
            if (uint8_cnt >= 100)               /* 数据无效 */
            {
                uint16_straight = 1024;        /* 无效处理 */
                uint16_turn     = 1024;        /* 无效处理 */
            }
            else
            {
                uint16_straight = 1024;
                uint16_turn     = 1024;
//                uint16_straight = uData.Remote.RXData.Channel[2];
//                uint16_turn     = uData.Remote.RXData.Channel[1];
            }  
        }
        else if (uData.Remote.Fresh == SET)/* 有效数据 */
        {
            uint8_cnt = 0;
          
            /* 清除更新标志位 */
            uData.Remote.Fresh = RESET;
            data_type = CDA_DataType_RemoteCtrl;
            Write_CDA_DataIRQ(data_type , &uData);
            
            uint16_straight = uData.Remote.RXData.Channel[2];
            uint16_turn     = uData.Remote.RXData.Channel[1];
          
            uint16_key[0]   = uData.Remote.RXData.Channel[4];
            uint16_key[1]   = uData.Remote.RXData.Channel[5];
            uint16_key[2]   = uData.Remote.RXData.Channel[6];
            uint16_key[3]   = uData.Remote.RXData.Channel[7];         
        }
        
        data_type = CDA_DataType_MotorArmDrive;
    
        /*  从公共数据区读出小车数据  */
        if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
        { 
            uData.Drive.updateFlag = SET;
        
            uData.Drive.channel[0]   = (float)uint16_straight/1024 - 1;   /* 将遥控的0~2048数据 归一化为-1~1 */
            uData.Drive.channel[1]   = (float)uint16_turn/1024 - 1;       /* 将遥控的0~2048数据 归一化为-1~1 */
          
          
            /* 判断KEY数据 选择模式 */
            if (uint16_key[0] == 2047)
            {
                uData.Drive.mode   = MODE_Car_Motor_Drive;
            }
            else if (uint16_key[1] == 2047)
            {
                uData.Drive.mode   = MODE_Car_RobotArm_12;
            }
            else if (uint16_key[2] == 2047)
            {
                uData.Drive.mode   = MODE_Car_RobotArm_34;
            }
            else if (uint16_key[3] == 2047)
            {
                uData.Drive.mode   = MODE_Car_RobotArm_56;
            }
          
            /*  将解析完的数据写回公共数据区  */
            data_type = CDA_DataType_MotorArmDrive;
            Write_CDA_DataIRQ(data_type , &uData);
        }
    }
}


/**
 * @brief 超声波数据转化
 */
void Remap_Sonic_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;
  
    float                            drive_limit = 0;
  
    /*  从公共数据区读出测距数据  */
    data_type = CDA_DataType_UltraSonic;
  
    if ( (SUCCESS == Read_CDA_DataIRQ(data_type , &uData)) && (uData.Sonic.updateFlag == SET) )
    {

        /* 清除更新标志位                   */
        uData.Sonic.updateFlag    = RESET;
        
        /* 计算实际距离                    */
        uData.Sonic.distance      = uData.Sonic.time * 34.0 / 2000 ;
      
        if (uData.Sonic.distance > SONIC_SAFETY_DISTANCE)           /* 安全距离,速度限制0.9     */
        {
            drive_limit = 0.8;          
        }
        else if(uData.Sonic.distance > SONIC_WARNING_DISTANCE)      /* 防碰撞距离,速度限制0.6   */
        {
            drive_limit = 0.6;    
        }
        else if (uData.Sonic.distance <= SONIC_WARNING_DISTANCE)    /* 警报距离,速度限制-1      */
        {
            drive_limit = -1;    
        }
            
        /*  将解析完的数据写回公共数据区  */
        data_type = CDA_DataType_UltraSonic;
        Write_CDA_DataIRQ(data_type , &uData);  
        
    }
 
    
    /*  从公共数据区读出小车数据  */
    data_type = CDA_DataType_MotorArmDrive;
  
    if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
    {
        uData.Drive.channel[2] = drive_limit;
      
        /*  将解析完的数据写回公共数据区  */
        data_type = CDA_DataType_MotorArmDrive;
        Write_CDA_DataIRQ(data_type , &uData);  
    }
}



					


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
