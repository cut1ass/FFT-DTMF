#include "led.h"
#include "usart.h"
#include "timer.h"
#include "key.h"
#include "adc.h"
#include "oled.h"
#include "delay.h"

int main(void){
	    
		delay_init();	    	 //��ʱ������ʼ��	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
		uart_init(921600);	 	//���ڳ�ʼ��Ϊ
		OLED_Init();//��ʼ��
	    	    OLED_ShowCHinese(29,0,0);//
		OLED_ShowCHinese(47,0,1);//
		OLED_ShowCHinese(65,0,2);//
		OLED_ShowCHinese(83,0,3);//
		
		OLED_ShowCHinese(29,2,4);//
		OLED_ShowCHinese(47,2,5);//
		OLED_ShowCHinese(65,2,3);//
		OLED_ShowCHinese(83,2,6);//
		
	    OLED_ShowCHinese(11,4,7); //1
		OLED_ShowCHinese(29,4,8); //2	 
	    OLED_ShowString(47,4,":");
		OLED_ShowCHinese(65,4,9);
		OLED_ShowCHinese(83,4,10);
		OLED_ShowCHinese(101,4,11);
		
		OLED_ShowString(25,6,"2018/12/07");
		delay_ms(1000);
		delay_ms(1000);
		LED_Init();
		KEY_Init();//��ʼ��������Ӧioģʽ
		Adc_Init();//ADC��ʼ��
		EXTIX_Init();//�ⲿ�жϣ�������
		TIM3_Int_Init(24,71);//41666hz  72m/��(24)*(71+1)��
//		delay_ms(250); //

	    
		while(1);	
}	
