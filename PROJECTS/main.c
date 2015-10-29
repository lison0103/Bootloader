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
        BKP_Init();             //BKP寄存器初始化
        Version_init();         //读取APP更新到的版本号
        Language_init();        //读取APP设置的语言
        
 	if(exfuns_init())		//为fatfs相关变量申请内存
        {
            //申请内存失败
        }
        menu_init();            //初始化菜单       
        
        //初始化一个定时器用作时间显示
        TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms       
//        wdt_init();             //初始化独立看门狗，5s复位
     
/********************************************************************************************/	
               
        while(1)
        {             
            menu_pocess();         //主程序       
            
//            IWDG_ReloadCounter();  //喂狗
	}												 
        
}
	   



