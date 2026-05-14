#include "main.h"
#include "lcd.h"
#include "keypad.h"

typedef enum {
	STATE_INIT,
	STATE_INPUT_NUM1,
	STATE_INPUT_NUM2,
	STATE_CALCULATE
} CalcState_t;

int main(void) {
	lcd_init();
	keypad_init();
	timer0_init();
	
	sei();

	CalcState_t system_state = STATE_INIT;
	char buffer[16] = "";
	uint8_t buf_idx = 0;
	float num1 = 0, num2 = 0, result = 0;
	char math_operator = 0;

	while(1) {
		if (flag_key_ready) {
			char key = current_key;
			flag_key_ready = 0; 

			if (key == 'C') {
				system_state = STATE_INIT;
			}

			switch (system_state) {
				case STATE_INIT:
				num1 = 0; num2 = 0; result = 0; math_operator = 0;
				buf_idx = 0; buffer[0] = '\0';
				lcd_cmd(LCD_CLEAR);
				lcd_print("Ready...");
				system_state = STATE_INPUT_NUM1;
				break;

				case STATE_INPUT_NUM1:
				if (key == 'C') break;
				
				if ((key >= '0' && key <= '9') || key == '.' || (key == '-' && buf_idx == 0)) {
					if (buf_idx == 0 && key != '-') lcd_cmd(LCD_CLEAR);
					if (buf_idx < 15) {
						buffer[buf_idx++] = key;
						buffer[buf_idx] = '\0';
						lcd_cmd(LCD_CLEAR);
						lcd_print(buffer);
					}
				}
				else if (key == '+' || key == '-' || key == '*' || key == '/' || key == '^') {
					if (buf_idx > 0 && strcmp(buffer, "-") != 0) {
						num1 = atof(buffer);
						math_operator = key;
						buf_idx = 0; buffer[0] = '\0';
						lcd_cmd(LCD_CLEAR);
						lcd_data(math_operator);
						system_state = STATE_INPUT_NUM2; 
					}
				}
				else if (key == 'S') {
					if (buf_idx > 0 && strcmp(buffer, "-") != 0) num1 = atof(buffer);
					
					if (num1 < 0) {
						lcd_cmd(LCD_CLEAR);
						lcd_print("Math Error");
						system_state = STATE_INIT;
						} else {
						result = sqrt(num1);
						lcd_cmd(LCD_SET_CURSOR_LINE2);
						lcd_print("Ans= ");
						lcd_print_float(result);
						num1 = result;
						buf_idx = 0; buffer[0] = '\0';
					}
				}
				break;

				case STATE_INPUT_NUM2:
				if (key == 'C') break;

				if ((key >= '0' && key <= '9') || key == '.' || (key == '-' && buf_idx == 0)) {
					if (buf_idx == 0) lcd_cmd(LCD_CLEAR);
					if (buf_idx < 15) {
						buffer[buf_idx++] = key;
						buffer[buf_idx] = '\0';
						lcd_cmd(LCD_CLEAR);
						lcd_data(math_operator);
						lcd_print(buffer);
					}
				}
				else if (key == '=') {
					if (buffer[0] != '\0') {
						if (strcmp(buffer, "-") == 0) num2 = 0; 
						else num2 = atof(buffer);
					}
					system_state = STATE_CALCULATE; 
				}
				else if (key == 'S') {
					if (buffer[0] != '\0') num2 = atof(buffer); 
					
					if (num2 < 0) {
						lcd_cmd(LCD_CLEAR);
						lcd_print("Math Error");
						system_state = STATE_INIT;
						} else {
						num2 = sqrt(num2); 
						
						lcd_cmd(LCD_CLEAR);
						lcd_data(math_operator); 
						lcd_print_float(num2);   
						
						buf_idx = 0; buffer[0] = '\0';
					}
				}
				break;

				case STATE_CALCULATE:
				switch(math_operator) {
					case '+': result = num1 + num2; break;
					case '-': result = num1 - num2; break;
					case '*': result = num1 * num2; break;
					case '^':
					if (num2 == (int)num2) {
						result = 1.0;
						int exponent = (int)num2;
						
						if (exponent > 0) {
							for (int i = 0; i < exponent; i++) result *= num1;
						}
						else if (exponent < 0) {
							for (int i = 0; i > exponent; i--) result /= num1;
						}
						} else {
						if (num1 < 0) {
							lcd_cmd(LCD_CLEAR);
							lcd_print("Math Error");
							system_state = STATE_INIT; 
							goto skip_print; 
							} else {
							result = pow(num1, num2);
						}
					}
					break;
					case '/':
					if (num2 == 0) {
						lcd_cmd(LCD_CLEAR);
						lcd_print("Math Error");
						system_state = STATE_INIT;
						goto skip_print;
						} else {
						result = num1 / num2;
					}
					break;
				}
				
				lcd_cmd(LCD_SET_CURSOR_LINE2);
				lcd_print("Ans= ");
				lcd_print_float(result);
				
				num1 = result;
				buf_idx = 0; buffer[0] = '\0';
				system_state = STATE_INPUT_NUM1;
				
				skip_print:
				break;
			}
		}
	}
}