#include "parser.h"
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
  } else if ((ch) == 'm') {
    type = MOD;
  } else if ((ch) == '^') {
    type = POW;
  }
  return type;
}

void remove_spaces(char* data) {  // удаляем пробелы.. как эта хрень работает?
  char* i = data;
  char* j = data;
  while (*j != 0) {
    *i = *j++;
    if (*i != ' ') i++;
  }
  *i = 0;
}

int main() {
  char str[256] = "sin(-1^2)";
  double number = 0;
  struct stack* stack_n = NULL;
  struct stack* stack_o = NULL;
  data_t data = {0, '\0'};
  char tmp[256] = {0};

  remove_spaces(str);
  for (int i = 0; i < (int)strlen(str); i++) {
    memset(tmp, '\0', 256);

    if (str[i] == 's' || str[i] == 'c' || str[i] == 't') {
      char func[3] = {0};
      for (int j = 0; j < 3; j++) {
        func[j] = str[i];
        i++;
      }
      i--;
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

    if ((str[i] == '-' && i == 0) ||
        (i > 0 && str[i] == '-' && str[i - 1] == '(')) {
      data.value = 0;
      data.type = NUM;
      push(&stack_n, data);
      data.value = 0;
      data.type = SUB;
      push(&stack_o, data);
      continue;
    }

    if ((str[i] == '+' && i == 0) ||
        (i > 0 && str[i] == '+' && str[i - 1] == '(')) {
      data.value = 0;
      data.type = NUM;
      push(&stack_n, data);
      data.value = 0;
      data.type = SUM;
      push(&stack_o, data);
      continue;
    }

    if (is_number(str[i])) {
      int error = 0;
      int exit_fun = 0;
      int count_dot = 0;
      for (int j = 0; exit_fun != 1; j++) {
        if (str[i] == ',') str[i] = '.';  // если ',' меняем на '.'
        if (str[i] == '.') count_dot++;
        tmp[j] = str[i];
        i++;

        // если i+1 тоже цифра или точка - продолжаем цикл
        if (is_number(str[i]) || str[i] == '.') {
          continue;
        } else {
          exit_fun = 1;
        }
      }
      i--;
      if (count_dot > 1) {
        error = 1;
      } else {
        data.value = atof(tmp);  // преобразуем массив цифр в число
        data.type = NUM;
      }
      push(&stack_n, data);
      continue;
    }

    if (str[i] == 'p') {
      data.value = PI;
      data.type = NUM;
      push(&stack_n, data);
      continue;
    }

    if (is_operation(str[i]) ||
        (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd')) {
      int type = type_operation(str[i]);
      if (isEmpty(stack_o)) {
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
        }
        if (get_priority(type) <= get_priority(peek(stack_o).type)) {
          maths(&stack_n, &stack_o, &data);
          i--;
          continue;
        }
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
  return 0;
}
