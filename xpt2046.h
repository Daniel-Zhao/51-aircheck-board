#ifndef	  __XPT2046_H_
#define   __XPT2046_H_
//---包含头文件---//
#include<reg52.h>
#include<intrins.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif//结束条件编译

#ifndef uint
#define uint  unsigned int
#endif

#ifndef ulong
#define ulong  unsigned long
#endif

//---定义使用的IO口---//
sbit DCLK = P3^6;	  //时钟	 
sbit CS   = P3^5;	  //片选
sbit DIN  = P3^4;	  //输入 数据输入端口
sbit DOUT = P3^7;	  //输出

uint Read_AD_Data(uchar cmd);
uint SPI_Read(void);
void SPI_Write(uchar dat);

#endif
