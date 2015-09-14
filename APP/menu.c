#include "menu.h"


const u8 *Menu_Item_Descrip[][2] =
{                                          
  {" POWER:����APP    "," POWER:Enter APP  "},
  {" F1:���ӵ���      "," F1:Connect to PC "},
  {" F2:����APP       "," F2:Update APP    "},
  {" F3:�Ͽ���������  "," F3:Disconnect PC "},
  
};

u8 TimeBuff[6];
u32 Current_Date;

void RCC_init(void)
{
  
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE); //for dma  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//Ϊ�ⲿ�ж�
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); //USART1 ʱ��ʹ��
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

void Lcd_init(void)
{
  
  delay_ms(1000);  //����ʱ�ε�������û��ʾ
  ZTM_FullScreenImageDisp(300);
  delay_ms(5);
  ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
  delay_ms(5);
  TXM_StringDisplay(0,10,290,24,0,RED ,WHITE, "����");       
  delay_ms(5);  
  TXM_StringDisplay(0,30,50,24,1,YELLOW ,BLUE,  " POWER:����APP   ");
  delay_ms(5);  
  TXM_StringDisplay(0,30,100,24,1,YELLOW ,BLUE, " F1:���ӵ���     ");
  delay_ms(5);  
  TXM_StringDisplay(0,30,150,24,1,YELLOW ,BLUE, " F2:����APP      ");
  delay_ms(5);  
  TXM_StringDisplay(0,30,200,24,1,YELLOW ,BLUE, " F3:�Ͽ��������� ");
  delay_ms(5);  
  TXM_StringDisplay(0,20,250,24,1,RED ,BLUE,    " ״̬�� ��ѡ��   ");
  delay_ms(5); 
  
              RTCC_GetTime(TimeBuff);
              Current_Date = GetDate(TimeBuff);
              
              printf("Current_Date = %d\r\n", Current_Date);
  
}




void menu_pocess(void)
{
            u8 key = 0;
  
            RTCC_GetTime(TimeBuff);
            time_display(307, 308, TimeBuff);
  
            key=key_scan();
            if(key==KEY_F1)			//KEY_F1��������
            {
              
              delay_ms(200);
              if(key==KEY_F1){
                
                TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "״̬��ѡ�����ӵ���");
                delay_ms(5); 
                TXM_StringDisplay(0,30,100,24,1,YELLOW ,RED, " F1:���ӵ���     ");
                
                printf("\r\n��ʼ��FATFS!!\r\n");
                Fatfs_init();
                
                printf("\r\n��ʼ��USB!!\r\n");
                UsbMassStor_init();
                
              }
            } 
            else if(key==KEY_F2)			//KEY_F2��������
            {
              
              delay_ms(200);
              if(key==KEY_F2){
                
                
                delay_ms(1500); 
                TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "״̬��ѡ�����APP");
                delay_ms(5); 
                TXM_StringDisplay(0,30,150,24,1,YELLOW ,RED, " F2:����APP      ");
                
                printf("��ʼ��FATFS!!\r\n");
                Fatfs_init();
                
                if(1)//!isFileExist())//�ж��Ƿ���̼�
                {
                  
                  printf("��ʼ���¹̼�...\r\n");	
                  
                  if(!isFileExist())//((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
                  {	 
                    //iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,10);//����FLASH����   
                    
                    
                    
                    printf("�̼��������!\r\n");	
                  }else 
                  {
                    
                    printf("��FLASHӦ�ó���!\r\n");
                  }
                }else 
                {
                  printf("û�п��Ը��µĹ̼�!\r\n");
                  
                }
                
              }
            }
            else if(key==KEY_POWER)			//KEY_POWER��������
            {
              delay_ms(200);
              if(key==KEY_POWER){
                
                delay_ms(1000); 
                TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, " ״̬��ѡ�����APP");
                delay_ms(5);                
                TXM_StringDisplay(0,30,50,24,1,YELLOW ,RED,  " POWER:����APP   ");
                delay_ms(1000);
                
                printf("��ʼִ��FLASH�û�����!!\r\n");
                if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
                {	 
                  iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
                }else 
                {
                  printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
                  
                }	
                
                
              }
            }
            

            delay_ms(10);
}



#endif


