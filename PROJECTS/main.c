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
  
	NVIC_Configuration();	 
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
 	exfuns_init();		//为fatfs相关变量申请内存				 
	
        hardware_init();        //硬件版本确认初始化        
        
 	mem_init();			//初始化内存池	               
        key_init();   
        SPI_Flash_Init();
        
        RCC_init();                  
        NVIC_Configuration_Usart();
        USART2_Init();
        
        RTCC_Init();      
        
        
        LCM_Init();
        enter_menu();
        
        menu_init(0);
        
//        Cpu_LockID = GetLockCode();
//        printf("Cpu_LockID = %x\r\n",Cpu_LockID);
//        
//        printf("Confirm_word = %d\r\n",Cpu_LockID/1000 + Current_Date);
//        
//        printf("password = %d\r\n",(Cpu_LockID/1000 + Current_Date)*2 + 3);

/********************************************************************************************/	
               
        while(1){    
          
          menu_pocess();
          
          
	}												 

        
}
	   



