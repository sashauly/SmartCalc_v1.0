#ifndef SRC_PARSER_H
#define SRC_PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define PI acos(-1)

#define is_number(ch) ((ch) >= '0' && (ch) <= '9')
#define is_letter(ch) \
  ((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z')
#define is_operation(ch) \
  ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' || (ch) == '^')

double s21_smart_calc(char* src, double x);
void remove_spaces(char* src, char* dst);
int validator(char* str);
void maths(struct stack** stack_n, struct stack** stack_o, data_t* data);
double number_parser(char* dst, char* src, int* i);
int func_parser(char* dst, char* src, int* i);
int type_operation(char ch);

#endif  // SRC_PARSER_H
