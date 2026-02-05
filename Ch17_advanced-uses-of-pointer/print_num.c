#include <stdio.h>
#include <stdlib.h>

#define TEST_DATA 100

struct node {
  int value;
  struct node* next;
};

struct node* add_new_node(struct node* list, int n);

int main(void) {
  struct node* first = NULL;

  // 填入 data
  for (int i = TEST_DATA; i > 0; i--) {
    first = add_new_node(first, i);
  }

  // 列印出結果
  for (struct node *p = first; p != NULL ; p = p->next) {
    printf("%d ", p->value);
  }
  printf("\n");

  return 0;
}

struct node* add_new_node(struct node* list, int n) {
  struct node* new_node;

  new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("--- No space ---");
    exit(EXIT_FAILURE);
  }

  // 將 data 填入 linked list 中
  new_node->value = n;

  new_node->next = list;
  list = new_node;

  return list;
}

