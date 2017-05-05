//========================================================================
//	STCunio Studio�Ա�http://shop112966725.taobao.com
//	STCunio Studio QQȺ:117112538
//	���ߣ�mingbozhu
//	��ϵ��ʽ��13724273732
//	���䣺mingbozhu@yeah.net
//	�޸�����2014.11.7
//	�汾V1.1
//========================================================================


#include	"spi.h"
#include  "GPIO.h"
void 	SPIsetGroup(u8 Group)
{
	AUXR1 = (AUXR1 & ~(3<<2)) | Group;	
}
void	SPIbegin(void)
{
	SPCTL |=  (1<<6);//SPI enable	
	SPCTL |=  (1<<7);	//enable SS, conform Master or Slave by SS pin.
	SPCTL |=  (1<<4);	//master	
	
}
void SPIsetBitOrder(u8 bitOrder)
{
		if(bitOrder==LSBFIRST)SPCTL |= ~(1<<5);	//LSB first
		else SPCTL &= ~(1<<5);	//MSB first			
}
void SPIsetClockDivider(u8 rate)
{
		SPCTL = (SPCTL & ~3) | (rate & 3);					//set speed

}
//ģʽ0 �����ز��� �½�����λ SCK����ʱΪ0 SPI_MODE0 SPCTL &= ~(1<<3);SPCTL  &= ~(1<<2)
//ģʽ1 ��������λ �½��ز���							 SPI_MODE1 SPCTL &= ~(1<<3);SPCTL  |=  (1<<2)
//ģʽ2 �½��ز��� ��������λ SCK����ʱΪ1 SPI_MODE2 SPCTL |=  (1<<3);SPCTL  &= ~(1<<2)
//ģʽ3 �½�����λ �����ز���							 SPI_MODE2 SPCTL |=  (1<<3);SPCTL  |=  (1<<2)
void SPIsetDataMode(u8 mode)
{
		SPCTL =(SPCTL & ~(3<<2))|(mode<<2);
}
u8 SPItransfer(u8 _data)
{
	  SPDAT=_data;
		while (!(SPSTAT & 0x80));
		SPSTAT &=0x80;
    return SPDAT;
}
void SPIend()
{
      SPCTL &= ~(1<<6);
}