#ifndef SRC_CALC_H
#define SRC_CALC_H

#include <math.h>

#include "parser.h"
#include "stack.h"

double binary_operations(struct stack** stack_n, int operator);
double func_operations(struct stack** stack_n, int operator);
void maths(struct stack** stack_n, struct stack** stack_o, data_t* data);
double s21_smart_calc(char* src, double x);

#endif  // SRC_CALC_H