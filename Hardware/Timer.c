#include "stm32f10x.h"                  // Device header

uint16_t sec;
uint16_t min=26;
uint16_t hour=11;

void Timer_Init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  
  TIM_InternalClockConfig(TIM2);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructure;
  TIM_TimeBaseInitstructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseInitstructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitstructure.TIM_Period=10000-1;
  TIM_TimeBaseInitstructure.TIM_Prescaler=7200-1;
  TIM_TimeBaseInitstructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstructure);
  
  
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  
  NVIC_InitTypeDef NVIC_Initstructure;
  NVIC_Initstructure.NVIC_IRQChannel=TIM2_IRQn;
  NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=2;
  NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
  NVIC_Init(&NVIC_Initstructure);
  
  TIM_Cmd(TIM2,ENABLE);
}
void TIM2_IRQHandler(void)
{
if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
{
  sec++;
  if(sec==60)
  {
  min++;
   sec=0;
  }
  if(min==60)
  {
  hour++;
    min=0;
  }
    if(hour==24)
  {
   hour=0; 
  }
  
  
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}


}



