#include "activity.h"
#include "timer.h"
#include "math.h"
#include "key.h"
#include "adc.h"
#include "oled.h"
#include "delay.h"
#include "table_fft.h"
#include "stm32_dsp.h"
#include "findkey.h"
#include "frespectrum.h"
/*调试用***************/
#include "led.h"
#include "usart.h"
/**********************/
signed char FindKeyChr=0;//储存任务2查找到的单个字符
signed char FindKeyNumber=0;//任务2找到的字符个是
signed char FindKeyStr[FindStrLen]={" "};//将任务2的字符连成字符串储存
long lBufInArray[NPT];//fft输入数组   adc采样结果左移16后存入
long lBufOutArray[NPT];//fft输出数组 
unsigned long lBufMagArray[NPT/2];//储存fft得到结果的模值
unsigned short timerflag=0;//定时器标志。用来记录adc采样次数
unsigned char printi=0;//调试输出用的循环变量
ActFlag ActFlag_emu = ActivityOne;//任务标志位，

unsigned long MaxInArray(unsigned long array[]){//求一个数组中最大值，返回结果为最大值

	unsigned long max = array[1];
	int size = sizeof(array) / sizeof(array[0]);
	int i = 0;
	for ( i = 1; i < size; i++)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	return max;

}

 
void GetPowerMag(void)//获取fft得到结果的模值，储存在lBufMagArray[NPT/2]里
{
     signed short lX,lY;
     float X,Y,Mag;
     unsigned short i;
     for(i=0; i<NPT/2; i++)
     {
         lX  = (lBufOutArray[i] << 16) >> 16;
         lY  = (lBufOutArray[i] >> 16);
         X = NPT * ((float)lX) / 32768;
         Y = NPT * ((float)lY) / 32768;
         Mag = sqrt(X * X + Y * Y) / NPT;
         if(i == 0)
             lBufMagArray[i] = (unsigned long)(Mag * 32768);
         else
             lBufMagArray[i] = (unsigned long)(Mag * 65536);
     }
}
	
	
signed char ChangeFlag(ActFlag *Flag){//依照按键0(PC5)改变任务标志位（仅在key.c里的外部中断响应函数中被调用）
	switch(*Flag){//按Flag判断如何切换任务
			case NOFlag:
				break;
			case ActivityOne://任务1
				PAout(3)=0;//控制功放的电位器控制电平
				TIM3_Int_Init(293,71);//任务2所需的3401hz 采样
				*Flag = ActivityTwo;//标志位改为任务2
				break;
			case ActivityTwo://任务2
				PAout(3)=1;
				TIM_Cmd(TIM3, DISABLE);  //为任务3关闭定时器3 
				*Flag= ActivityThree;//标志位改为任务3
				Activity3();
			OLED_ShowString(25,3,"Function:3");
			delay_ms(1500);
				break;
			case ActivityThree://任务3
				TIM3_Int_Init(24,71);//任务1所需的41660hz采样
				//TIM_Cmd(TIM3, ENABLE);
				PAout(3)=0;
				*Flag= ActivityOne;//标志位改为任务1
				break;
			default:
				break;
		}
	OLED_Clear(); //清屏
	return 0;
}

//响应优先级按键>定时器3
signed char DoActivity(ActFlag *Flag){//按照标志位执行响应任务，仅在定时器3中断响应中被调用，以此满足相应采样频率
		u8 re=0;
		switch(*Flag){
					case NOFlag:
						re=0;
						break;
					case ActivityOne:
						re=Activity1();
						break;
					case ActivityTwo:
						re=Activity2();
						break;
					case ActivityThree:
						re=Activity3();
						break;
					default:
						re=0;
						break;
				}
			return re;
}

signed char Activity1(void){
	LED1=1;
	LED0=~LED0;
	if( timerflag<NPT){//当adc采样不够256时继续采样，够256时则处理数据
						lBufInArray[timerflag]=Get_Adc(ADC_Channel_1)<<16;//adc采样
						timerflag++;
					}
					else{
						cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);//fft变换
						GetPowerMag();//对fft结果取模
						arctan();//取模并显示，函数在frespectrum.c中
						DisplayColumn();	
						timerflag=0;	//adc采样标记归零，继续下次采样，					
					}

	return 0;
}

signed char Activity2(void){
	
	LED1=~LED1;
	LED0=1;
		if( timerflag<NPT){//当adc采样不够256时继续采样，够256时则处理数据
							lBufInArray[timerflag]=Get_Adc(ADC_Channel_1)<<16;//adc采样
							timerflag++;
						}
		else{ 
			cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);//fft变换
			GetPowerMag();					//对fft结果取模
			Display128Dolumn();
			OLED_ShowString16(0,0,FindKeyStr);//显示已识别的字符串
			FindKeyChr=findval();//取出识别的结果（单个字符，识别失败为负数）
			if(FindKeyChr<0)printf(".");
			else {//printf("%c ",FindKeyChr);
					if(!(FindKeyNumber<FindStrLen-2)){
								FindKeyStr[0]=' ';
								FindKeyStr[1]='\0';
								FindKeyNumber=0;
						}
					if(FindKeyNumber<FindStrLen-2)
						{//当识别成功且字符串长度未溢出
							FindKeyNumber++;//指向字符串中的'\0'
							FindKeyStr[FindKeyNumber]=FindKeyChr;//用新的字符替代'\0'
							FindKeyStr[FindKeyNumber+1]='\0';//补上'\0'
							delay_ms(50);//延时避免一次按键音识别多次结果
						}
					}
				timerflag=0;//adc采样标记归零，继续下次采样，
		}
		return 0;
}


signed char Activity3(void){
	
    OLED_Clear();
	LED1=~LED1;
	LED0=~LED0;//	
	timerflag=0;
	return 0;
}

