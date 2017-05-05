#ifndef _LCD_H_
#define _LCD_H_
#include "config.h"
#include "GPIO.h"
#define cspin		12
#define rstpin	14
#define rspin		13
#define sidpin	16
#define sclkpin 19
#define backlightpin 15
#define lcd_select digitalWrite(cspin,LOW)
#define lcd_unselect digitalWrite(cspin,HIGH)
#define lcd_rest digitalWrite(rstpin,LOW)
#define lcd_normal digitalWrite(rstpin,HIGH)
#define lcd_command digitalWrite(rspin,LOW)
#define lcd_data digitalWrite(rspin,HIGH)
#define sid_high	digitalWrite(12,HIGH)
#define sid_low		digitalWrite(12,LOW)
#define sclk_high digitalWrite(11,HIGH)
#define sclk_low	digitalWrite(11,LOW)

#define backlight_on digitalWrite(backlightpin,LOW)
#define backlight_off digitalWrite(backlightpin,HIGH)
void transfer_command(u8);
void transfer_data(u8);
void lcd_address(u8,u8);
void initial_lcd();
void display_string_8x16(u16 ,u16 ,u8*);
void display_single_8x16(u16 ,u16 ,u8*);
void display_graphic_16x16(u8 ,u8 ,u8*);
void display_graphic_32x32(u8 ,u8 ,u8*);
void clear_screen();


sbit Rom_IN=P1^2; //�ֿ�IC �ӿڶ���:Rom_IN �����ֿ�IC ��SI
sbit Rom_OUT=P1^3; //�ֿ�IC �ӿڶ���:Rom_OUT �����ֿ�IC ��SO
sbit Rom_SCK=P1^4; //�ֿ�IC �ӿڶ���:Rom_SCK �����ֿ�IC ��SCK
sbit Rom_CS=P1^5; //�ֿ�IC �ӿڶ���Rom_CS �����ֿ�IC ��CS#
void send_command_to_ROM(u8);
void display_GB2312_string(u8 page,u8 column,u8 *text);
void display_string_5x8(u8 page,u8 column,u8 *text);
#endif