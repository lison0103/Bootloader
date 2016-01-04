/****************************************Copyright (c)****************************************************
** File Name:           main.c
** Created By:          lisonchen
** Created date:        2015-09-08
** Version:             v0.2
** Descriptions:        Bootloader
** Last Update:         2015-10-27           
*********************************************************************************************************/

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "flash.h"
#include "malloc.h"  
#include "menu.h"
#include "usb.h"
#include "fatfs.h"
#include "lcd.h"
#include "iwdg.h"
#include "bkp.h"

u8 *Version = {"V0.3"};

int main(void)
{ 
  
//        RCC_init(); 
        RCC_Configuration(RCC_PLLMul_9);//ʱ�ӳ�ʼ��
	NVIC_Configuration();	 //�жϷ�������
	delay_init();	    	 //��ʱ������ʼ��	          					
        hardware_init();        //Ӳ���汾ȷ�ϳ�ʼ��  
#if EN_USART3_PRINTF
	uart_init(9600);	 //USART3��ʼ��Ϊ9600,��������log��ӡ
#endif        	               
        key_init();             //������ʼ��                               
        USART2_Init(115200);          //USART2��ʼ��������LCD���ݴ���  
//  USART2_Init(921600);  
        LCM_Init();             //ZTM LCD��ʼ��
        
//  u8 high_baud[] = {0xAA, 0xE0, 0x55, 0xAA, 0x5A, 0xA5, 0x00, 0x0E, 0x10, 0x00, 0x75, 0x5F, 0x00, 0x01, 0xCC, 0x33, 0xC3, 0x3C};
//  
//  BSP_USART_Send(LCM_COM_PORT,high_baud,sizeof(high_baud)/sizeof(char));
  
//  USART2_Init(921600);        
        BKP_Init();             //BKP�Ĵ�����ʼ��      
        enter_menu();           //�ж��Ƿ����Loader���ȴ�Լ1s������F1���룬�������APP
        mem_init();		//��ʼ���ڴ��
        SPI_Flash_Init();       //�ⲿflash��ʼ��        
        RTCC_Init();            //RTC��ʼ����rt1302
        
        Version_init();         //��ȡAPP���µ��İ汾��
        Language_init();        //��ȡAPP���õ�����
        
 	if(exfuns_init())		//Ϊfatfs��ر��������ڴ�
        {
            //�����ڴ�ʧ��
        }
        menu_init();            //��ʼ���˵�       
        
        //��ʼ��һ����ʱ������ʱ����ʾ
        TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms       
        wdt_init();             //��ʼ���������Ź���20s��λ
     
/********************************************************************************************/	
               
        while(1)
        {             
            menu_pocess();         //������       
            
            IWDG_ReloadCounter();  //ι��
	}												 
        
}
	   



