#include "menu.h"


const u8 *Menu_Item_Descrip[][2] =
{   
  {"Lang","����"},
  {" ��:���ӵ���     "," ��:Connect to PC"},
  {" ��:�Ͽ��������� "," ��:Disconnect PC"},
  {" ��:����APP      "," ��:Update APP   "},
  {" SET:����APP     "," SET:Enter APP   "},
  
};

const u8 *Status_Item_Descrip[][2] =
{                                          
  
  {" ״̬�� ��ѡ��    "," Status:  Select  "},
  {"״̬�����ӵ���    "," Status: Connect  "},
  {"״̬����ʼ����APP "," Status:  Update  "},
  {"״̬��APP������� "," Status:  Finish  "},
  {"״̬������ʧ��    "," Status:  Fail    "},
  {"״̬���޿ɸ��¹̼�"," Status: NO FILE  "},
  {" ״̬������APP    "," Status: Enter APP"},
  {" ״̬����APP����  "," Status:  NO APP  "},
  {"״̬���ѶϿ�����  "," Status:Disconnect"},
  {"״̬��USB������   "," Status:  Connect "},
  {"״̬��USB���γ��� "," Status:Disconnect"},
  {"״̬���ǺϷ�����  "," Status:  Illegal "},
};

u8 *Version = {"V0.1"};


//u8 TimeBuff[6];
//u32 Current_Date;

void RCC_init(void)
{
  
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //for dma  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//Ϊ�ⲿ�ж�
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); //USART2 ʱ��ʹ��
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  
                         |RCC_APB2Periph_GPIOB   
                           |RCC_APB2Periph_GPIOC,
                           
                           ENABLE); //�˿�ʱ��ʹ��  
  
}

#if 0





u16 MenuItem=0,MenuItem_Max=4,Menu_Level=0,disFlag=0;
u8 LANGUAGE = 0;

void menu_item_display(void)
{
  u16 i;
  
  if(disFlag)
  {
    i = MenuItem+1;
    if(i>=4) i=0;
    TXM_StringDisplay(0,8,60+(i*50),24,1,YELLOW ,BLUE, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
    if(MenuItem) i=MenuItem-1; else i=4 - 1;
    TXM_StringDisplay(0,8,60+(i*50),24,1,YELLOW ,BLUE, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
    
    TXM_StringDisplay(0,8,60+(MenuItem*50),24,1,YELLOW ,RED, (void*)Menu_Item_Descrip[MenuItem][LANGUAGE]); 
  }
  else
  {  
    for(i=0;i<4;i++)
    {  
      if(MenuItem==i)
      {  
        TXM_StringDisplay(0,8,60+(i*50),24,1,YELLOW ,RED, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
      }
      else
      {
        TXM_StringDisplay(0,8,60+(i*50),24,1,YELLOW ,BLUE, (void*)Menu_Item_Descrip[i][LANGUAGE]); 
      }  
      delay_ms(5);
      
      disFlag = 1;
    }
  }
}

void Lcd_init(void)
{
  
  delay_ms(1000);  //����ʱ�ε�������û��ʾ
  ZTM_FullScreenImageDisp(300);
  delay_ms(5);
  ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
  delay_ms(5);
  TXM_StringDisplay(0,10,290,24,0,RED ,WHITE, "����");       
  delay_ms(5);  
  //          TXM_StringDisplay(0,40,50,24,1,YELLOW ,BLUE, "POWER:����APP");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,40,100,24,1,YELLOW ,BLUE, "F1:���ӵ���");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,40,150,24,1,YELLOW ,BLUE, "F2:����APP");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,40,200,24,1,YELLOW ,BLUE, "F3:�Ͽ���������");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "״̬�� ��ѡ��");
  //          delay_ms(5); 
  
  menu_item_display();
  
}

void menu_pocess(void)
{
  u8 key,usbconnect = 0;
  
  u8 offline_cnt=0;
  u8 tct=0;
  u8 USB_STA = USB_STATUS_REG;
  u8 Divece_STA;
  
  key=key_scan();
  if(key == KEY_UP)
  {
    delay_ms(200);
    if(key==KEY_UP){
      if(MenuItem) MenuItem--; else MenuItem = MenuItem_Max-1;
      menu_item_display();
    }
  } 
  else if(key == KEY_DOWN)
  {
    delay_ms(200);
    if(key==KEY_DOWN){
      MenuItem++; if(MenuItem>=MenuItem_Max) MenuItem = 0;
      menu_item_display();
    }
  }  
  else if(key == KEY_LEFT)
  {
    delay_ms(200);
    if(key==KEY_LEFT){
      disFlag = 0;
      if(LANGUAGE == 1)
      {
        LANGUAGE = 0;
        ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
        delay_ms(5);
        TXM_StringDisplay(0,10,290,24,0,RED ,WHITE, "����");       
        delay_ms(5); 
      }
      else
      {
        LANGUAGE = 1;
        ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
        delay_ms(5);
        TXM_StringDisplay(0,10,290,24,0,RED ,WHITE, "Lanuage");       
        delay_ms(5); 
      }
      menu_item_display();
    }
  }
  else if(key == KEY_SET)
  {
    delay_ms(200);
    if(key==KEY_SET){
      
      switch(MenuItem)
      {
      case 0:
        printf("��ʼִ��FLASH�û�����!!\r\n");
        if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
        {	 
          iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
        }else 
        {
          printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
          
        }	
        break;
      case 1:
        printf("\r\n��ʼ��FATFS!!\r\n");
        Fatfs_init();
        
        printf("\r\n��ʼ��USB!!\r\n");
        UsbMassStor_init();
        usbconnect = 1;
        break;
      case 2:
        printf("��ʼ��FATFS!!\r\n");
        Fatfs_init();
        if(!isFileExist())
        {	 
          
          printf("�̼��������!\r\n");	
        }else 
        {
          
          printf("��FLASHӦ�ó���!\r\n");
        }
        break;
      case 3:
        usb_port_set(0);
        usbconnect = 0;
        break;
      default:
        break;
      } 
      
    }
  }  
  
  if(usbconnect)
  {	
    
    
    delay_ms(1);	
    
    if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
    {	 						   
      //�����ʾ			  	   
      if(USB_STATUS_REG&0x01)//����д		  
      {
        //��ʾUSB����д������	 
      }
      if(USB_STATUS_REG&0x02)//���ڶ�
      {
        //��ʾUSB���ڶ�������  		 
      }	 										  
      if(USB_STATUS_REG&0x04){}//��ʾд�����
      else {}//�����ʾ	  
      if(USB_STATUS_REG&0x08){}//��ʾ��������
      else {}//�����ʾ    
      USB_STA=USB_STATUS_REG;//��¼����״̬
    }
    if(Divece_STA!=bDeviceState) 
    {
      if(bDeviceState==CONFIGURED){}//��ʾUSB�����Ѿ�����
      else {}//��ʾUSB���γ���
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
      }else//û�еõ���ѯ 
      {
        offline_cnt++;  
        if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
      }
      USB_STATUS_REG=0;
    }
  }
  delay_ms(10);
}

#else

u8 LANGUAGE = 0;
u8 menu_item = 0;

//�˵���ʼ��
void menu_init(void)
{
  
  if(0 == menu_item)//�˵���ʼ��
  {
      ZTM_FullScreenImageDisp(300);
      delay_ms(5);
      ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
      delay_ms(5);
      TXM_StringDisplay(0,180,290,24,0,RED ,WHITE, (void*)Menu_Item_Descrip[0][LANGUAGE]);       
      delay_ms(5);  
      
      TXM_StringDisplay(0,5,35,16,0,BLACK ,BLUE,  (void*)Version);
      delay_ms(5);                 
      
      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }
      
      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE,    (void*)Status_Item_Descrip[0][LANGUAGE]);
      delay_ms(5);      
      
      menu_item = 1;
  
  }
  else if(1 == menu_item)//�����л�
  {
      ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
      delay_ms(5);
      TXM_StringDisplay(0,180,290,24,0,RED ,WHITE, (void*)Menu_Item_Descrip[0][LANGUAGE]);       
      delay_ms(5); 
      
      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }
      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE,    (void*)Status_Item_Descrip[0][LANGUAGE]);
      delay_ms(5);      
  
  }
  else if(2 == menu_item)//ѡ�����ӵ���
  {
      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }  
      TXM_StringDisplay(0,30,70,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[1][LANGUAGE]);
      delay_ms(5); 
      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[1][LANGUAGE]);
      delay_ms(5);       
  }  
  else if(3 == menu_item)//ѡ��Ͽ�����
  {

      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }    
      TXM_StringDisplay(0,30,115,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[2][LANGUAGE]);
      delay_ms(5);      
      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[8][LANGUAGE]);
      delay_ms(5);  
  } 
  else if(4 == menu_item)//ѡ�����APP
  {

      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }   
      TXM_StringDisplay(0,30,160,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[3][LANGUAGE]);
      delay_ms(5);
      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[2][LANGUAGE]);
      delay_ms(5); 
  
  } 
  else if(5 == menu_item)//ѡ�����APP
  {

      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }   
      TXM_StringDisplay(0,30,205,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[4][LANGUAGE]);
      delay_ms(5);      
      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[6][LANGUAGE]);
      delay_ms(5);  
  }   


  
//              RTCC_GetTime(TimeBuff);
//              Current_Date = GetDate(TimeBuff);
//              
//              printf("Current_Date = %d\r\n", Current_Date);
  
}


void enter_menu(void)
{
          u8 key = 0;
          u8 timeover = 0;
                  
          while(1){
            
              key=key_scan();
              if(key==KEY_F1)			//KEY_F1��������
              {
                delay_ms(50);
                if(key==KEY_F1){
                  
                  break;                                   
                }
              }        
              delay_ms(100);
              timeover++;
              printf("enter_menu:timeover = %d\r\n", timeover);
              
              if(timeover >= 10)
              {                
                  printf("��ʼִ��FLASH�û�����!!\r\n");
                  if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
                  {	 
                    iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
                  }
                  else 
                  {
                    printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
                    break;
                    
                  }
                  
              }
          }          
}

u8 lcd_sleep = 0;
u8 usb_connect = 0;
extern u8 sleepcount;

void menu_pocess(void)
{
            u8 key = 0;
  
//            RTCC_GetTime(TimeBuff);
//            time_display(307, 308, TimeBuff);
  
            key=key_scan();
            if(key)
            {
                sleepcount = 0;
                if(lcd_sleep)
                {
                    lcd_sleep = 0;                    
                    LCM_Light_Setting(50);
                    delay_ms(500);
                }
                
//                if(key == KEY_POWER)
//                {
//                  delay_ms(1);
//                  if(key == KEY_POWER)
//                  {
//                      if(lcd_sleep)
//                      {
//                        lcd_sleep = 0;                   
//                        LCM_Light_Setting(50);  
//                        delay_ms(500);
//                      }
//                      else
//                      {
//                        lcd_sleep = 1;                    
//                        LCM_Light_Setting(0);   
//                        delay_ms(500);
//                      }
//                  }
//                }
                else if(key == KEY_F3)
                {
                  delay_ms(1);
                  if(key == KEY_F3)
                  {
                      LANGUAGE = (~LANGUAGE) & 0x01;
                      menu_init();
                      delay_ms(500);
                  }
                }
                else if(key==KEY_LEFT)			
                {
                  
                  delay_ms(1);
                  if(key==KEY_LEFT)
                  {               
                    if(usb_connect == 0)
                    {
                      usb_connect = 1;
                      menu_item = 2;
                      menu_init();
                      
                      printf("\r\n��ʼ��FATFS!!\r\n");
                      Fatfs_init();
                      
                      printf("\r\n��ʼ��USB!!\r\n");
                      UsbMassStor_init();
                    
    //                f_mount(NULL,"0:",1); //ж��
                    }
                    
                  }
                }
                if(key==KEY_RIGHT)			
                {
                  
                  delay_ms(1);
                  if(key==KEY_RIGHT)
                  {    
                    if(usb_connect)
                    {
                      usb_connect = 0;
                      menu_item = 3;
                      menu_init();
                      printf("\r\n exit usb mass \r\n");
                      
                      usb_port_set(0);       
                       #if defined(USE_MYMALLOC)
                          myfree(Data_Buffer);
                          myfree(Bulk_Data_Buff);
                       #endif
                       delay_ms(500);   
                    }
                    
                  }
                }
                else if(key==KEY_UP)			
                {
                  
                  delay_ms(1);
                  if(key==KEY_UP)
                  {
                      if(usb_connect == 0)
                      {
                          menu_item = 4;
                          menu_init();
                          
                          printf("��ʼ��FATFS!!\r\n");
                          
        //                  #if defined(USE_MYMALLOC)	       
        //                      Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//�������ڴ���ʧ�ܣ�����----------10.10 ԭ���ǳ�ʼ����ʱ��û�и�fatfs���뵽�ڴ棬Ҫ�ȳ�ʼ���ڴ���������ڴ�
        //                      Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	            
        //                  #endif
                          
                          u8 count = 3;
                          u8 res = 0;
                              
                          while(count)//ʧ����������
                          {
                              
                              Fatfs_init();
                              
                              
                              if(!isFileExist())//�жϹ̼��Ƿ����
                              {
                                
                                  printf("��ʼ���¹̼�...\r\n");	
                                  
                                  res = UpdateApp();
                                  if(!res)//��spi flash����APP��stmflash��
                                  {	                                       
                                      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[3][LANGUAGE]);//״̬��APP�������
                                      printf("�̼��������!\r\n");	
        //                              break;
                                      delay_ms(500);
                                      if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
                                      {	 
                                          TIM_Cmd(TIM3, DISABLE);
                                          delay_ms(500);
                                          iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
                                      }
                                      else 
                                      {
                                          printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
                                          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[7][LANGUAGE]);//״̬����APP����                   
                                      }
                                  }
                                  else if(FR_INVALID_OBJECT == res)
                                  {
                                      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[11][LANGUAGE]);//״̬���ǺϷ�����  
                                  
                                  }
                                  else 
                                  {
                                      TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[4][LANGUAGE]);//״̬������ʧ��
                                      printf("��FLASHӦ�ó���!\r\n");
                                  }
                              }
                              else 
                              {
                                  TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[5][LANGUAGE]);//״̬���޿ɸ��¹̼�
                                  printf("û�п��Ը��µĹ̼�!\r\n");
                                  break;                        
                              }
                              count--;
                          }
        //                  #if defined(USE_MYMALLOC)
        //                      myfree(Data_Buffer);
        //                      myfree(Bulk_Data_Buff);
        //                  #endif
                      }
                    
                  }
                }
                else if(key==KEY_SET)			
                {
                  delay_ms(1);
                  if(key==KEY_SET)
                  {       
                      if(usb_connect == 0)
                      {
                          menu_item = 5;
                          menu_init();
                          delay_ms(500);
                          
                          printf("��ʼִ��FLASH�û�����!!\r\n");
                          if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
                          {	 
                              TIM_Cmd(TIM3, DISABLE);
                              delay_ms(500);
                              iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
                          }
                          else 
                          {
                              printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
                              TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[7][LANGUAGE]);//״̬����APP����                   
                          }	               
                      }
                  }
                }
            
            }
            delay_ms(10);
}



#endif


