/**
  ******************************************************************************
  * @file    Common_Data_Area.h
  * @author  LYB
  * @version V1.0.1
  * @date    2021/5/24
  * @brief   �����������������ⲿ�ӿ�
  ******************************************************************************/


#ifndef __COMMON_DATA_AREA_H
#define __COMMON_DATA_AREA_H



/* Includes ------------------------------------------------------------------*/

#include "map_XDATA.h"



/* typedef -------------------------------------------------------------------*/


/**  
  * @brief  ����CDA��������������������
  */	
typedef enum  __CDA_REG_PARAM_TYPE_ENUM
{
    CDA_DataType_RemoteCtrl,                            /*  ң����������                    */
	  CDA_DataType_MotorArmDrive, 	                      /*  �����е����������              */
	  CDA_DataType_UltraSonic,                            /*  ��������������                  */
}CDA_REG_PARAM_TYPE_ENUM;


/**  
  * @brief  ����С������ģʽ����������
  */	
typedef enum  __MODE_CAR_DRIVE_ENUM
{	 
    MODE_Car_Motor_Drive        = 1,                      /* �������ģʽ                      */
    MODE_Car_RobotArm_12        = 2,                      /* ��е��P1P2����ģʽ                */
    MODE_Car_RobotArm_34        = 3,                      /* ��е��P3P4����ģʽ                */
    MODE_Car_RobotArm_56        = 4,                      /* ��е��P5P6����ģʽ                */
}MODE_CAR_DRIVE_ENUM;


/**  
  * @brief  �������ͻ�е���������ݽṹ��
  */	
typedef struct  __DATA_MOTOR_ARM_DRIVE_STRUCT
{	 
    FlagStatus                  updateFlag;               /* ���±�־λ                         */
    MODE_CAR_DRIVE_ENUM         mode;                     /* С��������ģʽ                     */
    float                       channel[3];               /*      ���      ��е��              */
                                                          /* 0: ֱ���ٶ�   P1/3/5ת��Ƕ�       */
                                                          /* 1��ת���ٶ�   P2/4/6ת��Ƕ�       */
                                                          /* 2�������ٶ�   ��                   */
}DATA_MOTOR_DRIVE_STRUCT;


/**  
  * @brief  ���峬���������ݽṹ��
  */	
typedef struct  __DATA_ULTRA_SONIC_STRUCT
{	 
    FlagStatus                  updateFlag;                /*  ���±�־λ                       */
    uint16_t                    time;                      /*  ��ƽ����ʱ��                     */
    float                       distance;                  /*  ����: cm                         */ 
}DATA_ULTRA_SONIC_STRUCT;

/**  
  * @brief  ����CDA�����������ṹ��
  */	
typedef struct  __CDA_REG_PARAM_STRU
{	 
    XDATA_READ_DATA_Struct      Remote;                   /* Э��ת������ ��ң������           */
    DATA_MOTOR_DRIVE_STRUCT     Drive;                    /* Э��ת������ �������е������     */
    DATA_ULTRA_SONIC_STRUCT     Sonic;                    /* Э��ת������ ������������         */
} CDA_REG_PARAM_STRU;


/**  
  * @brief  ����CDA����������������
  */	
typedef union  __CDA_REG_PARAM_UNION
{	  
    XDATA_READ_DATA_Struct      Remote;                   /* Э��ת������ ��ң������           */
    DATA_MOTOR_DRIVE_STRUCT     Drive;                    /* Э��ת������ �������е������     */
    DATA_ULTRA_SONIC_STRUCT     Sonic;                    /* Э��ת������ ������������         */
} CDA_REG_PARAM_UNION;
 



/* Interface declaration -----------------------------------------------------*/
	

/**
 * @brief  ��ʼ����������ģ��
 * @param  void
 * @return void
 */
void Common_Data_Area_Init(void);



/**
 * @brief  д������
 * @param  data_type  : д����������
 * @param  param_union��д������
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Write_CDA_DataIRQ(CDA_REG_PARAM_TYPE_ENUM data_type , CDA_REG_PARAM_UNION *param_union);



/**
 * @brief  ��������
 * @param  data_type  : ������������
 * @param  param_union����������
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Read_CDA_DataIRQ(CDA_REG_PARAM_TYPE_ENUM data_type , CDA_REG_PARAM_UNION *param_union);





#endif 







