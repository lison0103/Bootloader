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
  
	NVIC_Configuration();	 //中断分组设置
	delay_init();	    	 //延时函数初始化	          					
        hardware_init();        //硬件版本确认初始化  
#if EN_USART3_PRINTF
	uart_init(9600);	 //USART3初始化为9600,用作串口log打印
#endif
        	               
        key_init();             //按键初始化       
        RCC_init();                  
        USART2_Init();          //USART2初始化，用作LCD数据传输                              
        LCM_Init();             //ZTM LCD初始化
        
        
        enter_menu();           //判断是否进入Loader，等待约1s，按键F1进入，否则进入APP
        
        
        mem_init();		//初始化内存池
        SPI_Flash_Init();       //外部flash初始化        
        RTCC_Init();            //RTC初始化，rt1302
 	exfuns_init();		//为fatfs相关变量申请内存
        
        menu_init(0);            //初始化菜单       
        
        //初始化一个定时器用作时间显示
        TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms
        

        
//        Cpu_LockID = GetLockCode();
//        printf("Cpu_LockID = %x\r\n",Cpu_LockID);
//        
//        printf("Confirm_word = %d\r\n",Cpu_LockID/1000 + Current_Date);
//        
//        printf("password = %d\r\n",(Cpu_LockID/1000 + Current_Date)*2 + 3);

/********************************************************************************************/	
               
        while(1){    
          
          menu_pocess();         //主程序       
          
          
	}												 

        
}
	   



