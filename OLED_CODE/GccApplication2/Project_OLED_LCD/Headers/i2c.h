#ifndef I2C_H_
#define I2C_H_
#include "main.h"

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t d);

#endif