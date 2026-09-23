#include <REGX52.H>
#include "OneWire.h"


#define DS18B20_SKIP_RAM			0xCC
#define DS18B20_CONVERT				0x44
#define DS18B20_READ_SCRATCHPAD		0xBE

void DS18B20_Convert(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_RAM);
	OneWire_SendByte(DS18B20_CONVERT);
}

float  DS18B20_ReadT(void)
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_RAM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB=OneWire_ReceiveByte();
	TMSB=OneWire_ReceiveByte();
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0;
	return T;
}