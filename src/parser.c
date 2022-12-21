#include "parser.h"
void maths(struct stack** stack_n, struct stack** stack_o, data_t* data) {
  double a = 0, b = 0, c = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  switch (peek(*stack_o).type) {
    case SUM:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = a + b;
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      pop(stack_o);
      break;

    case SUB:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = b - a;
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      printf("HERE?!\n");
      pop(stack_o);
      break;

    case MULT:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = a * b;
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      pop(stack_o);
      break;

    case DIV:
      if (a != 0) {
        b = (peek(*stack_n).value);
        pop(stack_n);
        c = b / a;
        data->value = c;
        data->type = NUM;
        push(stack_n, *data);
        pop(stack_o);
      } else {
        fprintf(stderr, "Сan't divide by zero\n");
        exit(EXIT_FAILURE);
      }
      break;

    case COS:
      c = cos(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      pop(stack_o);
      break;

    case SIN:
      c = sin(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      pop(stack_o);
      break;

    case TAN:
      c = tan(a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      pop(stack_o);
      break;

    case POW:
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = pow(b, a);
      data->value = c;
      data->type = NUM;
      push(stack_n, *data);
      pop(stack_o);
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

int s21_string_to_double(char* str, char** end, double* number) {
  int flag = 1;
  double num = 0;
  int dot = 0;
  size_t i = 0;
  // int sign = str[i] == '-' ? -1 : 1;

  if (is_number(str[i]) == 0) {
    if (str[i] == '.') {
      if (is_number(str[i + 1]) == 0) {
        flag = 0;
      }
    } else {
      flag = 0;
    }
  }
  if (flag == 1) {
    for (;; i++) {
      if (is_number(str[i]) == 0) {
        if (str[i] != '.') {
          break;
        }
      }
      if (str[i] == '.') {
        dot = 10;
      }
      if (dot == 0) {
        num = (num * 10) + (double)(str[i] - '0');
      } else if (str[i] != '.') {
        num += (double)(str[i] - '0') / dot;
        dot *= 10;
      }
    }
  }
  *end = (char*)&str[i];
  // num *= sign;
  *number = num;
  return flag;
}

int type_operation(char ch) {
  int type = 0;
  if ((ch) == '+') {
    type = SUM;
  }
  if ((ch) == '-') {
    type = SUB;
  }
  if ((ch) == '*') {
    type = MULT;
  }
  if ((ch) == '/') {
    type = DIV;
  }
  if ((ch) == '^') {
    type = POW;
  }
  return type;
}

int main() {
  char str[256] = "5 - (4+5+6)*2-5";
  double number = 0;
  struct stack* stack_n = NULL;
  struct stack* stack_o = NULL;
  data_t data = {0, '\0'};
  char tmp[256] = {0};
  int unary = 1;

  for (int i = 0, j = 0; i < (int)strlen(str); i++) {
    if (str[i] == ' ') {
      continue;
    }

    if (str[i] == 's' || str[i] == 'c' || str[i] == 't') {
      char func[3] = {0};
      for (int j = 0; j < 3; j++) {
        func[j] = str[i];
        ++i;
      }
      if (func[0] == 's' && func[1] == 'i' && func[2] == 'n') {
        data.value = 0;
        data.type = SIN;
        push(&stack_o, data);
        continue;
      }
      if (func[0] == 'c' && func[1] == 'o' && func[2] == 's') {
        data.value = 0;
        data.type = COS;
        push(&stack_o, data);
        continue;
      }
      if (func[0] == 't' && func[1] == 'a' && func[2] == 'n') {
        data.value = 0;
        data.type = TAN;
        push(&stack_o, data);
        continue;
      }
    }

    // if ((str[i] == '-' && unary == 1)) {
    //   data.value = 0;
    //   data.type = NUM;
    //   push(&stack_n, data);

    //   data.value = 0;
    //   data.type = SUB;
    //   push(&stack_o, data);
    //   unary = 0;

    //   continue;
    // }
    // if (str[i] == '+' && unary == 0) {
    //   data.value = 0;
    //   data.type = NUM;
    //   push(&stack_n, data);
    //   data.value = 0;
    //   data.type = SUM;
    //   push(&stack_o, data);
    //   unary++;
    //   continue;
    // }
    if (is_number(str[i]) || str[i] == '-' && unary == 1) {
      while (is_number(str[i]) || str[i] == '.' || str[i] == ',') {
        tmp[j] = str[i];
        i++;
        j++;
      }
      number = atof(tmp);
      i--;

      // s21_string_to_double(&str[i], &tmp, &number);
      data.value = number;
      data.type = NUM;

      // printf("NUMBER!!\n");
      push(&stack_n, data);
      // i += tmp - &str[i];
      for (j = strlen(tmp); j > 0; j--) {
        tmp[j] = '\0';
      }
      unary = 0;
      continue;
    }

    if (str[i] == 'p') {
      data.value = PI;
      data.type = NUM;
      push(&stack_n, data);
      continue;
    }

    if (is_operation(str[i]) || ((str[i]) == '-' && unary == 0)) {
      int type = type_operation(str[i]);
      if (isEmpty(stack_o)) {
        data.value = 0;
        data.type = type;
        printf("OPERATOR!!\n");
        push(&stack_o, data);
        continue;
      }
      if (!isEmpty(stack_o) &&
          get_priority(type) > get_priority(peek(stack_o).type)) {
        data.value = 0;
        data.type = type;
        printf("OPERATOR!!\n");
        push(&stack_o, data);
        continue;
      }
      if (!isEmpty(stack_o) &&
          get_priority(type) <= get_priority(peek(stack_o).type)) {
        maths(&stack_n, &stack_o, &data);
        printf("OPERATOR!!\n");
        data.value = 0;
        data.type = type;
        push(&stack_o, data);
        continue;
      }
    }
    if (str[i] == '(') {
      data.value = 0;
      data.type = OPEN;
      push(&stack_o, data);
      continue;
    }
    if (str[i] == ')') {
      while (peek(stack_o).type != OPEN) {
        maths(&stack_n, &stack_o, &data);
      }
      pop(&stack_o);
      continue;
    }
  }

  while (!isEmpty(stack_o)) {
    maths(&stack_n, &stack_o, &data);
  }
  printf("RESULT %lf\n", peek(stack_n).value);
  printf("TYPE %d\n", peek(stack_o).type);
  return 0;
}
