#include "menu.h"


const u8 *Menu_Item_Descrip[][2] =
{   
  {"Lang","语言"},
  {" ←:连接电脑     "," ←:Connect to PC"},
  {" →:断开电脑连接 "," →:Disconnect PC"},
  {" ↑:更新APP      "," ↑:Update APP   "},
  {" SET:进入APP     "," SET:Enter APP   "},
  
};

const u8 *Status_Item_Descrip[][2] =
{                                          
  
  {" 状态： 请选择    "," Status:  Select  "},
  {"状态：连接电脑    "," Status: Connect  "},
  {"状态：开始更新APP "," Status:  Update  "},
  {"状态：APP更新完成 "," Status:  Finish  "},
  {"状态：更新失败    "," Status:  Fail    "},
  {"状态：无可更新固件"," Status: NO FILE  "},
  {" 状态：进入APP    "," Status: Enter APP"},
  {" 状态：无APP程序  "," Status:  NO APP  "},
  {"状态：已断开电脑  "," Status:Disconnect"},
  {"状态：USB已连接   "," Status:  Connect "},
  {"状态：USB被拔出了 "," Status:Disconnect"},
};

u8 *Version = {"V0.1"};


u8 TimeBuff[6];
//u32 Current_Date;

void RCC_init(void)
{
  
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //for dma  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//为外部中断
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); //USART2 时钟使能
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  
                         |RCC_APB2Periph_GPIOB   
                           |RCC_APB2Periph_GPIOC,
                           
                           ENABLE); //端口时钟使能  
  
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
  
  delay_ms(1000);  //不延时拔掉仿真器没显示
  ZTM_FullScreenImageDisp(300);
  delay_ms(5);
  ZTM_RectangleFill (0, 280,239, 319,DGRAY); 
  delay_ms(5);
  TXM_StringDisplay(0,10,290,24,0,RED ,WHITE, "语言");       
  delay_ms(5);  
  //          TXM_StringDisplay(0,40,50,24,1,YELLOW ,BLUE, "POWER:进入APP");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,40,100,24,1,YELLOW ,BLUE, "F1:连接电脑");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,40,150,24,1,YELLOW ,BLUE, "F2:更新APP");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,40,200,24,1,YELLOW ,BLUE, "F3:断开电脑连接");
  //          delay_ms(5);  
  //          TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, "状态： 请选择");
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
        TXM_StringDisplay(0,10,290,24,0,RED ,WHITE, "语言");       
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
        printf("开始执行FLASH用户代码!!\r\n");
        if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
        {	 
          iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
        }else 
        {
          printf("非FLASH应用程序,无法执行!\r\n");
          
        }	
        break;
      case 1:
        printf("\r\n初始化FATFS!!\r\n");
        Fatfs_init();
        
        printf("\r\n初始化USB!!\r\n");
        UsbMassStor_init();
        usbconnect = 1;
        break;
      case 2:
        printf("初始化FATFS!!\r\n");
        Fatfs_init();
        if(!isFileExist())
        {	 
          
          printf("固件更新完成!\r\n");	
        }else 
        {
          
          printf("非FLASH应用程序!\r\n");
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
    
    if(USB_STA!=USB_STATUS_REG)//状态改变了 
    {	 						   
      //清除显示			  	   
      if(USB_STATUS_REG&0x01)//正在写		  
      {
        //提示USB正在写入数据	 
      }
      if(USB_STATUS_REG&0x02)//正在读
      {
        //提示USB正在读出数据  		 
      }	 										  
      if(USB_STATUS_REG&0x04){}//提示写入错误
      else {}//清除显示	  
      if(USB_STATUS_REG&0x08){}//提示读出错误
      else {}//清除显示    
      USB_STA=USB_STATUS_REG;//记录最后的状态
    }
    if(Divece_STA!=bDeviceState) 
    {
      if(bDeviceState==CONFIGURED){}//提示USB连接已经建立
      else {}//提示USB被拔出了
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
      }else//没有得到轮询 
      {
        offline_cnt++;  
        if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
      }
      USB_STATUS_REG=0;
    }
  }
  delay_ms(10);
}

#else

u8 LANGUAGE = 0;

//菜单初始化
void menu_init(u8 item)
{
  
  if(0 == item)
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
  
  }
  else if(1 == item)
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
  else if(2 == item)
  {
      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }  
      TXM_StringDisplay(0,30,70,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[1][LANGUAGE]);
      delay_ms(5);  
  }  
  else if(3 == item)
  {

      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }    
      TXM_StringDisplay(0,30,115,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[2][LANGUAGE]);
      delay_ms(5);      
  
  } 
  else if(4 == item)
  {

      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }   
      TXM_StringDisplay(0,30,160,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[3][LANGUAGE]);
      delay_ms(5);       
  
  } 
  else if(5 == item)
  {

      for(u8 i = 0;i < 4;i++)
      {
        TXM_StringDisplay(0,30,70 + (i*45),24,1,YELLOW ,BLUE,  (void*)Menu_Item_Descrip[i+1][LANGUAGE]);
        delay_ms(5);                
      }   
      TXM_StringDisplay(0,30,205,24,1,YELLOW ,RED,  (void*)Menu_Item_Descrip[4][LANGUAGE]);
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
              if(key==KEY_F1)			//KEY_F1按键按下
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
                
                  printf("开始执行FLASH用户代码!!\r\n");
                  if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
                  {	 
                    iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
                  }
                  else 
                  {
                    printf("非FLASH应用程序,无法执行!\r\n");
                    break;
                    
                  }
                  
              }
          }
          
}



void menu_pocess(void)
{
            u8 key = 0;
  
            RTCC_GetTime(TimeBuff);
            time_display(307, 308, TimeBuff);
  
            key=key_scan();
            if(key == KEY_F3)
            {
              delay_ms(50);
              if(key == KEY_F3)
              {
                  LANGUAGE = (~LANGUAGE) & 0x01;
                  menu_init(1);
                  delay_ms(500);
              }
            }
            else if(key==KEY_LEFT)			
            {
              
              delay_ms(50);
              if(key==KEY_LEFT){
                
                TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[1][LANGUAGE]);
                delay_ms(5); 
                menu_init(2);
                
                printf("\r\n初始化FATFS!!\r\n");
                Fatfs_init();
                
                printf("\r\n初始化USB!!\r\n");
                UsbMassStor_init();
                
//                f_mount(NULL,"0:",1); //卸载
                
              }
            } 
            else if(key==KEY_UP)			
            {
              
              delay_ms(50);
              if(key==KEY_UP){
                
                TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[2][LANGUAGE]);
                delay_ms(5); 
                menu_init(4);
                
                printf("初始化FATFS!!\r\n");
                Fatfs_init();
                
                if(!isFileExist())//判断固件是否存在
                {
                  
                  printf("开始更新固件...\r\n");	
                  
                  if(!UpdateApp())//从spi flash复制APP到stmflash中
                  {	                                       
                    TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[3][LANGUAGE]);
                    printf("固件更新完成!\r\n");	
                  }
                  else 
                  {
                    TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[4][LANGUAGE]);
                    printf("非FLASH应用程序!\r\n");
                  }
                }
                else 
                {
                  TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[5][LANGUAGE]);
                  printf("没有可以更新的固件!\r\n");
                  
                }
                
              }
            }
            else if(key==KEY_SET)			
            {
              delay_ms(50);
              if(key==KEY_SET){
                
                TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[6][LANGUAGE]);
                delay_ms(5);                
                menu_init(5);
                delay_ms(1000);
                
                printf("开始执行FLASH用户代码!!\r\n");
                if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
                {	 
                  iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
                }
                else 
                {
                  printf("非FLASH应用程序,无法执行!\r\n");
                  TXM_StringDisplay(0,20,250,24,1,RED ,BLUE, (void*)Status_Item_Descrip[7][LANGUAGE]);
                  
                }	
                
                
              }
            }
            

            delay_ms(10);
}



#endif


