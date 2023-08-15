/**
  ******************************************************************************
  * @file    bsp_motor.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/5/24
  * @brief   �����˵ײ���ģ�������ʵ��
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "bsp_motor.h"

/* Global variable -----------------------------------------------------------*/
MOTOR_TypeDef_Struct      MOTOR1_BASE,MOTOR2_BASE;




/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_MOTOR_GPIO_Config(MOTOR_TypeDef_Struct *MOTORx);
ErrorStatus MOTOR_Drive_Set_Voltage(MOTOR_TypeDef_Struct *MOTORx , MOTOR_DRIVE_MODE drive_mode);
ErrorStatus MOTOR_Drive_Set_Duty(MOTOR_TypeDef_Struct *MOTORx , MOTOR_DRIVE_MODE drive_mode);


/* Public functions ----------------------------------------------------------*/


/**
 * @brief  ��ʼ�� MOTOR �ṹ��Ĭ������
 * @param  MOTOR_InitStruct  : MOTOR ��ʼ���ṹ��
 * @return void
 */
void BSP_MOTOR_InitStruct(MOTOR_InitTypedef_Struct *MOTOR_InitStruct)
{

    MOTOR_InitStruct->enable_MOTOR              = MOTOR_ENABLE_DEFAULT;         /* MOTOR ʹ��          */
    
    MOTOR_InitStruct->MOTOR_PWM_Prescaler       = MOTOR_PWM_PRESCALER_DEFAULT;  /* MOTOR PWM ��Ƶ      */
    MOTOR_InitStruct->MOTOR_PWM_Period          = MOTOR_PWM_PERIOD_DEFAULT;     /* MOTOR PWM ת��ֵ    */
    MOTOR_InitStruct->MOTOR_PWM_OCMode          = MOTOR_PWM_OCMODE_DEFAULT;     /* MOTOR PWM ���ģʽ  */
  
    MOTOR_InitStruct->MOTOR_PID_L.Kp            = MOTOR_PID_KP_L_DEFAULT;       /* MOTPR PID Kp ����ϵ��  */
    MOTOR_InitStruct->MOTOR_PID_L.Ki            = MOTOR_PID_KI_L_DEFAULT;       /* MOTPR PID Ki ����ϵ��  */
    MOTOR_InitStruct->MOTOR_PID_L.Kd            = MOTOR_PID_KD_L_DEFAULT;       /* MOTPR PID Kd ����ϵ��  */
    MOTOR_InitStruct->MOTOR_PID_L.Output_limit  = MOTOR_PID_OL_L_DEFAULT;       /* MOTPR PID OL ����ϵ�� */

    MOTOR_InitStruct->MOTOR_PID_R.Kp            = MOTOR_PID_KP_R_DEFAULT;       /* MOTPR PID Kp ����ϵ��  */
    MOTOR_InitStruct->MOTOR_PID_R.Ki            = MOTOR_PID_KI_R_DEFAULT;       /* MOTPR PID Ki ����ϵ��  */
    MOTOR_InitStruct->MOTOR_PID_R.Kd            = MOTOR_PID_KD_R_DEFAULT;       /* MOTPR PID Kd ����ϵ��  */
    MOTOR_InitStruct->MOTOR_PID_R.Output_limit  = MOTOR_PID_OL_R_DEFAULT;       /* MOTPR PID OL ����ϵ�� */  
           
}




/**
 * @brief  ��ʼ�� MOTOR �ṹ��
 * @param  *MOTORx           : MOTOR �ṹ��
 *         *MOTOR_InitStruct : MOTOR ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Init(MOTOR_TypeDef_Struct *MOTORx , MOTOR_InitTypedef_Struct *MOTOR_InitStruct)
{
    if ((MOTORx == NULL) || (MOTOR_InitStruct == NULL))
    {
        return ERROR;
    }
    
    BSP_PWM_InitStruct(&MOTORx->MOTOR_Operating.PWM_InitStruct);
    
    /*  MOTOR �Ĵ�����ֵ  */
    MOTORx->MOTOR_Operating.enable_MOTOR                     = MOTOR_InitStruct->enable_MOTOR;
    
    MOTORx->MOTOR_Operating.PWM_InitStruct.PWM_TIM_Prescaler = MOTOR_InitStruct->MOTOR_PWM_Prescaler;
    MOTORx->MOTOR_Operating.PWM_InitStruct.PWM_TIM_Period    = MOTOR_InitStruct->MOTOR_PWM_Period;
    MOTORx->MOTOR_Operating.PWM_InitStruct.PWM_TIM_OCMode    = MOTOR_InitStruct->MOTOR_PWM_OCMode;
    
    if (MOTORx == MOTOR1)
    {
        MOTOR1_BASE.MOTOR_Hardware.L_PWMx         = MOTOR1_L_PWM;
        MOTOR1_BASE.MOTOR_Hardware.R_PWMx         = MOTOR1_R_PWM;      
        MOTOR1_BASE.MOTOR_Hardware.L_EN_GPIO      = MOTOR1_L_EN_GPIO;
        MOTOR1_BASE.MOTOR_Hardware.L_EN_GPIO_PIN  = MOTOR1_L_EN_GPIO_PIN;
        MOTOR1_BASE.MOTOR_Hardware.R_EN_GPIO      = MOTOR1_R_EN_GPIO;
        MOTOR1_BASE.MOTOR_Hardware.R_EN_GPIO_PIN  = MOTOR1_R_EN_GPIO_PIN;
        MOTOR1_BASE.MOTOR_Hardware.L_DIR_GPIO     = MOTOR1_L_DIR_GPIO;
        MOTOR1_BASE.MOTOR_Hardware.L_DIR_GPIO_PIN = MOTOR1_L_DIR_GPIO_PIN;
        MOTOR1_BASE.MOTOR_Hardware.R_DIR_GPIO     = MOTOR1_R_DIR_GPIO;
        MOTOR1_BASE.MOTOR_Hardware.R_DIR_GPIO_PIN = MOTOR1_R_DIR_GPIO_PIN;
    }
    else if (MOTORx == MOTOR2)
    {
        MOTOR2_BASE.MOTOR_Hardware.L_PWMx         = MOTOR2_L_PWM;
        MOTOR2_BASE.MOTOR_Hardware.R_PWMx         = MOTOR2_R_PWM;      
        MOTOR2_BASE.MOTOR_Hardware.L_EN_GPIO      = MOTOR2_L_EN_GPIO;
        MOTOR2_BASE.MOTOR_Hardware.L_EN_GPIO_PIN  = MOTOR2_L_EN_GPIO_PIN;
        MOTOR2_BASE.MOTOR_Hardware.R_EN_GPIO      = MOTOR2_R_EN_GPIO;
        MOTOR2_BASE.MOTOR_Hardware.R_EN_GPIO_PIN  = MOTOR2_R_EN_GPIO_PIN;
        MOTOR2_BASE.MOTOR_Hardware.L_DIR_GPIO     = MOTOR2_L_DIR_GPIO;
        MOTOR2_BASE.MOTOR_Hardware.L_DIR_GPIO_PIN = MOTOR2_L_DIR_GPIO_PIN;
        MOTOR2_BASE.MOTOR_Hardware.R_DIR_GPIO     = MOTOR2_R_DIR_GPIO;
        MOTOR2_BASE.MOTOR_Hardware.R_DIR_GPIO_PIN = MOTOR2_R_DIR_GPIO_PIN;
    }
    else 
    {
        return ERROR;
    }
    
    /*  ��ʼ�� MOTOR PWM ͨ��   */
    if (  (ERROR == BSP_PWM_Init(MOTORx->MOTOR_Hardware.L_PWMx , &MOTORx->MOTOR_Operating.PWM_InitStruct))
       || (ERROR == BSP_PWM_Init(MOTORx->MOTOR_Hardware.R_PWMx , &MOTORx->MOTOR_Operating.PWM_InitStruct)) )
    {
        return ERROR;
    }
     
    /*  ��ʼ�� MOTOR PID ���ֵĻ������ֵĻ�  */
    if (  (ERROR ==  Algorithm_PID_Init(&MOTORx->MOTOR_Operating.L_PID_Buffer , &MOTOR_InitStruct->MOTOR_PID_L))
       || (ERROR ==  Algorithm_PID_Init(&MOTORx->MOTOR_Operating.R_PID_Buffer , &MOTOR_InitStruct->MOTOR_PID_R)) )
    {
        return ERROR;
    }
    
    /*  ��ʼ�� MOTOR GPIO ����  */
    if (ERROR == BSP_MOTOR_GPIO_Config(MOTORx))
    {
        return ERROR;
    }

    /*  ��ʼ�� MOTOR ����       */
    if ( ERROR == BSP_MOTOR_Drive(MOTORx , 0, 0, 1 ) )
    {
        return ERROR;
    }
    
    return SUCCESS;
    
}



/**
 * @brief  ʹ�� MOTOR ͨ��
 * @param  *MOTORx           : MOTORx �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Open(MOTOR_TypeDef_Struct *MOTORx)
{
    if (MOTORx == NULL)
    {
        return ERROR;
    }
    
    MOTORx->MOTOR_Operating.enable_MOTOR = ENABLE;
    
    if ( (PWM_Open(MOTORx->MOTOR_Hardware.L_PWMx)) || (PWM_Open(MOTORx->MOTOR_Hardware.R_PWMx)) )
    {
        return ERROR;
    }

    return SUCCESS;
}


/**
 * @brief  ʧ�� MOTOR ͨ��
 * @param  *MOTORx           : MOTORx �ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Close(MOTOR_TypeDef_Struct *MOTORx)
{
    if (MOTORx == NULL)
    {
        return ERROR;
    }
    
    MOTORx->MOTOR_Operating.enable_MOTOR = DISABLE;
    
    if ( (PWM_Close(MOTORx->MOTOR_Hardware.L_PWMx)) || (PWM_Close(MOTORx->MOTOR_Hardware.R_PWMx)) )
    {
        return ERROR;
    }
    return SUCCESS;
}




/**
 * @brief  ���� MOTOR ͨ�����
 * @param  *MOTORx           : MOTORx �ṹ��
 * @param  straight          : MOTORx ǰ���ٶ� -1~1
 * @param  turn              : MOTORx ����ת�� -1~1
 * @param  limit             : MOTORx �����ٶ�  0~1
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_Drive(MOTOR_TypeDef_Struct *MOTORx , float straight , float turn , float limit)
{
    MOTOR_DRIVE_MODE         drive_mode;
    static MOTOR_DRIVE_MODE  last_drive_mode = MOTOR_Drive_Brake_Mode; 
  
    if ((MOTORx == NULL) || (straight > 1) || (straight < -1) || (turn < -1) || (turn > 1))
    {
        return ERROR;
    }  
    
    MOTORx->MOTOR_Operating.straight_speed = straight;
    MOTORx->MOTOR_Operating.turn_speed     = turn;
    MOTORx->MOTOR_Operating.limit_speed    = limit;
    
    
    /* �ȴ���С���ȵ�ƫת�����͸���   */
    if ( (straight < 0.05) && (straight > -0.05) )
    {
        straight = 0;
    }
    if ( (turn < 0.05) && (turn > -0.05) )
    {
        turn = 0;
    }
    

    /* ͨ���趨���ٶ� �жϾ�������ģʽ */
    if (straight > 0) 
    {
        if (turn > 0)
        {
            drive_mode = MOTOR_Drive_Forward_Right_Mode;
        }
        else if (turn < 0)
        {
            drive_mode = MOTOR_Drive_Forward_Left_Mode;
        }
        else if (turn == 0)
        {
            drive_mode = MOTOR_Drive_Forward_Mode;
        }
    }
    else if (straight < 0)
    {
        if (turn > 0)
        {
            drive_mode = MOTOR_Drive_Backward_Right_Mode;
        }
        else if (turn < 0)
        {
            drive_mode = MOTOR_Drive_Backward_Left_Mode;
        }
        else if (turn == 0)
        {
            drive_mode = MOTOR_Drive_Backward_Mode;
        }
    }
    else if (straight == 0)
    {
        if (turn > 0)
        {
            drive_mode = MOTOR_Drive_Right_Mode;
        }
        else if (turn < 0)
        {
            drive_mode = MOTOR_Drive_Left_Mode;
        }
        else if (turn == 0)
        {
            drive_mode = MOTOR_Drive_Brake_Mode;
        }
    }
    
    /* ���������ϰ� ֻ��������ԭ�ز���     */
    if (MOTORx->MOTOR_Operating.limit_speed < 0)
    {
        if (straight > 0.01)
        {
            drive_mode = MOTOR_Drive_Brake_Mode;
        }
    }

    /* �������ģʽ�����ı� ��Ҫ�������õ�ƽ */
    if (drive_mode != last_drive_mode)
    {
        /*  ����ģʽ���õ�ƽ       */
        MOTOR_Drive_Set_Voltage(MOTORx , drive_mode);
    }

    
    /*  ����ģʽ����PWMռ�ձ�  */
    if (ERROR == MOTOR_Drive_Set_Duty(MOTORx , drive_mode))
    {
        return ERROR;
    } 


    last_drive_mode = drive_mode;
  
    return SUCCESS;
}




/* Private functions ---------------------------------------------------------*/




/**
 * @brief  ��ʼ�� MOTOR GPIO ����
 * @param  *PWMx           : PWM�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_MOTOR_GPIO_Config(MOTOR_TypeDef_Struct *MOTORx)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
  
    if ( (MOTORx == NULL) || (MOTORx->MOTOR_Hardware.L_EN_GPIO      == NULL) 
                          || (MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN  == NULL)
                          || (MOTORx->MOTOR_Hardware.R_EN_GPIO      == NULL) 
                          || (MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN  == NULL)
                          || (MOTORx->MOTOR_Hardware.L_DIR_GPIO     == NULL) 
                          || (MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN == NULL)
                          || (MOTORx->MOTOR_Hardware.R_DIR_GPIO     == NULL) 
                          || (MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN == NULL) )
    
    {
        return ERROR;
    }
    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_InitStructure.GPIO_Pin   = MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN;
    GPIO_Init(MOTORx->MOTOR_Hardware.L_EN_GPIO , &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN;
    GPIO_Init(MOTORx->MOTOR_Hardware.R_EN_GPIO , &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN;
    GPIO_Init(MOTORx->MOTOR_Hardware.L_DIR_GPIO , &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN;
    GPIO_Init(MOTORx->MOTOR_Hardware.R_DIR_GPIO , &GPIO_InitStructure);
    
    GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_EN_GPIO ,  MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN);
    GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_EN_GPIO ,  MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN);
    GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_DIR_GPIO , MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN);
    GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_DIR_GPIO , MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN);
    
    return SUCCESS;
}



/**
 * @brief  ���� MOTOR �������Ÿߵ͵�ƽ
 * @param  *MOTORx           : MOTORx �ṹ��
 * @param  drive_mode        : MOTORx ����ģʽ
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MOTOR_Drive_Set_Voltage(MOTOR_TypeDef_Struct *MOTORx , MOTOR_DRIVE_MODE drive_mode)
{
  
    uint8_t voltage_mode = 0;
  
    if (MOTORx == NULL)
    {
        return ERROR;
    }
  
    if ((drive_mode == MOTOR_Drive_Forward_Mode) || (drive_mode == MOTOR_Drive_Forward_Right_Mode) 
                                                 || (drive_mode == MOTOR_Drive_Forward_Left_Mode) )
    {
        voltage_mode = 0;
    }
    else if ((drive_mode == MOTOR_Drive_Backward_Mode) || (drive_mode == MOTOR_Drive_Backward_Right_Mode) 
                                                       || (drive_mode == MOTOR_Drive_Backward_Left_Mode) )
    {
        voltage_mode = 1;
    }
    else if (drive_mode == MOTOR_Drive_Left_Mode)
    {
        voltage_mode = 2;
    }
    else if (drive_mode == MOTOR_Drive_Right_Mode)
    {
        voltage_mode = 3;
    }
    else if (drive_mode == MOTOR_Drive_Brake_Mode)
    {
        voltage_mode = 4;
    }
    else 
    {
        return ERROR;
    }
    
    switch(voltage_mode)
    {
        /*  ��ǰ  L:10 R:01   */
        case 0:
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.L_EN_GPIO  , MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN);
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_DIR_GPIO , MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN);
        
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_EN_GPIO  , MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN);
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.R_DIR_GPIO , MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN);
            break;
        
        /*  ���  L:01 R:10   */
        case 1:
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_EN_GPIO  , MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN);
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.L_DIR_GPIO , MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN);
        
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.R_EN_GPIO  , MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN);
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_DIR_GPIO , MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN);
            break;
        
        /*  ����  L:01 R:01   */
        case  2:
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_EN_GPIO  , MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN);
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.L_DIR_GPIO , MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN);
           
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_EN_GPIO  , MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN);
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.R_DIR_GPIO , MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN);
            break;
        
        /*  ����  L:10 R:10   */
        case 3:
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.L_EN_GPIO  , MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN);
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_DIR_GPIO , MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN);
            
            GPIO_SetBits  (MOTORx->MOTOR_Hardware.R_EN_GPIO  , MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN);
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_DIR_GPIO , MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN);
            break;
        
        /*  ɲ��  L:00 R:00   */
        case 4: 
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_EN_GPIO  , MOTORx->MOTOR_Hardware.L_EN_GPIO_PIN);
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.L_DIR_GPIO , MOTORx->MOTOR_Hardware.L_DIR_GPIO_PIN);
            
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_EN_GPIO  , MOTORx->MOTOR_Hardware.R_EN_GPIO_PIN);
            GPIO_ResetBits(MOTORx->MOTOR_Hardware.R_DIR_GPIO , MOTORx->MOTOR_Hardware.R_DIR_GPIO_PIN);
            break;
        default:
            break;
        
    }
  
    return SUCCESS;
}



/**
 * @brief  ���� MOTOR ����PWMռ�ձ�
 * @param  *MOTORx           : MOTORx �ṹ��
 * @param  drive_mode        : MOTORx ����ģʽ
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MOTOR_Drive_Set_Duty(MOTOR_TypeDef_Struct *MOTORx , MOTOR_DRIVE_MODE drive_mode)
{   
    float stiaght_speed = 0;
    float turn_speed    = 0;
    float limit_speed   = 1;
  
    float left_speed    = 0;
    float right_speed   = 0;
  
    static float left_speed_last    = 0;
    static float right_speed_last   = 0;
  
    if (MOTORx == NULL)
    {
        return ERROR;
    }
  
    stiaght_speed = MOTORx->MOTOR_Operating.straight_speed;            /* ֱ�е��ٶ�   */
    turn_speed    = MOTORx->MOTOR_Operating.turn_speed;                /* ת����ٶ�   */ 
    limit_speed   = MOTORx->MOTOR_Operating.limit_speed;               /* �ɷ�����ٶ� */
    
    /* ����PWM ��������Ҫ�����ķ���         */
    if(stiaght_speed < 0)
    {
        stiaght_speed = -stiaght_speed;
    }
    
    if(turn_speed < 0)
    {
        turn_speed = -turn_speed;
    }
    
    
    /* ���������ϰ� ֻ��������ԭ�ز���     */
    if (limit_speed < 0)
    {
        limit_speed = 0.6;
    }
    
    /* ֱ��ģʽ */
    if ( (drive_mode == MOTOR_Drive_Forward_Mode) || (drive_mode == MOTOR_Drive_Backward_Mode)) 
    {
        left_speed  = stiaght_speed * 0.55 * limit_speed;
        right_speed = stiaght_speed * 0.55 * limit_speed;
    }
    
    /* ɲ��ģʽ */
    else if  (drive_mode == MOTOR_Drive_Brake_Mode)
    {
        left_speed  = 0;
        right_speed = 0;
    }
    
    /* ����ģʽ */
    else if ((drive_mode == MOTOR_Drive_Forward_Right_Mode) || (drive_mode == MOTOR_Drive_Backward_Right_Mode))
    {
        left_speed  = ( stiaght_speed * 0.55 + turn_speed * 0.45 ) * limit_speed;
        right_speed =   stiaght_speed * 0.55                      * limit_speed;
    }
    
    /* ����ģʽ */
    else if ((drive_mode == MOTOR_Drive_Forward_Left_Mode) || (drive_mode == MOTOR_Drive_Backward_Left_Mode)) 
    {
        left_speed  =   stiaght_speed * 0.55                      * limit_speed;          
        right_speed = ( stiaght_speed * 0.55 + turn_speed * 0.45 ) * limit_speed;
    }
    
    /* ԭ��ģʽ */
    else if ((drive_mode == MOTOR_Drive_Left_Mode) || (drive_mode == MOTOR_Drive_Right_Mode))
    { 
        left_speed  = turn_speed * 0.45 * limit_speed;
        right_speed = turn_speed * 0.45 * limit_speed;
    }
    else 
    {
        return ERROR;
    }
    
   
    /* PID ���ƻ�����    */
    PID_Adjustable_Ring(&MOTORx->MOTOR_Operating.L_PID_Buffer , left_speed 
                        , ( (left_speed + left_speed_last) / 2) );
    
    PID_Adjustable_Ring(&MOTORx->MOTOR_Operating.R_PID_Buffer , right_speed 
                        , ( (right_speed + right_speed_last) / 2) );

    /*  PID ������ֵ     */
    left_speed  += MOTORx->MOTOR_Operating.L_PID_Buffer.Inc;
    right_speed += MOTORx->MOTOR_Operating.R_PID_Buffer.Inc;
    
    left_speed_last = left_speed;
    right_speed_last = right_speed_last;
    
    /*  ���õ��ռ�ձ�   */
    if ( (ERROR == PWM_Set_Duty(MOTORx->MOTOR_Hardware.L_PWMx , left_speed))
       ||(ERROR == PWM_Set_Duty(MOTORx->MOTOR_Hardware.R_PWMx , right_speed)) )
    {
        return ERROR;
    }
  
    return SUCCESS;
    
}




















