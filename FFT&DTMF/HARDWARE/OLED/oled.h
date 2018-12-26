//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PD6��SCL��
//              D1   ��PD7��SDA��
//              RES  ��PD4
//              DC   ��PD5
//              CS   ��PD3               
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------  					   
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOC,GPIO_Pin_13)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOC,GPIO_Pin_13)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_2)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOC,GPIO_Pin_2)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_0)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOC,GPIO_Pin_0)

//PC0~7,��Ϊ������
//#define DATAOUT(x) GPIO_Write(GPIOC,x);//���  
//ʹ��4�ߴ��нӿ�ʱʹ�� 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_10)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOC,GPIO_Pin_10)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_3)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOC,GPIO_Pin_3)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

extern unsigned char  OledBuff[8][128];
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,char chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, signed char *p);	 
void OLED_ShowChar16(u8 x,u8 y,char chr);
void OLED_ShowString16(u8 x,u8 y,signed char *chr);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void Draw_Colmuns_OLED(u8 x,u8 y,u8 no);
void Draw_Colmun_OLED(unsigned char x,unsigned char high);
void OLED_FlushOledBuff(void);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
#endif  
