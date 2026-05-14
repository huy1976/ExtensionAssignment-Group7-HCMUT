#ifndef OLED_H_
#define OLED_H_
#include "main.h"

void oled_init(void);
void oled_cmd(uint8_t c);
void oled_data(uint8_t d);
void oled_char(char c, uint8_t x, uint8_t y);
void oled_print(const char *s, uint8_t x, uint8_t y);
void oled_clear(void);
void oled_clear_line(uint8_t y);

#endif