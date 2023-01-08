#include "calc.h"

//  Вычисление бинарных операций
double binary_operations(struct stack** stack_n, int operator) {
  double a = 0, b = 0, c = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  b = (peek(*stack_n).value);
  pop(stack_n);
  switch (operator) {
    case SUM:
      c = a + b;
      break;
    case SUB:
      c = b - a;
      break;
    case MULT:
      c = a * b;
      break;
    case DIV:
      if (a != 0) {
        c = b / a;
      } else {
        fprintf(stderr, "Can't divide by zero\n");
        exit(EXIT_FAILURE);
      }
      break;
    case MOD:
      c = fmod(b, a);
      break;
  }
  return c;
}
//  Вычисление функций
double func_operations(struct stack** stack_n, int operator) {
  double a = 0, b = 0, c = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  if (operator== COS) {
    c = cos(a);
  } else if (operator== SIN) {
    c = sin(a);
  } else if (operator== TAN) {
    c = tan(a);
  } else if (operator== ACOS) {
    c = acos(a);
  } else if (operator== ASIN) {
    c = asin(a);
  } else if (operator== ATAN) {
    c = atan(a);
  } else if (operator== LN) {
    c = log(a);
  } else if (operator== LOG) {
    c = log10(a);
  } else if (operator== SQRT) {
    c = sqrt(a);
  } else if (operator== POW) {
    b = (peek(*stack_n).value);
    pop(stack_n);
    c = pow(b, a);
  }
  return c;
}
//  Вычисление в зависимости от оператора в стеке
void maths(struct stack** stack_n, struct stack** stack_o, data_t* data) {
  double c = 0;
  int operator= peek(*stack_o).type;
  if (operator>= SUM && operator<= MOD) {
    c = binary_operations(stack_n, operator);
  } else if (operator>= COS && operator<= POW) {
    c = func_operations(stack_n, operator);
  }
  pop(stack_o);
  push(stack_n, data, c, NUM);
}
//  Основная функция SMART_CALC
double s21_smart_calc(char* src, double x) {
  char str[256] = {0};
  struct stack* stack_n = NULL;
  struct stack* stack_o = NULL;
  data_t data = {0, 0};
  double number = 0;
  remove_spaces(src, str);
  if (!validator(str)) {
    parser(str, &stack_n, &stack_o, &data, &number, x);
    while (!is_empty(stack_o)) {
      maths(&stack_n, &stack_o, &data);
    }
    number = peek(stack_n).value;
    while (!is_empty(stack_n)) {
      pop(&stack_n);
    }
    return number;
  } else {
    exit(EXIT_FAILURE);
  }
}

// int main() {
//   double value = s21_smart_calc("", 7);
//   printf("%lf\n", value);
// }