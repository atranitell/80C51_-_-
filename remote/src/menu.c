#include"12864.h"

void draw_curve(u8 x, u8 y)
{
	u8 i, j, k;
	lcd_select;
	i = 8 - y / 8;
	j = y % 8;


	for (k = 1; k <= 8; k++)
	{
		lcd_address(k, x); //������߸���֮ǰ��ͬX����ĵ�
		transfer_data(0x00); //
	}

	lcd_address(i, x + 3);
	transfer_data(0x00); //
	lcd_address(i, x + 2);
	transfer_data(0x00); //
	lcd_address(i, x + 1);
	transfer_data(0x00); //

	lcd_address(i, x);
	transfer_data(0x80 >> j); //
	lcd_unselect;

}

void display_gb(u8 page)
{

	display_string_8x16(page, 0, "->"); /*�ڵ�1 ҳ����10 ����ʾ�ַ���*/
}

void clear_gb(u8 page)
{
	u8 k;
	for (k = 1; k <= 16; k++)
	{
		lcd_address(page, k); //������߸���֮ǰ��ͬX����ĵ�
		transfer_data(0x00); //
		lcd_address(page + 1, k); //������߸���֮ǰ��ͬX����ĵ�
		transfer_data(0x00); //
	}

}
