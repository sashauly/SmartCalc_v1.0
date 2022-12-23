#include "parser.h"

void remove_spaces(char* src) {
  char* i = src;
  char* j = src;
  while (*j != 0) {
    *i = *j++;
    if (*i != ' ') i++;
  }
  *i = 0;
}

void number_parser(char* dst, char* src, data_t* data, int* i) {
  int exit_fun = 0;
  int count_dot = 0;
  for (int j = 0; exit_fun != 1; j++) {
    if (src[*i] == ',') src[*i] = '.';
    if (src[*i] == '.') count_dot++;
    dst[j] = src[*i];
    i++;
    if (is_number(src[*i]) || src[*i] == '.') {
      continue;
    } else {
      exit_fun = 1;
    }
  }
  i--;
  if (count_dot > 1) {
    exit(EXIT_FAILURE);
  } else {
    data->value = atof(dst);
    data->type = NUM;
  }
}

void func_parser(char* dst, char* src, data_t* data, int* i) {
  int exit_fun = 0;

  for (int l = 0; exit_fun != 1; l++) {
    dst[l] = src[*i];
    *i = *i + 1;
    if (src[*i] >= 'a' && src[*i] <= 'z') {
      continue;
    } else {
      exit_fun = 1;
    }
  }
  *i = *i - 1;
  data->value = 0;

  if (!strcmp(dst, "cos"))
    data->type = COS;
  else if (!strcmp(dst, "sin"))
    data->type = SIN;
  else if (!strcmp(dst, "tan"))
    data->type = TAN;
  else if (!strcmp(dst, "acos"))
    data->type = ACOS;
  else if (!strcmp(dst, "asin"))
    data->type = ASIN;
  else if (!strcmp(dst, "atan"))
    data->type = ATAN;
  else if (!strcmp(dst, "sqrt"))
    data->type = SQRT;
  else if (!strcmp(dst, "ln"))
    data->type = LN;
  else if (!strcmp(dst, "log"))
    data->type = LOG;
  else if (!strcmp(dst, "mod"))
    data->type = MOD;
}

void maths(struct stack** stack_n, struct stack** stack_o, data_t* data) {
  double a = 0, b = 0, c = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  switch (peek(*stack_o).type) {
    case SUM:
      b = (peek(*stack_n).value);
      pop(stack_n);
      pop(stack_o);
      c = a + b;
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case SUB:
      b = (peek(*stack_n).value);
      pop(stack_n);
      pop(stack_o);
      c = b - a;
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case MULT:
      b = (peek(*stack_n).value);
      pop(stack_n);
      pop(stack_o);
      c = a * b;
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case DIV:
      if (a != 0) {
        b = (peek(*stack_n).value);
        pop(stack_n);
        pop(stack_o);
        c = b / a;
        data->value = c;
        data->type = NUM;
        push(stack_n, *data);
      } else {
        fprintf(stderr, "Сan't divide by zero\n");
        exit(EXIT_FAILURE);
      }
      break;

    case MOD:
      b = (peek(*stack_n).value);
      pop(stack_n);
      pop(stack_o);
      c = fmod(a, b);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case COS:
      pop(stack_o);
      c = cos(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case SIN:
      pop(stack_o);
      c = sin(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case TAN:
      pop(stack_o);
      c = tan(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case ACOS:
      pop(stack_o);
      c = acos(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case ASIN:
      pop(stack_o);
      c = asin(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case ATAN:
      pop(stack_o);
      c = atan(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case LN:
      pop(stack_o);
      c = log(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case LOG:
      pop(stack_o);
      c = log10(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case SQRT:
      pop(stack_o);
      c = pow(a, 0.5);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    case POW:
      b = (peek(*stack_n).value);
      pop(stack_n);
      pop(stack_o);
      c = pow(b, a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      break;

    default:
      break;
  }
}

int get_priority(int type) {
  int priority = 0;
  if (type == SUM || type == SUB) priority = 1;
  if (type == MULT || type == DIV || type == MOD) priority = 2;
  if (type == POW) priority = 3;
  if (type == COS || type == SIN || type == TAN || type == ACOS ||
      type == ASIN || type == ATAN || type == LN || type == LOG || type == SQRT)
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

int main() {
  char str[256] = "9mod4";
  struct stack* stack_n = NULL;
  struct stack* stack_o = NULL;
  data_t data = {0, '\0'};
  char tmp[256] = {0};

  remove_spaces(str);
  for (int i = 0; i < (int)strlen(str); i++) {
    memset(tmp, '\0', 256);

    if ((str[i] == '-' && i == 0) ||
        (i > 0 && str[i] == '-' && str[i - 1] == '(')) {
      data.value = 0;
      data.type = NUM;
      push(&stack_n, data);
      data.value = 0;
      data.type = SUB;
      push(&stack_o, data);
      continue;
    } else if ((str[i] == '+' && i == 0) ||
               (i > 0 && str[i] == '+' && str[i - 1] == '(')) {
      data.value = 0;
      data.type = NUM;
      push(&stack_n, data);
      data.value = 0;
      data.type = SUM;
      push(&stack_o, data);
      continue;
    } else if (is_number(str[i])) {
      number_parser(tmp, str, &data, &i);
      push(&stack_n, data);
      continue;
    } else if (str[i] == 'p') {
      data.value = PI;
      data.type = NUM;
      push(&stack_n, data);
      continue;
    } else if (is_letter(str[i])) {
      func_parser(tmp, str, &data, &i);
      push(&stack_o, data);
      continue;
    } else if (is_operation(str[i])) {
      int type = type_operation(str[i]);
      if (is_empty(stack_o)) {
        data.value = 0;
        data.type = type;
        push(&stack_o, data);
        continue;
      } else {
        if (get_priority(type) > get_priority(peek(stack_o).type)) {
          data.value = 0;
          data.type = type;
          push(&stack_o, data);
          continue;
        } else {
          maths(&stack_n, &stack_o, &data);
          i--;
          continue;
        }
      }
    } else if (str[i] == '(') {
      data.value = 0;
      data.type = OPEN;
      push(&stack_o, data);
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
  printf("RESULT %lf\n", peek(stack_n).value);
  return 0;
}
