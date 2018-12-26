#ifndef __FINDKEY_H
#define __FINDKEY_H
#include "activity.h"

#define Threshold 15//背景噪音阈值，超过此值才认为有输入
extern unsigned long lBufMagArray[NPT/2];

signed char diaoyonghanshu(void);

unsigned long findmaxinarray( unsigned char i,unsigned long Darray[]);
unsigned long findindexinarray( unsigned long Da,unsigned long Darray[],unsigned char len);
void ToGroup(void);
signed char findval(void);

#endif
