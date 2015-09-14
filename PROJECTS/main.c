
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "flash.h"

#include "malloc.h"  

#include "menu.h"
#include "usb.h"
#include "fatfs.h"




int main(void)
{ 
  
	NVIC_Configuration();	 
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
 	exfuns_init();		//为fatfs相关变量申请内存				 
							    	
 	mem_init();			//初始化内存池	               
        key_init();   
        SPI_Flash_Init();
        
        RCC_init();                  
        USART1_Init();
        USART2_Init();
        
        Lcd_init();
//        delay_ms(1000); 


/********************************************************************************************/	
               
        while(1){    
          
          menu_pocess();
          
          
	}												 

        
}
	   



