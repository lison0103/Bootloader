
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
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	exfuns_init();		//Ϊfatfs��ر��������ڴ�				 
							    	
 	mem_init();			//��ʼ���ڴ��	               
        key_init();   
        SPI_Flash_Init();
        
        RCC_init();                  
        NVIC_Configuration_Usart();
        USART2_Init();
        
        RTCC_Init();      
        
        
        LCM_Init();
        enter_menu();
        
        menu_init();
        
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
	   



