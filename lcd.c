#include<lcd.h>
#define uchar unsigned char
#define uint unsigned int

void Lcd_delayms(uchar yms)
{
	uchar a,b;
	for(a=yms;a>0;a--)
		for(b=110;b>0;b--);
}
//向LCD写入一个字节的命令
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd_delayms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd_delayms(5);	  //保持时间
	LCD1602_E = 0;
}
//向LCD写入一个数据的命令
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd_delayms(1);

	LCD1602_E = 1;   //写入时序
	Lcd_delayms(5);   //保持时间
	LCD1602_E = 0;
}
//LCD初始化
void LcdInit()
{
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}