#include "fatfs.h"




void Fatfs_init(void)
{
  
  u8 res;
  u16 temp=0;
  u32 dtsize,dfsize;
  
  printf("\r\n FATFS init! \r\n");
  
  
  f_mount(fs[0],"0:",0); 					//����FLASH.	  
  
  
  //W25Q64���,����������ļ�ϵͳ,���ȴ���.
  temp=0;	
  do
  {
    temp++;
    res=exf_getfree("0:",&dtsize,&dfsize);//�õ�FLASHʣ��������������
    delay_ms(200);		   
  }while(res&&temp<20);//�������20��		  
  if(res==0X0D)//�ļ�ϵͳ������
  {
    printf("\r\nFlash Disk Formatting...\r\n");	//��ʽ��FLASH
    res=f_mkfs("0:",1,4096);//��ʽ��FLASH,1,�̷�;1,����Ҫ������,8������Ϊ1����
    if(res==0)
    {
      f_setlabel((const TCHAR *)"0:DU");	//����Flash���̵�����
      printf("\r\n OK \r\n");//��־��ʽ���ɹ�
      res=exf_getfree("0:",&dtsize,&dfsize);//���»�ȡ����
    }
  }   
  if(res==0)//�õ�FLASH��ʣ��������������
  {				   
    temp=dtsize; 	 
    printf("\r\n Flash Disk: %d   KB \r\n",temp);
  }else 
    printf("\r\n Flash Fat Error! \r\n");	//flash �ļ�ϵͳ���� 
  
  
  
}




u8 isFileExist(void)
{
  FIL* fp;
  FRESULT res = FR_NO_FILE;
  
  fp = (FIL*)mymalloc(sizeof(FIL));	//�����ڴ�

  
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
  
  fp = (FIL*)mymalloc(sizeof(FIL));	//�����ڴ�
  tempbuf = mymalloc(4096);	//����4096���ֽڿռ�
  
  if(fp != NULL && tempbuf != NULL){
    
      res = f_open(fp,"0:DU.bin",FA_READ);
  
      printf("\r\n open res = %d \r\n",res);
      
      while(res==FR_OK)//��ѭ��ִ��
      {
        res=f_read(fp,tempbuf,4096,(UINT *)&bread);		//��ȡ����	
        if(res!=FR_OK)break;								//ִ�д���
        if(0 == flag)
        {
            flag = 1;
            if(((*(vu32*)(tempbuf + 4))&0xFF000000)!=0x08000000)
            {
              res = FR_INVALID_OBJECT;
              break;             
            }
        }
        iap_write_appbin(FLASH_APP1_ADDR + offx,tempbuf,4096);//����FLASH���� 	  
        offx+=bread;
        if(bread!=4096)break;								//������.
      }      
  }
  
  printf("\r\n update res = %d \r\n",res);
  
  f_close(fp);	
  myfree(fp);
  
  return res;  
}