#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define LCD_PORT PORTC
#define LCD_DDR  DDRC
#define RS       PC0
#define EN       PC1

#define LCD_CLEAR           0x01
#define LCD_RETURN_HOME     0x02
#define LCD_4BIT_2LINE      0x28
#define LCD_DISP_ON         0x0C
#define LCD_SET_CURSOR_LINE2 0xC0

void lcd_cmd(char cmd);
void lcd_data(char data);
void lcd_init(void);
void lcd_print(const char *str);
void lcd_print_float(float num);

#endif