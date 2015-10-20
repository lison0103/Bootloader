#include "wakeup.h"
#include "sys.h"


void Sys_Standby(void)
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ʹ��PWR����ʱ��
	PWR_WakeUpPinCmd(ENABLE);  //ʹ�ܻ��ѹܽŹ���
	PWR_EnterSTANDBYMode();	  //���������STANDBY��ģʽ 		 
}
//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{			 
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE);	//��λ����IO��
	Sys_Standby();
}
void Sys_Stop(void)
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ʹ��PWR����ʱ��

	PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);		 
}

void Sys_Enter_SleepMode(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ʹ��PWR����ʱ��
    SCB->SCR |= SCB_SCR_SLEEPONEXIT;
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
    
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPONEXIT);
  
//  SCB->SCR |= 0x00;
    
//    __WFI(); 

}
void Sys_Exit_SleepMode(void)
{
//  SCB->SCR |= SCB_SCR_SLEEPDEEP;
  SCB->SCR |=SCB_SCR_SLEEPONEXIT;
}