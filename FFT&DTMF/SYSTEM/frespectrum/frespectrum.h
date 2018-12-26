#ifndef FRESPECTRUM_H
#define FRESPECTRUM_H

void DisplayColumn(void);
void Display128Dolumn(void);
//从取模结果lBUFMAG[i]中（前128个）挑选出25个值做显示。挑选的原则是：0-4K为主，4K-8K次之，8K-18K最少。将挑选出的25个值赋给COLUMN1[i]
void arctan(void);
#endif
