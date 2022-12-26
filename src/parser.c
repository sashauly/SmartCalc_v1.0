#include "parser.h"

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
  for (int j = 0; exit_fun != 1; j++) {
    if (is_number(src[*i]) || src[*i] == '.') {
      if (src[*i] == ',') src[*i] = '.';
      if (src[*i] == '.') count_dot++;
      dst[j] = src[*i];
      *i = *i + 1;
    } else {
      exit_fun = 1;
    }
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

  for (int l = 0; exit_fun != 1; l++) {
    if (src[*i] >= 'a' && src[*i] <= 'z') {
      dst[l] = src[*i];
      *i = *i + 1;
    } else {
      exit_fun = 1;
    }
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

double s21_smart_calc(char* src, double x) {
  char str[256] = {0};
  struct stack* stack_n = NULL;
  struct stack* stack_o = NULL;
  data_t data = {0, 0};
  double number = 0;
  x = 0;
  remove_spaces(src, str);
  if (!validator(str)) {
    for (int i = 0; i < (int)strlen(str); i++) {
      char tmp[256] = {0};

      if ((str[i] == '-' && i == 0) ||
          (i > 0 && str[i] == '-' && str[i - 1] == '(')) {
        push(&stack_n, &data, 0, NUM);
        push(&stack_o, &data, 0, SUB);
        continue;
      } else if ((str[i] == '+' && i == 0) ||
                 (i > 0 && str[i] == '+' && str[i - 1] == '(')) {
        push(&stack_n, &data, 0, NUM);
        push(&stack_o, &data, 0, SUM);
        continue;
      } else if (is_number(str[i])) {
        number = number_parser(tmp, str, &i);
        push(&stack_n, &data, number, NUM);
        continue;
      } else if (str[i] == 'p') {
        push(&stack_n, &data, PI, NUM);
        continue;
      } else if (is_letter(str[i])) {
        int func_type = func_parser(tmp, str, &i);
        push(&stack_o, &data, 0, func_type);
        continue;
      } else if (is_operation(str[i])) {
        int type = type_operation(str[i]);
        if (is_empty(stack_o)) {
          push(&stack_o, &data, 0, type);
          continue;
        } else {
          if (get_priority(type) > get_priority(peek(stack_o).type)) {
            push(&stack_o, &data, 0, type);
            continue;
          } else {
            maths(&stack_n, &stack_o, &data);
            i--;
            continue;
          }
        }
      } else if (str[i] == '(') {
        push(&stack_o, &data, 0, OPEN);
        continue;
      } else if (str[i] == ')') {
        while (peek(stack_o).type != OPEN) {
          maths(&stack_n, &stack_o, &data);
        }
        pop(&stack_o);
        continue;
      }
    }

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
//   double value = s21_smart_calc("9mod8", 0);
//   printf("%lf\n", value);
// }