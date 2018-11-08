#include<lcd.h>
#define uchar unsigned char
#define uint unsigned int

void Lcd_delayms(uchar yms)
{
	uchar a,b;
	for(a=yms;a>0;a--)
		for(b=110;b>0;b--);
}
//��LCDд��һ���ֽڵ�����
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	Lcd_delayms(1);		//�ȴ������ȶ�

	LCD1602_E = 1;	          //д��ʱ��
	Lcd_delayms(5);	  //����ʱ��
	LCD1602_E = 0;
}
//��LCDд��һ�����ݵ�����
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd_delayms(1);

	LCD1602_E = 1;   //д��ʱ��
	Lcd_delayms(5);   //����ʱ��
	LCD1602_E = 0;
}
//LCD��ʼ��
void LcdInit()
{
 	LcdWriteCom(0x38);  //����ʾ
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}