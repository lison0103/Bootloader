#include "menu.h"


u8 LANGUAGE = 0;
u8 menu_item = 0;
u8 lcd_sleep = 0;
u8 usb_connect = 0;
extern u8 sleepcount;

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


/*******************************************************************************
���ܣ�RCCʱ�ӳ�ʼ��
*******************************************************************************/
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

/*******************************************************************************
���ܣ��˵���ʾ
*******************************************************************************/
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
  else
  {
    
      TXM_StringDisplay(0,180,290,24,1,RED ,DGRAY, (void*)Menu_Item_Descrip[0][LANGUAGE]);       
      delay_ms(5); 
      
      for(u8 i = 0;i < 4;i++)
      {
          TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
          delay_ms(5);                
      }    
      
      if(1 == menu_item)//�����л�
      {
          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE,    (void*)Status_Item_Descrip[0][LANGUAGE]);
          delay_ms(5);            
      }
      else if(2 == menu_item)//ѡ�����ӵ���
      {
          TXM_StringDisplay(0,30,70,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[1][LANGUAGE]);
          delay_ms(5); 
          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[1][LANGUAGE]);
          delay_ms(5);       
      }  
      else if(3 == menu_item)//ѡ��Ͽ�����
      {   
          TXM_StringDisplay(0,30,115,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[2][LANGUAGE]);
          delay_ms(5);      
          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[8][LANGUAGE]);
          delay_ms(5);  
      } 
      else if(4 == menu_item)//ѡ�����APP
      {  
          TXM_StringDisplay(0,30,160,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[3][LANGUAGE]);
          delay_ms(5);
          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[2][LANGUAGE]);
          delay_ms(5); 
      
      } 
      else if(5 == menu_item)//ѡ�����APP
      {  
          TXM_StringDisplay(0,30,205,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[4][LANGUAGE]);
          delay_ms(5);      
          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[6][LANGUAGE]);
          delay_ms(5);  
      }   
  }
  
}

/*******************************************************************************
���ܣ��ȴ�����loader����Լ1s����F1����
*******************************************************************************/
void enter_menu(void)
{
          u8 key = 0;
          u8 timeover = 0;
                  
          while(1)
          {           
              key=key_scan();
              if(key==KEY_F1)			//KEY_F1��������
              {
                  delay_ms(50);
                  if(key==KEY_F1)
                  {                 
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

/*******************************************************************************
���ܣ����ӵ����ӳ���
*******************************************************************************/
void ConnectToPc_process(void)
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
    }  
}
/*******************************************************************************
���ܣ��Ͽ�USB���������ӳ���
*******************************************************************************/
void DisconnectUsb_process(void)
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

/*******************************************************************************
���ܣ�����APP�ӳ���
*******************************************************************************/
void UpdateApp_process(void)
{
    if(usb_connect == 0)
    {
      menu_item = 4;
      menu_init();                            
      printf("��ʼ��FATFS!!\r\n");                       
      
      u8 count = 3;
      u8 res = 0;                               
      while(count)//ʧ����������
      {                               
          Fatfs_init();                                                              
          if(!isFileExist("0:DU.bin"))//�жϹ̼��Ƿ����
          {                                 
              printf("��ʼ���¹̼�...\r\n");	
              
              res = UpdateApp();
              if(!res)//��spi flash����APP��stmflash��
              {	                                       
                  TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[3][LANGUAGE]);//״̬��APP�������
                  printf("�̼��������!\r\n");	
                  
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
    } 
}

/*******************************************************************************
���ܣ���ת����APP�ӳ���
*******************************************************************************/
void JumpToApp_process(void)
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

/*******************************************************************************
���ܣ��ȴ��������룬������Ӧ����
*******************************************************************************/
void menu_pocess(void)
{
            u8 key = 0;
    
            key=key_scan();
            if(key)                                             //�������ⰴ��
            {
                sleepcount = 0;
                
                if(lcd_sleep)                                   //��lcd���ߣ����˳�
                {
                    lcd_sleep = 0;                    
                    LCM_Light_Setting(50);
                    delay_ms(500);
                }              
                else if(key == KEY_F3)                          
                {
                    delay_ms(1);
                    if(key == KEY_F3)
                    {
                        LANGUAGE = (~LANGUAGE) & 0x01;          //�����л�
                        menu_init();
                        delay_ms(500);
                    }
                }
                else if(key==KEY_LEFT)			        
                {                  
                    delay_ms(1);
                    if(key==KEY_LEFT)
                    {               
                        ConnectToPc_process();                  //���ӵ���
                    }
                }
                else if(key==KEY_RIGHT)			        
                {                  
                    delay_ms(1);
                    if(key==KEY_RIGHT)
                    {    
                         DisconnectUsb_process();               //�Ͽ�����
                    }
                }
                else if(key==KEY_UP)			        
                {                  
                    delay_ms(1);
                    if(key==KEY_UP)
                    {
                         UpdateApp_process();                  //����APP���ɹ���������
                    }
                }
                else if(key==KEY_SET)			        
                {
                    delay_ms(1);
                    if(key==KEY_SET)
                    {       
                         JumpToApp_process();                   //����APP
                    }
                }           
            }
            delay_ms(10);
}



