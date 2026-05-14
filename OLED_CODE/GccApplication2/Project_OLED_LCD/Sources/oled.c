#include "oled.h"
#include "i2c.h"
#include "font.h"

void oled_cmd(uint8_t c) { i2c_start(); i2c_write(0x78); i2c_write(0x00); i2c_write(c); i2c_stop(); }
void oled_data(uint8_t d) { i2c_start(); i2c_write(0x78); i2c_write(0x40); i2c_write(d); i2c_stop(); }

void oled_init(void) {
	uint8_t cmds[] = {0xAE, 0x20, 0x10, 0xB0, 0xC8, 0x00, 0x10, 0x40, 0x81, 0xFF, 0xA1, 0xA6, 0xA8, 0x3F, 0xA4, 0xD3, 0x00, 0xD5, 0xF0, 0xD9, 0x22, 0xDA, 0x12, 0xDB, 0x20, 0x8D, 0x14, 0xAF};
	i2c_init(); _delay_ms(100);
	for(uint8_t i=0; i<28; i++) oled_cmd(cmds[i]);
}

void oled_char(char c, uint8_t x, uint8_t y) {
	uint8_t idx = 0;
	if (c == ' ') idx = 0;
	else if (c >= '0' && c <= '9') idx = c - '0' + 1;
	else if (c >= 'A' && c <= 'Z') idx = c - 'A' + 11;
	else if (c == '+') idx = 37; else if (c == '-') idx = 38; else if (c == '*') idx = 39;
	else if (c == '/') idx = 40; else if (c == '.') idx = 41; else if (c == '=') idx = 42;
	else if (c == ':') idx = 43; else if (c == '^') idx = 44; else if (c == 'q') idx = 45;
	else if (c == 's') idx = 46; else if (c == 'i') idx = 47; else if (c == 'n') idx = 48;
	else if (c == 'c') idx = 49; else if (c == 'o') idx = 50; else if (c == 't') idx = 51;
	else if (c == 'a') idx = 52; else if (c == '(') idx = 53; else if (c == ')') idx = 54;
	else if (c == 'l') idx = 55; else if (c == 'g') idx = 56;
	
	oled_cmd(0xB0 + y); oled_cmd(0x00 + (x & 0x0F)); oled_cmd(0x10 + ((x >> 4) & 0x0F));
	for (int i = 0; i < 5; i++) {
		oled_data(pgm_read_byte(&(font[idx][i])));
	}
	oled_data(0x00);
}

void oled_print(const char *s, uint8_t x, uint8_t y) { while(*s) { oled_char(*s++, x, y); x+=6; } }
void oled_clear(void) { for(uint8_t i=0; i<8; i++) { oled_cmd(0xB0+i); oled_cmd(0x00); oled_cmd(0x10); for(int j=0; j<128; j++) oled_data(0x00); } }
void oled_clear_line(uint8_t y) { oled_cmd(0xB0+y); oled_cmd(0x00); oled_cmd(0x10); for(int j=0; j<128; j++) oled_data(0x00); }