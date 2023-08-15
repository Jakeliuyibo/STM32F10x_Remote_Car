/**
  ******************************************************************************
  * @file    map_SCOMandSBUS.h
  * @author  LYB
  * @version V1.0.0
  * @date    202/4/18
  * @brief   ������SCOM����Э��ת��SBUS�Ĺ���ʵ��
  ******************************************************************************/
  
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __MAP_SCOMANDSBUS_H
#define __MAP_SCOMANDSBUS_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"


/* Defitions -----------------------------------------------------------------*/



/* typedef -------------------------------------------------------------------*/

/** 
  * @brief  ����SBUS���ݽṹ��
  */
typedef struct __SBUSData_Struct
{
    uint16_t           Channel[16];       /* ͨ��   */
    uint8_t            FlagByte;          /* ��־λ */
}SBUSData_Struct;



/* Interface declaration -----------------------------------------------------*/



/**
 * @brief  ��SCOMЭ������ת��ΪSBUSЭ��
 * @param  *SCOMdata�� SCOM����ָ�룬���鳤��25byte   8bit     
 *            * SCOMdata[0]               ���ֽ�      0x0F           
 *            * SCOMdata[1]-SCOMdata[22]  �û�����    
 *            * SCOMdata[23]              ��־�ֽ�    0x00     
 *            * SCOMdata[24]              β�ֽ�      0x00      
 * @param  *SBUSdata�� SBUS���ݴ洢ָ��,���鳤��16byte 11bit
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_SCOMtoSBUS(uint8_t *SCOMdata , SBUSData_Struct *SBUSdata);


/**
 * @brief  ��SBUSЭ������ת��ΪSCOMЭ��
 * @param  *SBUSdata�� SBUS���ݴ洢ָ��,���鳤��16byte  11bit
 * @param  *SCOMdata�� ��������ָ�룬Ҫ�����鳤��25byte 8bit     
 *            * SCOMdata[0]               ���ֽ�        0x0F           
 *            * SCOMdata[1]-SCOMdata[22]  �û�����    
 *            * SCOMdata[23]              ��־�ֽ�      0x00     
 *            * SCOMdata[24]              β�ֽ�        0x00      
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_SBUStoSCOM(SBUSData_Struct *SBUSdata , uint8_t *SCOMdata);







#endif





