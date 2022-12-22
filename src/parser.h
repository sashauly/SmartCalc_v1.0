#ifndef SRC_PARSER_H
#define SRC_PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define PI acos(-1)

#define is_number(ch) ((ch) >= '0' && (ch) <= '9')
#define is_operation(ch) \
  ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' || (ch) == '^')

void maths(struct stack** stack_n, struct stack** stack_o, data_t* data);
int num_pars(char* str, char* arr, int* i, data_t* data);
int type_operation(char ch);
void remove_spaces(char* data);

#endif  // SRC_PARSER_H
