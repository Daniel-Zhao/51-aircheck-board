#ifndef	  __XPT2046_H_
#define   __XPT2046_H_
//---����ͷ�ļ�---//
#include<reg52.h>
#include<intrins.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif//������������

#ifndef uint
#define uint  unsigned int
#endif

#ifndef ulong
#define ulong  unsigned long
#endif

//---����ʹ�õ�IO��---//
sbit DCLK = P3^6;	  //ʱ��	 
sbit CS   = P3^5;	  //Ƭѡ
sbit DIN  = P3^4;	  //���� ��������˿�
sbit DOUT = P3^7;	  //���

uint Read_AD_Data(uchar cmd);
uint SPI_Read(void);
void SPI_Write(uchar dat);

#endif
