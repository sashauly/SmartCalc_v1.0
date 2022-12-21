#include "stack.h"

void push(struct stack** top, data_t data) {
  struct stack* node = NULL;
  node = (struct stack*)malloc(sizeof(struct stack));
  if (!node) {
    printf("Heap Overflow\n");
    exit(-1);
  }
  printf("Inserting {%lf, %d}\n", data.value, data.type);
  node->data = data;
  node->next = *top;
  *top = node;
  // node->nodesCount += 1;
}

data_t pop(struct stack** top) {
  struct stack* node;
  if (*top == NULL) {
    printf("Stack Underflow\n");
    exit(EXIT_FAILURE);
  }
  data_t x = peek(*top);
  printf("Removing {%lf, %d}\n", x.value, x.type);
  node = *top;
  *top = (*top)->next;
  // node->nodesCount -= 1;
  free(node);
  return x;
}

int isEmpty(struct stack* top) { return top == NULL; }

data_t peek(struct stack* top) {
  if (!isEmpty(top)) {
    return top->data;
  } else {
    printf("The stack is empty\n");
    exit(EXIT_FAILURE);
  }
}

// int size(struct stack* node) { return node->nodesCount; }
