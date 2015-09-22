#include "fatfs.h"




void Fatfs_init(void)
{
  
  u8 res;
  u16 temp=0;
  u32 dtsize,dfsize;
  
  printf("\r\n FATFS init! \r\n");
  
  
  f_mount(fs[0],"0:",0); 					//挂载FLASH.	  
  
  
  //W25Q64检测,如果不存在文件系统,则先创建.
  temp=0;	
  do
  {
    temp++;
    res=exf_getfree("0:",&dtsize,&dfsize);//得到FLASH剩余容量和总容量
    delay_ms(200);		   
  }while(res&&temp<20);//连续检测20次		  
  if(res==0X0D)//文件系统不存在
  {
    printf("\r\nFlash Disk Formatting...\r\n");	//格式化FLASH
    res=f_mkfs("0:",1,4096);//格式化FLASH,1,盘符;1,不需要引导区,8个扇区为1个簇
    if(res==0)
    {
      f_setlabel((const TCHAR *)"0:DU");	//设置Flash磁盘的名字
      printf("\r\n OK \r\n");//标志格式化成功
      res=exf_getfree("0:",&dtsize,&dfsize);//重新获取容量
    }
  }   
  if(res==0)//得到FLASH卡剩余容量和总容量
  {				   
    temp=dtsize; 	 
    printf("\r\n Flash Disk: %d   KB \r\n",temp);
  }else 
    printf("\r\n Flash Fat Error! \r\n");	//flash 文件系统错误 
  
  
  
}




u8 isFileExist(void)
{
  FIL* fp;
  FRESULT res = FR_NO_FILE;
  
  fp = (FIL*)mymalloc(sizeof(FIL));	//分配内存

  
  if(fp != NULL){
    
      res = f_open(fp,"0:DU.bin",FA_READ);
  
      printf("\r\n open res = %d \r\n",res);
      
      if(res==FR_OK)
      {
	 f_close(fp);						
      }
      myfree(fp);      
  }  
  	
  
  
  return res;
  
}

u8 UpdateApp(void)
{
  FIL* fp;
  FRESULT res;
  u8 *tempbuf;
  u16 bread;
  u32 offx=0;
  u8  flag = 0;
  
  fp = (FIL*)mymalloc(sizeof(FIL));	//分配内存
  tempbuf = mymalloc(4096);	//分配4096个字节空间
  
  if(fp != NULL && tempbuf != NULL){
    
      res = f_open(fp,"0:DU.bin",FA_READ);
  
      printf("\r\n open res = %d \r\n",res);
      
      while(res==FR_OK)//死循环执行
      {
        res=f_read(fp,tempbuf,4096,(UINT *)&bread);		//读取数据	
        if(res!=FR_OK)break;								//执行错误
        if(0 == flag)
        {
            flag = 1;
            if(((*(vu32*)(tempbuf + 4))&0xFF000000)!=0x08000000)
            {
              res = FR_INVALID_OBJECT;
              break;             
            }
        }
        iap_write_appbin(FLASH_APP1_ADDR + offx,tempbuf,4096);//更新FLASH代码 	  
        offx+=bread;
        if(bread!=4096)break;								//读完了.
      }      
  }
  
  printf("\r\n update res = %d \r\n",res);
  
  f_close(fp);	
  myfree(fp);
  
  return res;  
}