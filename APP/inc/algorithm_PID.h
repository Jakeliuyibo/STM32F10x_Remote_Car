/**
  ******************************************************************************
  * @file    algorithm_PID.h
  * @author  LYB
  * @version V1.0.0
  * @date    2021/3/29
  * @brief   ����PID����ģ����ⲿ����
  ******************************************************************************/
  
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __ALGORITHM_PID_H
#define __ALGORITHM_PID_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"


/* Defitions -----------------------------------------------------------------*/
  
#define             PID_CONTROL_KP_DEFAULT                 0.7              /* PID Ĭ�ϱ���ϵ�� */
#define             PID_CONTROL_KI_DEFAULT                 0.1              /* PID Ĭ�ϻ���ϵ�� */
#define             PID_CONTROL_KD_DEFAULT                 0.2              /* PID Ĭ��΢��ϵ�� */
#define             PID_CONTROL_OUTPUT_LIMIT_DEFAULT       0.9              /* PID Ĭ������޷� */


/* Typedef -------------------------------------------------------------------*/


/**
  * @brief  ����PID���ƽṹ��
  */
typedef struct  __PIDControl_InitTypedef_Struct
{
  
    float           Kp;               /*  PID ����ϵ��  */
    float           Ki;               /*  PID ����ϵ��  */
    float           Kd;               /*  PID ΢��ϵ��  */
    float           Output_limit;     /*  PID ����޷�  */
  
}PIDControl_InitTypedef_Struct;


/**
  * @brief  ����PID���ƽṹ��
  */
typedef struct  __PIDControl_Typedef_Struct
{
  
    float           Kp;               /*  PID ����ϵ��  */
    float           Ki;               /*  PID ����ϵ��  */
    float           Kd;               /*  PID ΢��ϵ��  */
    float           Ek;               /*  PID ��ֵ      */
    float           Ek1;              /*  PID ǰ��ֵ    */
    float           Ek2;              /*  PID ǰǰ��ֵ  */
    float           Inc;              /*  PID ��������  */
    float           Output_limit;     /*  PID ����޷�  */
  
}PIDControl_Typedef_Struct;



/* PID BASE ------------------------------------------------------------------*/




/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  ��ʼ��PID�ṹ��Ĭ������
 * @param  *PID_InitStruct : PID ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
void Algorithm_PID_InitStruct(PIDControl_InitTypedef_Struct *PID_InitStruct);



/**
 * @brief  ��ʼ��PID�ṹ��
 * @param  *PID            : PID �����ṹ��
 * @param  *PID_InitStruct : PID ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus Algorithm_PID_Init(PIDControl_Typedef_Struct *PID , PIDControl_InitTypedef_Struct *PID_InitStruct);



/**
 * @brief  PID ���ƻ�
 * @param  *PID            : PID �����ṹ��
 * @param  SetVal          : �����ٶ�
 * @param  ActualVal       : ʵ���ٶ�
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus PID_Adjustable_Ring(PIDControl_Typedef_Struct *PID , float SetVal , float ActualVal);












#endif

