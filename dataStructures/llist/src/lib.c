/*
 *
 *
 *
 *
 */

#include "../inc/lib.h"
#include <stdio.h>
#include <stdlib.h>

struct llist llist_init() {
  struct llist list;
  list.length = 0;
  list.head = NULL;
  list.tail = NULL;
  return list;
}

void llist_deinit(struct llist list) {
  void* ptr = llist_pop(&list, head);
  while (ptr != NULL) {
    free(ptr);
    ptr = llist_pop(&list, head);
  }
  list.tail = NULL;

  if (list.head == NULL && list.tail == NULL) {
    return;
  } else {
    printf("Something went wrong!");
  }
}

void llist_push(struct llist* list, void* item) {
  struct lnode* new = malloc(sizeof(lnode));
  new->item = item;
  new->next = NULL;

  if (list->length > 0) {
    list->tail->next = new;
    list->tail = new;
  } else {
    list->tail = new;
    list->head = new;
  }
  list->length++;
}

void* llist_pop(struct llist* list, llside side) {
  if (list->head == NULL) {
    return NULL;
  }
  struct lnode* popped_node;
  void* popped_item;
  switch (side) {
  case head: {
    popped_node = list->head;
    popped_item = list->head->item;
    list->head = popped_node->next;
    break;
  }
  case tail: {
    popped_node = list->tail;
    popped_item = list->tail->item;
    if (list->head == list->tail) {
      list->head = NULL;
      list->tail = NULL;
    } else {
      struct lnode* cursor = list->head;
      while (cursor->next != popped_node && cursor->next != NULL) {
        cursor = cursor->next;
      }
      cursor->next = NULL;
      list->tail = cursor;
    }
    break;
  }
  }
  list->length--;
  return popped_item;
}

void* llist_select(struct llist* list, void* item, int (*compare_fn)(void* item1, void* item2)) {
  struct lnode* ptr = list->head;

  while (ptr != NULL) {
    if (compare_fn(ptr->item, item) == 0) {
      break;
    }
    ptr = ptr->next;
  }

  if (ptr == NULL) {
    return NULL;
  } else {
    return ptr->item;
  }
}

struct lnode** unpack_array(struct llist* list) {
  struct lnode** array = malloc(sizeof(void*) * list->length);
  struct lnode* ptr = list->head;
  int i = 0;
  while (ptr != NULL) {
    array[i] = ptr;
    ptr = ptr->next;
    i++;
  }
  return array;
}

size_t pack_array(struct lnode** source, struct llist* dest) {
  if (source == NULL) {
    return 0;
  }

  struct lnode* ptr = dest->head;
  dest->head = source[0];
  int j;
  for (j = 0; j < dest->length; j++) {
    ptr->next = source[j];
    ptr = ptr->next;
  }
  dest->tail = ptr;
  ptr->next = NULL;
  return j + 1;
}

// PROTIP: Sort linked lists by turning them into arrays first
void llist_bubble_sort(struct llist* list, int (*compare_fn)(void* item1, void* item2)) {
  struct lnode** array = unpack_array(list);

  int swapped_this_pass = 1;
  while (swapped_this_pass) {
    swapped_this_pass = 0;
    for (int j = 0; j < list->length - 1; j++) {
      if (compare_fn(array[j]->item, array[j + 1]->item) == 1) {
        struct lnode* temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        swapped_this_pass = 1;
      }
    }
  }
  pack_array(array, list);
  free(array);
}

size_t count_chain(struct lnode* node) {
  size_t counter = 0;
  if (node->next == NULL) {
    return 1;
  } else {
    return 1 + count_chain(node->next);
  }
}

size_t length(struct llist* list) { return list->length; }

size_t empty(struct llist* list) {
  if (list->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

size_t lsize(struct llist* list) {
  struct lnode* cursor = list->head;
  if (empty(list)) {
    return 0;
  } else {
    return count_chain(list->head);
  }
}

struct lnode* traverse_n_nodes(struct lnode* node, size_t length) {
  size_t counter = 0;
  struct lnode* cursor = node;
  while (counter < length) {
    if (cursor->next == NULL) {
      return cursor;
    } else {
      cursor = cursor->next;
      counter++;
    }
  }
  return cursor;
}

void* value_at(struct llist* list, size_t index) {
  if (empty(list) || index >= list->length) {
    return NULL;
  } else {
    return traverse_n_nodes(list->head, index)->item;
  }
}

size_t push_front(struct llist* list, void* item) {
  struct lnode* new = malloc(sizeof(lnode));
  new->item = item;
  new->next = list->head;
  if (list->head == NULL) {
    list->tail = new;
  }
  list->head = new;
  list->length++;
  return 0;
}

size_t push_back(struct llist* list, void* item) {
  struct lnode* new = malloc(sizeof(lnode));
  new->item = item;
  list->length++;
  if (list->tail == NULL) {
    new->next = NULL;
    list->head = new;
    list->tail = new;
    return 1;
  } else {
    new->next = list->tail->next;
    list->tail->next = new;
    list->tail = new;
    return list->length - 1;
  }
}

void* pop_back(struct llist* list) { return llist_pop(list, tail); }

void* pop_front(struct llist* list) { return llist_pop(list, head); }

void* front(struct llist* list) { return list->head->item; }

void* back(struct llist* list) { return list->tail->item; };

size_t insert(struct llist* list, size_t index, void* item) {
  if (index == 0) {
    return push_front(list, item);
  }
  struct lnode* before_node = traverse_n_nodes(list->head, index - 1);
  struct lnode* after_node = before_node->next;
  struct lnode* inserted_node = malloc(sizeof(lnode));
  inserted_node->item = item;
  inserted_node->next = after_node;
  before_node->next = inserted_node;
  return index;
}

void* erase(struct llist* list, size_t index) {
  if (index == 0) {
    return pop_front(list);
  }
  struct lnode* before_node = traverse_n_nodes(list->head, index - 1);
  struct lnode* deleted_node = before_node->next;
  struct lnode* after_node = deleted_node->next;
  before_node->next = after_node;
  void* deleted_item = deleted_node->item;
  free(deleted_node);
  return deleted_item;
}

void* value_n_from_end(struct llist* list, size_t offset) {
  if (empty(list) || offset >= list->length) {
    return NULL;
  }
  size_t n_to_traverse = list->length - offset;
  return traverse_n_nodes(list->head, n_to_traverse)->item;
}

size_t reverse(struct llist* list) {
  struct lnode** array = unpack_array(list);
  int bcursor = list->length - 1;
  int fcursor = 0;
  while (fcursor < list->length && bcursor > fcursor) {
    struct lnode* holder = array[fcursor];
    array[fcursor] = array[bcursor];
    array[bcursor] = holder;
    fcursor++;
    bcursor--;
  }
  return pack_array(array, list);
}

size_t find(struct llist* list, void* item) {
  struct lnode* cursor = list->head;
  size_t counter = 0;
  while (cursor != NULL && cursor->item != item) {
    cursor = cursor->next;
    counter++;
  }
  return counter;
}

size_t remove_value(struct llist* list, void* item) {
  size_t index = find(list, item);
  erase(list, index);
  return index;
}
