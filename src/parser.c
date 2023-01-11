#include "parser.h"

#include <math.h>

//  Удаляет пробелы из входной строки
void remove_spaces(char* src, char* dst) {
  int j = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    if (src[i] != ' ') {
      dst[j] = src[i];
      j++;
    }
  }
  dst[j] = '\0';
}
//  Проверка ошибок во входной строке
int validator(char* str) {
  int error = 0;
  int i = 0;
  int open_sk = 0;
  int close_sk = 0;
  for (; str[i] != '\0' && str[i] != '\n' && error == 0; i++) {
    if (str[i] == '(') open_sk++;
    if (str[i] == ')') close_sk++;
    if ((str[i] == '(' && str[i + 1] == ')') ||
        (str[i] == ')' && str[i + 1] == '(') || (str[0] == ')') ||
        (is_operation(str[i]) && is_operation(str[i + 1]))) {
      error = 1;
      break;
    }
  }
  if (is_operation(str[i - 1])) error = 1;
  if ((open_sk != close_sk) || (str[i - 1]) == '(') error = 1;
  return error;
}
//  Перевод числовых значений из строки в число
int number_parser(char* dst, char* src, int* i, double* number) {
  *number = 0;
  int count_dot = 0;
  int error = 0;
  int j = 0;

  while (is_number(src[*i]) || src[*i] == '.') {
    if (src[*i] == ',') src[*i] = '.';
    if (src[*i] == '.') count_dot++;
    dst[j] = src[*i];
    *i = *i + 1;
    j++;
  }
  *i = *i - 1;
  if (count_dot > 1) {
    error = 1;
  } else {
    *number = atof(dst);
  }
  return error;
}
//  Возвращает тип функции, полученный путем парсинга строки
int func_parser(char* dst, char* src, int* i, int* type) {
  *type = 0;
  int error = 0;
  int j = 0;

  while (is_letter(src[*i])) {
    dst[j] = src[*i];
    *i = *i + 1;
    j++;
  }
  *i = *i - 1;

  if (!strcmp(dst, "cos")) {
    *type = COS;
  } else if (!strcmp(dst, "sin")) {
    *type = SIN;
  } else if (!strcmp(dst, "tan")) {
    *type = TAN;
  } else if (!strcmp(dst, "acos")) {
    *type = ACOS;
  } else if (!strcmp(dst, "asin")) {
    *type = ASIN;
  } else if (!strcmp(dst, "atan")) {
    *type = ATAN;
  } else if (!strcmp(dst, "sqrt")) {
    *type = SQRT;
  } else if (!strcmp(dst, "ln")) {
    *type = LN;
  } else if (!strcmp(dst, "log")) {
    *type = LOG;
  } else if (!strcmp(dst, "mod")) {
    *type = MOD;
  } else {
    error = 1;
  }
  return error;
}
//  Возвращает приоритет операции или функции
int get_priority(int type) {
  int priority = 0;
  if (type == SUM || type == SUB)
    priority = 1;
  else if (type >= MULT && type <= MOD)
    priority = 2;
  else if (type == POW || type == SQRT)
    priority = 3;
  else if (type >= COS && type <= LOG)
    priority = 4;
  return priority;
}
//  Возвращает тип операции
int type_operation(char ch) {
  int type = 0;
  if ((ch) == '+') {
    type = SUM;
  } else if ((ch) == '-') {
    type = SUB;
  } else if ((ch) == '*') {
    type = MULT;
  } else if ((ch) == '/') {
    type = DIV;
  } else if ((ch) == '^') {
    type = POW;
  }
  return type;
}

//  Вычисление бинарных операций
int binary_operations(struct stack** stack_n, int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
  int error = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  b = (peek(*stack_n).value);
  pop(stack_n);
  switch (oper) {
    case SUM:
      *c = a + b;
      break;
    case SUB:
      *c = b - a;
      break;
    case MULT:
      *c = a * b;
      break;
    case DIV:
      if (a != 0) {
        *c = b / a;
      } else {
        error = 1;
      }
      break;
    case MOD:
      *c = fmod(b, a);
      break;
  }
  return error;
}
//  Вычисление функций
int func_operations(struct stack** stack_n, int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
  int error = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  if (oper == COS) {
    *c = cos(a);
  } else if (oper == SIN) {
    *c = sin(a);
  } else if (oper == TAN) {
    *c = tan(a);
  } else if (oper == ACOS) {
    *c = acos(a);
  } else if (oper == ASIN) {
    *c = asin(a);
  } else if (oper == ATAN) {
    *c = atan(a);
  } else if (oper == LN) {
    *c = log(a);
  } else if (oper == LOG) {
    *c = log10(a);
  } else if (oper == SQRT) {
    *c = sqrt(a);
  } else if (oper == POW) {
    b = (peek(*stack_n).value);
    pop(stack_n);
    *c = pow(b, a);
  }
  return error;
}

//  Вычисление в зависимости от оператора в стеке
int calculations(struct stack** stack_n, struct stack** stack_o, data_t* data) {
  double c = 0;
  int error = 0;
  int oper = peek(*stack_o).type;
  if (oper >= SUM && oper <= MOD) {
    error = binary_operations(stack_n, oper, &c);
  } else if (oper >= COS && oper <= POW) {
    error = func_operations(stack_n, oper, &c);
  }
  pop(stack_o);
  if (error == 0) {
    push(stack_n, data, c, NUM);
  }
  return error;
}

//  Основной парсер строки
int parser(char* str, struct stack** stack_n, struct stack** stack_o,
           data_t* data, double x) {
  int error = 0;
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
      double number = 0;
      error = number_parser(tmp, str, &i, &number);
      if (error == 0) {
        push(stack_n, data, number, NUM);
        continue;
      } else {
        break;
      }
    } else if (str[i] == 'p') {
      push(stack_n, data, PI, NUM);
      i++;
      continue;
    } else if (str[i] == 'x') {
      push(stack_n, data, x, NUM);
      continue;
    } else if (is_letter(str[i])) {
      int func_type = 0;
      error = func_parser(tmp, str, &i, &func_type);
      if (error == 0) {
        push(stack_o, data, 0, func_type);
        continue;
      } else {
        break;
      }
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
          error = calculations(stack_n, stack_o, data);
          if (error == 0) {
            i--;
            continue;
          } else {
            break;
          }
        }
      }
    } else if (str[i] == '(') {
      push(stack_o, data, 0, OPEN);
      continue;
    } else if (str[i] == ')') {
      while (peek(*stack_o).type != OPEN) {
        error = calculations(stack_n, stack_o, data);
        if (error != 0) {
          break;
        }
      }
      pop(stack_o);
      continue;
    } else {
      error = 1;
      break;
    }
  }
  return error;
}

//  Основная функция SMART_CALC
int s21_smart_calc(char* src, double x, double* result) {
  char str[256] = {0};
  struct stack* stack_n = NULL;
  struct stack* stack_o = NULL;
  data_t data = {0, 0};
  *result = 0;
  int error = 0;
  remove_spaces(src, str);
  if (!(validator(str))) {
    error = parser(str, &stack_n, &stack_o, &data, x);
    if (error == 0) {
      while (!is_empty(stack_o)) {
        error = calculations(&stack_n, &stack_o, &data);
        if (error != 0) {
          while (!is_empty(stack_o)) {
            pop(&stack_o);
          }
          break;
        }
      }
      if (error == 0) {
        *result = peek(stack_n).value;
      }
      while (!is_empty(stack_n)) {
        pop(&stack_n);
      }
    } else {
      while (!is_empty(stack_o)) {
        pop(&stack_o);
      }
      while (!is_empty(stack_n)) {
        pop(&stack_n);
      }
    }
  } else {
    error = 1;
  }
  return error;
}
