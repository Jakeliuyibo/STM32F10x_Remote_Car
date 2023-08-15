/**
  ******************************************************************************
  * @file    Common_Data_Area.h
  * @author  LYB
  * @version V1.0.1
  * @date    2021/5/24
  * @brief   描述公共数据区的外部接口
  ******************************************************************************/


#ifndef __COMMON_DATA_AREA_H
#define __COMMON_DATA_AREA_H



/* Includes ------------------------------------------------------------------*/

#include "map_XDATA.h"



/* typedef -------------------------------------------------------------------*/


/**  
  * @brief  定义CDA公共数据区的数据类型
  */	
typedef enum  __CDA_REG_PARAM_TYPE_ENUM
{
    CDA_DataType_RemoteCtrl,                            /*  遥控数据类型                    */
	  CDA_DataType_MotorArmDrive, 	                      /*  电机机械臂驱动类型              */
	  CDA_DataType_UltraSonic,                            /*  超声波数据类型                  */
}CDA_REG_PARAM_TYPE_ENUM;


/**  
  * @brief  定义小车驱动模式的数据类型
  */	
typedef enum  __MODE_CAR_DRIVE_ENUM
{	 
    MODE_Car_Motor_Drive        = 1,                      /* 电机驱动模式                      */
    MODE_Car_RobotArm_12        = 2,                      /* 机械臂P1P2驱动模式                */
    MODE_Car_RobotArm_34        = 3,                      /* 机械臂P3P4驱动模式                */
    MODE_Car_RobotArm_56        = 4,                      /* 机械臂P5P6驱动模式                */
}MODE_CAR_DRIVE_ENUM;


/**  
  * @brief  定义电机和机械臂驱动数据结构体
  */	
typedef struct  __DATA_MOTOR_ARM_DRIVE_STRUCT
{	 
    FlagStatus                  updateFlag;               /* 更新标志位                         */
    MODE_CAR_DRIVE_ENUM         mode;                     /* 小车驱动的模式                     */
    float                       channel[3];               /*      电机      机械臂              */
                                                          /* 0: 直行速度   P1/3/5转向角度       */
                                                          /* 1：转向速度   P2/4/6转向角度       */
                                                          /* 2：限制速度   空                   */
}DATA_MOTOR_DRIVE_STRUCT;


/**  
  * @brief  定义超声波的数据结构体
  */	
typedef struct  __DATA_ULTRA_SONIC_STRUCT
{	 
    FlagStatus                  updateFlag;                /*  更新标志位                       */
    uint16_t                    time;                      /*  电平持续时间                     */
    float                       distance;                  /*  距离: cm                         */ 
}DATA_ULTRA_SONIC_STRUCT;

/**  
  * @brief  定义CDA公共数据区结构体
  */	
typedef struct  __CDA_REG_PARAM_STRU
{	 
    XDATA_READ_DATA_Struct      Remote;                   /* 协议转换数据 ，遥控数据           */
    DATA_MOTOR_DRIVE_STRUCT     Drive;                    /* 协议转化数据 ，电机机械臂数据     */
    DATA_ULTRA_SONIC_STRUCT     Sonic;                    /* 协议转化数据 ，超声波数据         */
} CDA_REG_PARAM_STRU;


/**  
  * @brief  定义CDA公共数据区联合体
  */	
typedef union  __CDA_REG_PARAM_UNION
{	  
    XDATA_READ_DATA_Struct      Remote;                   /* 协议转换数据 ，遥控数据           */
    DATA_MOTOR_DRIVE_STRUCT     Drive;                    /* 协议转化数据 ，电机机械臂数据     */
    DATA_ULTRA_SONIC_STRUCT     Sonic;                    /* 协议转化数据 ，超声波数据         */
} CDA_REG_PARAM_UNION;
 



/* Interface declaration -----------------------------------------------------*/
	

/**
 * @brief  初始化公共数据模块
 * @param  void
 * @return void
 */
void Common_Data_Area_Init(void);



/**
 * @brief  写入数据
 * @param  data_type  : 写入数据类型
 * @param  param_union：写入数据
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Write_CDA_DataIRQ(CDA_REG_PARAM_TYPE_ENUM data_type , CDA_REG_PARAM_UNION *param_union);



/**
 * @brief  读出数据
 * @param  data_type  : 读出数据类型
 * @param  param_union：读出数据
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Read_CDA_DataIRQ(CDA_REG_PARAM_TYPE_ENUM data_type , CDA_REG_PARAM_UNION *param_union);





#endif 







