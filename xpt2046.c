#include <xpt2046.h>

#define uchar unsigned char
#define uint unsigned int
//��������ADת��ģ����������

/*void SPI_Start()//SPI ��ʼ��
{
	DCLK=0;
	CS=1;
	DIN=1;
	DCLK=1;
	CS=0;
}*/

void SPI_Write(uchar dat)//ʹ��SPIд������,д��һ���ֽڣ���λ�����ȸ����λ
{
	uchar i;
	DCLK=0;
	for(i=0;i<8;i++)
	{
		DIN=dat>>7;//�������λ  �ȴ������λ
		dat<<=1;
		DCLK=0;//�����ط������ݣ�����ʱ��ͼ��ʱ��һֱ�仯
		DCLK=1;		
	}
}
uint SPI_Read()//ʹ��SPI��ȡ���ݣ�����dat
{
	uint i,dat=0;
	DCLK=0;
	for(i=0;i<12;i++)//�ӵ�λ��ʼ����
	{
		dat<<=1;
		DCLK=1;
		DCLK=0;
		dat|=DOUT;	
	}
	return dat;
}
uint Read_AD_Data(uchar cmd)//��д�룬�ٶ�ȡ
{
	uchar i;
	uint AD_Value;
	DCLK = 0;		  //����ʱ��ͼ����ʱ��Ƭѡ����
	CS  = 0;
	SPI_Write(cmd);	   //д��
	for(i=6; i>0; i--); 	//��ʱ�ȴ�ת�������ʱ��ͼ������ʱ��
	DCLK = 1;	  //����һ��ʱ�����ڣ����BUSY
	_nop_();
	_nop_();
	DCLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read(); //����ȡ����ֵ�����ڶ���ı��������ĩβ���ر���
	CS = 1;				  //Ƭѡ���ߣ��رգ�
	return AD_Value;	
}

