#include "calc.h"

void maths(struct stack** stack_n, struct stack** stack_o, data_t* data) {
  double a = 0, b = 0, c = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  switch (peek(*stack_o).type) {
    case SUM:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = a + b;
      break;

    case SUB:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = b - a;
      break;

    case MULT:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = a * b;
      break;

    case DIV:
      if (a != 0) {
        b = (peek(*stack_n).value);
        pop(stack_n);
        c = b / a;
      } else {
        fprintf(stderr, "Can't divide by zero\n");
        exit(EXIT_FAILURE);
      }
      break;

    case MOD:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = fmod(b, a);
      break;

    case COS:
      c = cos(a);
      break;

    case SIN:
      c = sin(a);
      break;

    case TAN:
      c = tan(a);
      break;

    case ACOS:
      c = acos(a);
      break;

    case ASIN:
      c = asin(a);
      break;

    case ATAN:
      c = atan(a);
      break;

    case LN:
      c = log(a);
      break;

    case LOG:
      c = log10(a);
      break;

    case SQRT:
      c = sqrt(a);
      break;

    case POW:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = pow(b, a);
      break;

    default:
      break;
  }
  pop(stack_o);
  push(stack_n, data, c, NUM);
}

void parser(char* str, struct stack** stack_n, struct stack** stack_o,
            data_t* data, double* number, double x) {
  for (int i = 0; i < (int)strlen(str); i++) {
    char tmp[256] = {0};

    if ((str[i] == '-' && i == 0) ||
        (i > 0 && str[i] == '-' && str[i - 1] == '(')) {
      push(stack_n, data, 0, NUM);
      push(stack_o, data, 0, SUB);
      continue;
    } else if ((str[i] == '+' && i == 0) ||
               (i > 0 && str[i] == '+' && str[i - 1] == '(')) {
      push(stack_n, data, 0, NUM);
      push(stack_o, data, 0, SUM);
      continue;
    } else if (is_number(str[i])) {
      *number = number_parser(tmp, str, &i);
      push(stack_n, data, *number, NUM);
      continue;
    } else if (str[i] == 'p') {
      push(stack_n, data, PI, NUM);
      continue;
    } else if (str[i] == 'x') {
      push(stack_n, data, x, NUM);
      continue;
    } else if (is_letter(str[i])) {
      int func_type = func_parser(tmp, str, &i);
      push(stack_o, data, 0, func_type);
      continue;
    } else if (is_operation(str[i])) {
      int type = type_operation(str[i]);
      if (is_empty(*stack_o)) {
        push(stack_o, data, 0, type);
        continue;
      } else {
        if (get_priority(type) > get_priority(peek(*stack_o).type)) {
          push(stack_o, data, 0, type);
          continue;
        } else {
          maths(stack_n, stack_o, data);
          i--;
          continue;
        }
      }
    } else if (str[i] == '(') {
      push(stack_o, data, 0, OPEN);
      continue;
    } else if (str[i] == ')') {
      while (peek(*stack_o).type != OPEN) {
        maths(stack_n, stack_o, data);
      }
      pop(stack_o);
      continue;
    }
  }
}

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