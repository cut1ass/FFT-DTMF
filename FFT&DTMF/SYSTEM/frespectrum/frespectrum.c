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

//从取模结果lBUFMAG[i]中（前128个）挑选出25个值做显示。挑选的原则是：0-4K为主，4K-8K次之，8K-18K最少。将挑选出的25个值赋给COLUMN1[i]
void arctan(void)
{
	  u8 i,temp,a[14]={13,16,19,23,26,29,32,38,45,51,64,77,90,115}; //因为后14个无规律，所以将其位置号列出来
    //u8 j=2;
    for(i=0;i<12;i++)
        { COLUMN1[i]= lBufMagArray[i+1];}  //挑选前面11个（除lBUFMAG[0]外），因为lBUFMAG[0]为直流分量。
    for(i=0;i<15;i++)  //后14个
        {
           temp=a[i];
           COLUMN1[i+12]=lBufMagArray[temp];                
				}	
	 
for(i=0;i<25;i++)  //增益调整
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
//		   	COLUMN1[i]=2*atan(COLUMN1[i]); //用反正切函数来适当压缩较高的模的值,使柱条显示均衡
					 
			 } 
 }
 

