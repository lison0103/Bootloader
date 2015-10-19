#include "wakeup.h"
#include "sys.h"


void Sys_Standby(void)
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//使能PWR外设时钟
	PWR_WakeUpPinCmd(ENABLE);  //使能唤醒管脚功能
	PWR_EnterSTANDBYMode();	  //进入待命（STANDBY）模式 		 
}
//系统进入待机模式
void Sys_Enter_Standby(void)
{			 
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE);	//复位所有IO口
	Sys_Standby();
}
void Sys_Stop(void)
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//使能PWR外设时钟

	PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);		 
}

void Sys_Enter_SleepMode(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//使能PWR外设时钟
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