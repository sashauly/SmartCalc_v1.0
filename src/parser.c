#include "parser.h"

#include "calc.h"

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

int validator(char* str) {
  int error = 0;
  int i = 0;
  int open_sk = 0;
  int close_sk = 0;
  for (; str[i] != '\0' && str[i] != '\n' && error == 0; i++) {
    if (str[i] == '(') open_sk++;
    if (str[i] == ')') close_sk++;
    if ((str[i] == '(' && str[i + 1] == ')') ||
        (str[i] == ')' && str[i + 1] == '(') || (str[0] == ')')) {
      error = 1;
    }
  }
  if ((open_sk != close_sk) || (str[i - 1]) == '(') error = 1;
  return error;
}

double number_parser(char* dst, char* src, int* i) {
  double number = 0;
  int exit_fun = 0;
  int count_dot = 0;
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
    exit(EXIT_FAILURE);
  } else {
    number = atof(dst);
  }
  return number;
}

int func_parser(char* dst, char* src, int* i) {
  int type = 0;
  int exit_fun = 0;
  int j = 0;

  while (is_letter(src[*i])) {
    dst[j] = src[*i];
    *i = *i + 1;
    j++;
  }
  *i = *i - 1;

  if (!strcmp(dst, "cos"))
    type = COS;
  else if (!strcmp(dst, "sin"))
    type = SIN;
  else if (!strcmp(dst, "tan"))
    type = TAN;
  else if (!strcmp(dst, "acos"))
    type = ACOS;
  else if (!strcmp(dst, "asin"))
    type = ASIN;
  else if (!strcmp(dst, "atan"))
    type = ATAN;
  else if (!strcmp(dst, "sqrt"))
    type = SQRT;
  else if (!strcmp(dst, "ln"))
    type = LN;
  else if (!strcmp(dst, "log"))
    type = LOG;
  else if (!strcmp(dst, "mod"))
    type = MOD;
  return type;
}

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
