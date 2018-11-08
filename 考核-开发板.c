#include <reg52.h>
#include "lcd.h"
#include <ds1302.h>
#include <xpt2046.h>

#define uchar unsigned char
#define uint unsigned int
#define Key_juzhen P1
//空气检测
sbit k1=P3^1;    //模式(检测或设置)k1
sbit k2=P3^2;    //加
sbit k3=P3^3;    //减

sbit beep=P1^5;
uchar mode=0;
uchar temp;
uchar temph=5;
uchar flag;
//时钟设置
sbit k4=P3^0;
uchar SetState,SetPlace;
uchar KeyValue; 
uchar TIME[]={0, 0, 0x13, 0x01, 0x09, 0x06, 0x18};
//延时函数(1毫秒)
void delayms(uchar xms)
{
	uchar i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
//空气检测模块
void key_pros()//按键处理函数（空气检测）
{
	if(k1==0)
	{
		delayms(100);
		if(k1==0)
		{
			mode++;
			flag=0;
			if(mode==2)
			{
				mode=0;
				flag=1;
			}
			while(!k1);	
		}
	}
	if(mode==1)//k1按下一次
	{
		if(k2==0)
		{
			delayms(100);
			if(k2==0)
			{
				temph+=1;
			}
			while(!k2);	
		}
		
		if(k3==0)
		{
			delayms(100);
			if(k3==0)
			{
				temph-=1;
				if(temph<=0)
				temph=0;
			}
			while(!k3);
		}
	}
}

void data_pros()	//数据处理函数	空气值0-500，三位数
{
	uchar tempbuf[3],temp_buf[3],i;

	tempbuf[0]=temp/100+0x30;		//百位
	tempbuf[1]=temp%100/10+0x30;	//十位			
	tempbuf[2]=temp%100%10+0x30;	//个位
	
	temp_buf[0]=temph/100+0x30;
	temp_buf[1]=temph%100/10+0x30;				
	temp_buf[2]=temph%100%10+0x30;

	for(i=0;i<3;i++)
	{
		LcdWriteCom(0x80+i);
		LcdWriteData(tempbuf[i]);
	}

	for(i=0;i<3;i++)
	{
		LcdWriteCom(0xc0+i);
		LcdWriteData(temp_buf[i]);
	}
}

void sound()
{
	uchar i=100;
	while(i--)
	{
		beep=~beep;
		delayms(10000);
	}
}

void baojinpros()	//报警处理
{
	if(temp>=temph&&flag==1)
	{
		sound();//蜂鸣器叫
	}
	else
	{	
		beep=1;//  蜂鸣器不叫
	}
}

//时钟显示模块

void LcdDisplay()
{
	LcdWriteCom(0x84);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+TIME[6]/16);			//年
	LcdWriteData('0'+(TIME[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);			//月
	LcdWriteData('0'+(TIME[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);			//日
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+(TIME[5]&0x07));	//星期

	LcdWriteCom(0x88+0X40);
	LcdWriteData('0'+TIME[2]/16);				//时
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData('-');
	LcdWriteData('0'+TIME[1]/16);				//分
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData('-');
	LcdWriteData('0'+TIME[0]/16);				//秒
	LcdWriteData('0'+(TIME[0]&0x0f));	
}

void Int0Configuration()// 配置外部中断0,无输入无输出
{
	//设置INT0
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。
	EA=1;//打开总中断	
}

void Int0() interrupt 0	//外部中断0 中断函数,无输入无输出	 
{
	delayms(10);
	if(k4==0)//如果要按下S3进入时钟设置，那么将setstate翻转，setplace置零（便于选择改变什么）
	{
		delayms(100);
		if(k4==0)
		{
			SetState=~SetState;
			SetPlace=0;
			Ds1302Init();			
		}	
	}
}


void main()
{
	//uchar i;
	beep=0;
	Int0Configuration();
	LcdInit();	//lcd初始化
	Ds1302Init(); //时钟芯片初始化
	while(1)
	{		
		if(SetState==0)
		{
			Ds1302ReadTime();
		}
		LcdDisplay();//时间显示
		key_pros();//按键处理函数
		data_pros();//数据处理函数
		baojinpros(); //报警处理（蜂鸣器动态）
		temp = Read_AD_Data(0xE4);  //读取这个通道的值 A2A1A0=	根据数据手册 X+通道		
	}
	
}
