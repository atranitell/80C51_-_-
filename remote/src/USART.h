//========================================================================
//	STCunio Studio�Ա�http://shop112966725.taobao.com
//	STCunio Studio QQȺ:117112538
//	���ߣ�mingbozhu
//	��ϵ��ʽ��13724273732
//	���䣺mingbozhu@yeah.net
//	�޸�����2014.11.7
//	�汾V1.1
//========================================================================
#ifndef __USART_H
#define __USART_H	 

#include	"config.h"
#define COM1 1
#define COM2 2
#define COM3 3
#define COM4 4

#define	UART_8bit_BRTx	(1<<6)	//8λ����,�ɱ䲨����
#define	UART1_SW_P30_P31	0
#define	BRT_Timer2	2

void Serialbegin(u32 baud,u8 sum,...);
//char _getkey (void);
char putchar (char c);
void putbuf (char c);
void print(char comx);

#endif

