#include "findkey.h"
#include "activity.h"
#include "usart.h"

// 频率表对应表    H  L 
signed char HzList[4][4]={{'1','4','7','*'},
													{'2','5','8','0'},
													{'3','6','9','#'},
													{'A','B','C','D'},
													};

unsigned long High[4]={0,0,0,0};//高频四组
unsigned long Low[4]={0,0,0,0};//低频四组
unsigned long HighHz=0;//高频最高
unsigned long LowHz=0;//低频

unsigned long findmaxinarray( unsigned char i,unsigned long Darray[]){//在数组里从第i开始往后对比4个数，查找最大值
	unsigned a=0;
	unsigned long temp=0;
	for(a=i; a < i+4; a++){
		if (temp<Darray[a])
						temp=Darray[a];
	}
	return temp;
}

unsigned long findindexinarray( unsigned long Da,unsigned long Darray[],unsigned char len){
	//查找值Da在数组Darray里的索引位置，len为查找长度，返回值为索引值，未找到返回len
	unsigned i=0;
	for(i=0; i< len; i++){
		if (Darray[i]==Da)
						break;
	}
	return i;
}

void ToGroup(void){//分低频四组，高频四组区间查找极大值，将找到的值存入对应数组
		High[0]=0;
		High[1]=0;
		High[2]=0;
		High[3]=0;
		Low[0]=0;
		Low[1]=0;
		Low[2]=0;
		Low[3]=0;
		//低频组
		Low[0]=findmaxinarray(52,lBufMagArray);//697hz
		Low[1]=findmaxinarray(57,lBufMagArray);//770hz
		Low[2]=findmaxinarray(63,lBufMagArray);//852hz
		Low[3]=findmaxinarray(70,lBufMagArray);//941hz
		//高频组
		High[0]=findmaxinarray(91,lBufMagArray);//1209hz
		High[1]=findmaxinarray(101,lBufMagArray);//1336hz
		High[2]=findmaxinarray(112,lBufMagArray);//1477hz
		High[3]=findmaxinarray(124,lBufMagArray);//1633hz
}

signed char onlyones(unsigned long Array[],unsigned long Number){//确定极大值是否唯一及判断同一组噪音值是否超过阈值
																																	//唯一且噪音值不超过阈值则返回0否则返回非零
	signed char i=0;	
	signed char Nbool=-1;
	for(i=0;i<4;i++){
			if(Number==Array[i]){Nbool++; continue;}
			if(Array[i]>Threshold)return -1;
		
	}
	return Nbool;
}

signed char findval(void){//依照模值数组查找字符
	unsigned char IndexH1=0,IndexL1=0;//高、低组索引
	HighHz=0;
	LowHz=0;
	ToGroup();//将可能的极大值装入数组
	LowHz=findmaxinarray(0,Low);//找低组最大值
	HighHz=findmaxinarray(0,High);//找高组最大值
	if(HighHz<Threshold)return -3;//高组极大值小于噪音返回-3
	if(LowHz<Threshold)return -4;//低组极大值小于噪音，返回-4
	if(onlyones(Low,LowHz))return -1;//低组极大值不唯一返回-1
	if(onlyones(High,HighHz))return -2;//高组极大值不唯一返回-2
	IndexH1=findindexinarray(HighHz,High,4);//取得查表索引值
	IndexL1=findindexinarray(LowHz,Low,4);//取得查表索引值
	return HzList[IndexH1][IndexL1];	//返回查表所得值
	
}

