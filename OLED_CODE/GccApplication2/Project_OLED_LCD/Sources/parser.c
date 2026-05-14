#include "parser.h"

#define PI 3.14159265
static const char *ptr;

static double expression(void);
static double term(void);
static double number(void);

double calculate_expression(const char* expression_string) {
	ptr = expression_string;
	return expression();
}

static double number(void) {
	double r = 0;
	if (*ptr == '(') { ptr++; r = expression(); if (*ptr == ')') ptr++; return r; }
	if (strncmp(ptr, "sin", 3) == 0) { ptr += 3; return sin(number() * PI / 180.0); }
	if (strncmp(ptr, "cos", 3) == 0) { ptr += 3; return cos(number() * PI / 180.0); }
	if (strncmp(ptr, "tan", 3) == 0) { ptr += 3; return tan(number() * PI / 180.0); }
	if (strncmp(ptr, "cot", 3) == 0) { ptr += 3; return 1.0 / tan(number() * PI / 180.0); }
	if (strncmp(ptr, "log", 3) == 0) { ptr += 3; return log10(number()); }
	if (*ptr == 'q') { ptr++; return sqrt(number()); }
	int sign = 1; if (*ptr == '-') { sign = -1; ptr++; }
	while (*ptr >= '0' && *ptr <= '9') r = r * 10 + (*ptr++ - '0');
	if (*ptr == '.') { ptr++; double w = 0.1; while (*ptr >= '0' && *ptr <= '9') { r += (*ptr++ - '0') * w; w /= 10; } }
	return r * sign;
}

static double term(void) {
	double r = number();
	while (*ptr == '*' || *ptr == '/' || *ptr == '^') {
		char o = *ptr++;
		if (o == '*') r *= number(); else if (o == '/') r /= number(); else if (o == '^') r = pow(r, number());
	}
	return r;
}

static double expression(void) {
	double r = term();
	while (*ptr == '+' || *ptr == '-') {
		char o = *ptr++;
		if (o == '+') r += term(); else r -= term();
	}
	return r;
}