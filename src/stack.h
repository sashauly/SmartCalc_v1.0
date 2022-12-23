#ifndef SRC_STACK_H
#define SRC_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  NUM = 1,
  SUM,
  SUB,
  MULT,
  DIV,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  LN,
  LOG,
  SQRT,
  POW,
  OPEN,
  CLOSED
} lexeme_enum;

typedef struct data_t {
  double value;
  lexeme_enum type;
} data_t;

struct stack {
  data_t data;
  struct stack* next;
};

void push(struct stack** top, data_t data);
data_t pop(struct stack** top);
data_t peek(struct stack* top);
int is_empty(struct stack* top);

#endif  // SRC_STACK_H