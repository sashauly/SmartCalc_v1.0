#ifndef SRC_STACK_H
#define SRC_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct data_t {
  double value;
  char type;
} data_t;

struct stack {
  data_t data;
  struct stack* next;
};

void push(struct stack** top, data_t data);
data_t pop(struct stack** top);
int isEmpty(struct stack* top);
data_t peek(struct stack* top);
int size(struct stack* node);

#endif  // SRC_STACK_H