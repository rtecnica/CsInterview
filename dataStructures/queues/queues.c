#include "inc/lib.h"
#include <stdlib.h>

void print_int_llqueue(llqueue* q) {
  llist* list = (llist*)q;
  if (empty(list)) {
    printf("Empty list!\n");
  } else {
    lnode* cursor = list->head;
    printf("H -> ");
    while (cursor != NULL) {
      printf("%d -> ", *(int*)(cursor->item));
      cursor = cursor->next;
    }
    printf("NULL\n");
  }
}

void print_int_aqueue(aqueue* q) {
  if (aempty(q)) {
    printf("Empty Queue!\n");
    return;
  }
  printf("H -> ");
  for (int i = 0; i < q->size; i++) {
    printf("%d -> ", *(int*)q->array[i]);
  }
  printf("NULL");
  if (afull(q)) {
    printf(" - Full!\n");
  } else {
    printf("\n");
  }
}

int main(void) {
  printf("Testing llist queues...\n");
  printf("Initialized list queue...\n");

  llqueue* q = queue_init();
  printf("Is Empty: %d\n", llempty(q));
  printf("Filling queue...");
  for (int i = 0; i < 10; i++) {
    int* value = malloc(sizeof(int));
    *value = i;
    llenqueue(q, value);
  }
  print_int_llqueue(q);
  printf("Dequeuing... val: %d\n", *(int*)lldequeue(q));
  printf("Dequeuing... val: %d\n", *(int*)lldequeue(q));
  printf("Dequeuing... val: %d\n", *(int*)lldequeue(q));
  print_int_llqueue(q);

  printf("\nTesting array queues...\n");
  printf("Initialized array queue...\n");
  aqueue arrayQueue = aqueue_init(10);
  aqueue* qq = &arrayQueue;
  printf("Is Empty: %d\n", aempty(qq));
  printf("Filling queue to capacity...\n");
  for (int i = 0; i < 10; i++) {
    int* value = malloc(sizeof(int));
    *value = i;
    aenqueue(qq, value);
  }

  printf("Is Empty: %d\n", aempty(qq));
  printf("Is Full: %d\n", afull(qq));
  print_int_aqueue(qq);
  printf("Dequeuing all elements: \n");
  while (1) {
    int* ptr = adequeue(qq);
    if (ptr != NULL) {
      printf("%d -> ", *ptr);
    } else {
      printf("NULL\n");
      break;
    }
  }
  print_int_aqueue(qq);
}
