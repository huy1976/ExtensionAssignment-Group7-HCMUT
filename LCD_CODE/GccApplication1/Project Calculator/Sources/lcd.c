#include "lcd.h"
#include "hw_timer.h" 

void lcd_cmd(char cmd) {
	LCD_PORT = (LCD_PORT & 0x0F) | (cmd & 0xF0);
	LCD_PORT &= ~(1 << RS);
	LCD_PORT |= (1 << EN);
	timer1_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	timer1_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | ((cmd << 4) & 0xF0);
	LCD_PORT |= (1 << EN);
	timer1_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	timer1_delay_ms(2);
}

void lcd_data(char data) {
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_PORT |= (1 << RS);
	LCD_PORT |= (1 << EN);
	timer1_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	timer1_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | ((data << 4) & 0xF0);
	LCD_PORT |= (1 << EN);
	timer1_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	timer1_delay_ms(2);
}

void lcd_init(void) {
	LCD_DDR = 0xFF;
	timer1_delay_ms(20);
	lcd_cmd(LCD_RETURN_HOME);
	lcd_cmd(LCD_4BIT_2LINE);
	lcd_cmd(LCD_DISP_ON);
	lcd_cmd(LCD_CLEAR);
	timer1_delay_ms(2);
}

void lcd_print(const char *str) {
	while(*str) {
		lcd_data(*str++);
	}
}

void lcd_print_float(float num) {
	char str[16];
	//int int_part = (int)num;
	//int frac_part = (int)(fabs(num - int_part) * 1000);
	//sprintf(str, "%d.%03d", int_part, frac_part);
	
	dtostrf(num, 0, 6, str);
	
	lcd_print(str);
}