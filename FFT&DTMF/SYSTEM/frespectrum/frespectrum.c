#include "frespectrum.h"
#include "oled.h"
#include "activity.h"
#include "math.h"
#include "delay.h"

u16 COLUMN1[25];


void DisplayColumn(void)
{
	u8 i,j=2;

	for(i=0;i<25;i++){
		Draw_Colmun_OLED(j,0);
		Draw_Colmuns_OLED(j+1,j+5,COLUMN1[i]);
		j=j+5;	 		  		     
	 }
	OLED_FlushOledBuff();	 
	delay_ms(50); 
}
void Display128Dolumn(void)
{
	u8 i;

//	for(i=2;i<128;i+=2){
//		Draw_Colmun_OLED(i,lBufMagArray[i/2]);
//	Draw_Colmun_OLED(i+1,0); 		
//	 }
		for(i=1;i<128;i++){
		Draw_Colmun_OLED(i,lBufMagArray[i]);	
	 }
	OLED_FlushOledBuff();	 
	delay_ms(10); 
}

//��ȡģ���lBUFMAG[i]�У�ǰ128������ѡ��25��ֵ����ʾ����ѡ��ԭ���ǣ�0-4KΪ����4K-8K��֮��8K-18K���١�����ѡ����25��ֵ����COLUMN1[i]
void arctan(void)
{
	  u8 i,temp,a[14]={13,16,19,23,26,29,32,38,45,51,64,77,90,115}; //��Ϊ��14���޹��ɣ����Խ���λ�ú��г���
    //u8 j=2;
    for(i=0;i<12;i++)
        { COLUMN1[i]= lBufMagArray[i+1];}  //��ѡǰ��11������lBUFMAG[0]�⣩����ΪlBUFMAG[0]Ϊֱ��������
    for(i=0;i<15;i++)  //��14��
        {
           temp=a[i];
           COLUMN1[i+12]=lBufMagArray[temp];                
				}	
	 
for(i=0;i<25;i++)  //�������
   {    
//	  COLUMN1[i]=COLUMN1[i]*4;

			 if(COLUMN1[i]==0) 
	   {COLUMN1[i]=2;}
			 else if((COLUMN1[i]<5)&&(COLUMN1[i]>0)) 
	   {COLUMN1[i]=COLUMN1[i]+7;}
			 else if((COLUMN1[i]>=5)&&(COLUMN1[i]<10))
	   {COLUMN1[i]=COLUMN1[i]+5;}
			 else if((COLUMN1[i]>=10)&&(COLUMN1[i]<15))
	   {COLUMN1[i]=COLUMN1[i]+4;} 
			 else if(COLUMN1[i]>=64) 
	   {COLUMN1[i]=63;} 			 
			 else if((COLUMN1[i]>=55)&&(COLUMN1[i]<=63)) 
	   {COLUMN1[i]=COLUMN1[i]-8;}
//		   	COLUMN1[i]=2*atan(COLUMN1[i]); //�÷����к������ʵ�ѹ���ϸߵ�ģ��ֵ,ʹ������ʾ����
					 
			 } 
 }
 

