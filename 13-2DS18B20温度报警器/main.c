#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "Delay.h"

float T,TShow;
unsigned char KeyNum;
int  TLow=0,THigh=0;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TL:");
	LCD_ShowString(2,9,"TH:");
	DS18B20_Convert();
	TLow=AT24C02_ReadByte(0);
	THigh=AT24C02_ReadByte(1);
	if(TLow<-55||THigh>125||TLow>=THigh)
	{
		TLow=20;
		THigh=25;
	}
	Delay(600);
	LCD_ShowSignedNum(2,4,TLow,3);
	LCD_ShowSignedNum(2,12,THigh,3);

	while(1)
	{
	 	KeyNum=Key();
		DS18B20_Convert();
		T=DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			TShow=-T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			TShow=T;
		}
		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
		if(KeyNum)
		{
			if(KeyNum==1)
			{	 
				TLow--;
				if(TLow<-55)TLow++;
			}
			if(KeyNum==2)
			{
				TLow++;
				if(TLow>THigh)TLow--;

			}
			if(KeyNum==3)
			{	 				
				THigh--;
				if(THigh<TLow)THigh++;
			}
			if(KeyNum==4)
			{  				
				THigh++;
				if(THigh>125)THigh--;
			}
			LCD_ShowSignedNum(2,4,TLow,3);
			LCD_ShowSignedNum(2,12,THigh,3);
			AT24C02_WriteByte(0,TLow);
			Delay(5);
			AT24C02_WriteByte(1,THigh);
			Delay(5);
		}
		if(T>THigh)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if(T<TLow)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD_ShowString(1,13,"    ");
		}
	}
}