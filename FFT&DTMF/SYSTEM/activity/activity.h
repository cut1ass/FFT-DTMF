#ifndef ACTIVITY_H
#define ACTIVITY_H

#define NPT 256//FFT�������
#define PI2 6.28318530717959//2Pi
#define Fs 3401//ʵ�ʲ���Ƶ��
#define FindStrLen 9//����2���ҳ����ַ���

typedef enum {//�����־λ����
		NOFlag = 0x00,
		ActivityOne =0x01,
		ActivityTwo =0x02,
		ActivityThree= 0x04,

}ActFlag;  		

extern ActFlag ActFlag_emu; //�����־λ��������activity.c��
extern unsigned long lBufMagArray[NPT/2];//����fft�õ������ģֵ��������activity.c��

//void arctan(void);
//void InitBufInArray(void);
void GetPowerMag(void);//��ȡfft�õ������ģֵ��������lBufMagArray[NPT/2]��
signed char ChangeFlag(ActFlag *Flag);//���ⲿ�жϸı������־λ������key0��PC5��
signed char DoActivity(ActFlag *Flag);//ִ�а��ձ�־λִ������
signed char Activity1(void);//����1����
signed char Activity2(void);//����2����
signed char Activity3(void);//����3����

#endif
