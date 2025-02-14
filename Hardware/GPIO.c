#include "stm32f10x.h"                  // Device header
void GPIOA_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //����APB2����ʱ�ӣ�����GPIOA��
	GPIO_InitTypeDef GPIO_Initstructure;     //�ṹ��
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;  //��������ģʽ
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;         //A00�ڣ��޸�����
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
    //��ʼ��GPIOA-PIN_0                                   
}
void GPIOB_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //����APB2����ʱ�ӣ�����GPIOB��
	GPIO_InitTypeDef GPIO_Initstructure;     //�ṹ��
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;             //�޸�����
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
    //��ʼ��GPIOB-PIN_0 Ϊ��©���ģʽ
}
void GPIOC_Init(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //����APB2����ʱ�ӣ�����GPIOC��
	GPIO_InitTypeDef GPIO_Initstructure;     //�ṹ��
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_13;             //�޸�����
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
    //��ʼ��GPIOC-PIN13 Ϊ��©���ģʽ
}
//ģʽ����	              ����
//GPIO_Mode_AIN		      ģ������
//GPIO_Mode_IN_FLOATING	  �������룺���迹״̬
//GPIO_Mode_IPD		      �������룺��������ҪĬ�ϵ͵�ƽ��ż�������ߵĳ��ϡ�
//GPIO_Mode_IPU		      �������룺��������ҪĬ�ϸߵ�ƽ��ż�������͵ĳ��ϡ�
//GPIO_Mode_Out_OD		  ��©���������ֻ������͵�ƽ������ֻ������͵�ƽ����迹״̬
//GPIO_Mode_Out_PP		  ����    ��������ſ�����������ߵ�ƽ�͵͵�ƽ���ܹ���������
//GPIO_Mode_AF_OD		  ���ÿ�©���
//GPIO_Mode_AF_PP		  �����������
