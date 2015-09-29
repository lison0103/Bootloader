/****************************************Copyright (c)****************************************************
** File Name:           main.c
** Created By:          lisonchen
** Created date:        2015-09-08
** Version:             v0.1
** Descriptions:        Bootloader
**
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





//u32 Cpu_LockID;
//
//extern u32 Current_Date;


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
 	exfuns_init();		//Ϊfatfs��ر��������ڴ�
        
        menu_init(0);            //��ʼ���˵�       
        
        //��ʼ��һ����ʱ������ʱ����ʾ
        TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
        

        
//        Cpu_LockID = GetLockCode();
//        printf("Cpu_LockID = %x\r\n",Cpu_LockID);
//        
//        printf("Confirm_word = %d\r\n",Cpu_LockID/1000 + Current_Date);
//        
//        printf("password = %d\r\n",(Cpu_LockID/1000 + Current_Date)*2 + 3);

/********************************************************************************************/	
               
        while(1){    
          
          menu_pocess();         //������       
          
          
	}												 

        
}
	   



