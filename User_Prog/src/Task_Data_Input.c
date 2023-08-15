/**
  ******************************************************************************
  * @file    Task_Data_input.c
  * @author  LYB
  * @version V1.0.1
  * @date    202/5/24
  * @brief   ������������ͨ�����ܵ�ʵ��
  ******************************************************************************/



/* Includes ------------------------------------------------------------------*/

#include "Task_Data_input.h"




/* Public functions ----------------------------------------------------------*/


/**
 * @brief  ����ң������ͨ��
 */
void Input_Remote_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;

		uData.Remote.Fresh = RESET;

		if ( (SUCCESS == XDATA_ReadData(XDATA1 , &uData.Remote)) && (uData.Remote.Fresh == SET) )
		{
        data_type = CDA_DataType_RemoteCtrl;
        Write_CDA_DataIRQ(data_type , &uData);			
		}
   
}



/**
 * @brief  ���볬��������ͨ��
 */
void Input_Sonic_Channel(void)
{
	  CDA_REG_PARAM_TYPE_ENUM          data_type;
    CDA_REG_PARAM_UNION              uData;


		if (SET == SONIC1->SONIC_Operating.updateFlag)    /* ������ȷ                                 */
		{		
        SONIC1->SONIC_Operating.updateFlag = RESET;
      
        uData.Sonic.updateFlag    = SET;
        uData.Sonic.time          = SONIC1->SONIC_Operating.time;
      
        data_type = CDA_DataType_UltraSonic;
        Write_CDA_DataIRQ(data_type , &uData);	
		}
    else                                              /* ���ݴ��� ��time = 2DF4 ת��Ϊ����Ϊ200cm */
    {
        uData.Sonic.updateFlag    = SET;
        uData.Sonic.time          = 0x2DF4;
      
        data_type = CDA_DataType_UltraSonic;
        Write_CDA_DataIRQ(data_type , &uData);	
    }
}



/**
 * @brief  ���볬����ʹ��
 */
void Input_Sonic_Start(void)
{
    SONIC_Start(SONIC1); 
}

