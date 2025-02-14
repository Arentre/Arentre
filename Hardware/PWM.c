#include "stm32f10x.h"                  // Device header
void PWM_Init(void)

{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
          
	GPIO_InitTypeDef GPIO_Initstructure;     //结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF_PP ;        //复用推挽输出
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_2;             //修改引脚
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
  
  TIM_InternalClockConfig(TIM2);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructure;
  TIM_TimeBaseInitstructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseInitstructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitstructure.TIM_Period=100-1;            //ARR  周期
  TIM_TimeBaseInitstructure.TIM_Prescaler=36-1;          //PSC  预分频器
  TIM_TimeBaseInitstructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstructure);                    
                                                                       //一般CK_PSC=72MHZ  
  TIM_OCInitTypeDef TIM_OCInitStrructure;                              //PWM频率:  Freq=CK_PSC/(PSC+1)/(ARR+1)
  TIM_OCStructInit(&TIM_OCInitStrructure);                             //PWM占空比：Duty=CCR/(ARR+1)
  TIM_OCInitStrructure.TIM_OCMode=TIM_OCMode_PWM1;                     //PWM分辨率：Reso=1/(ARR+1) 
  TIM_OCInitStrructure.TIM_OCPolarity=TIM_OCPolarity_High;
  TIM_OCInitStrructure.TIM_OutputState=TIM_OutputState_Enable;
  TIM_OCInitStrructure.TIM_Pulse= 0;                         //CCR
  TIM_OC3Init(TIM2,&TIM_OCInitStrructure);
  
  TIM_Cmd(TIM2,ENABLE);
}
void PWM_SetCompare3(uint16_t Compare)
{
TIM_SetCompare3(TIM2,Compare);

}



