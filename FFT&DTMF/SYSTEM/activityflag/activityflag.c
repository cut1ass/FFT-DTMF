#include "activityflag.h"
#include "key.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "activityflag.h"


signed char ActivityOne(){
				PAout(3)=1;
				TIM3_Int_Init(30,719);//3.33khz 
				OLED_Clear(); 
				Flag= ActivityFlagTwo;
				return 0;

}


				

 void EXTI9_5_IRQHandler(void)
{			
	delay_ms(10);   //消抖			 
	if(KEY0==0)	{
		while(!KEY0);
		switch(Flag){
			case NOFlag:
				break;
			case ActivityOne:
				PAout(3)=1;
				TIM3_Int_Init(30,719);//3.33khz 
				OLED_Clear(); 
				Flag= ActivityTwo;
				break;
			case ActivityTwo:
				PAout(3)=0;
				TIM_Cmd(TIM3, DISABLE);  //使能TIMx外设
				OLED_Clear(); 
				Flag= ActivityThree;
				break;
			case ActivityThree:
				TIM3_Int_Init(24,71);//40khz 
				PAout(3)=0;
				OLED_Clear(); 
				Flag= ActivityOne;
				break;
			default:
				break;
		
		}
		LED0=!LED0;
	}
 	 EXTI_ClearITPendingBit(EXTI_Line5);    //清除LINE5上的中断标志位  
}

