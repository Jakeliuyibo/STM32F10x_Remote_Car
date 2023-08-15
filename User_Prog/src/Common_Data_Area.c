/**
  ******************************************************************************
  * @file    Common_Data_Area.c
  * @author  LYB
  * @version V1.0.1
  * @date    2021/5/24
  * @brief   描述公共数据区的功能实现
  ******************************************************************************/
	
  
/* Includes ------------------------------------------------------------------*/
#include "Common_Data_Area.h"




/* Global variable -----------------------------------------------------------*/
CDA_REG_PARAM_STRU       CDA_BASE;


/* 中断  存储变量 ----------------------------------------------------------- */
static uint32_t __Car_CPU_PRIMASK_REG_SAVE_VALUE;


/* Private functions declaration----------------------------------------------*/
static __INLINE void __Car_Disable_IRQ(void);
static __INLINE void __Car_Restore_IRQ(void);



/* Public functions ----------------------------------------------------------*/


/**
 * @brief  初始化公共数据模块
 * @param  void
 * @return void
 */
void Common_Data_Area_Init(void)
{
    uint8_t            ii;
	
	  CDA_BASE.Drive.updateFlag       = RESET;
    CDA_BASE.Drive.mode             = MODE_Car_Motor_Drive;
	  CDA_BASE.Drive.channel[0]       = 0.0f;
	  CDA_BASE.Drive.channel[1]       = 0.0f;
	  CDA_BASE.Drive.channel[2]       = 1;

 
	  CDA_BASE.Remote.Fresh           = RESET;
	  CDA_BASE.Remote.RXData.FlagByte = 0x00;
  
    /*  设置为默认值1024  */
	  for(ii = 0; ii < 16; ii++)
	  {
		    CDA_BASE.Remote.RXData.Channel[ii] = 1024;
		}	
  
    CDA_BASE.Sonic.updateFlag       = RESET;
    CDA_BASE.Sonic.time             = 0;
    CDA_BASE.Sonic.distance         = 0.0f;

}	




/**
 * @brief  写入数据
 * @param  data_type  : 写入数据类型
 * @param  pUnion     ：写入数据
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Write_CDA_DataIRQ(CDA_REG_PARAM_TYPE_ENUM data_type , CDA_REG_PARAM_UNION *pUnion)
{
		ErrorStatus                err;
    uint8_t                    ii;
	
		if (pUnion == NULL) 
		{
			  return ERROR;
		}

	  err = SUCCESS;
	 __Car_Disable_IRQ();		
		switch(data_type)
		{					
        case CDA_DataType_RemoteCtrl:
            CDA_BASE.Remote.Fresh                  = pUnion->Remote.Fresh;
            CDA_BASE.Remote.RXData.FlagByte        = pUnion->Remote.RXData.FlagByte;			     
            for(ii = 0; ii < 16; ii++)
            {
                CDA_BASE.Remote.RXData.Channel[ii] = pUnion->Remote.RXData.Channel[ii];
            }					 
            break;	
        case CDA_DataType_MotorArmDrive:
            CDA_BASE.Drive.updateFlag              = pUnion->Drive.updateFlag;
            CDA_BASE.Drive.mode                    = pUnion->Drive.mode;
            CDA_BASE.Drive.channel[0]              = pUnion->Drive.channel[0];
            CDA_BASE.Drive.channel[1]              = pUnion->Drive.channel[1];
            CDA_BASE.Drive.channel[2]              = pUnion->Drive.channel[2];
      
            break;	
        case CDA_DataType_UltraSonic:
            CDA_BASE.Sonic.updateFlag              = pUnion->Sonic.updateFlag;
            CDA_BASE.Sonic.time                    = pUnion->Sonic.time;
            CDA_BASE.Sonic.distance                = pUnion->Sonic.distance;
            break;
        default: 
            err = ERROR;
            break;
		}
	 __Car_Restore_IRQ();			
    return err;		
}



/**
 * @brief  读出数据
 * @param  data_type  : 读出数据类型
 * @param  pUnion     ：读出数据
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Read_CDA_DataIRQ(CDA_REG_PARAM_TYPE_ENUM data_type , CDA_REG_PARAM_UNION *pUnion)
{
	  ErrorStatus           err;
    uint8_t               ii;
	
	  if (pUnion == NULL) 
		{
			  return ERROR;
		}
	
	  err = SUCCESS;
    __Car_Disable_IRQ();	
    
		switch(data_type)
		{				
			case CDA_DataType_RemoteCtrl:
				   pUnion->Remote.Fresh                  = CDA_BASE.Remote.Fresh;
           pUnion->Remote.RXData.FlagByte        = CDA_BASE.Remote.RXData.FlagByte;
           for(ii = 0; ii < 16; ii++)
			     {
					     pUnion->Remote.RXData.Channel[ii] = CDA_BASE.Remote.RXData.Channel[ii];
					 }			
			     CDA_BASE.Remote.Fresh                 = RESET;
           break;	
			case CDA_DataType_MotorArmDrive:
				   pUnion->Drive.updateFlag              = CDA_BASE.Drive.updateFlag;
           pUnion->Drive.mode                    = CDA_BASE.Drive.mode;
           pUnion->Drive.channel[0]              = CDA_BASE.Drive.channel[0];
					 pUnion->Drive.channel[1]              = CDA_BASE.Drive.channel[1];
           pUnion->Drive.channel[2]              = CDA_BASE.Drive.channel[2];  
           break;	
      case CDA_DataType_UltraSonic:
           pUnion->Sonic.updateFlag              = CDA_BASE.Sonic.updateFlag;              
           pUnion->Sonic.time                    = CDA_BASE.Sonic.time;
           pUnion->Sonic.distance                = CDA_BASE.Sonic.distance;
           break;
			default: 
				   err = ERROR;
				   break;
		}
    
    __Car_Restore_IRQ();
    return err;
}






/* Private functions ---------------------------------------------------------*/


/**
 * @brief  关中断
 */
static __INLINE void __Car_Disable_IRQ(void)
{
	  __Car_CPU_PRIMASK_REG_SAVE_VALUE = __get_PRIMASK();
	  __disable_irq();
}


/**
 * @brief  开中断
 */
static __INLINE void __Car_Restore_IRQ(void)
{
	  __set_PRIMASK(__Car_CPU_PRIMASK_REG_SAVE_VALUE);
}
