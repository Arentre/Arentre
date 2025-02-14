//" Max7219.c "
#include "stm32f10x.h"                  // USE_STDPERIPH_DRIVER
#include "delay.h"
#include "Max7219.h"
#include "math.h"

uint8_t graph[10]={0};//���������ڲ���ÿһ�еĶ�����ֵ�����仯����ֹÿ���޸�����

/*
���ܣ���ʼ�����Ų���
������-
���ܣ�ע�� ����ģʽ
*/
void Max7219_SpiInit(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // ����CS����Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Pin = MAX7219_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MAX7219_CS_PORT, &GPIO_InitStructure);

    // ����CLK����Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Pin = MAX7219_CLK_PIN;
    GPIO_Init(MAX7219_CLK_PORT, &GPIO_InitStructure);

    // ����DIN����Ϊ�������ģʽ-Mosi
    GPIO_InitStructure.GPIO_Pin = MAX7219_DIN_PIN;
    GPIO_Init(MAX7219_DIN_PORT, &GPIO_InitStructure);
}


/*
���ܣ���ʼ��Max7219
������-
���ܣ���������Լ����Σ�һ�㲻��Ķ�
*/
void Max7219_InitDisplay(void) {
		Max7219_SpiInit();
		Max7219_Bright(3); //���ó�ʼ���ȣ���ѡ 0-15
		Max7219_SendByte(0X0C,1);//����ģʽѡ��   1:��������  0:����ģʽ��Ϩ�����������ݣ�  
		Max7219_SendByte(0X0F,0);//����ģʽ����   1:������ģʽ  0:��������
	  Max7219_SendByte(0X0B,7);	//ɨ�跽ʽѡ��  0-7 ����ɨ��1-8��LED
		Max7219_SendByte(0X09,0);	//���뷽ʽ  0��Ϊ�����룬������û������ܡ�
	  Max7219_Clear();             //MA7219������У��������������Send��DIGX��num��һ����ʾ
}

//���ȫ�����ݣ�Ϩ��
void Max7219_Clear(void){
	for(int i=1;i<=8;i++){
		Max7219_SendByte(i,0);
		graph[i]=0;
	}
}

/*
���ܣ������һ��
������ĳһ�У�1-8
���ܣ���ֹ���������������磺�ȵ�����һ�С�1��6���ĵƣ��ٵ㡾2��4��
      ����������գ���Ч�������ǡ��������и����Եı仯����ʱ����һ��ͼ�����ò�����
*/
void Max7219_Clearline(uint8_t l){
	graph[l]=0;
	Max7219_SendByte(l,graph[l]);
	//Max7219_SendByte(l,0)Ҳ���ԣ����޷������鱣����䣬ֻ��������ʱ��ʾ
}

/*
����1��ģ��SPIͨ��
����1����ַ
����2������ֵ
���ܣ�SPIΪ16λͨ�ţ���ƬCS�ź����Ϳ�ʼ���ͣ�����λ���ͺ󣬽�ʱ���ź��ø����õͲ���
      ʱ�����巢����ɺ󣬽�Ƭѡ�ź����߽���ͨ�š�

����2��������ֵ���趨ĳ�еĵ���
����1��ѡ��ĳһ�У�1-8����ַǡΪ0x01-0x08����ֱ����ʮ���ƣ�
����2������ֵ�Ķ�������ʽ����Ӧÿһ��8��LEd������
���ܣ�����ȡģ�����ͼ��ֵ��Ȼ��������
*/
void Max7219_SendByte(uint8_t address, uint8_t data) {
    uint8_t i;
	// ����CS���ţ�ѡ��Max7219
    GPIO_ResetBits(MAX7219_CS_PORT, MAX7219_CS_PIN);


    // ���͵�ַ�ֽ�
    for (i = 0; i < 8; i++) {
        // ����DIN��������λ-д������
        if (address & 0x80) {
            GPIO_SetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        } else {
            GPIO_ResetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        }
        // ����ʱ������ 1-0
        GPIO_SetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // �ӳ�1΢��
        GPIO_ResetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // �ӳ�1΢��
        address <<= 1;
    }

    // ���������ֽ�
    for (i = 0; i < 8; i++) {
        // ����DIN��������λ
        if (data & 0x80) {
            GPIO_SetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        } else {
            GPIO_ResetBits(MAX7219_DIN_PORT, MAX7219_DIN_PIN);
        }
        // ����ʱ������ 1-0
        GPIO_SetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // �ӳ�1΢��
        GPIO_ResetBits(MAX7219_CLK_PORT, MAX7219_CLK_PIN);
        Delay_us(1); // �ӳ�1΢��
        data <<= 1;
    }
    
    // ����CS���ţ�����ͨ��
    GPIO_SetBits(MAX7219_CS_PORT, MAX7219_CS_PIN);
		
}


//���õ��������ȣ�0-15
void Max7219_Bright(uint8_t dt){
		Max7219_SendByte(0X0A,dt);
}

/*
���ܣ�����ĳһ�еġ�x,y�����LED�ƣ�֧���ظ�����ͬһ�У�Ч�����ǡ�
����1���ڼ��У�1-8
����2����ʼLEdλ�ã�1-8
����3������LEdλ�ã�1-8
�� �ܣ�ԭ���Ǽ������[x,y]������Ӧ�Ķ�����ֵ��д���Ӧ�С�
*/
void Max7219_ShowGraph(uint8_t line,uint8_t x,uint8_t y){
		uint8_t tem=pow(2,9-x) - pow(2,8-y);
	  graph[line]|=tem;
		Max7219_SendByte(line,graph[line]);
}


