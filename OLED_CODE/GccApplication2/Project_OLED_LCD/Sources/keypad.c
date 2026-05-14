#include "keypad.h"

volatile uint8_t flag_key_ready = 0;
volatile char current_key = 0;

const char keys[4][4] = {
	{'.', '/', '*', '='},
	{'8', '9', '+', '-'},
	{'4', '5', '6', '7'},
	{'0', '1', '2', '3'}
};

void keypad_init(void) {
	DDRA = 0x0F; PORTA = 0xFF; 
	
	DDRB &= ~((1 << PB2) | (1 << PB1) | (1 << PB0) | (1 << PB3));
	PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0) | (1 << PB3);

	DDRD &= ~((1 << PD1) | (1 << PD3)); PORTD |= (1 << PD1) | (1 << PD3);
}

void timer0_init(void) {
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02) | (1 << CS00);
	OCR0A = 77;
	TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	char detected_key = 0;
	
	if (!(PINB & (1 << PB2))) detected_key = 'C';      
	else if (!(PINB & (1 << PB1))) detected_key = 'D'; 
	else if (!(PINB & (1 << PB3))) detected_key = 'i';
	else if (!(PINB & (1 << PB0))) detected_key = 'q'; 
	else if (!(PIND & (1 << PD1))) detected_key = '^'; 
	else if (!(PIND & (1 << PD3))) detected_key = 'H'; 
	else {
		for (int r = 0; r < 4; r++) {
			PORTA = 0xFF & ~(1 << r);
			asm volatile ("nop");
			for (int c = 0; c < 4; c++) {
				if (!(PINA & (1 << (c + 4)))) {
					detected_key = keys[r][c];
					break;
				}
			}
			if (detected_key) break;
		}
	}

	static char last_key = 0;
	static uint8_t debounce_cnt = 0;
	static uint8_t key_released = 1;

	if (detected_key != 0) {
		if (detected_key == last_key) {
			debounce_cnt++;
			if (debounce_cnt >= 3 && key_released) {
				current_key = detected_key;
				flag_key_ready = 1;
				key_released = 0;
			}
			} else { debounce_cnt = 0; }
			} else {
			debounce_cnt = 0;
			key_released = 1;
		}
		last_key = detected_key;
	}