#include "hw_timer.h"

void timer1_delay_us(uint16_t us) {
	TCNT1 = 0; 
	TCCR1B = (1 << CS11);
	
	while(TCNT1 < us); 
	
	TCCR1B = 0; 
}

void timer1_delay_ms(uint16_t ms) {
	for(uint16_t i = 0; i < ms; i++) {
		timer1_delay_us(1000); 
	}
}