//#include "Max7219.h"
#ifndef __MAX7219_H
#define __MAX7219_H

//���ߣ�Din-A6 Cs-A4  Clk-A5
//ģ��SPI�����������Լ��Ķ�����
#define MAX7219_CS_PIN GPIO_Pin_4
#define MAX7219_CS_PORT GPIOA
#define MAX7219_CLK_PIN GPIO_Pin_5
#define MAX7219_CLK_PORT GPIOA
#define MAX7219_DIN_PIN GPIO_Pin_6
#define MAX7219_DIN_PORT GPIOA

void Max7219_InitDisplay(void); //��ʼ��������:���ȡ�ģʽ�����ԡ�ɨ�衢���뷽ʽ
void Max7219_Bright(uint8_t dt);//16�����ȣ�dt=0-15
void Max7219_Clear(void);       //ȫ�����
void Max7219_Clearline(uint8_t l);//����յ�L�У�L:1-8
void Max7219_SendByte(uint8_t address, uint8_t data);//������ֵ��������SPIͨ�ţ�����2�ֽ�
void Max7219_ShowGraph(uint8_t line,uint8_t x,uint8_t y);//������line�У�x-y�ĵ㣬���߽ԣ�1-8

#endif

