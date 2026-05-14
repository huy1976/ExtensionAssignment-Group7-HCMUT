#include "main.h"
#include "oled.h"
#include "keypad.h"
#include "parser.h"

typedef enum {
	STATE_MENU,
	STATE_SCI_CALC,
	STATE_PT2_A, STATE_PT2_B, STATE_PT2_C, STATE_PT2_RESULT,
	STATE_HPT_A1, STATE_HPT_B1, STATE_HPT_C1,
	STATE_HPT_A2, STATE_HPT_B2, STATE_HPT_C2,
	STATE_HPT_RESULT,
	STATE_CMPLX_Z1, STATE_CMPLX_OP, STATE_CMPLX_Z2, STATE_CMPLX_RESULT
} AppState_t;

void parse_complex(char* str, double* real_part, double* imag_part) {
	*real_part = 0;
	*imag_part = 0;
	
	char* i_ptr = strchr(str, 'i');
	if (i_ptr != NULL) {
		*i_ptr = '\0';
		char* plus_ptr = strchr(str + 1, '+');
		char* minus_ptr = strchr(str + 1, '-');
		
		if (plus_ptr) {
			*plus_ptr = '\0';
			*real_part = atof(str);
			*imag_part = atof(plus_ptr + 1);
			if (*imag_part == 0 && *(plus_ptr + 1) == '\0') *imag_part = 1;
		}
		else if (minus_ptr) {
			*minus_ptr = '\0';
			*real_part = atof(str);
			*imag_part = -atof(minus_ptr + 1);
			if (*imag_part == 0 && *(minus_ptr + 1) == '\0') *imag_part = -1;
		}
		else {
			*real_part = 0;
			*imag_part = atof(str);
			if (*imag_part == 0 && str[0] == '\0') *imag_part = 1;
		}
	}
	else {
		*real_part = atof(str);
		*imag_part = 0;
	}
}

int main(void) {
	oled_init();
	oled_clear();
	keypad_init();
	timer0_init();
	sei();

	AppState_t current_state = STATE_MENU;
	char buffer[64] = "";
	uint8_t shift_h = 0;

	double a = 0, b = 0, c = 0;
	double a1 = 0, b1 = 0, c1 = 0, a2 = 0, b2 = 0, c2 = 0;
	char complex_op = 0;
	double real1 = 0, imag1 = 0, real2 = 0, imag2 = 0;

	oled_print("CHOOSE MODE:", 0, 0);
	oled_print("1. SCI CALC", 0, 2);
	oled_print("2. PT BAC 2", 0, 3);
	oled_print("3. HPT 2 AN", 0, 4);
	oled_print("4. SO PHUC", 0, 5);

	while (1) {
		if (flag_key_ready) {
			char key = current_key;
			flag_key_ready = 0;
			
			if (key == 'C') {
				current_state = STATE_MENU;
				buffer[0] = '\0';
				shift_h = 0;
				oled_clear();
				oled_print("CHOOSE MODE:", 0, 0);
				oled_print("1. SCI CALC", 0, 2);
				oled_print("2. PT BAC 2", 0, 3);
				oled_print("3. HPT 2 AN", 0, 4);
				oled_print("4. SO PHUC", 0, 5);
				continue;
			}

			switch (current_state) {
				case STATE_MENU:
				if (key == '1') {
					current_state = STATE_SCI_CALC; buffer[0] = '\0'; oled_clear();
					oled_print("MODE 1: CALC", 0, 0);
				}
				else if (key == '2') {
					current_state = STATE_PT2_A; buffer[0] = '\0'; oled_clear();
					oled_print("PT: AX^2 + BX + C = 0", 0, 0); oled_print("A: ", 0, 2);
				}
				else if (key == '3') {
					current_state = STATE_HPT_A1; buffer[0] = '\0'; oled_clear();
					oled_print("HPT: A1X + B1Y = C1", 0, 0); oled_print("A1: ", 0, 2);
				}
				else if (key == '4') {
					current_state = STATE_CMPLX_Z1; buffer[0] = '\0'; oled_clear();
					oled_print("MODE 4: CMPLX", 0, 0); oled_print("Z1: ", 0, 2);
				}
				break;

				case STATE_SCI_CALC:
				if (key == 'H') {
					shift_h = !shift_h;
					oled_char(shift_h ? 'H' : ' ', 115, 0);
				}
				else if (key == '=') {
					double res = calculate_expression(buffer);
					char s[20];
					dtostrf(res, 7, 3, s);
					oled_clear_line(5); oled_print("Ans:", 0, 5); oled_print(s, 30, 5);
				}
				else if (key == 'D') {
					int len = strlen(buffer);
					if (len > 0) {
						buffer[len - 1] = '\0';
						oled_clear_line(2);
						oled_print(buffer, 0, 2);
					}
				}
				else {
					if (shift_h) {
						if (key == '+') strcat(buffer, "sin"); else if (key == '-') strcat(buffer, "cos");
						else if (key == '*') strcat(buffer, "tan"); else if (key == '/') strcat(buffer, "cot");
						else if (key == '.') strcat(buffer, "log"); else if (key == '0') strcat(buffer, "(");
						else if (key == '1') strcat(buffer, ")"); else { char t[2] = {key, '\0'}; strcat(buffer, t); }
						shift_h = 0; oled_char(' ', 115, 0);
					}
					else {
						char t[2] = {key, '\0'}; strcat(buffer, t);
					}
					oled_clear_line(2); oled_print(buffer, 0, 2);
				}
				break;

				case STATE_PT2_A:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(2); oled_print("A: ", 0, 2); oled_print(buffer, 20, 2);
				}
				else if (key == '=') {
					a = atof(buffer); buffer[0] = '\0';
					oled_print("B: ", 0, 3); current_state = STATE_PT2_B;
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 20, 2);
				}
				break;

				case STATE_PT2_B:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(3); oled_print("B: ", 0, 3); oled_print(buffer, 20, 3);
				}
				else if (key == '=') {
					b = atof(buffer); buffer[0] = '\0';
					oled_print("C: ", 0, 4); current_state = STATE_PT2_C;
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 20, 3);
				}
				break;

				case STATE_PT2_C:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(4); oled_print("C: ", 0, 4); oled_print(buffer, 20, 4);
				}
				else if (key == '=') {
					c = atof(buffer); buffer[0] = '\0'; current_state = STATE_PT2_RESULT;
					char s1[16], s2[16]; oled_clear_line(6);
					
					if (a == 0) {
						oled_print("A=0 -> PT Bac 1", 0, 5);
						if (b == 0) {
							if (c == 0) oled_print("VO SO NGHIEM !", 0, 6); else oled_print("VO NGHIEM !", 0, 6);
						}
						else {
							double x = -c / b; if (x == -0.0) x = 0.0;
							dtostrf(x, 6, 2, s1); oled_print("X =", 0, 6); oled_print(s1, 25, 6);
						}
					}
					else {
						double d = b*b - 4*a*c;
						if (d < 0) oled_print("VO NGHIEM !", 0, 6);
						else if (d == 0) {
							double x = -b / (2*a); if (x == -0.0) x = 0.0;
							dtostrf(x, 6, 2, s1); oled_print("X1=X2=", 0, 6); oled_print(s1, 40, 6);
						}
						else {
							double x1 = (-b + sqrt(d)) / (2*a);
							double x2 = (-b - sqrt(d)) / (2*a);
							if (x1 == -0.0) x1 = 0.0; if (x2 == -0.0) x2 = 0.0;
							
							dtostrf(x1, 5, 2, s1); dtostrf(x2, 5, 2, s2);
							oled_print("X1:", 0, 6); oled_print(s1, 20, 6);
							oled_print("X2:", 65, 6); oled_print(s2, 85, 6);
						}
					}
					oled_print("PRESS AC TO BACK", 0, 7);
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 20, 4);
				}
				break;
				
				case STATE_HPT_A1:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(2); oled_print("A1: ", 0, 2); oled_print(buffer, 25, 2);
				}
				else if (key == '=') {
					a1 = atof(buffer); buffer[0] = '\0';
					oled_print("B1: ", 0, 3); current_state = STATE_HPT_B1;
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 2);
				}
				break;

				case STATE_HPT_B1:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(3); oled_print("B1: ", 0, 3); oled_print(buffer, 25, 3);
				}
				else if (key == '=') {
					b1 = atof(buffer); buffer[0] = '\0';
					oled_print("C1: ", 0, 4); current_state = STATE_HPT_C1;
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 3);
				}
				break;

				case STATE_HPT_C1:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(4); oled_print("C1: ", 0, 4); oled_print(buffer, 25, 4);
				}
				else if (key == '=') {
					c1 = atof(buffer); buffer[0] = '\0';
					oled_clear(); oled_print("HPT: A2X + B2Y = C2", 0, 0); oled_print("A2: ", 0, 2);
					current_state = STATE_HPT_A2;
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 4);
				}
				break;

				case STATE_HPT_A2:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(2); oled_print("A2: ", 0, 2); oled_print(buffer, 25, 2);
				}
				else if (key == '=') {
					a2 = atof(buffer); buffer[0] = '\0';
					oled_print("B2: ", 0, 3); current_state = STATE_HPT_B2;
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 2);
				}
				break;

				case STATE_HPT_B2:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(3); oled_print("B2: ", 0, 3); oled_print(buffer, 25, 3);
				}
				else if (key == '=') {
					b2 = atof(buffer); buffer[0] = '\0';
					oled_print("C2: ", 0, 4); current_state = STATE_HPT_C2;
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 3);
				}
				break;

				case STATE_HPT_C2:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(4); oled_print("C2: ", 0, 4); oled_print(buffer, 25, 4);
				}
				else if (key == '=') {
					c2 = atof(buffer); buffer[0] = '\0'; current_state = STATE_HPT_RESULT;

					double D  = a1 * b2 - a2 * b1;
					double Dx = c1 * b2 - c2 * b1;
					double Dy = a1 * c2 - a2 * c1;
					
					oled_clear_line(6);
					if (D == 0) {
						if (Dx == 0 && Dy == 0) oled_print("VO SO NGHIEM !", 0, 6);
						else oled_print("VO NGHIEM !", 0, 6);
					}
					else {
						char s1[16], s2[16];
						double x = Dx / D; double y = Dy / D;
						if (x == -0.0) x = 0.0; if (y == -0.0) y = 0.0;
						
						dtostrf(x, 5, 2, s1); dtostrf(y, 5, 2, s2);
						oled_print("X: ", 0, 6); oled_print(s1, 20, 6);
						oled_print("Y: ", 65, 6); oled_print(s2, 85, 6);
					}
					oled_print("PRESS AC TO BACK", 0, 7);
				}
				else if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 4);
				}
				break;

				case STATE_CMPLX_Z1:
				if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(2); oled_print("Z1: ", 0, 2); oled_print(buffer, 25, 2);
				}
				else if (key == '=') {
					parse_complex(buffer, &real1, &imag1);
					buffer[0] = '\0';
					oled_print("OP (+-*/): ", 0, 3); current_state = STATE_CMPLX_OP;
					}
					else if ((key >= '0' && key <= '9') || key == '.' || key == '-' || key == '+' || key == 'i') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 2);
					}
					break;

					case STATE_CMPLX_OP:
					if (key == '+' || key == '-' || key == '*' || key == '/') {
					complex_op = key;
					char t[2] = {key, '\0'}; oled_print(t, 70, 3);
					oled_print("Z2: ", 0, 4); current_state = STATE_CMPLX_Z2;
					}
					break;

					case STATE_CMPLX_Z2:
					if (key == 'D' && strlen(buffer) > 0) {
					buffer[strlen(buffer) - 1] = '\0';
					oled_clear_line(4); oled_print("Z2: ", 0, 4); oled_print(buffer, 25, 4);
					}
					else if (key == '=') {
					parse_complex(buffer, &real2, &imag2);
					buffer[0] = '\0'; current_state = STATE_CMPLX_RESULT;
					
					double res_real = 0, res_imag = 0;
					
					if (complex_op == '+') {
					res_real = real1 + real2; res_imag = imag1 + imag2;
					}
					else if (complex_op == '-') {
					res_real = real1 - real2; res_imag = imag1 - imag2;
					}
					else if (complex_op == '*') {
					res_real = real1 * real2 - imag1 * imag2;
					res_imag = real1 * imag2 + imag1 * real2;
					}
					else if (complex_op == '/') {
					double denom = real2 * real2 + imag2 * imag2;
					if (denom != 0) {
					res_real = (real1 * real2 + imag1 * imag2) / denom;
					res_imag = (imag1 * real2 - real1 * imag2) / denom;
					}
					}
					
					char sr[16], si[16], final_ans[32];
					dtostrf(res_real, 0, 2, sr);
					dtostrf(fabs(res_imag), 0, 2, si);
					
					oled_clear_line(6); oled_print("Ans: ", 0, 6);
					if (res_imag >= 0) sprintf(final_ans, "%s + %si", sr, si);
					else sprintf(final_ans, "%s - %si", sr, si);
					
					oled_print(final_ans, 35, 6);
					}
					else if ((key >= '0' && key <= '9') || key == '.' || key == '-' || key == '+' || key == 'i') {
					char t[2] = {key, '\0'}; strcat(buffer, t); oled_print(buffer, 25, 4);
					}
					break;
					
					case STATE_PT2_RESULT:
					case STATE_HPT_RESULT:
					case STATE_CMPLX_RESULT:
					break;
					}
					}
					}
					}