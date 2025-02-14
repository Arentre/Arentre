#include "stm32f10x.h"                  // Device header
void GPIOA_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //启动APB2总线时钟，激活GPIOA区
	GPIO_InitTypeDef GPIO_Initstructure;     //结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;  //上拉输入模式
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;         //A00口，修改引脚
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
    //初始化GPIOA-PIN_0                                   
}
void GPIOB_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //启动APB2总线时钟，激活GPIOB区
	GPIO_InitTypeDef GPIO_Initstructure;     //结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;             //修改引脚
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
    //初始化GPIOB-PIN_0 为开漏输出模式
}
void GPIOC_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //启动APB2总线时钟，激活GPIOC区
	GPIO_InitTypeDef GPIO_Initstructure;     //结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_13;             //修改引脚
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
    //初始化GPIOC-PIN13 为开漏输出模式
}
//模式名称	              描述
//GPIO_Mode_AIN		      模拟输入
//GPIO_Mode_IN_FLOATING	  浮空输入：高阻抗状态
//GPIO_Mode_IPD		      下拉输入：适用于需要默认低电平且偶尔被拉高的场合。
//GPIO_Mode_IPU		      上拉输入：适用于需要默认高电平且偶尔被拉低的场合。
//GPIO_Mode_Out_OD		  开漏输出：引脚只能输出低电平或引脚只能输出低电平或高阻抗状态
//GPIO_Mode_Out_PP		  推挽    ：输出引脚可以主动输出高电平和低电平，能够驱动负载
//GPIO_Mode_AF_OD		  复用开漏输出
//GPIO_Mode_AF_PP		  复用推挽输出
