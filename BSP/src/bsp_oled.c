/**
  ******************************************************************************
  * @file    bsp_oled.c
  * @author  LYB
  * @version V1.0.1
  * @date    2021/3/30
  * @brief   �����˵ײ�oledͨ�õ������ⲿ�ӿ�
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "bsp_oled.h"
#include "lib_oledfont.h"


/* Global variable -----------------------------------------------------------*/
OLED_TypeDef_Struct                       OLED1_BASE,OLED2_BASE;


/* Private functions declaration----------------------------------------------*/
ErrorStatus BSP_OLED_GPIO_Config(OLED_TypeDef_Struct *OLEDx);
ErrorStatus BSP_OLED_Reset(OLED_TypeDef_Struct *OLEDx);
ErrorStatus BSP_OLED_WriteByte(OLED_TypeDef_Struct *OLEDx , uint8_t data , uint8_t mode);
ErrorStatus BSP_OLED_DrawPoint(OLED_TypeDef_Struct *OLEDx ,u8 x_coordinate, u8 y_coordinate, u8 mode);



/* Public functions ----------------------------------------------------------*/

/**
 * @brief  ��ʼ�� OLED �ṹ��Ĭ������
 * @param  OLED_InitStruct  : OLED ��ʼ���ṹ��
 * @return void
 */
void BSP_OLED_InitStruct(OLED_InitTypeDef_Struct *OLED_InitStruct)
{
  
    OLED_InitStruct->enable_OLED         = OLED_ENABLE_DEFAULT;                     /* OLED ʹ��       */
  
}




/**
 * @brief  ��ʼ�� OLED �ṹ��
 * @param  *OLEDx            : OLED �ṹ��
 *         *OLED_InitStruct  : OLED ��ʼ���ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Init(OLED_TypeDef_Struct *OLEDx , OLED_InitTypeDef_Struct *OLED_InitStruct)
{
    if ( (OLEDx == NULL) || (OLED_InitStruct == NULL) )
    {
        return ERROR;
    }
    
    OLEDx->OLED_Operating.enable_OLED         = OLED_InitStruct->enable_OLED;
    
    if (OLEDx == OLED1)
    {
        OLEDx->OLED_Hardware.CLK_GPIO         = OLED1_CLK_GPIO;
        OLEDx->OLED_Hardware.CLK_GPIO_PIN     = OLED1_CLK_GPIO_PIN;
        OLEDx->OLED_Hardware.DATA_GPIO        = OLED1_DATA_GPIO;
        OLEDx->OLED_Hardware.DATA_GPIO_PIN    = OLED1_DATA_GPIO_PIN;
        OLEDx->OLED_Hardware.RES_GPIO         = OLED1_RES_GPIO;
        OLEDx->OLED_Hardware.RES_GPIO_PIN     = OLED1_RES_GPIO_PIN;
        OLEDx->OLED_Hardware.DC_GPIO          = OLED1_DC_GPIO;
        OLEDx->OLED_Hardware.DC_GPIO_PIN      = OLED1_DC_GPIO_PIN;
        OLEDx->OLED_Hardware.CS_GPIO          = OLED1_CS_GPIO;
        OLEDx->OLED_Hardware.CS_GPIO_PIN      = OLED1_CS_GPIO_PIN;
    }
    else if (OLEDx == OLED2)
    {
        OLEDx->OLED_Hardware.CLK_GPIO         = OLED2_CLK_GPIO;
        OLEDx->OLED_Hardware.CLK_GPIO_PIN     = OLED2_CLK_GPIO_PIN;
        OLEDx->OLED_Hardware.DATA_GPIO        = OLED2_DATA_GPIO;
        OLEDx->OLED_Hardware.DATA_GPIO_PIN    = OLED2_DATA_GPIO_PIN;
        OLEDx->OLED_Hardware.RES_GPIO         = OLED2_RES_GPIO;
        OLEDx->OLED_Hardware.RES_GPIO_PIN     = OLED2_RES_GPIO_PIN;
        OLEDx->OLED_Hardware.DC_GPIO          = OLED2_DC_GPIO;
        OLEDx->OLED_Hardware.DC_GPIO_PIN      = OLED2_DC_GPIO_PIN;
        OLEDx->OLED_Hardware.CS_GPIO          = OLED2_CS_GPIO;
        OLEDx->OLED_Hardware.CS_GPIO_PIN      = OLED2_CS_GPIO_PIN;
    }
    else 
    {
        return ERROR;
    }
    
    /*  ��ʼ�� OLED GPIO ����  */
    if (ERROR == BSP_OLED_GPIO_Config(OLEDx))
    {
        return ERROR;
    }


    /*  ��λ OLED              */
    BSP_OLED_Reset(OLEDx);
    
    /*  ���üĴ���             */
    BSP_OLED_WriteByte(OLEDx , 0xAE , OLED_Write_Mode_Cmd);//--turn off oled panel
    BSP_OLED_WriteByte(OLEDx , 0x00 , OLED_Write_Mode_Cmd);//---set low column address
    BSP_OLED_WriteByte(OLEDx , 0x10 , OLED_Write_Mode_Cmd);//---set high column address
    BSP_OLED_WriteByte(OLEDx , 0x40 , OLED_Write_Mode_Cmd);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    BSP_OLED_WriteByte(OLEDx , 0x81 , OLED_Write_Mode_Cmd);//--set contrast control register
    BSP_OLED_WriteByte(OLEDx , 0xCF , OLED_Write_Mode_Cmd);// Set SEG Output Current Brightness
    BSP_OLED_WriteByte(OLEDx , 0xA1 , OLED_Write_Mode_Cmd);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    BSP_OLED_WriteByte(OLEDx , 0xC8 , OLED_Write_Mode_Cmd);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    BSP_OLED_WriteByte(OLEDx , 0xA6 , OLED_Write_Mode_Cmd);//--set normal display
    BSP_OLED_WriteByte(OLEDx , 0xA8 , OLED_Write_Mode_Cmd);//--set multiplex ratio(1 to 64)
    BSP_OLED_WriteByte(OLEDx , 0x3f , OLED_Write_Mode_Cmd);//--1/64 duty
    BSP_OLED_WriteByte(OLEDx , 0xD3 , OLED_Write_Mode_Cmd);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    BSP_OLED_WriteByte(OLEDx , 0x00 , OLED_Write_Mode_Cmd);//-not offset
    BSP_OLED_WriteByte(OLEDx , 0xd5 , OLED_Write_Mode_Cmd);//--set display clock divide ratio/oscillator frequency
    BSP_OLED_WriteByte(OLEDx , 0x80 , OLED_Write_Mode_Cmd);//--set divide ratio, Set Clock as 100 Frames/Sec
    BSP_OLED_WriteByte(OLEDx , 0xD9 , OLED_Write_Mode_Cmd);//--set pre-charge period
    BSP_OLED_WriteByte(OLEDx , 0xF1 , OLED_Write_Mode_Cmd);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    BSP_OLED_WriteByte(OLEDx , 0xDA , OLED_Write_Mode_Cmd);//--set com pins hardware configuration
    BSP_OLED_WriteByte(OLEDx , 0x12 , OLED_Write_Mode_Cmd);
    BSP_OLED_WriteByte(OLEDx , 0xDB , OLED_Write_Mode_Cmd);//--set vcomh
    BSP_OLED_WriteByte(OLEDx , 0x40 , OLED_Write_Mode_Cmd);//Set VCOM Deselect Level
    BSP_OLED_WriteByte(OLEDx , 0x20 , OLED_Write_Mode_Cmd);//-Set Page Addressing Mode (0x00/0x01/0x02)
    BSP_OLED_WriteByte(OLEDx , 0x02 , OLED_Write_Mode_Cmd);//
    BSP_OLED_WriteByte(OLEDx , 0x8D , OLED_Write_Mode_Cmd);//--set Charge Pump enable/disable
    BSP_OLED_WriteByte(OLEDx , 0x14 , OLED_Write_Mode_Cmd);//--set(0x10) disable
    BSP_OLED_WriteByte(OLEDx , 0xA4 , OLED_Write_Mode_Cmd);// Disable Entire Display On (0xa4/0xa5)
    BSP_OLED_WriteByte(OLEDx , 0xA6 , OLED_Write_Mode_Cmd);// Disable Inverse Display On (0xa6/a7) 
    BSP_OLED_Clear(OLEDx);
    BSP_OLED_WriteByte(OLEDx , 0xAF , OLED_Write_Mode_Cmd);

    return SUCCESS;
}



/**
 * @brief  OLED д������
 * @param  *OLEDx            : OLED �ṹ��
 * @param  x_coordinate      : x������ 0-127
 * @param  y_coordinate      : y������ 0-63
 * @param  num               : ��ʾ������
 * @param  len               : ���ֵĳ���
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteNum(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u32 num)
{
    u8 i = 0, temp = 0;
    u8 len = (int)log10(num) + 1;
  
  
    if (OLEDx == NULL)
    {
        return ERROR;
    }

    for(i = 0 ; i < len ; i++)
    {
        /* ȡ��1λ�� */
        temp = (num / (int)pow(10,(double)len-i-1) ) % 10;

        if(temp == 0)                                                 /* ���Ϊ0  */
        {
            BSP_OLED_WriteChar(OLEDx, x_coordinate + 8 * i, y_coordinate, '0');
        }
        else                                                          /* �����Ϊ0 */
        {
            BSP_OLED_WriteChar(OLEDx, x_coordinate + 8 * i, y_coordinate, temp + '0');
         }
    }   

    return SUCCESS;
}



/**
 * @brief  OLED д���ַ���
 * @param  *OLEDx            : OLED �ṹ��
 * @param  x_coordinate      : x������ 0-127
 * @param  y_coordinate      : y������ 0-63
 * @param  pchar             : ��ʾ���ַ�
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteString(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u8 *pchar)
{
  
    if (OLEDx == NULL)
    {
        return ERROR;
    }
  
    /* �ж��Ƿ�Ϊ�Ƿ��ַ� */
    while((*pchar >= ' ') && (*pchar<='~'))
    {
        /* ��ʾ�ַ� */
        BSP_OLED_WriteChar(OLEDx, x_coordinate, y_coordinate, *pchar);
        x_coordinate += 8;
        pchar++;
    }
    
    return SUCCESS;
}



/**
 * @brief  OLED д���ַ�
 * @param  *OLEDx            : OLED �ṹ��
 * @param  x_coordinate      : x������ 0-127
 * @param  y_coordinate      : y������ 0-63
 * @param  pchar             : ��ʾ���ַ�
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteChar(OLED_TypeDef_Struct *OLEDx, u8 x_coordinate, u8 y_coordinate, u8 chr)
{

    u8 i, j, chr1602;
    u8 x0 = x_coordinate, y0 = y_coordinate;
  
    if (OLEDx == NULL)
    {
        return ERROR;
    }

    for(i = 0 ; i < 16 ; i++)
    {
        /* ȡ1602�������� */
        chr1602 = asc2_1608[chr - ' '][i]; 

        for(j = 0; j < 8; j++)
        {
            if(chr1602 & 0x01)
            {
                BSP_OLED_DrawPoint(OLEDx, x_coordinate, y_coordinate, 1);
            }
            else 
            {
                BSP_OLED_DrawPoint(OLEDx, x_coordinate, y_coordinate, 0);
            }
            chr1602 >>= 1;
            y_coordinate++;
        }
        x_coordinate++;
        if((x_coordinate - x0) == 8)
        {
            x_coordinate = x0;
            y0 = y0 + 8;
        }
        y_coordinate = y0;
    }  
  
    return SUCCESS;

}




/**
 * @brief  ���� OLED 
 * @param  *OLEDx           : OLED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Clear(OLED_TypeDef_Struct *OLEDx)
{
    uint8_t byte = 0;
    uint8_t page = 0;
  
    if (OLEDx == NULL)
    {
        return ERROR;
    }
    
    for (page = 0 ; page < OLED_NUMBER_OF_PAGES ; page++)
    {    
        for (byte = 0 ; byte < OLED_NUMBER_OF_BYTES ; byte++)
        {
            OLEDx->OLED_Operating.buffer[byte][page] = 0;
        }
    }
    
//    /* ������ʾ */
//    BSP_OLED_Refresh(OLEDx);
    
    return SUCCESS;
}



/**
 * @brief  ������ʾ OLED 
 * @param  *OLEDx           : OLED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Refresh(OLED_TypeDef_Struct *OLEDx)
{
    uint8_t byte = 0;
    uint8_t page = 0;

    if (OLEDx == NULL)
    {
        return ERROR;
    }
    
    for(page = 0; page < OLED_NUMBER_OF_PAGES; page++)
    {
        BSP_OLED_WriteByte(OLEDx, 0xb0+page, OLED_Write_Mode_Cmd);   /* ��������ʼ��ַ   */
        BSP_OLED_WriteByte(OLEDx, 0x00     , OLED_Write_Mode_Cmd);   /* ���õ�����ʼ��ַ */
        BSP_OLED_WriteByte(OLEDx, 0x10     , OLED_Write_Mode_Cmd);   /* ���ø�����ʼ��ַ */
        for(byte = 0; byte < OLED_NUMBER_OF_BYTES; byte++)
        {
            BSP_OLED_WriteByte(OLEDx, OLEDx->OLED_Operating.buffer[byte][page], OLED_Write_Mode_Data);    
        }

    }
    return SUCCESS;
}



/* Private functions ---------------------------------------------------------*/



/**
 * @brief  ��ʼ�� OLED GPIO ����
 * @param  *OLEDx           : OLED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_GPIO_Config(OLED_TypeDef_Struct *OLEDx)
{
  
    GPIO_InitTypeDef    GPIO_InitStructure;
  
    if ( (OLEDx == NULL) || (OLEDx->OLED_Hardware.CLK_GPIO      == NULL)
                         || (OLEDx->OLED_Hardware.CLK_GPIO_PIN  == NULL)
                         || (OLEDx->OLED_Hardware.DATA_GPIO     == NULL)
                         || (OLEDx->OLED_Hardware.DATA_GPIO_PIN == NULL)
                         || (OLEDx->OLED_Hardware.RES_GPIO      == NULL)
                         || (OLEDx->OLED_Hardware.RES_GPIO_PIN  == NULL)
                         || (OLEDx->OLED_Hardware.DC_GPIO       == NULL)
                         || (OLEDx->OLED_Hardware.DC_GPIO_PIN   == NULL) )
    {
        return ERROR;
    }
    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_InitStructure.GPIO_Pin   = OLEDx->OLED_Hardware.CLK_GPIO_PIN;
    GPIO_Init(OLEDx->OLED_Hardware.CLK_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = OLEDx->OLED_Hardware.DATA_GPIO_PIN;
    GPIO_Init(OLEDx->OLED_Hardware.DATA_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = OLEDx->OLED_Hardware.RES_GPIO_PIN;
    GPIO_Init(OLEDx->OLED_Hardware.RES_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = OLEDx->OLED_Hardware.DC_GPIO_PIN;
    GPIO_Init(OLEDx->OLED_Hardware.DC_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = OLEDx->OLED_Hardware.CS_GPIO_PIN;
    GPIO_Init(OLEDx->OLED_Hardware.CS_GPIO, &GPIO_InitStructure);
    
    GPIO_SetBits(OLEDx->OLED_Hardware.CLK_GPIO , OLEDx->OLED_Hardware.CLK_GPIO_PIN );
    GPIO_SetBits(OLEDx->OLED_Hardware.DATA_GPIO, OLEDx->OLED_Hardware.DATA_GPIO_PIN);
    GPIO_SetBits(OLEDx->OLED_Hardware.RES_GPIO , OLEDx->OLED_Hardware.RES_GPIO_PIN );
    GPIO_SetBits(OLEDx->OLED_Hardware.DC_GPIO  , OLEDx->OLED_Hardware.DC_GPIO_PIN  );
    GPIO_SetBits(OLEDx->OLED_Hardware.CS_GPIO  , OLEDx->OLED_Hardware.CS_GPIO_PIN  );
    
    return SUCCESS;
}







/**
 * @brief  ��λ OLED 
 * @param  *OLEDx           : OLED�ṹ��
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_Reset(OLED_TypeDef_Struct *OLEDx)
{
    if (OLEDx == NULL)
    {
        return ERROR;
    }
    
    GPIO_ResetBits(OLEDx->OLED_Hardware.RES_GPIO, OLEDx->OLED_Hardware.RES_GPIO_PIN);
    Delay_ms(100);
    GPIO_SetBits(OLEDx->OLED_Hardware.RES_GPIO  , OLEDx->OLED_Hardware.RES_GPIO_PIN); 
    
    return SUCCESS;
}





/**
 * @brief  OLED ��һ����
 * @param  *OLEDx            : OLED �ṹ��
 * @param  x_coordinate      : x������ 0-127
 * @param  y_coordinate      : y������ 0-63
 * @param  mode              : 1 ��ʾ 0 ��ʧ
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_DrawPoint(OLED_TypeDef_Struct *OLEDx ,u8 x_coordinate, u8 y_coordinate, u8 mode)
{
    if (OLEDx == NULL)
    {
        return ERROR;
    }

    if (mode == 1)
    {
        OLEDx->OLED_Operating.buffer[x_coordinate][y_coordinate / 8] |= (1 << (y_coordinate % 8)) ;
    }
    else if (mode == 0)
    {
    		OLEDx->OLED_Operating.buffer[x_coordinate][y_coordinate / 8]  = ~OLEDx->OLED_Operating.buffer[x_coordinate][y_coordinate / 8];
        OLEDx->OLED_Operating.buffer[x_coordinate][y_coordinate / 8] |= (1 << (y_coordinate % 8));
        OLEDx->OLED_Operating.buffer[x_coordinate][y_coordinate / 8]  = ~OLEDx->OLED_Operating.buffer[x_coordinate][y_coordinate / 8];
    }
  
    return SUCCESS;
}





/**
 * @brief  д�ֽ� OLED 
 * @param  *OLEDx           : OLED�ṹ��
 * @param  data             : д�������
 * @param  mode             : ���� ����or����
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus BSP_OLED_WriteByte(OLED_TypeDef_Struct *OLEDx , uint8_t data , uint8_t mode)
{
    uint8_t ii = 0;

    if (OLEDx == NULL)
    {
        return ERROR;
    }
    		  
    if (mode == OLED_Write_Mode_Data)                                  /* ���ݲ��� */
    {
        GPIO_SetBits(OLEDx->OLED_Hardware.DC_GPIO, OLEDx->OLED_Hardware.DC_GPIO_PIN);
    }
    else if (mode == OLED_Write_Mode_Cmd)                              /* ������� */
    {
        GPIO_ResetBits(OLEDx->OLED_Hardware.DC_GPIO, OLEDx->OLED_Hardware.DC_GPIO_PIN);
    }
    else 
    {
        return ERROR;
    }

    /* �ر�Ƭѡ */
    GPIO_ResetBits(OLEDx->OLED_Hardware.CS_GPIO, OLEDx->OLED_Hardware.CS_GPIO_PIN);
    
    for(ii = 0; ii < 8; ii++)
    {
        /* ʱ������ */
        GPIO_ResetBits(OLEDx->OLED_Hardware.CLK_GPIO, OLEDx->OLED_Hardware.CLK_GPIO_PIN);
      
        if(data & 0x80) /* 0b1000 0000 ȡ���λ */
        {
            GPIO_SetBits(OLEDx->OLED_Hardware.DATA_GPIO, OLEDx->OLED_Hardware.DATA_GPIO_PIN);
        }
        else 
        {
            GPIO_ResetBits(OLEDx->OLED_Hardware.DATA_GPIO, OLEDx->OLED_Hardware.DATA_GPIO_PIN);
        }
        
        /* ʱ������ */
        GPIO_SetBits(OLEDx->OLED_Hardware.CLK_GPIO, OLEDx->OLED_Hardware.CLK_GPIO_PIN);
        
        data <<= 1;   
    }	
    
    /* ��Ƭѡ */
    GPIO_SetBits(OLEDx->OLED_Hardware.CS_GPIO, OLEDx->OLED_Hardware.CS_GPIO_PIN);
    
    GPIO_SetBits(OLEDx->OLED_Hardware.DC_GPIO, OLEDx->OLED_Hardware.DC_GPIO_PIN);
  
    return SUCCESS;
}



