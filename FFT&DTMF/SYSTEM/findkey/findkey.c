#include "findkey.h"
#include "activity.h"
#include "usart.h"

// Ƶ�ʱ��Ӧ��    H  L 
signed char HzList[4][4]={{'1','4','7','*'},
													{'2','5','8','0'},
													{'3','6','9','#'},
													{'A','B','C','D'},
													};

unsigned long High[4]={0,0,0,0};//��Ƶ����
unsigned long Low[4]={0,0,0,0};//��Ƶ����
unsigned long HighHz=0;//��Ƶ���
unsigned long LowHz=0;//��Ƶ

unsigned long findmaxinarray( unsigned char i,unsigned long Darray[]){//��������ӵ�i��ʼ����Ա�4�������������ֵ
	unsigned a=0;
	unsigned long temp=0;
	for(a=i; a < i+4; a++){
		if (temp<Darray[a])
						temp=Darray[a];
	}
	return temp;
}

unsigned long findindexinarray( unsigned long Da,unsigned long Darray[],unsigned char len){
	//����ֵDa������Darray�������λ�ã�lenΪ���ҳ��ȣ�����ֵΪ����ֵ��δ�ҵ�����len
	unsigned i=0;
	for(i=0; i< len; i++){
		if (Darray[i]==Da)
						break;
	}
	return i;
}

void ToGroup(void){//�ֵ�Ƶ���飬��Ƶ����������Ҽ���ֵ�����ҵ���ֵ�����Ӧ����
		High[0]=0;
		High[1]=0;
		High[2]=0;
		High[3]=0;
		Low[0]=0;
		Low[1]=0;
		Low[2]=0;
		Low[3]=0;
		//��Ƶ��
		Low[0]=findmaxinarray(52,lBufMagArray);//697hz
		Low[1]=findmaxinarray(57,lBufMagArray);//770hz
		Low[2]=findmaxinarray(63,lBufMagArray);//852hz
		Low[3]=findmaxinarray(70,lBufMagArray);//941hz
		//��Ƶ��
		High[0]=findmaxinarray(91,lBufMagArray);//1209hz
		High[1]=findmaxinarray(101,lBufMagArray);//1336hz
		High[2]=findmaxinarray(112,lBufMagArray);//1477hz
		High[3]=findmaxinarray(124,lBufMagArray);//1633hz
}

signed char onlyones(unsigned long Array[],unsigned long Number){//ȷ������ֵ�Ƿ�Ψһ���ж�ͬһ������ֵ�Ƿ񳬹���ֵ
																																	//Ψһ������ֵ��������ֵ�򷵻�0���򷵻ط���
	signed char i=0;	
	signed char Nbool=-1;
	for(i=0;i<4;i++){
			if(Number==Array[i]){Nbool++; continue;}
			if(Array[i]>Threshold)return -1;
		
	}
	return Nbool;
}

signed char findval(void){//����ģֵ��������ַ�
	unsigned char IndexH1=0,IndexL1=0;//�ߡ���������
	HighHz=0;
	LowHz=0;
	ToGroup();//�����ܵļ���ֵװ������
	LowHz=findmaxinarray(0,Low);//�ҵ������ֵ
	HighHz=findmaxinarray(0,High);//�Ҹ������ֵ
	if(HighHz<Threshold)return -3;//���鼫��ֵС����������-3
	if(LowHz<Threshold)return -4;//���鼫��ֵС������������-4
	if(onlyones(Low,LowHz))return -1;//���鼫��ֵ��Ψһ����-1
	if(onlyones(High,HighHz))return -2;//���鼫��ֵ��Ψһ����-2
	IndexH1=findindexinarray(HighHz,High,4);//ȡ�ò������ֵ
	IndexL1=findindexinarray(LowHz,Low,4);//ȡ�ò������ֵ
	return HzList[IndexH1][IndexL1];	//���ز������ֵ
	
}

