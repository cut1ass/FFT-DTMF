#ifndef __FINDKEY_H
#define __FINDKEY_H
#include "activity.h"

#define Threshold 15//����������ֵ��������ֵ����Ϊ������
extern unsigned long lBufMagArray[NPT/2];

signed char diaoyonghanshu(void);

unsigned long findmaxinarray( unsigned char i,unsigned long Darray[]);
unsigned long findindexinarray( unsigned long Da,unsigned long Darray[],unsigned char len);
void ToGroup(void);
signed char findval(void);

#endif
