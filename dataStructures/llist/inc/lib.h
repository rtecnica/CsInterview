/*
 *
 *
 *
 *
 *
 */
#ifndef LLIST_H
#define LLIST_H

#include <stdio.h>

typedef struct lnode {
  void* item;
  struct lnode* next;
} lnode;

typedef struct llist {
  struct lnode* head;
  struct lnode* tail;
  size_t length;
} llist;

typedef enum llside { head, tail } llside;

struct llist llist_init();

void llist_deinit(struct llist list);

void llist_push(struct llist* list, void* item);

void* llist_pop(struct llist* list, llside side);

void* llist_select(struct llist* list, void* item, int (*compare_fn)(void* item1, void* item2));

void llist_bubble_sort(struct llist* list, int (*compare_fn)(void* item1, void* item2));

void llist_free(struct llist* list);

size_t length(struct llist* list);

size_t lsize(struct llist* list);

size_t empty(struct llist* list);

void* value_at(struct llist* list, size_t index);

size_t push_front(struct llist* list, void* item);

size_t push_back(struct llist* list, void* item);

void* pop_back(struct llist* list);

void* pop_front(struct llist* list);

void* front(struct llist* list);

void* back(struct llist* list);

size_t insert(struct llist* list, size_t index, void* item);

void* erase(struct llist* list, size_t index);

void* value_n_from_end(struct llist* list, size_t offset);

size_t reverse(struct llist* list);

size_t find(struct llist* list, void* item);

size_t remove_value(struct llist* list, void* item);

#endif  // LLIST_H
