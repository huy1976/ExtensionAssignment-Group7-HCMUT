#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "main.h"

void keypad_init(void);
void timer0_init(void);

extern volatile uint8_t flag_key_ready;
extern volatile char current_key;

#endif