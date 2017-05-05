//                                 MCU����Ƶ��5.5296MHz
//=========================================================================
//1�������Ҫ���Ĺ���Ƶ�ʣ����޸ı������е�config.hͷ�ļ��� MAIN_Fosc�ĺ궨�壬
//   ��ʱ�������ᱣ��һ�£���������ӳٵĲ�����
//2��������Ϊ2400�������Ҫ���ģ������STC-ISP��Ͳ����ʱ���һ�²���ʵ���Զ�����
//3��IO���ѱ����¶��壬STC15W4K58S4����װΪ64�ţ�����62��IO�ڣ�������8��ģ��ڣ�
//   ��Ȼģ���Ҳ���������ֿڣ�������D��ʾ��ģ����A����ʾ���˶���ר��ΪSTC15W4K58S4
//   �����IO�����㷽���Ժ����պ��ʹ�ã��˶��巽������arduino��
//   ʹ������IO��ʱ���������£�
//   P3.0-P3.7--->D0-D7   Ҳ����ֱ��ʹ��0-7
//   P2.0-P2.7--->D8-D15  Ҳ����ֱ��ʹ��8-15
//   P4.0-P4.7--->D16-D23 Ҳ����ֱ��ʹ��16-23
//   P5.0-P5.7--->D24-D31 Ҳ����ֱ��ʹ��24-31
//   P6.0-P6.7--->D32-D39 Ҳ����ֱ��ʹ��32-39
//   P7.0-P7.7--->D40-D47 Ҳ����ֱ��ʹ��40-47
//   P0.0-P0.7--->D48-D55 Ҳ����ֱ��ʹ��48-55
//   P1.0-P1.7--->D56-D63 Ҳ����ֱ��ʹ��56-63 Ҳ����ʹ��A0-A7
//   ʹ��ģ��IO��ʱ���������£�
//   P1.0-P1.7--->0-7
//4��pinMode��digitalWrite����ʹ������IO���巽����analogRead����ʹ��ģ��IO���巽��
//5�������⺯���÷���ο���STCunio���Ż�����
//=============================================================================
#include "config.h"
#include "usart.h"
#include "GPIO.h"
#include "delay.h"
#include "adc.h"
#include "spi.h"
#include <stdio.h>
#include <string.h>
#include "NRF24L01.H"
#include "12864.h"
#include "pitches.h"
#include "eInterrupt.h"
#include "menu.h"

#define blueled 28
#define redled  29

#define Forward  23
#define Backward 61
#define Left	 62
#define Right    63

#define LKEY  21
#define RKEY  18

#define IRQ  2
#define MISO 11
#define MOSI 10
#define SCK  9
#define CSN  20
#define CE   8

#define CS   12
#define RST  14
#define RS   13
#define SDA  16
#define CLK  19
#define LED_EN 15
#define	note1 NOTE_D4

#define SMALL_FLY 	2
#define BIG_FLY		1

volatile int idata Last_Thro, Last_Yaw, Last_Pitch, Last_Roll;
volatile int idata Thro, Yaw, Pitch, Roll; //
volatile int idata battery;
unsigned char xdata TxBuf[20] = {0};
u8 xdata RxBuf[20] = {0};
u8 data count;
u8 data count1;
int data Angle_X;
int data Angle_Y;
int xdata Angle_X_temp;
int xdata Angle_Y_temp;
u8 bdata key;
sbit key0 = key ^ 0;
sbit key1 = key ^ 1;
sbit key2 = key ^ 2;
u8 bdata menu_status;
sbit menu_main = menu_status ^ 0;
sbit menu_1 = menu_status ^ 1;
sbit menu_2 = menu_status ^ 2;
sbit menu_3 = menu_status ^ 3;
sbit menu_4 = menu_status ^ 4;
char xdata gb;
u8 bai, shi, ge;
u8 FLY_MODE = 0 ;

double _data[10] = {0} ;

u8 flag_once = 1 ;
int count_cls = 0 ;

// int code melody[] = {
// 	NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3,
// 	NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4,
// 	NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
// 	NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4,
// 	NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
// 	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4,
// 	NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_C5, NOTE_C5, NOTE_C5,
// 	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4,
// 	NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_C4,
// 	NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_C4,
// 	NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
// 	NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3
// };

// u8 code noteDurations[] = {
// 	8, 4, 4, 8, 4, 2, 2,
// 	3, 3, 3, 4, 4, 8, 4, 8, 8, 8, 4, 8, 4, 3, 8, 8, 3,
// 	3, 3, 3, 4, 4, 8, 4, 8, 8, 8, 4, 8, 4, 3, 8, 8, 2,
// 	8, 8, 8, 4, 4, 8, 8, 4, 8, 8, 3, 8, 8, 8, 4, 4, 4, 8, 2,
// 	8, 8, 8, 4, 4, 8, 8, 4, 8, 8, 3, 3, 3, 1,
// 	8, 4, 4, 8, 4, 8, 4, 8, 2, 8, 4, 4, 8, 4, 1,
// 	8, 4, 4, 8, 4, 8, 4, 8, 2
// };

void printPWM() {
	int i = 0, ttt ;
	if ( RxBuf[0]  == 0xAA ) {
		// printf( "%d ", RxBuf[0]) ;
		for ( i = 0 ; i < 4 ; i++ ) {
			ttt = 0 ;
			ttt = RxBuf[i * 2 + 2] & 0xFFFF;
			ttt = ttt << 8 | RxBuf[i * 2 + 1];
			// printf( "%d ", ttt) ;
			_data[i] = ttt;
		}
		// printf( "\n", TxBuf[9]);
	}
	memset(RxBuf, 0, 20) ;
}

void showChoice() {
	if ( FLY_MODE == SMALL_FLY )
		display_string_8x16(1, 120, "S");
	if ( FLY_MODE == BIG_FLY )
		display_string_8x16(1, 120, "B");
}

void printACC() {
	int i = 0, ttt ;
	if ( RxBuf[0]  == 0xAB ) {
		// printf( "%d ", RxBuf[0]) ;
		for ( i = 0 ; i < 3 ; i++ ) {
			ttt = 0 ;
			ttt = RxBuf[i * 2 + 2] & 0xFFFF;
			ttt = ttt << 8 | RxBuf[i * 2 + 1];
			// printf( "%f ", (float)ttt/100) ;
			_data[i] = (double)ttt/10 ;
		}
		_data[i] = RxBuf[i * 2 + 1] ;
		// printf( "\n", TxBuf[9]);
	}
	for ( i = 0 ; i < 20 ; i++ ) RxBuf[i] = 0 ;
}

void printGYO() {
	int i = 0, ttt ;
	if ( RxBuf[0]  == 0xAC ) {
		// printf( "%d ", RxBuf[0]) ;
		for ( i = 0 ; i < 3 ; i++ ) {
			ttt = 0 ;
			ttt = RxBuf[i * 2 + 2] & 0xFFFF;
			ttt = ttt << 8 | RxBuf[i * 2 + 1];
			// printf( "%f ", (float)ttt/100) ;
			_data[i] = ttt ;
		}
		// printf( "\n", TxBuf[9]);
	}
	for ( i = 0 ; i < 20 ; i++ ) RxBuf[i] = 0 ;
}

void ShowData_menu(u8 choice)
{
	char tmp[11] = {0} ;
	int i = 0 ;
	int count = 0 ;

	showChoice() ;
	if ( count_cls == 200 ) {
		clear_screen() ;
		count_cls = 0 ;
	}
	count_cls++ ;
	
	if ( choice == 0 ) {
		display_string_8x16(1, 5, "Ax:"); /*�ڵ�3 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(3, 5, "Ay:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(5, 5, "Az:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(7, 5, "Ht:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		count = 4 ;
	} else if ( choice == 1 ) {
		display_string_8x16(1, 5, "Gx:"); /*�ڵ�3 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(3, 5, "Gy:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(5, 5, "Gz:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		count = 3 ;
	} else if ( choice == 2 ) {
		display_string_8x16(1, 5, "F:"); /*�ڵ�3 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(3, 5, "R:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(5, 5, "B:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		display_string_8x16(7, 5, "L:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
		count = 4 ;
	}

	for ( i = 0 ; i < count ; i++ ) {
		sprintf( tmp, "%8.2f", _data[i]) ;
		display_string_8x16(1 + i * 2, 30, tmp) ;
		memset(tmp, 0, 11) ;
	}
}

void ShowStatus_menu(int Thro, int Yaw, int Pitch, int Roll )
{
	char tmp[4] = {0} ;

	showChoice() ;
	display_string_8x16(1, 10, "Thro :"); /*�ڵ�3 ҳ����10 ����ʾ�ַ���*/
	display_string_8x16(3, 10, "Yaw  :"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
	display_string_8x16(5, 10, "Pitch:"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/
	display_string_8x16(7, 10, "Roll :"); /*�ڵ�5 ҳ����10 ����ʾ�ַ���*/

	sprintf( tmp, "%3d", Thro) ;
	display_string_8x16(1, 68, tmp) ;
	memset(tmp, 0, 4) ;

	sprintf( tmp, "%3d", Yaw) ;
	display_string_8x16(3, 68, tmp) ;
	memset(tmp, 0, 4) ;

	sprintf( tmp, "%3d", Pitch) ;
	display_string_8x16(5, 68, tmp) ;
	memset(tmp, 0, 4) ;

	sprintf( tmp, "%3d", Roll) ;
	display_string_8x16(7, 68, tmp) ;
	memset(tmp, 0, 4) ;

}

void ShowThroAtten() {
	display_string_8x16(1, 5, "---------------");
	display_string_8x16(3, 5, "   PULL DOWN   "); /*�ڵ�4 ҳ����16 ����ʾ�ַ���*/
	display_string_8x16(5, 5, "     THRO      ");
	display_string_8x16(7, 5, "---------------");

}

void ShowWait() {
	display_string_8x16(1, 5, "---------------");
	display_string_8x16(3, 5, "     PLEASE    "); /*�ڵ�4 ҳ����16 ����ʾ�ַ���*/
	display_string_8x16(5, 5, "      WAIT     ");
	display_string_8x16(7, 5, "---------------");

}

void ShowLogo() {
	clear_screen();
	display_string_8x16(1, 5, "---------------");
	display_string_8x16(3, 5, "    WELCOME    "); /*�ڵ�4 ҳ����16 ����ʾ�ַ���*/
	display_string_8x16(5, 5, "      CNU      ");
	display_string_8x16(7, 5, "---------------");
}

void main_menu()
{
	showChoice() ;
	display_string_8x16(1, 20, "Remote");
	display_string_8x16(3, 20, "Gyro");
	display_string_8x16(5, 20, "Accelate");
	display_string_8x16(7, 20, "PWM");
}

void choose_menu()
{
	display_string_8x16(1, 20, "CHOOSE MODE");
	display_string_8x16(3, 20, "*Big   Mode");
	display_string_8x16(5, 20, "*Small Mode");
}

void menu_choose() {
	if (menu_main == 1) {
		main_menu();
		key0 = !digitalRead(24);
		key1 = !digitalRead(25);
		key2 = !digitalRead(26);
		switch (key) {
		case 3 ://s8�����£��ϣ�
			clear_gb(gb);
			if (gb != 1)gb = gb - 2;
			display_gb(gb);
			while ((key && 0x03) != 0)
			{
				key0 = !digitalRead(24);
				key1 = !digitalRead(25);
			}
			break;
		case 4 :			//s11�����£�ȷ����
			menu_status = 1 << ((gb + 1) / 2);
			clear_screen();
			break;
		case 6 :			//s10�����£��£�
			clear_gb(gb);
			if (gb != 7)gb = gb + 2;
			display_gb(gb);
			while ((key && 0x06) != 0) {
				key1 = !digitalRead(25);
				key2 = !digitalRead(26);
			}
			break;
		default:	display_gb(gb);
			break;
		}
	} else if (menu_1 == 1) {
		ShowStatus_menu( TxBuf[4], TxBuf[3], TxBuf[1], TxBuf[2] );
		key0 = !digitalRead(24);
		key1 = !digitalRead(25);
		key2 = !digitalRead(26);
		switch (key) {
		case 5:
			menu_status = 0x01;
			clear_screen();
			break;
		default:
			break;
		}
	} else if (menu_2 == 1) {
		printACC() ;
		ShowData_menu(0) ;
		key0 = !digitalRead(24);
		key1 = !digitalRead(25);
		key2 = !digitalRead(26);
		switch (key) {
		case 5:
			menu_status = 0x01;
			clear_screen();
			break;
		default:
			break;
		}
	} else if (menu_3 == 1) {
		printGYO() ;
		ShowData_menu(1) ;
		key0 = !digitalRead(24);
		key1 = !digitalRead(25);
		key2 = !digitalRead(26);
		switch (key) {
		case 5:
			menu_status = 0x01;
			clear_screen();
			break;
		default:
			break;
		}
	} else if (menu_4 == 1) {
		printPWM() ;
		ShowData_menu(2) ;
		key0 = !digitalRead(24);
		key1 = !digitalRead(25);
		key2 = !digitalRead(26);
		switch (key) {
		case 5:
			menu_status = 0x01;
			clear_screen();
			break;
		default:
			break;
		}
	} 
}

void choose_mode() {
	if (menu_main == 1)
	{
		choose_menu();
		key0 = !digitalRead(24);
		key1 = !digitalRead(25);
		key2 = !digitalRead(26);
		switch (key)
		{
		case 3 :
			// shang
			clear_gb(gb);
			if (gb != 3) gb = gb - 2;
			display_gb(gb);
			while ((key && 0x03) != 0) {
				key0 = !digitalRead(24);
				key1 = !digitalRead(25);
			}
			break;
		case 4 :
			// queding
			menu_status = 1 << ((gb + 1) / 2);
			clear_screen();
			break;
		case 6 :
			// xia
			clear_gb(gb);
			if (gb != 5)gb = gb + 2;
			display_gb(gb);
			while ((key && 0x06) != 0) {
				key1 = !digitalRead(25);
				key2 = !digitalRead(26);
			}
			break;
		default:
			display_gb(gb);
			break;
		}

	}
	if (menu_2 == 1) {
		FLY_MODE = BIG_FLY ; // ������
		TxBuf[7] = FLY_MODE ;
		delay_ms(50) ;
	}
	if (menu_3 == 1) {
		FLY_MODE = SMALL_FLY ; // С����
		TxBuf[7] = FLY_MODE ;
		delay_ms(50) ;
	}
}

void pinINIT() {
	Serialbegin(2400, 1, COM1); //��ʼ������1��������Ϊ2400�������STC-ISP��Ͳ����ʱ���һ�²���ʵ���Զ�����
	pinMode(IRQ, pullup);
	pinMode(MISO, pullup);
	pinMode(MOSI, pullup);
	pinMode(SCK, pullup);
	pinMode(CSN, pullup);
	pinMode(CE, pullup);

	SPIsetGroup(SPI_P54_P40_P41_P43);
	SPIsetDataMode(SPI_MODE3);
	SPIbegin();
	SPIsetBitOrder(MSBFIRST);
	SPIsetClockDivider(SPI_CLOCK_DIV8);

	pinMode(redled, OutPP); //IO�ڹ���ģʽ��OutPP�����죩��pullup���ڲ���������highz�����裩��openD����©��
	pinMode(blueled, OutPP);
	pinMode(LKEY, pullup);
	pinMode(RKEY, pullup);

	pinMode(Forward, pullup);
	pinMode(Backward, pullup);
	pinMode(Left, pullup);
	pinMode(Right, pullup);

	pinMode(CS, pullup);
	pinMode(RST, pullup);
	pinMode(RS, pullup);
	pinMode(SDA, pullup);
	pinMode(CLK, pullup);
	pinMode(LED_EN, pullup);


	pinMode(A0, highz); //�������
	pinMode(A1, highz); //�������
	pinMode(A2, highz); //�Ҹ�����
	pinMode(A3, highz); //�Ҹ�����
	pinMode(A4, highz); //��ص�ѹ����

	pinMode(24, pullup);
	pinMode(25, pullup);
	pinMode(26, pullup); // P35

	pinMode(5, pullup); // P36
	pinMode(6, pullup); // P37
	pinMode(7, pullup);

	init_NRF24L01();  //��ʼ������ģ��
}

void smalladjust() {
	// ������΢��
	// ǰ΢��
	if (digitalRead(Forward) == 0) {
		// Last_Pitch-- ;
		TxBuf[7] = 3 ;
		tone(4, note1);
		while (!digitalRead(Forward));
		noTone(4);
	} else TxBuf[7] = 0 ;
	//��΢��
	if (digitalRead(Backward) == 0) {
		// Last_Pitch++ ;
		TxBuf[7] = 4 ;
		tone(4, note1);
		while (!digitalRead(Backward));
		noTone(4);
	} else TxBuf[7] = 0 ;
	//��΢��
	if (digitalRead(Left) == 0) {
		// Last_Roll--;
		TxBuf[7] = 5 ;
		tone(4, note1);
		while (!digitalRead(Left));
		noTone(4);
	} else TxBuf[7] = 0 ;
	//��΢��
	if (digitalRead(Right) == 0) {
		// Last_Roll++;
		TxBuf[7] = 6 ;
		tone(4, note1);
		while (!digitalRead(Right));
		noTone(4);
	} else TxBuf[7] = 0 ;

	key0 = !digitalRead(5);
	key1 = !digitalRead(6);
	key2 = !digitalRead(7);
	// ���ٶȼ�΢��
	switch ( key ) {
		// shang
		case 3:
			TxBuf[7] = 7 ;
			while ((key && 0x03) != 0) {
				key0 = !digitalRead(5);
				key1 = !digitalRead(6);
			}
		break;
		// xia
		case 6:
			TxBuf[7] = 8 ;
			while ((key && 0x06) != 0) {
				key1 = !digitalRead(6);
				key2 = !digitalRead(7);
			}
		break;
		// zuo
		case 1:
			TxBuf[7] = 9 ;
			while ((key && 0x01) != 0) {
				key0 = !digitalRead(5);
			}
		break;
		// you
		case 2:
			TxBuf[7] = 10 ;
			while ((key && 0x02) != 0) {
				key0 = !digitalRead(5);
				key1 = !digitalRead(6);
			}
		break;
		default:
			TxBuf[7] = 0 ;
	}
}

void main()
{
	pinINIT() ;

	//**************************************************
	initial_lcd();
	ShowLogo();
	delay_ms(2000);
	clear_screen(); 

	//****************************************************
	Last_Yaw = analogRead(0) / 4 - 128;
	Last_Pitch = analogRead(3) / 4 - 128;
	Last_Roll = analogRead(2) / 4 - 128;
	setHighPolity(TIMER0);
	Timer0_attachInterrupt(5000);
	
	//**************************************************
	// ģʽѡ��
	menu_status = 1;
	gb = 3;
	while (!FLY_MODE) {
		choose_mode() ;
	}
	// ��λ
	menu_status = 1;
	gb = 1;

	//**************************************************
	// �ȴ�accУ׼
	// while ( TxBuf[0] != 0xCC ) {
	// 	digitalWrite(redled, low);
	// 	ShowWait() ;
	// }
	// digitalWrite(redled, high);

	// ��ѭ������
	while (1) {

		Thro = analogRead(1) / 4;
		Yaw = analogRead(0) / 4;
		Pitch = analogRead(3) / 4;
		Roll = analogRead(2) / 4;
		battery = analogRead(4);

		if (battery <= 574) {
			digitalWrite(redled, high);
			digitalWrite(blueled, low);
		} else {
			digitalWrite(redled, low);
			digitalWrite(blueled, high);
		}

		TxBuf[0]++;
		TxBuf[1] = 128;
		TxBuf[2] = 128;
		TxBuf[3] = 128;

		ShowThroAtten() ;

		// ��������
		if (Thro < 20) {

			if ( flag_once ) {
				clear_screen();
				flag_once = 0 ;
			}

			while (1) {
				Thro = analogRead(1) / 4; //��ȡ4��ҡ��ͨ��ÿ��ͨ����8λ���ݣ�ȡֵ��Χ0-255
				Yaw = analogRead(0) / 4;
				Pitch = analogRead(3) / 4;
				Roll = analogRead(2) / 4;
				battery = analogRead(4); //��ص�ѹ���ͨ�� ����3.7V�����

				// ���˵�����ѡ��
				menu_choose() ;

				if (battery <= 574)
					digitalWrite(blueled, high);
				else if (battery >= 584)
					digitalWrite(blueled, low);

				// ���ţ�TxBuf[4]
				// ������TxBuf[3]
				// ������TxBuf[1]
				// �����TxBuf[2]
				if ((Pitch - Last_Pitch) >= 255) {TxBuf[1] = 255;}
				else if ((Pitch - Last_Pitch) <= 0) {TxBuf[1] = 0;}
				else {TxBuf[1] = Pitch - Last_Pitch;}

				if ((Roll - Last_Roll) >= 255) {TxBuf[2] = 255;}
				else if ((Roll - Last_Roll) <= 0) {TxBuf[2] = 0;}
				else {TxBuf[2] = Roll - Last_Roll;}

				if ((Yaw - Last_Yaw) >= 255) {TxBuf[3] = 255;}
				else if ((Yaw - Last_Yaw) <= 0) {TxBuf[3] = 0;}
				else {TxBuf[3] = Yaw - Last_Yaw;}
				
				TxBuf[4] = Thro;

				// һ��ɲ��
				if (digitalRead(RKEY) == 0) {
					tone(4, note1);
					TxBuf[5] = 1;
					while (!digitalRead(RKEY));
					noTone(4);
				} else TxBuf[5] = 0;

				//
				if (digitalRead(LKEY) == 0) {
					tone(4, note1);
					TxBuf[6] = 1;
					while (!digitalRead(LKEY));
					noTone(4);
				} else TxBuf[6] = 0;

				//�ֶ�У׼���ýǶ�
				smalladjust() ;

				TxBuf[0]++;
			}
		}
	}
}

void timer0_int (void) interrupt TIMER0_VECTOR {
	u8 n;
	count++;
	if (count == 1) {
		TxBuf[9] = 0;
		for (n = 0; n < 9; n++)
			TxBuf[9] = TxBuf[9] + TxBuf[n];
		nRF24L01_TxPacket(TxBuf);//��������
	}
	else if (count == 2) SetRX_Mode();
	else if (count == 3) {
		count1++;
		nRF24L01_RxPacket(RxBuf);//��������
		if (count1 == 128) count1 = 0;
		count = 0;
	}
}