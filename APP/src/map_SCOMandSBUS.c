/**
  ******************************************************************************
  * @file    map_SCOMandSBUS.c
  * @author  LYB
  * @version V1.0.0
  * @date    202/4/18
  * @brief   描述了SCOM数据协议转换SBUS的功能实现
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "map_SCOMandSBUS.h"
#include "string.h"





/* Public functions ----------------------------------------------------------*/



/**
 * @brief  将SCOM协议数据转化为SBUS协议
 * @param  *SCOMdata： SCOM数据指针，数组长度25byte   8bit     
 *            * SCOMdata[0]               首字节      0x0F           
 *            * SCOMdata[1]-SCOMdata[22]  用户数据    
 *            * SCOMdata[23]              标志字节    0x00     
 *            * SCOMdata[24]              尾字节      0x00      
 * @param  *SBUSdata： SBUS数据存储指针,数组长度16byte 11bit
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_SCOMtoSBUS(uint8_t *SCOMdata , SBUSData_Struct *SBUSdata)
{

	  uint8_t        ii;
	
    if (SCOMdata == NULL) 
		{			
			  return ERROR;
		}
    
    /*  SCOMdata[0]=0x0F  SCOMdata[24]=0x00    */
    if ((SCOMdata[0] != 0x0F) || (SCOMdata[24] != 0x00))
    {
        return ERROR;
    }
    
 	  /*  SCOMdata[23] 标志字节                  */
		SBUSdata->FlagByte    =   *(SCOMdata + 23);     
    
    /*  0x07FF = 0B 11111111111 ,即保留前11位  */
		SBUSdata->Channel[0]  = ( (*(SCOMdata + 2) << 8)  | (*(SCOMdata + 1)) >> 0) & 0x07FF;
		SBUSdata->Channel[1]  = ( (*(SCOMdata + 3) << 5)  | (*(SCOMdata + 2)) >> 3) & 0x07FF; 
		SBUSdata->Channel[2]  = ( (*(SCOMdata + 5) << 10) |((*(SCOMdata + 4)) << 2) | ((*(SCOMdata + 3)) >> 6)) & 0x07FF;
		SBUSdata->Channel[3]  = ( (*(SCOMdata + 6) << 7)  | (*(SCOMdata + 5)) >> 1) & 0x07FF;
		SBUSdata->Channel[4]  = ( (*(SCOMdata + 7) << 4)  | (*(SCOMdata + 6)) >> 4) & 0x07FF;
		SBUSdata->Channel[5]  = ( (*(SCOMdata + 9) << 9)  |((*(SCOMdata + 8)) << 1) | ((*(SCOMdata + 7)) >> 7)) & 0x07FF;
		SBUSdata->Channel[6]  = ((*(SCOMdata + 10) << 6) | (*(SCOMdata + 9))  >> 2) & 0x07FF;
		SBUSdata->Channel[7]  = ((*(SCOMdata + 11) << 3) | (*(SCOMdata + 10)) >> 5) & 0x07FF;
		SBUSdata->Channel[8]  = ((*(SCOMdata + 13) << 8) | (*(SCOMdata + 12)) >> 0) & 0x07FF;
		SBUSdata->Channel[9]  = ((*(SCOMdata + 14) << 5) | (*(SCOMdata + 13)) >> 3) & 0x07FF;
		SBUSdata->Channel[10] = ((*(SCOMdata + 16) << 10)| ((*(SCOMdata + 15))<< 2) | ((*(SCOMdata + 14)) >> 6)) & 0x07FF;
		SBUSdata->Channel[11] = ((*(SCOMdata + 17) << 7) | (*(SCOMdata + 16)) >> 1) & 0x07FF;
		SBUSdata->Channel[12] = ((*(SCOMdata + 18) << 4) | (*(SCOMdata + 17)) >> 4) & 0x07FF;
		SBUSdata->Channel[13] = ((*(SCOMdata + 20) << 9) | ((*(SCOMdata + 19))<< 1) | ((*(SCOMdata + 18)) >> 7)) & 0x07FF;
		SBUSdata->Channel[14] = ((*(SCOMdata + 21) << 6) | (*(SCOMdata + 20)) >> 2) & 0x07FF;
		SBUSdata->Channel[15] = ((*(SCOMdata + 22) << 3) | ((*(SCOMdata + 21))>> 5))& 0x07FF;

		for(ii = 0; ii < 16; ii++)
		{
				if(SBUSdata->Channel[ii] > 2047)
				{
						SBUSdata->Channel[ii] = 2047;
				}
		}        

    return SUCCESS;

}

/* SBUSdata->Channel[0] = SCOMdata[2]后3位 + SCOMdata[1]全8位                      */
/* SBUSdata->Channel[1] = SCOMdata[3]后6位 + SCOMdata[2]前5位                      */
/* SBUSdata->Channel[2] = SCOMdata[5]后1位 + SCOMdata[4]全8位 + SCOMdata[3]前2位   */
/* SBUSdata->Channel[3] = SCOMdata[6]后4位 + SCOMdata[5]前7位                      */
/* SBUSdata->Channel[4] = SCOMdata[7]后7位 + SCOMdata[6]前4位                      */
/* SBUSdata->Channel[5] = SCOMdata[9]后2位 + SCOMdata[8]全8位 + SCOMdata[7]前1位   */
/* SBUSdata->Channel[6] = SCOMdata[10]后5位 + SCOMdata[9]前6位                     */
/* SBUSdata->Channel[7] = SCOMdata[11]全8位 + SCOMdata[10]前3位                    */
/* SBUSdata->Channel[8] = SCOMdata[13]后3位 + SCOMdata[12]全8位                    */
/* SBUSdata->Channel[9] = SCOMdata[14]后6位 + SCOMdata[13]前5位                    */
/* SBUSdata->Channel[10]= SCOMdata[16]后1位 + SCOMdata[15]全8位 + SCOMdata[14]前2位*/
/* SBUSdata->Channel[11]= SCOMdata[17]后4位 + SCOMdata[16]前7位                    */
/* SBUSdata->Channel[12]= SCOMdata[18]后7位 + SCOMdata[17]前4位                    */
/* SBUSdata->Channel[13]= SCOMdata[20]后2位 + SCOMdata[19]全8位 + SCOMdata[18]前1位*/
/* SBUSdata->Channel[14]= SCOMdata[21]后5位 + SCOMdata[20]前6位                    */
/* SBUSdata->Channel[15]= SCOMdata[22]全8位 + SCOMdata[21]前3位                    */





/**
 * @brief  将SBUS协议数据转化为SCOM协议
 * @param  *SBUSdata： SBUS数据存储指针,数组长度16byte  11bit
 * @param  *SCOMdata： 串口数据指针，要求数组长度25byte 8bit     
 *            * SCOMdata[0]               首字节        0x0F           
 *            * SCOMdata[1]-SCOMdata[22]  用户数据    
 *            * SCOMdata[23]              标志字节      0x00     
 *            * SCOMdata[24]              尾字节        0x00      
 * @return ErrorStatus: ERROR or SUCCESS   
 */
ErrorStatus MAP_SBUStoSCOM(SBUSData_Struct *SBUSdata , uint8_t *SCOMdata)
{
    uint8_t       ii;	
	  uint16_t      Tempdata[16];
	
    if(SBUSdata == NULL)
		{
        return ERROR;
    }

	  *(SCOMdata + 0)  = 0x0F;	
	  *(SCOMdata + 24) = 0x00;	
 	  *(SCOMdata + 23) = SBUSdata->FlagByte; 

		for(ii=0;ii<16;ii++)
		{
			 Tempdata[ii] = SBUSdata->Channel[ii] & 0x07FF;
		}

		*(SCOMdata + 1)  = Tempdata[0] & 0xFF;
		*(SCOMdata + 2)  = (Tempdata[0] >> 8) | (Tempdata[1] << 3);	
		*(SCOMdata + 3)  = (Tempdata[1] >> 5) | (Tempdata[2] << 6);	
		*(SCOMdata + 4)  = (Tempdata[2] >> 2);	
		*(SCOMdata + 5)  = (Tempdata[2] >> 10) | (Tempdata[3] << 1);
		*(SCOMdata + 6)  = (Tempdata[3] >> 7)  | (Tempdata[4] << 4);
		*(SCOMdata + 7)  = (Tempdata[4] >> 4)  | (Tempdata[5] << 7);	
		*(SCOMdata + 8)  = (Tempdata[5] >> 1);	
		*(SCOMdata + 9)  = (Tempdata[5] >> 9)  | (Tempdata[6] << 2);
		*(SCOMdata + 10) = (Tempdata[6] >> 6)  | (Tempdata[7] << 5);
		*(SCOMdata + 11) = (Tempdata[7] >> 3);
		*(SCOMdata + 12) = (Tempdata[8] & 0xFF);		
		*(SCOMdata + 13) = (Tempdata[8] >> 8)  | (Tempdata[9] << 3);		
		*(SCOMdata + 14) = (Tempdata[9] >> 5)  | (Tempdata[10] << 6);
		*(SCOMdata + 15) = (Tempdata[10] >> 2);																																		
		*(SCOMdata + 16) = (Tempdata[10] >> 10) | (Tempdata[11] << 1);
		*(SCOMdata + 17) = (Tempdata[11] >> 7)  | (Tempdata[12] << 4);
		*(SCOMdata + 18) = (Tempdata[12] >> 4)  | (Tempdata[13] << 7);
		*(SCOMdata + 19) = (Tempdata[13] >> 1);	
		*(SCOMdata + 20) = (Tempdata[13] >> 9)  | (Tempdata[14] << 2);	
		*(SCOMdata + 21) = (Tempdata[14] >> 6)  | (Tempdata[15] << 5);	
		*(SCOMdata + 22) = (Tempdata[15] >> 3);		

    return SUCCESS;

}








