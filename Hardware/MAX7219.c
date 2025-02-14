//" Max7219.c "
#include "stm32f10x.h"                  // USE_STDPERIPH_DRIVER
#include "delay.h"
#include "Max7219.h"
#include "math.h"

uint8_t graph[10]={0};//函数调用内部：每一行的二进制值，记忆化，防止每次修改闪屏

/*
功能：初始化引脚参数
参数：-
介绍：注意 引脚模式
*/
void Max7219_SpiInit(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置CS引脚为推挽输出模式
    GPIO_InitStructure.GPIO_Pin = MAX7219_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MAX7219_CS_PORT, &GPIO_InitStructure);

    // 配置CLK引脚为推挽输出模式
    GPIO_InitStructure.GPIO_Pin = MAX7219_CLK_PIN;
    GPIO_Init(MAX7219_CLK_PORT, &GPIO_InitStructure);

    // 配置DIN引脚为推挽输出模式-Mosi
    GPIO_InitStructure.GPIO_Pin = MAX7219_DIN_PIN;
    GPIO_Init(MAX7219_DIN_PORT, &GPIO_InitStructure);
}


/*
功能：初始化Max7219
参数：-
介绍：有需求可自己调参，一般不需改动
*/
void Max7219_InitDisplay(void) {
		Max7219_SpiInit();
		Max7219_Bright(3); //设置初始亮度，可选 0-15
		Max7219_SendByte(0X0C,1);//工作模式选择   1:正常工作  0:掉电模式（熄屏但不丢数据）  
		Max7219_SendByte(0X0F,0);//测试模式开关   1:开测试模式  0:正常工作
	  Max7219_SendByte(0X0B,7);	//扫描方式选择  0-7 设置扫描1-8个LED
		Max7219_SendByte(0X09,0);	//译码方式  0：为不解码，点阵屏没这个功能。
	  Max7219_Clear();             //MA7219数码管中，开启译码可以用Send（DIGX，num）一键显示
}

//清空全部内容，熄灭
void Max7219_Clear(void){
	for(int i=1;i<=8;i++){
		Max7219_SendByte(i,0);
		graph[i]=0;
	}
}

/*
功能：仅清空一行
参数：某一行：1-8
介绍：防止多数覆盖少数，如：先点亮第一行【1，6】的灯，再点【2，4】
      若不事先清空，则效果被覆盖。仅用于有覆盖性的变化需求时，仅一个图案则用不到。
*/
void Max7219_Clearline(uint8_t l){
	graph[l]=0;
	Max7219_SendByte(l,graph[l]);
	//Max7219_SendByte(l,0)也可以，但无法让数组保存记忆，只能做到即时显示
}

/*
功能1：模拟SPI通信
参数1：地址
参数2：数据值
介绍：SPI为16位通信，将片CS信号拉低开始发送，数据位发送后，将时钟信号置高再置低产生
      时钟脉冲发送完成后，将片选信号拉高结束通信。

功能2：二进制值，设定某行的灯阵
参数1：选中某一行，1-8（地址恰为0x01-0x08，可直接用十进制）
参数2：数据值的二进制形式，对应每一行8个LEd的亮灭
介绍：可用取模软件得图案值，然后快速输出
*/
void Max7219_SendByte(uint8_t address, uint8_t data) {
    uint8_t i;
	// 拉低CS引脚，选中Max7219
    GPIO_ResetBits(MAX7219_CS_PORT, MAX7219_CS_PIN);


    // 发送地址字节
    for (i = 0; i < 8; i++) {
        // 设置DIN引脚数据位-写入数据
        if (address & 0x80) {
            GPIO_SetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        } else {
            GPIO_ResetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        }
        // 产生时钟脉冲 1-0
        GPIO_SetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // 延迟1微秒
        GPIO_ResetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // 延迟1微秒
        address <<= 1;
    }

    // 发送数据字节
    for (i = 0; i < 8; i++) {
        // 设置DIN引脚数据位
        if (data & 0x80) {
            GPIO_SetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        } else {
            GPIO_ResetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        }
        // 产生时钟脉冲 1-0
        GPIO_SetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // 延迟1微秒
        GPIO_ResetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // 延迟1微秒
        data <<= 1;
    }
    
    // 拉高CS引脚，结束通信
    GPIO_SetBits(MAX7219_CS_PORT, MAX7219_CS_PIN);
		
}


//设置点阵屏亮度：0-15
void Max7219_Bright(uint8_t dt){
		Max7219_SendByte(0X0A,dt);
}

/*
功能：点亮某一行的【x,y】间的LED灯，支持重复操作同一行，效果覆盖。
参数1：第几行：1-8
参数2：起始LEd位置：1-8
参数3：结束LEd位置：1-8
介 绍：原理是计算出仅[x,y]点亮对应的二进制值，写入对应行。
*/
void Max7219_ShowGraph(uint8_t line,uint8_t x,uint8_t y){
		uint8_t tem=pow(2,9-x) - pow(2,8-y);
	  graph[line]|=tem;
		Max7219_SendByte(line,graph[line]);
}


