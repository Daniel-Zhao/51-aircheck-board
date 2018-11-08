#include <xpt2046.h>

#define uchar unsigned char
#define uint unsigned int
//开发板上AD转换模块引脚设置

/*void SPI_Start()//SPI 初始化
{
	DCLK=0;
	CS=1;
	DIN=1;
	DCLK=1;
	CS=0;
}*/

void SPI_Write(uchar dat)//使用SPI写入数据,写入一个字节（八位），先搞最高位
{
	uchar i;
	DCLK=0;
	for(i=0;i<8;i++)
	{
		DIN=dat>>7;//放置最高位  先传送最高位
		dat<<=1;
		DCLK=0;//上升沿放入数据，根据时序图，时序一直变化
		DCLK=1;		
	}
}
uint SPI_Read()//使用SPI读取数据，返回dat
{
	uint i,dat=0;
	DCLK=0;
	for(i=0;i<12;i++)//从低位开始接收
	{
		dat<<=1;
		DCLK=1;
		DCLK=0;
		dat|=DOUT;	
	}
	return dat;
}
uint Read_AD_Data(uchar cmd)//先写入，再读取
{
	uchar i;
	uint AD_Value;
	DCLK = 0;		  //根据时序图，讲时钟片选拉低
	CS  = 0;
	SPI_Write(cmd);	   //写入
	for(i=6; i>0; i--); 	//延时等待转换结果（时序图上有延时）
	DCLK = 1;	  //发送一个时钟周期，清除BUSY
	_nop_();
	_nop_();
	DCLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read(); //将读取的数值保存在定义的变量里，函数末尾返回变量
	CS = 1;				  //片选拉高（关闭）
	return AD_Value;	
}

