#include "inc/lib.h"
#include <stdio.h>

int main(void) {
  struct Vec* myVec = vec_new_heap();
  printf("new heap vec: \n");
  printf("direct size: %d | method size: %d\n", myVec->size, size(myVec));
  printf("capacity: %d | method capacity: %d\n", myVec->capacity, capacity(myVec));
  printf("is_empty (1 is true, 0 is false): %d\n", is_empty(myVec));

  printf("Pushing 11 powers of two to vec...\n");
  for (int i = 1; i <= 1024; i *= 2) {
    push(myVec, i);
  }

  printf("myVec: ");
  for (int i = 0; i < size(myVec); i++) {
    printf("%d ", at(myVec, i));
  }
  printf("\n");

  printf("index of 32: %d\n", find(myVec, 32));
  size_t idx = insert(myVec, 3, 69);
  printf("inserting a 69 at index 3 - index: %d, item: %d\n", idx, at(myVec, 3));

  printf("myVec: ");
  for (int i = 0; i < size(myVec); i++) {
    printf("%d ", at(myVec, i));
  }
  printf("\n");

  printf("preapend 420 - index: %d, item: %d\n", preappend(myVec, 420), at(myVec, 0));
  printf("myVec: ");
  for (int i = 0; i < size(myVec); i++) {
    printf("%d ", at(myVec, i));
  }
  printf("\n");

  printf("pop item - item: %d\n", pop(myVec));
  printf("myVec: ");
  for (int i = 0; i < size(myVec); i++) {
    printf("%d ", at(myVec, i));
  }
  printf("\n");

  printf("delete at index 4 - Item: %d\n", deleete(myVec, 4));
  printf("myVec: ");
  for (int i = 0; i < size(myVec); i++) {
    printf("%d ", at(myVec, i));
  }
  printf("\n");

  printf("Pushing 11 powers of two to vec...\n");
  for (int i = 1; i <= 50; i++) {
    push(myVec, i);
    printf("Size: %d, Capacity: %d \n", size(myVec), capacity(myVec));
  }
  printf("myVec: ");
  for (int i = 0; i < size(myVec); i++) {
    printf("%d ", at(myVec, i));
  }
  printf("\n");

  printf("Poppinf all but one element of vec...\n");
  size_t p = size(myVec);
  for (int i = 0; i < p; i++) {
    pop(myVec);
    printf("idx: %d, Size: %d, Capacity: %d \n", i, size(myVec), capacity(myVec));
  }
  printf("myVec: ");
  for (int i = 0; i < size(myVec); i++) {
    printf("%d ", at(myVec, i));
  }
  printf("\n");
  printf("Freed Mem: %d\n", vec_delete(myVec));
}
