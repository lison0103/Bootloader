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

u8 *Version = {"V0.2"};

int main(void)
{ 
  
	NVIC_Configuration();	 //�жϷ�������
	delay_init();	    	 //��ʱ������ʼ��	          					
        hardware_init();        //Ӳ���汾ȷ�ϳ�ʼ��  
#if EN_USART3_PRINTF
	uart_init(9600);	 //USART3��ʼ��Ϊ9600,��������log��ӡ
#endif
        	               
        key_init();             //������ʼ��       
        RCC_init();                  
        USART2_Init();          //USART2��ʼ��������LCD���ݴ���                              
        LCM_Init();             //ZTM LCD��ʼ��
              
        enter_menu();           //�ж��Ƿ����Loader���ȴ�Լ1s������F1���룬�������APP
        mem_init();		//��ʼ���ڴ��
        SPI_Flash_Init();       //�ⲿflash��ʼ��        
        RTCC_Init();            //RTC��ʼ����rt1302
        BKP_Init();             //BKP�Ĵ�����ʼ��
        Version_init();         //��ȡAPP���µ��İ汾��
        Language_init();        //��ȡAPP���õ�����
        
 	if(exfuns_init())		//Ϊfatfs��ر��������ڴ�
        {
            //�����ڴ�ʧ��
        }
        menu_init();            //��ʼ���˵�       
        
        //��ʼ��һ����ʱ������ʱ����ʾ
        TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms       
//        wdt_init();             //��ʼ���������Ź���5s��λ
     
/********************************************************************************************/	
               
        while(1)
        {             
            menu_pocess();         //������       
            
//            IWDG_ReloadCounter();  //ι��
	}												 
        
}
	   



