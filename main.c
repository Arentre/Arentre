#include "stm32f10x.h"               
#include "delay.h"
#include "OLED.h"
#include "MOTOR.h"

int main(void)
{
	OLED_Init(); 
  Motor_Init();
OLED_ShowString(1,4,"Speed");
	  
	while(1)
	{
                                                                                              Motor_SetSpeed(20);
    OLED_ShowNum(2,2,20,2);
    Delay_s(2);
    Motor_SetSpeed(60);   
    OLED_ShowNum(2,2,60,2);
    Delay_s(2);
    Motor_SetSpeed(80);
   OLED_ShowNum(2,2,80,2);
    Delay_s(2);  
      Motor_SetSpeed(0);
     Delay_s(4);  
		Motor_SetSpeed(-20);
    OLED_ShowSignedNum(2,2,-20,2);
    Delay_s(2);  	
    Motor_SetSpeed(-60);
   OLED_ShowSignedNum(2,2,-60,2);
    Delay_s(2);  	
    Motor_SetSpeed(-80);
    OLED_ShowSignedNum(2,2,-80,2);
    Delay_s(2);  	
        Motor_SetSpeed(0);
     Delay_s(4);  
	}
}

