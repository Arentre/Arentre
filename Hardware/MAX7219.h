//#include "Max7219.h"
#ifndef __MAX7219_H
#define __MAX7219_H

//接线：Din-A6 Cs-A4  Clk-A5
//模拟SPI，如有需求自己改动即可
#define MAX7219_CS_PIN GPIO_Pin_4
#define MAX7219_CS_PORT GPIOA
#define MAX7219_CLK_PIN GPIO_Pin_5
#define MAX7219_CLK_PORT GPIOA
#define MAX7219_DIN_PIN GPIO_Pin_6
#define MAX7219_DIN_PORT GPIOA

void Max7219_InitDisplay(void); //初始化点阵屏:亮度、模式、测试、扫描、译码方式
void Max7219_Bright(uint8_t dt);//16级亮度：dt=0-15
void Max7219_Clear(void);       //全部清空
void Max7219_Clearline(uint8_t l);//仅清空第L行，L:1-8
void Max7219_SendByte(uint8_t address, uint8_t data);//二进制值点亮灯阵；SPI通信，发送2字节
void Max7219_ShowGraph(uint8_t line,uint8_t x,uint8_t y);//点亮第line行，x-y的点，三者皆：1-8

#endif

