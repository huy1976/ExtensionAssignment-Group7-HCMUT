#include "i2c.h"

void i2c_init(void) { TWBR = 32; }
void i2c_start(void) { TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
uint16_t t = 1000; while (!(TWCR & (1<<TWINT)) && t--); }
void i2c_stop(void) { TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); }
void i2c_write(uint8_t d) { TWDR = d; TWCR = (1<<TWINT) | (1<<TWEN);
uint16_t t = 1000; while (!(TWCR & (1<<TWINT)) && t--); }