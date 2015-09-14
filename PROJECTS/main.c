
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
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	exfuns_init();		//Ϊfatfs��ر��������ڴ�				 
							    	
 	mem_init();			//��ʼ���ڴ��	               
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
	   



