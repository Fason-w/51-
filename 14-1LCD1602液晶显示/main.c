#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
	LCD_Init();
	LCD_ShowString(1,3,"Fight!");
	LCD_ShowNum(2,1,123,4);
	LCD_ShowSignedNum(2,6,-123,3);
	LCD_ShowHexNum(2,12,0xB7,2);
	LCD_ShowString(1,16,"Welcome to China!");
	while(1)
	{
		LCD_WriteCommand(0x18);
		Delay(300);
	}
}