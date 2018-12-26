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
/*������***************/
#include "led.h"
#include "usart.h"
/**********************/
signed char FindKeyChr=0;//��������2���ҵ��ĵ����ַ�
signed char FindKeyNumber=0;//����2�ҵ����ַ�����
signed char FindKeyStr[FindStrLen]={" "};//������2���ַ������ַ�������
long lBufInArray[NPT];//fft��������   adc�����������16�����
long lBufOutArray[NPT];//fft������� 
unsigned long lBufMagArray[NPT/2];//����fft�õ������ģֵ
unsigned short timerflag=0;//��ʱ����־��������¼adc��������
unsigned char printi=0;//��������õ�ѭ������
ActFlag ActFlag_emu = ActivityOne;//�����־λ��

unsigned long MaxInArray(unsigned long array[]){//��һ�����������ֵ�����ؽ��Ϊ���ֵ

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

 
void GetPowerMag(void)//��ȡfft�õ������ģֵ��������lBufMagArray[NPT/2]��
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
	
	
signed char ChangeFlag(ActFlag *Flag){//���հ���0(PC5)�ı������־λ������key.c����ⲿ�ж���Ӧ�����б����ã�
	switch(*Flag){//��Flag�ж�����л�����
			case NOFlag:
				break;
			case ActivityOne://����1
				PAout(3)=0;//���ƹ��ŵĵ�λ�����Ƶ�ƽ
				TIM3_Int_Init(293,71);//����2�����3401hz ����
				*Flag = ActivityTwo;//��־λ��Ϊ����2
				break;
			case ActivityTwo://����2
				PAout(3)=1;
				TIM_Cmd(TIM3, DISABLE);  //Ϊ����3�رն�ʱ��3 
				*Flag= ActivityThree;//��־λ��Ϊ����3
				Activity3();
			OLED_ShowString(25,3,"Function:3");
			delay_ms(1500);
				break;
			case ActivityThree://����3
				TIM3_Int_Init(24,71);//����1�����41660hz����
				//TIM_Cmd(TIM3, ENABLE);
				PAout(3)=0;
				*Flag= ActivityOne;//��־λ��Ϊ����1
				break;
			default:
				break;
		}
	OLED_Clear(); //����
	return 0;
}

//��Ӧ���ȼ�����>��ʱ��3
signed char DoActivity(ActFlag *Flag){//���ձ�־λִ����Ӧ���񣬽��ڶ�ʱ��3�ж���Ӧ�б����ã��Դ�������Ӧ����Ƶ��
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
	if( timerflag<NPT){//��adc��������256ʱ������������256ʱ��������
						lBufInArray[timerflag]=Get_Adc(ADC_Channel_1)<<16;//adc����
						timerflag++;
					}
					else{
						cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);//fft�任
						GetPowerMag();//��fft���ȡģ
						arctan();//ȡģ����ʾ��������frespectrum.c��
						DisplayColumn();	
						timerflag=0;	//adc������ǹ��㣬�����´β�����					
					}

	return 0;
}

signed char Activity2(void){
	
	LED1=~LED1;
	LED0=1;
		if( timerflag<NPT){//��adc��������256ʱ������������256ʱ��������
							lBufInArray[timerflag]=Get_Adc(ADC_Channel_1)<<16;//adc����
							timerflag++;
						}
		else{ 
			cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);//fft�任
			GetPowerMag();					//��fft���ȡģ
			Display128Dolumn();
			OLED_ShowString16(0,0,FindKeyStr);//��ʾ��ʶ����ַ���
			FindKeyChr=findval();//ȡ��ʶ��Ľ���������ַ���ʶ��ʧ��Ϊ������
			if(FindKeyChr<0)printf(".");
			else {//printf("%c ",FindKeyChr);
					if(!(FindKeyNumber<FindStrLen-2)){
								FindKeyStr[0]=' ';
								FindKeyStr[1]='\0';
								FindKeyNumber=0;
						}
					if(FindKeyNumber<FindStrLen-2)
						{//��ʶ��ɹ����ַ�������δ���
							FindKeyNumber++;//ָ���ַ����е�'\0'
							FindKeyStr[FindKeyNumber]=FindKeyChr;//���µ��ַ����'\0'
							FindKeyStr[FindKeyNumber+1]='\0';//����'\0'
							delay_ms(50);//��ʱ����һ�ΰ�����ʶ���ν��
						}
					}
				timerflag=0;//adc������ǹ��㣬�����´β�����
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

