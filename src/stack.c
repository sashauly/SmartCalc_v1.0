#include "stack.h"

// Вспомогательная функция для добавления элемента `x` в stack
void push(struct stack** top, data_t data) {  // вставляем в начало
  struct stack* node = NULL;  // выделяем новый узел в куче
  node = (struct stack*)malloc(sizeof(struct stack));
  if (!node) {  // проверяем, заполнен ли Stack (heap). Тогда вставка элемента
                // может привести к переполнению stack
    printf("Heap Overflow\n");
    exit(-1);
  }
  printf("Inserting {%lf, %c}\n", data.value, data.type);
  node->data = data;
  node->next = *top;  // устанавливаем указатель .next нового узла так, чтобы он
                      // указывал на текущий верхний узел списка
  *top = node;  // обновить верхний указатель
  // node->nodesCount += 1;  // увеличить размер stack на 1
}

// Вспомогательная функция для извлечения верхнего элемента из stack
data_t pop(struct stack** top) {  // удалить в начале
  struct stack* node;
  if (*top == NULL) {  // проверка на опустошение stack
    printf("Stack Underflow\n");
    exit(EXIT_FAILURE);
  }
  data_t x = peek(*top);  // принять к сведению данные верхнего узла
  printf("Removing {%lf, %c}\n", x.value, x.type);
  node = *top;
  *top = (*top)->next;  // обновляем верхний указатель, чтобы он указывал на
                        // следующий узел
  // node->nodesCount -= 1;  // уменьшить размер stack на 1
  free(node);  // освободить выделенную память
  return x;
}

// Вспомогательная функция для проверки, пуст stack или нет
int isEmpty(struct stack* top) { return top == NULL; }

// Вспомогательная функция для возврата верхнего элемента stack
data_t peek(struct stack* top) {
  if (!isEmpty(top)) {  // проверка на пустой stack
    return top->data;
  } else {
    printf("The stack is empty\n");
    exit(EXIT_FAILURE);
  }
}

// // Вспомогательная функция для возврата числа узлов stack
// int size(struct stack* node) { return node->nodesCount; }