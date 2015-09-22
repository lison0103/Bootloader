#include "usb.h"


extern u8 LANGUAGE;
extern const u8 *Status_Item_Descrip[][2];
extern const u8 *Menu_Item_Descrip[][2];
extern void menu_init(u8 item);

void usb_port_set(u8 enable)
{
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //ʹ��PORTAʱ��	   	 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));     //�˳��ϵ�ģʽ
	else{		  
		_SetCNTR(_GetCNTR()|(1<<1));  // �ϵ�ģʽ
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
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//ΪUSB���ݻ����������ڴ�
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//�����ڴ�              
#endif
        
 	//USB����
        
        
        delay_ms(200);
 	usb_port_set(0); 	//USB�ȶϿ�

	delay_ms(300);
   	usb_port_set(1);	//USB�ٴ�����	
        
															  
 	 Mass_Memory_Size[0]=4916*1024;//ǰ4.8M�ֽ�
	 Mass_Block_Size[0] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
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
////                    TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "״̬��ѡ��Ͽ�����");
////                    delay_ms(5); 
////                    TXM_StringDisplay(0,40,200,24,1,YELLOW ,RED, "F3:�Ͽ���������");
//                    printf("\r\n exit usb mass \r\n");
//                    break;
//                  }
//                }
//                
//		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
//		{	 						   
//			//�����ʾ			  	   
//			if(USB_STATUS_REG&0x01)//����д		  
//			{
//				//��ʾUSB����д������	 
//			}
//			if(USB_STATUS_REG&0x02)//���ڶ�
//			{
//				//��ʾUSB���ڶ�������  		 
//			}	 										  
//			if(USB_STATUS_REG&0x04){}//��ʾд�����
//			else {}//�����ʾ	  
//			if(USB_STATUS_REG&0x08){}//��ʾ��������
//			else {}//�����ʾ    
//			USB_STA=USB_STATUS_REG;//��¼����״̬
//		}
//		if(Divece_STA!=bDeviceState) 
//		{
//			if(bDeviceState==CONFIGURED){}//��ʾUSB�����Ѿ�����
//			else {}//��ʾUSB���γ���
//			Divece_STA=bDeviceState;
//		}
//		tct++;
//		if(tct==200)
//		{
//			tct=0;
//			if(USB_STATUS_REG&0x10)
//			{
//				offline_cnt=0;//USB������,�����offline������
//				bDeviceState=CONFIGURED;
//			}else//û�еõ���ѯ 
//			{
//				offline_cnt++;  
//				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
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
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//ΪUSB���ݻ����������ڴ�
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//�����ڴ�              
#endif
        
 	//USB����
        
        
        delay_ms(200);
 	usb_port_set(0); 	//USB�ȶϿ�

	delay_ms(300);
   	usb_port_set(1);	//USB�ٴ�����	
        
															  
 	 Mass_Memory_Size[0]=4*1024*1024;//��4.8M�ֽ�
	 Mass_Block_Size[0] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
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
                
		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
		{	 						   
			//�����ʾ			  	   
			if(USB_STATUS_REG&0x01)//����д		  
			{
				//��ʾUSB����д������	
//                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "״̬������д������");
			}
			if(USB_STATUS_REG&0x02)//���ڶ�
			{
				//��ʾUSB���ڶ������� 
//                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "״̬�����ڶ�������");
			}	 										  
			if(USB_STATUS_REG&0x04){}//��ʾд�����
			else {}//�����ʾ	  
			if(USB_STATUS_REG&0x08){}//��ʾ��������
			else {}//�����ʾ    
			USB_STA=USB_STATUS_REG;//��¼����״̬
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)
                        {
                          //��ʾUSB�����Ѿ�����
                          
                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[9][LANGUAGE]);  
                        }
			else 
                        {
                          //��ʾUSB���γ���
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
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=CONFIGURED;
			}
                        else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
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