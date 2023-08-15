/**
  ******************************************************************************
  * @file    bsp_motor.h
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/24
  * @brief   描述了底层电机模块的外部接口
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

#define MOTOR_ENABLE_DEFAULT            ENABLE              /* 默认 MOTOR 使能             */

#define MOTOR_PWM_PRESCALER_DEFAULT     0                   /* 默认 MOTOR PWM 分频系数     */
#define MOTOR_PWM_PERIOD_DEFAULT        9999                /* 默认 MOTOR PWM 预转载值    */
#define MOTOR_PWM_OCMODE_DEFAULT        TIM_OCMode_PWM1     /* 默认 MOTOR PWM 输出模式     */

#define MOTOR_PID_KP_L_DEFAULT          0.7                 /* 默认 MOTPR PID Kp 左轮系数  */
#define MOTOR_PID_KI_L_DEFAULT          0.1                 /* 默认 MOTPR PID Ki 左轮系数  */
#define MOTOR_PID_KD_L_DEFAULT          0.2                 /* 默认 MOTPR PID Kd 左轮系数  */
#define MOTOR_PID_OL_L_DEFAULT          0.9                 /* 默认 MOTPR PID OL 左轮系数  */

#define MOTOR_PID_KP_R_DEFAULT          0.7                 /* 默认 MOTPR PID Kp 右轮系数  */
#define MOTOR_PID_KI_R_DEFAULT          0.1                 /* 默认 MOTPR PID Ki 右轮系数  */
#define MOTOR_PID_KD_R_DEFAULT          0.2                 /* 默认 MOTPR PID Kd 右轮系数  */
#define MOTOR_PID_OL_R_DEFAULT          0.9                 /* 默认 MOTPR PID OL 右轮系数  */

/* typedef -------------------------------------------------------------------*/



/** 
  * @brief  定义 MOTOR 驱动模式
  */
typedef enum __MOTOR_DRIVE_MODE
{
    MOTOR_Drive_Forward_Mode,               /*  MOTOR 向前   模式  */
    MOTOR_Drive_Forward_Right_Mode,         /*  MOTOR 向前右 模式  */
    MOTOR_Drive_Forward_Left_Mode,          /*  MOTOR 向前左 模式  */
  
    MOTOR_Drive_Backward_Mode,              /*  MOTOR 向后   模式  */
    MOTOR_Drive_Backward_Right_Mode,        /*  MOTOR 向后右 模式  */
    MOTOR_Drive_Backward_Left_Mode,         /*  MOTOR 向后左 模式  */
  
    MOTOR_Drive_Brake_Mode,                 /*  MOTOR 刹车   模式  */
    MOTOR_Drive_Right_Mode,                 /*  MOTOR 右转   模式  */
    MOTOR_Drive_Left_Mode                   /*  MOTOR 左转   模式  */ 
  
}MOTOR_DRIVE_MODE;



/** 
  * @brief  定义 MOTOR 硬件结构体
  */
typedef struct __MOTORHardware_Typedef_Struct
{
    PWM_TypeDef_Struct                 *L_PWMx;                    /* MOTOR PWM 左通道 */
    PWM_TypeDef_Struct                 *R_PWMx;                    /* MOTOR PWM 右通道 */
  
    GPIO_TypeDef                       *L_EN_GPIO;                 /* MOTOR EN  左端口 */
    uint16_t                            L_EN_GPIO_PIN;             /* MOTOR EN  左引脚 */
    GPIO_TypeDef                       *R_EN_GPIO;                 /* MOTOR EN  右端口 */ 
    uint16_t                            R_EN_GPIO_PIN;             /* MOTOR EN  右引脚 */
    GPIO_TypeDef                       *L_DIR_GPIO;                /* MOTOR DIR 左端口 */
    uint16_t                            L_DIR_GPIO_PIN;            /* MOTOR DIR 左引脚 */
    GPIO_TypeDef                       *R_DIR_GPIO;                /* MOTOR DIR 右端口 */   
    uint16_t                            R_DIR_GPIO_PIN;            /* MOTOR DIR 右引脚 */
  
}MOTORHardware_Typedef_Struct;



/** 
  * @brief  定义 MOTOR 寄存器结构体
  */
typedef struct __MOTORRegister_Typedef_Struct
{
  
    FunctionalState                     enable_MOTOR;              /* MOTOR 使能            */
    PWM_InitTypedef_Struct              PWM_InitStruct;            /* MOTOR PWM初始化结构体 */
    float                               straight_speed;            /* MOTOR 前后速度 -1~1   */
    float                               turn_speed;                /* MOTOR 左右速度 -1~1   */   
    float                               limit_speed;               /* MOTOR 限制速度  0~1   */

    PIDControl_Typedef_Struct           L_PID_Buffer;              /* MOTOR PID 左轮控制    */
    PIDControl_Typedef_Struct           R_PID_Buffer;              /* MOTOR PID 右轮控制    */
    
}MOTORRegister_Typedef_Struct;



/** 
  * @brief  定义 MOTOR 结构体
  */
typedef struct __MOTOR_TypeDef_Struct
{
    MOTORHardware_Typedef_Struct        MOTOR_Hardware;            /* MOTOR 硬件结构体 */
    MOTORRegister_Typedef_Struct        MOTOR_Operating;           /* MOTOR 配置结构体 */
}MOTOR_TypeDef_Struct;


/** 
  * @brief  定义 MOTOR 初始化寄存器结构体
  */
typedef struct __MOTOR_InitTypedef_Struct
{
    FunctionalState                     enable_MOTOR;              /* MOTOR 使能            */
      
    uint16_t                            MOTOR_PWM_Prescaler;       /* MOTOR PWM  分频系数   */
    uint16_t                            MOTOR_PWM_Period;          /* MOTOR PWM  预转载值   */
    uint16_t                            MOTOR_PWM_OCMode;          /* MOTOR PWM  输出模式   */
    
    float                               straight_speed;            /* MOTOR 前后速度 -1~1   */
    float                               turn_speed;                /* MOTOR 左右速度 -1~1   */   
    float                               limit_speed;               /* MOTOR 限制速度  0~1   */
  
    PIDControl_InitTypedef_Struct       MOTOR_PID_L;               /* MOTOR PID 左控制环    */   
    PIDControl_InitTypedef_Struct       MOTOR_PID_R;               /* MOTOR PID 右控制环    */   
  
}MOTOR_InitTypedef_Struct;



/* MOTOR BASE ----------------------------------------------------------------*/
extern MOTOR_TypeDef_Struct             MOTOR1_BASE;
#define MOTOR1                          (&MOTOR1_BASE)   /* MOTOR1 selected          */
#define MOTOR1_L_PWM                    (PWM2        )   /* MOTOR1 LEFT  PWM CHANNEL */
#define MOTOR1_R_PWM                    (PWM1        )   /* MOTOR1 RIGHT PWM CHANNEL */
#define MOTOR1_L_EN_GPIO                (GPIOC       )   /* MOTOR1 LEFT  EN  端口    */
#define MOTOR1_L_EN_GPIO_PIN            (GPIO_Pin_0  )   /* MOTOR1 LEFT  EN  引脚    */
#define MOTOR1_R_EN_GPIO                (GPIOC       )   /* MOTOR1 RIGHT EN  端口    */
#define MOTOR1_R_EN_GPIO_PIN            (GPIO_Pin_2  )   /* MOTOR1 RIGHT EN  引脚    */
#define MOTOR1_L_DIR_GPIO               (GPIOC       )   /* MOTOR1 LEFT  DIR 端口    */
#define MOTOR1_L_DIR_GPIO_PIN           (GPIO_Pin_1  )   /* MOTOR1 LEFT  DIR 引脚    */
#define MOTOR1_R_DIR_GPIO               (GPIOC       )   /* MOTOR1 RIGHT DIR 端口    */
#define MOTOR1_R_DIR_GPIO_PIN           (GPIO_Pin_3  )   /* MOTOR1 RIGHT DIR 引脚    */


extern MOTOR_TypeDef_Struct             MOTOR2_BASE;
#define MOTOR2                          (&MOTOR2_BASE)   /* MOTOR2 selected          */
#define MOTOR2_L_PWM                    (PWM3        )   /* MOTOR2 LEFT  PWM CHANNEL */
#define MOTOR2_R_PWM                    (PWM4        )   /* MOTOR2 RIGHT PWM CHANNEL */
#define MOTOR2_L_EN_GPIO                (GPIOG       )   /* MOTOR2 LEFT  EN  端口    */
#define MOTOR2_L_EN_GPIO_PIN            (GPIO_Pin_4  )   /* MOTOR2 LEFT  EN  引脚    */
#define MOTOR2_R_EN_GPIO                (GPIOG       )   /* MOTOR2 RIGHT EN  端口    */
#define MOTOR2_R_EN_GPIO_PIN            (GPIO_Pin_5  )   /* MOTOR2 RIGHT EN  引脚    */
#define MOTOR2_L_DIR_GPIO               (GPIOG       )   /* MOTOR2 LEFT  DIR 端口    */
#define MOTOR2_L_DIR_GPIO_PIN           (GPIO_Pin_6  )   /* MOTOR2 LEFT  DIR 引脚    */
#define MOTOR2_R_DIR_GPIO               (GPIOG       )   /* MOTOR2 RIGHT DIR 端口    */
#define MOTOR2_R_DIR_GPIO_PIN           (GPIO_Pin_7  )   /* MOTOR2 RIGHT DIR 引脚    */




/* Interface declaration -----------------------------------------------------*/


/**
 * @brief  初始化 MOTOR 结构体默认配置
 * @param  MOTOR_InitStruct  : MOTOR 初始化结构体
 * @return void
 */
void BSP_MOTOR_InitStruct(MOTOR_InitTypedef_Struct *MOTOR_InitStruct);



/**
 * @brief  初始化 MOTOR 结构体
 * @param  *MOTORx           : MOTOR 结构体
 *         *MOTOR_InitStruct : MOTOR 初始化结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Init(MOTOR_TypeDef_Struct *MOTORx , MOTOR_InitTypedef_Struct *MOTOR_InitStruct);


/**
 * @brief  驱动 MOTOR 通道输出
 * @param  *MOTORx           : MOTORx 结构体
 * @param  straight          : MOTORx 前后速度 -1~1
 * @param  turn              : MOTORx 左右转向 -1~1
 * @param  limit             : MOTORx 限制速度  0~1
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Drive(MOTOR_TypeDef_Struct *MOTORx , float straight , float turn , float limit);


/**
 * @brief  使能 MOTOR 通道
 * @param  *MOTORx           : MOTORx 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Open(MOTOR_TypeDef_Struct *MOTORx);



/**
 * @brief  失能 MOTOR 通道
 * @param  *MOTORx           : MOTORx 结构体
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Close(MOTOR_TypeDef_Struct *MOTORx);






#endif







