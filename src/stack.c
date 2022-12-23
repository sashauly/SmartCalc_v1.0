#include "stack.h"

void push(struct stack** top, data_t data) {
  struct stack* node = NULL;
  node = (struct stack*)malloc(sizeof(struct stack));
  if (!node) {
    printf("Heap Overflow\n");
    exit(EXIT_FAILURE);
  }
  printf("Inserting {%lf, %d}\n", data.value, data.type);
  node->data = data;
  node->next = *top;
  *top = node;
}

data_t pop(struct stack** top) {
  struct stack* node;
  if (is_empty(*top)) {
    printf("Stack Underflow\n");
    exit(EXIT_FAILURE);
  }
  data_t x = peek(*top);
  printf("Removing {%lf, %d}\n", x.value, x.type);
  node = *top;
  *top = (*top)->next;
  free(node);
  return x;
}

data_t peek(struct stack* top) {
  if (!is_empty(top)) {
    return top->data;
  } else {
    printf("The stack is empty\n");
    exit(EXIT_FAILURE);
  }
}

int is_empty(struct stack* top) { return top == NULL; }
