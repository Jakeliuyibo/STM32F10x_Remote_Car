/**
  ******************************************************************************
  * @file    bsp_motor.h
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/24
  * @brief   �����˵ײ���ģ����ⲿ�ӿ�
  ******************************************************************************/
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_pwm.h"
#include "string.h"
#include "algorithm_PID.h"

/* Defitions -----------------------------------------------------------------*/

#define MOTOR_ENABLE_DEFAULT            ENABLE              /* Ĭ�� MOTOR ʹ��             */

#define MOTOR_PWM_PRESCALER_DEFAULT     0                   /* Ĭ�� MOTOR PWM ��Ƶϵ��     */
#define MOTOR_PWM_PERIOD_DEFAULT        9999                /* Ĭ�� MOTOR PWM Ԥת��ֵ    */
#define MOTOR_PWM_OCMODE_DEFAULT        TIM_OCMode_PWM1     /* Ĭ�� MOTOR PWM ���ģʽ     */

#define MOTOR_PID_KP_L_DEFAULT          0.7                 /* Ĭ�� MOTPR PID Kp ����ϵ��  */
#define MOTOR_PID_KI_L_DEFAULT          0.1                 /* Ĭ�� MOTPR PID Ki ����ϵ��  */
#define MOTOR_PID_KD_L_DEFAULT          0.2                 /* Ĭ�� MOTPR PID Kd ����ϵ��  */
#define MOTOR_PID_OL_L_DEFAULT          0.9                 /* Ĭ�� MOTPR PID OL ����ϵ��  */

#define MOTOR_PID_KP_R_DEFAULT          0.7                 /* Ĭ�� MOTPR PID Kp ����ϵ��  */
#define MOTOR_PID_KI_R_DEFAULT          0.1                 /* Ĭ�� MOTPR PID Ki ����ϵ��  */
#define MOTOR_PID_KD_R_DEFAULT          0.2                 /* Ĭ�� MOTPR PID Kd ����ϵ��  */
#define MOTOR_PID_OL_R_DEFAULT          0.9                 /* Ĭ�� MOTPR PID OL ����ϵ��  */

/* typedef -------------------------------------------------------------------*/



/** 
  * @brief  ���� MOTOR ����ģʽ
  */
typedef enum __MOTOR_DRIVE_MODE
{
    MOTOR_Drive_Forward_Mode,               /*  MOTOR ��ǰ   ģʽ  */
    MOTOR_Drive_Forward_Right_Mode,         /*  MOTOR ��ǰ�� ģʽ  */
    MOTOR_Drive_Forward_Left_Mode,          /*  MOTOR ��ǰ�� ģʽ  */
  
    MOTOR_Drive_Backward_Mode,              /*  MOTOR ���   ģʽ  */
    MOTOR_Drive_Backward_Right_Mode,        /*  MOTOR ����� ģʽ  */
    MOTOR_Drive_Backward_Left_Mode,         /*  MOTOR ����� ģʽ  */
  
    MOTOR_Drive_Brake_Mode,                 /*  MOTOR ɲ��   ģʽ  */
    MOTOR_Drive_Right_Mode,                 /*  MOTOR ��ת   ģʽ  */
    MOTOR_Drive_Left_Mode                   /*  MOTOR ��ת   ģʽ  */ 
  
}MOTOR_DRIVE_MODE;



/** 
  * @brief  ���� MOTOR Ӳ���ṹ��
  */
typedef struct __MOTORHardware_Typedef_Struct
{
    PWM_TypeDef_Struct                 *L_PWMx;                    /* MOTOR PWM ��ͨ�� */
    PWM_TypeDef_Struct                 *R_PWMx;                    /* MOTOR PWM ��ͨ�� */
  
    GPIO_TypeDef                       *L_EN_GPIO;                 /* MOTOR EN  ��˿� */
    uint16_t                            L_EN_GPIO_PIN;             /* MOTOR EN  ������ */
    GPIO_TypeDef                       *R_EN_GPIO;                 /* MOTOR EN  �Ҷ˿� */ 
    uint16_t                            R_EN_GPIO_PIN;             /* MOTOR EN  ������ */
    GPIO_TypeDef                       *L_DIR_GPIO;                /* MOTOR DIR ��˿� */
    uint16_t                            L_DIR_GPIO_PIN;            /* MOTOR DIR ������ */
    GPIO_TypeDef                       *R_DIR_GPIO;                /* MOTOR DIR �Ҷ˿� */   
    uint16_t                            R_DIR_GPIO_PIN;            /* MOTOR DIR ������ */
  
}MOTORHardware_Typedef_Struct;



/** 
  * @brief  ���� MOTOR �Ĵ����ṹ��
  */
typedef struct __MOTORRegister_Typedef_Struct
{
  
    FunctionalState                     enable_MOTOR;              /* MOTOR ʹ��            */
    PWM_InitTypedef_Struct              PWM_InitStruct;            /* MOTOR PWM��ʼ���ṹ�� */
    float                               straight_speed;            /* MOTOR ǰ���ٶ� -1~1   */
    float                               turn_speed;                /* MOTOR �����ٶ� -1~1   */   
    float                               limit_speed;               /* MOTOR �����ٶ�  0~1   */

    PIDControl_Typedef_Struct           L_PID_Buffer;              /* MOTOR PID ���ֿ���    */
    PIDControl_Typedef_Struct           R_PID_Buffer;              /* MOTOR PID ���ֿ���    */
    
}MOTORRegister_Typedef_Struct;



/** 
  * @brief  ���� MOTOR �ṹ��
  */
typedef struct __MOTOR_TypeDef_Struct
{
    MOTORHardware_Typedef_Struct        MOTOR_Hardware;            /* MOTOR Ӳ���ṹ�� */
    MOTORRegister_Typedef_Struct        MOTOR_Operating;           /* MOTOR ���ýṹ�� */
}MOTOR_TypeDef_Struct;


/** 
  * @brief  ���� MOTOR ��ʼ���Ĵ����ṹ��
  */
typedef struct __MOTOR_InitTypedef_Struct
{
    FunctionalState                     enable_MOTOR;              /* MOTOR ʹ��            */
      
    uint16_t                            MOTOR_PWM_Prescaler;       /* MOTOR PWM  ��Ƶϵ��   */
    uint16_t                            MOTOR_PWM_Period;          /* MOTOR PWM  Ԥת��ֵ   */
    uint16_t                            MOTOR_PWM_OCMode;          /* MOTOR PWM  ���ģʽ   */
    
    float                               straight_speed;            /* MOTOR ǰ���ٶ� -1~1   */
    float                               turn_speed;                /* MOTOR �����ٶ� -1~1   */   
    float                               limit_speed;               /* MOTOR �����ٶ�  0~1   */
  
    PIDControl_InitTypedef_Struct       MOTOR_PID_L;               /* MOTOR PID ����ƻ�    */   
    PIDControl_InitTypedef_Struct       MOTOR_PID_R;               /* MOTOR PID �ҿ��ƻ�    */   
  
}MOTOR_InitTypedef_Struct;



/* MOTOR BASE ----------------------------------------------------------------*/
extern MOTOR_TypeDef_Struct             MOTOR1_BASE;
#define MOTOR1                          (&MOTOR1_BASE)   /* MOTOR1 selected          */
#define MOTOR1_L_PWM                    (PWM2        )   /* MOTOR1 LEFT  PWM CHANNEL */
#define MOTOR1_R_PWM                    (PWM1        )   /* MOTOR1 RIGHT PWM CHANNEL */
#define MOTOR1_L_EN_GPIO                (GPIOC       )   /* MOTOR1 LEFT  EN  �˿�    */
#define MOTOR1_L_EN_GPIO_PIN            (GPIO_Pin_0  )   /* MOTOR1 LEFT  EN  ����    */
#define MOTOR1_R_EN_GPIO                (GPIOC       )   /* MOTOR1 RIGHT EN  �˿�    */
#define MOTOR1_R_EN_GPIO_PIN            (GPIO_Pin_2  )   /* MOTOR1 RIGHT EN  ����    */
#define MOTOR1_L_DIR_GPIO               (GPIOC       )   /* MOTOR1 LEFT  DIR �˿�    */
#define MOTOR1_L_DIR_GPIO_PIN           (GPIO_Pin_1  )   /* MOTOR1 LEFT  DIR ����    */
#define MOTOR1_R_DIR_GPIO               (GPIOC       )   /* MOTOR1 RIGHT DIR �˿�    */
#define MOTOR1_R_DIR_GPIO_PIN           (GPIO_Pin_3  )   /* MOTOR1 RIGHT DIR ����    */


extern MOTOR_TypeDef_Struct             MOTOR2_BASE;
#define MOTOR2                          (&MOTOR2_BASE)   /* MOTOR2 selected          */
#define MOTOR2_L_PWM                    (PWM3        )   /* MOTOR2 LEFT  PWM CHANNEL */
#define MOTOR2_R_PWM                    (PWM4        )   /* MOTOR2 RIGHT PWM CHANNEL */
#define MOTOR2_L_EN_GPIO                (GPIOG       )   /* MOTOR2 LEFT  EN  �˿�    */
#define MOTOR2_L_EN_GPIO_PIN            (GPIO_Pin_4  )   /* MOTOR2 LEFT  EN  ����    */
#define MOTOR2_R_EN_GPIO                (GPIOG       )   /* MOTOR2 RIGHT EN  �˿�    */
#define MOTOR2_R_EN_GPIO_PIN            (GPIO_Pin_5  )   /* MOTOR2 RIGHT EN  ����    */
#define MOTOR2_L_DIR_GPIO               (GPIOG       )   /* MOTOR2 LEFT  DIR �˿�    */
#define MOTOR2_L_DIR_GPIO_PIN           (GPIO_Pin_6  )   /* MOTOR2 LEFT  DIR ����    */
#define MOTOR2_R_DIR_GPIO               (GPIOG       )   /* MOTOR2 RIGHT DIR �˿�    */
#define MOTOR2_R_DIR_GPIO_PIN           (GPIO_Pin_7  )   /* MOTOR2 RIGHT DIR ����    */




/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  ��ʼ�� MOTOR �ṹ��Ĭ������
 * @param  MOTOR_InitStruct  : MOTOR ��ʼ���ṹ��
 * @return void
 */
void BSP_MOTOR_InitStruct(MOTOR_InitTypedef_Struct *MOTOR_InitStruct);



/**
 * @brief  ��ʼ�� MOTOR �ṹ��
 * @param  *MOTORx           : MOTOR �ṹ��
 *         *MOTOR_InitStruct : MOTOR ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Init(MOTOR_TypeDef_Struct *MOTORx , MOTOR_InitTypedef_Struct *MOTOR_InitStruct);


/**
 * @brief  ���� MOTOR ͨ�����
 * @param  *MOTORx           : MOTORx �ṹ��
 * @param  straight          : MOTORx ǰ���ٶ� -1~1
 * @param  turn              : MOTORx ����ת�� -1~1
 * @param  limit             : MOTORx �����ٶ�  0~1
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Drive(MOTOR_TypeDef_Struct *MOTORx , float straight , float turn , float limit);


/**
 * @brief  ʹ�� MOTOR ͨ��
 * @param  *MOTORx           : MOTORx �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Open(MOTOR_TypeDef_Struct *MOTORx);



/**
 * @brief  ʧ�� MOTOR ͨ��
 * @param  *MOTORx           : MOTORx �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Close(MOTOR_TypeDef_Struct *MOTORx);






#endif







