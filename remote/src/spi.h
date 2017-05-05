//========================================================================
//	STCunio Studio�Ա�http://shop112966725.taobao.com
//	STCunio Studio QQȺ:117112538
//	���ߣ�mingbozhu
//	��ϵ��ʽ��13724273732
//	���䣺mingbozhu@yeah.net
//	�޸�����2014.11.7
//	�汾V1.1
//========================================================================

#ifndef	__SPI_H
#define	__SPI_H

#include	"config.h"
#define	SPI_CLOCK_DIV4		0
#define	SPI_CLOCK_DIV8		1
#define	SPI_CLOCK_DIV16		2
#define	SPI_CLOCK_DIV32	  3

#define	SPI_P12_P13_P14_P15	(0<<2)
#define	SPI_P24_P23_P22_P21	(1<<2)
#define	SPI_P54_P40_P41_P43	(2<<2)
#define SPI_MODE0 		0
#define SPI_MODE1 		1
#define SPI_MODE2 		2
#define SPI_MODE3 		3

void 	SPIsetGroup(u8 Group);
void SPIbegin(void);
void SPIsetBitOrder(u8 bitOrder);
void SPIsetClockDivider(u8 rate);
void SPIsetDataMode(u8 mode);
u8 SPItransfer(u8 _data);
void SPIend();
#endif

