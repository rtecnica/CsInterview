#include "inc/lib.h"
#include <stdio.h>
#include <stdlib.h>

void print_int_list(struct llist* list) {
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

int compare_ints(void* i1, void* i2) {
  int a = *(int*)i1;
  int b = *(int*)i2;
  return ((a > b) - (a < b));
}

int main(void) {
  llist myList = llist_init();
  llist* list = &myList;
  printf("Initialize list:\n");
  print_int_list(list);
  printf("Is empty? %d\n", empty(list));
  printf("Populating list with even values on the left, odd values on the right\n");
  for (int i = 0; i < 10; i += 1) {
    int* item = malloc(sizeof(int));
    *item = i;
    if (i % 2 == 0) {
      push_front(list, item);
    } else {
      push_back(list, item);
    }
  }
  print_int_list(list);
  printf("Values at front: %d, and back %d\n", *(int*)front(list), *(int*)back(list));
  printf("Array Length: %d\n", length(list));
  printf("Value at index 4: %d\n", *(int*)value_at(list, 4));
  print_int_list(list);
  for (int i = 0; i < 10; i += 1) {
    if (i % 2 == 0) {
      printf("Value popped from front: %d\n", *(int*)pop_front(list));
    } else {
      printf("Value popped from back: %d\n", *(int*)pop_back(list));
    }
  }
  print_int_list(list);
  printf("Populating list with even values on the right, odd values on the left\n");
  for (int i = 0; i < 10; i += 1) {
    int* item = malloc(sizeof(int));
    *item = i;
    if (i % 2 != 0) {
      push_front(list, item);
    } else {
      push_back(list, item);
    }
  }
  print_int_list(list);
  printf("Erasing value from index 4, value: %d\n", *(int*)erase(list, 4));
  print_int_list(list);
  int* ptr = malloc(sizeof(int));
  *ptr = 1;
  printf("Inserting value 1 into index: %d\n", insert(list, 4, ptr));
  print_int_list(list);
  printf("Next to last value: %d\n", *(int*)value_n_from_end(list, 2));
  printf("Attempting to sort list...\n");
  llist_bubble_sort(list, &compare_ints);
  print_int_list(list);
  printf("Attempting to reverse list...\n");
  reverse(list);
  print_int_list(list);
  int* value_at_4 = value_at(list, 4);
  printf("Index of %d: %d\n", *value_at_4, find(list, value_at_4));
  printf("Removing value %d at index: %d\n", *value_at_4, remove_value(list, value_at_4));
  print_int_list(list);
  size_t n_to_pop = lsize(list);
  for (int i = 0; i < n_to_pop; i += 1) {
    if (i % 2 == 0) {
      printf("Value popped from front: %d\n", *(int*)pop_front(list));
    } else {
      printf("Value popped from back: %d\n", *(int*)pop_back(list));
    }
  }
  print_int_list(list);
  llist_deinit(*list);
}
