#include "parser.h"
void maths(struct stack** stack_n, struct stack** stack_o, data_t* data) {
  double a = 0, b = 0, c = 0;
  a = (peek(*stack_n).value);
  pop(stack_n);
  switch (peek(*stack_o).type) {
    case '+':
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = a + b;
      data->value = c;
      data->type = '0';
      push(stack_n, *data);
      pop(stack_o);
      break;

    case '-':
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = b - a;
      data->value = c;
      data->type = '0';
      push(stack_n, *data);
      pop(stack_o);
      break;

    case '*':
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = b * a;
      data->value = c;
      data->type = '0';
      push(stack_n, *data);
      pop(stack_o);
      break;

    case '/':
      if (a != 0) {
        b = (peek(*stack_n).value);
        pop(stack_n);
        c = b / a;
        data->value = c;
        data->type = '0';
        push(stack_n, *data);
        pop(stack_o);
      } else {
        fprintf(stderr, "Сan't divide by zero\n");
        exit(EXIT_FAILURE);
      }
      break;

    case '^':
      b = (peek(*stack_n).value);
      pop(stack_n);
      c = pow(b, a);
      data->value = c;
      data->type = '0';
      push(stack_n, *data);
      pop(stack_o);
      break;

    default:
      break;
  }
}

int get_priority(char ch) {
  int priority = 0;
  if (ch == '+' || ch == '-') priority = 1;
  if (ch == '*' || ch == '/') priority = 2;
  if (ch == '^') priority = 3;
  return priority;
}

int s21_string_to_double(char* str, char** end, double* number) {
  int flag = 1;
  double num = 0;
  int dot = 0;
  size_t i = 0;
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
  *number = num;
  return flag;
}

int main() {
  char str[256] = "-(2^7)-334";  // НИФИГА НЕ РАБОТАЕТ ОДИНАКОВЫЙ ПРИОРИТЕТ!!!
  double number = 0;
  struct stack* stack_n = NULL;
  struct stack* stack_o = NULL;
  data_t data = {0, '\0'};
  char* tmp = {0};
  int un_minus = 1;

  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == ' ') {
      continue;
    }
    if (is_number(str[i]) || str[i] == '-' && un_minus == 1) {
      s21_string_to_double(&str[i], &tmp,
                           &number);  // СДЕЛАТЬ НОРМАЛЬНЫЙ ПАРСЕР НА ДАБЛЛ
      data.value = number;
      data.type = '0';
      printf("NUMBER\n");
      push(&stack_n, data);
      i += tmp - &str[i];
      un_minus = 0;
      // continue;
    }

    if ((str[i]) == '+' || (str[i]) == '-' && un_minus == 0 ||
        (str[i]) == '*' || (str[i]) == '/' || (str[i]) == '^') {
      if (isEmpty(stack_o)) {
        data.value = 0;
        data.type = str[i];
        printf("OPERATOR\n");
        push(&stack_o, data);
        continue;
      }
      if (!isEmpty(stack_o) &&
          get_priority(str[i]) > get_priority(peek(stack_o).type)) {
        data.value = 0;
        data.type = str[i];
        printf("OPERATOR\n");
        push(&stack_o, data);
        continue;
      }
      if (!isEmpty(stack_o) &&
          get_priority(str[i]) <= get_priority(peek(stack_o).type)) {
        maths(&stack_n, &stack_o, &data);
        continue;
      }
    }
    if (str[i] == '(') {  //Если прочитана открывающаяся скобка
      data.value = 0;
      data.type = str[i];
      printf("OPERATOR\n");
      push(&stack_o, data);
      continue;
    }
    if (str[i] == ')') {  //Если прочитана закрывающаяся скобка
      while (peek(stack_o).type != '(') {
        maths(&stack_n, &stack_o, &data);  //Если функция вернет "false", то
        //прекращаем работу Если все        хорошо
      }
      pop(&stack_o);
    }
    // } else {  //Если прочитан какой-то странный символ
    //   fprintf(stderr, "ERROR!\n");
    //   exit(EXIT_FAILURE);
    // }
  }

  while (!isEmpty(stack_o)) {
    maths(&stack_n, &stack_o, &data);
  }
  printf("RESULT %lf\n", peek(stack_n).value);
  return 0;
}
