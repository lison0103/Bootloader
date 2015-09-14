/**
  ******************************************************************************
  * @file    mass_mal.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Medium Access Layer interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "platform_config.h" 
#include "mass_mal.h"
#include "flash.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
long long Mass_Memory_Size[MAX_LUN+1];
u32 Mass_Block_Size[MAX_LUN+1];
u32 Mass_Block_Count[MAX_LUN+1];


#define OFFSETADDR 	(3*1024 + 0)*1024				//从3M+0K地址开始的
	 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(uint8_t lun)
{
	u16 status = MAL_OK;  
	switch (lun)
	{
		case 0:			    
			break;			   
		case 1:					  
			break;		  
		default:
			return MAL_FAIL;
	}
	return status;
}
/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{
	u8 STA;
	switch (lun)
	{
		case 0:				  
			SPI_Flash_Write((u8*)Writebuff, Memory_Offset + OFFSETADDR, Transfer_Length);   		  
			break;							  
		case 1:		 
			STA=0;
			SPI_Flash_Write((u8*)Writebuff, Memory_Offset, Transfer_Length);   		  
			break; 
		default:
			return MAL_FAIL;
	}
	if(STA!=0)return MAL_FAIL;
	return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
	u8 STA;
	switch (lun)
	{
		case 0:		    
			SPI_Flash_Read((u8*)Readbuff, Memory_Offset + OFFSETADDR, Transfer_Length); 	   
			break;			    
		case 1:	 
			STA=0;
			SPI_Flash_Read((u8*)Readbuff, Memory_Offset, Transfer_Length);   		  
			break;	  
		default:
			return MAL_FAIL;
	}
	if(STA!=0)return MAL_FAIL;
	return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_GetStatus (uint8_t lun)
{
    switch(lun)
    {
    case 0:
        return MAL_OK;
    case 1:
        return MAL_OK;
    case 2:
        return MAL_FAIL;
    default:
        return MAL_FAIL;
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

