#include <REGX52.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  *@brief	I2C开始
  *@param	无
  *@retval	无
  */
void I2C_Start(void)
{
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
  *@brief	I2C停止
  *@param	无
  *@retval	无
  */
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/**
  *@brief	 I2C发送一个字节
  *@param	 Byte 要发送的字节
  *@retval	 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}	
}

/**
  *@brief	 I2C接收一个字节
  *@param	 无
  *@retval	 要接收的一个字节数据
  */
unsigned char I2C_ReciveByte(void)
{
	unsigned char i, Byte=0x00;
	I2C_SDA=1;//主机释放SDA

	for(i=0; i<8; i++)
	{
		I2C_SCL=1;
	 	if(I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL=0;
	}
	return Byte;
}

/**
  *@brief	 I2C发送应答
  *@param	 AckBit 发送的应答位 0应答/I非应答
  *@retval	 无
  */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
  *@brief	 I2C接收应答
  *@param	 无
  *@retval	 接收的应答位 0应答/I非应答
  */

unsigned char I2C_ReciveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;//主机释放SDA
	I2C_SCL=1;
	AckBit=I2C_SDA;
	//if(I2C_SDA)AckBit=I;
	I2C_SCL=0;
	return AckBit;
}