#include "stm32f10x.h"                  // Device header
 
 uint16_t Countsensor_Count;
 void CountSensor_Init(void)        //初始化
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;          //上拉输入
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitTypeDef EXTI_Initstructure;
	EXTI_Initstructure.EXTI_Line=EXTI_Line14;
	EXTI_Initstructure.EXTI_LineCmd=ENABLE;
	EXTI_Initstructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initstructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_Initstructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	}
uint16_t Countsensor_Get(void)
{
return Countsensor_Count;
}
  
void EXTI15_10_IRQHandler(void)
{
if(EXTI_GetITStatus(EXTI_Line14)==SET)   //SET为低电平
{
  Countsensor_Count ++;
  
EXTI_ClearITPendingBit(EXTI_Line14);     //清除中断标志位
}

}
