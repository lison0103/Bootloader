#include "usb.h"


extern u8 LANGUAGE;
extern const u8 *Status_Item_Descrip[][2];
extern const u8 *Menu_Item_Descrip[][2];
extern void menu_init(u8 item);

void usb_port_set(u8 enable)
{
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //使能PORTA时钟	   	 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));     //退出断电模式
	else{		  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		PAout(12)=0;	    		  
	}

} 


void USBD_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
 
 if(HARDWARE_V2 == GetHardwareVerison())
 {
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
     GPIO_Init(GPIOC, &GPIO_InitStructure);	
     
     GPIO_SetBits(GPIOC,GPIO_Pin_12);
 
 }
 else if(HARDWARE_V1 == GetHardwareVerison())
 {
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
     GPIO_Init(GPIOC, &GPIO_InitStructure);	
     
     GPIO_SetBits(GPIOC,GPIO_Pin_8);
 
 }

}

#if 0

void UsbMassStor_init(void)
{

//        u8 offline_cnt=0;
//	u8 tct=0;
//	u8 USB_STA = USB_STATUS_REG;
//	u8 Divece_STA;
//        
//        u8 key;

        printf("\r\n USB MASS STORAGE init! \r\n");
        
        USBD_Init();

#if defined(USE_MYMALLOC)	       
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//为USB数据缓存区申请内存
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//申请内存              
#endif
        
 	//USB配置
        
        
        delay_ms(200);
 	usb_port_set(0); 	//USB先断开

	delay_ms(300);
   	usb_port_set(1);	//USB再次连接	
        
															  
 	 Mass_Memory_Size[0]=4916*1024;//前4.8M字节
	 Mass_Block_Size[0] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	 Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
	 
	
        
        
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();
        

        
//	while(1)
//	{	
//                delay_ms(1);	
//                key=key_scan();
//                if(key==KEY_F3)			
//                {
//                               
//                  delay_ms(200);
//                  if(key==KEY_F3){
//                     
////                    delay_ms(1500); 
////                    TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "状态：选择断开电脑");
////                    delay_ms(5); 
////                    TXM_StringDisplay(0,40,200,24,1,YELLOW ,RED, "F3:断开电脑连接");
//                    printf("\r\n exit usb mass \r\n");
//                    break;
//                  }
//                }
//                
//		if(USB_STA!=USB_STATUS_REG)//状态改变了 
//		{	 						   
//			//清除显示			  	   
//			if(USB_STATUS_REG&0x01)//正在写		  
//			{
//				//提示USB正在写入数据	 
//			}
//			if(USB_STATUS_REG&0x02)//正在读
//			{
//				//提示USB正在读出数据  		 
//			}	 										  
//			if(USB_STATUS_REG&0x04){}//提示写入错误
//			else {}//清除显示	  
//			if(USB_STATUS_REG&0x08){}//提示读出错误
//			else {}//清除显示    
//			USB_STA=USB_STATUS_REG;//记录最后的状态
//		}
//		if(Divece_STA!=bDeviceState) 
//		{
//			if(bDeviceState==CONFIGURED){}//提示USB连接已经建立
//			else {}//提示USB被拔出了
//			Divece_STA=bDeviceState;
//		}
//		tct++;
//		if(tct==200)
//		{
//			tct=0;
//			if(USB_STATUS_REG&0x10)
//			{
//				offline_cnt=0;//USB连接了,则清除offline计数器
//				bDeviceState=CONFIGURED;
//			}else//没有得到轮询 
//			{
//				offline_cnt++;  
//				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
//			}
//			USB_STATUS_REG=0;
//		}
//	}
//        usb_port_set(0);

}

#else

void UsbMassStor_init(void)
{

        u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA = USB_STATUS_REG;
	u8 Divece_STA;
        
        u8 key;

        printf("\r\n USB MASS STORAGE init! \r\n");
        
        USBD_Init();

#if defined(USE_MYMALLOC)	       
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//为USB数据缓存区申请内存
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//申请内存              
#endif
        
 	//USB配置
        
        
        delay_ms(200);
 	usb_port_set(0); 	//USB先断开

	delay_ms(300);
   	usb_port_set(1);	//USB再次连接	
        
															  
 	 Mass_Memory_Size[0]=4*1024*1024;//后4.8M字节
	 Mass_Block_Size[0] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	 Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
	 
	
        
        
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();
        
        
	while(1)
	{	
                delay_ms(1);	
                key=key_scan();
                if(key==KEY_RIGHT)			
                {
                               
                  delay_ms(50);
                  if(key==KEY_RIGHT){
                     
                    
                    TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[8][LANGUAGE]);
                    delay_ms(5); 
                    menu_init(3);
                    printf("\r\n exit usb mass \r\n");
                    break;
                  }
                }
                
		if(USB_STA!=USB_STATUS_REG)//状态改变了 
		{	 						   
			//清除显示			  	   
			if(USB_STATUS_REG&0x01)//正在写		  
			{
				//提示USB正在写入数据	
//                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "状态：正在写入数据");
			}
			if(USB_STATUS_REG&0x02)//正在读
			{
				//提示USB正在读出数据 
//                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "状态：正在读出数据");
			}	 										  
			if(USB_STATUS_REG&0x04){}//提示写入错误
			else {}//清除显示	  
			if(USB_STATUS_REG&0x08){}//提示读出错误
			else {}//清除显示    
			USB_STA=USB_STATUS_REG;//记录最后的状态
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)
                        {
                          //提示USB连接已经建立
                          
                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[9][LANGUAGE]);  
                        }
			else 
                        {
                          //提示USB被拔出了
                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[10][LANGUAGE]); 
                        }
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB连接了,则清除offline计数器
				bDeviceState=CONFIGURED;
			}
                        else//没有得到轮询 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
			}
			USB_STATUS_REG=0;
		}
	}
        usb_port_set(0);
        
     #if defined(USE_MYMALLOC)
        myfree(Data_Buffer);
        myfree(Bulk_Data_Buff);
     #endif

}



#endif