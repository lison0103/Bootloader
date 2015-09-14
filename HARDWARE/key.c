#include "sys.h" 
#include "key.h" 

/***************************************************************************************************
***************************************************************************************************/
void key_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  //开漏输出
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
  GPIOC->BSRR |= 0X0000000F;
  //GPIOC->BRR |= 0X00000001;
  
  //上拉
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC , &GPIO_InitStruct);
}


/*
//72M
//n=2000 T=392us
//n=1000 T=196us
//n=500  T=98us
//n=100  T=20.6us
*/ 
void Delay_us(uint32_t n)
{ 
	uint32_t m=0;
  m=n*50;
	
	while(m)
	{
		m--;
	}	
}

/***************************************************************************************************
***************************************************************************************************/
u16 key_scan(void)
{
  u32 i=0,j=0,k=0,key_mask[4]={0x000000f0,0x000000b0,0x00000030,0x000000B0};
  u32 key_temp=0;  
  
  j=1;
  key_temp=0;
  for(i=0;i<4;i++)
  {
    GPIOC->BRR |= j;

    Delay_us(50); 

    k = GPIOC->IDR&key_mask[i];
    if(k != key_mask[i])
    {
      key_temp = k+i;
      key_temp &= 0x000000ff; 
    }                             
    GPIOC->BSRR |= j;
      
    j<<=1;
  }  

  return((u16)key_temp);
}

