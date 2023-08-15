/**
  ******************************************************************************
  * @file    Task_Data_Remap.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   ��������ת����ӳ��Ĺ���ʵ��
  ******************************************************************************/
  
  
/* Includes ------------------------------------------------------------------*/

#include "Task_Data_Remap.h"





/* Private Defitions ---------------------------------------------------------*/


#define  SONIC_SAFETY_DISTANCE               100         /*  ����ײ��ȫ���� 40cm */
#define  SONIC_WARNING_DISTANCE              30          /*  ��������       20cm */



/**
 * @brief  ң������ת����ӳ��
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
    
    /*  �ӹ�������������ң������  */
    if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
    {  
        if (uData.Remote.Fresh == RESET)
        {
            uint8_cnt++;
            if (uint8_cnt >= 100)               /* ������Ч */
            {
                uint16_straight = 1024;        /* ��Ч���� */
                uint16_turn     = 1024;        /* ��Ч���� */
            }
            else
            {
                uint16_straight = 1024;
                uint16_turn     = 1024;
//                uint16_straight = uData.Remote.RXData.Channel[2];
//                uint16_turn     = uData.Remote.RXData.Channel[1];
            }  
        }
        else if (uData.Remote.Fresh == SET)/* ��Ч���� */
        {
            uint8_cnt = 0;
          
            /* ������±�־λ */
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
    
        /*  �ӹ�������������С������  */
        if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
        { 
            uData.Drive.updateFlag = SET;
        
            uData.Drive.channel[0]   = (float)uint16_straight/1024 - 1;   /* ��ң�ص�0~2048���� ��һ��Ϊ-1~1 */
            uData.Drive.channel[1]   = (float)uint16_turn/1024 - 1;       /* ��ң�ص�0~2048���� ��һ��Ϊ-1~1 */
          
          
            /* �ж�KEY���� ѡ��ģʽ */
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
          
            /*  �������������д�ع���������  */
            data_type = CDA_DataType_MotorArmDrive;
            Write_CDA_DataIRQ(data_type , &uData);
        }
    }
}


/**
 * @brief ����������ת��
 */
void Remap_Sonic_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;
  
    float                            drive_limit = 0;
  
    /*  �ӹ��������������������  */
    data_type = CDA_DataType_UltraSonic;
  
    if ( (SUCCESS == Read_CDA_DataIRQ(data_type , &uData)) && (uData.Sonic.updateFlag == SET) )
    {

        /* ������±�־λ                   */
        uData.Sonic.updateFlag    = RESET;
        
        /* ����ʵ�ʾ���                    */
        uData.Sonic.distance      = uData.Sonic.time * 34.0 / 2000 ;
      
        if (uData.Sonic.distance > SONIC_SAFETY_DISTANCE)           /* ��ȫ����,�ٶ�����0.9     */
        {
            drive_limit = 0.8;          
        }
        else if(uData.Sonic.distance > SONIC_WARNING_DISTANCE)      /* ����ײ����,�ٶ�����0.6   */
        {
            drive_limit = 0.6;    
        }
        else if (uData.Sonic.distance <= SONIC_WARNING_DISTANCE)    /* ��������,�ٶ�����-1      */
        {
            drive_limit = -1;    
        }
            
        /*  �������������д�ع���������  */
        data_type = CDA_DataType_UltraSonic;
        Write_CDA_DataIRQ(data_type , &uData);  
        
    }
 
    
    /*  �ӹ�������������С������  */
    data_type = CDA_DataType_MotorArmDrive;
  
    if (SUCCESS == Read_CDA_DataIRQ(data_type , &uData))
    {
        uData.Drive.channel[2] = drive_limit;
      
        /*  �������������д�ع���������  */
        data_type = CDA_DataType_MotorArmDrive;
        Write_CDA_DataIRQ(data_type , &uData);  
    }
}



					


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
