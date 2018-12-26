#ifndef ACTIVITY_H
#define ACTIVITY_H

#define NPT 256//FFT处理点数
#define PI2 6.28318530717959//2Pi
#define Fs 3401//实际采样频率
#define FindStrLen 9//任务2查找出的字符串

typedef enum {//任务标志位类型
		NOFlag = 0x00,
		ActivityOne =0x01,
		ActivityTwo =0x02,
		ActivityThree= 0x04,

}ActFlag;  		

extern ActFlag ActFlag_emu; //任务标志位，定义在activity.c中
extern unsigned long lBufMagArray[NPT/2];//储存fft得到结果的模值，定义在activity.c中

//void arctan(void);
//void InitBufInArray(void);
void GetPowerMag(void);//获取fft得到结果的模值，储存在lBufMagArray[NPT/2]里
signed char ChangeFlag(ActFlag *Flag);//以外部中断改变任务标志位。按键key0（PC5）
signed char DoActivity(ActFlag *Flag);//执行按照标志位执行任务
signed char Activity1(void);//任务1内容
signed char Activity2(void);//任务2内容
signed char Activity3(void);//任务3内容

#endif
