#ifndef SRC_CALC_H
#define SRC_CALC_H

#include <math.h>

#include "parser.h"
#include "stack.h"

double s21_smart_calc(char* src, double x);
void maths(struct stack** stack_n, struct stack** stack_o, data_t* data);

#endif  // SRC_CALC_H