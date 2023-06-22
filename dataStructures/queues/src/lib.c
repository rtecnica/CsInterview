#include "../inc/lib.h"
#include "../inc/llist.h"
#include <stdlib.h>
#include <string.h>

#define QUEUE_ITEM_TYPE int

llqueue* queue_init(void) {
  llqueue* p = malloc(sizeof(llqueue));
  llqueue np = llist_init();
  p = memcpy(p, (llqueue*)(&np), sizeof(llqueue));
  return p;
}

int llenqueue(llqueue* q, void* value) {
  if (push_front((llist*)q, value) == 0) {
    return 0;
  } else {
    return 1;
  }
}
void* lldequeue(llqueue* q) { return pop_back((llist*)q); }
int llempty(llqueue* q) { return (int)empty((llist*)q); }

// Implement using fixed-sized array:
aqueue aqueue_init(size_t size) {
  aqueue q;
  q.size = size;
  q.cursor = 0;
  q.array = malloc(size * sizeof(void*));
  return q;
}

int afull(aqueue* q) {
  if (q->cursor == q->size) {
    return 1;
  } else {
    return 0;
  }
}

int aenqueue(aqueue* q, void* value) {
  if (!afull(q)) {
    q->array[q->cursor] = value;
    q->cursor++;
    return 1;
  } else {
    return 0;
  }
}

int aempty(aqueue* q) {
  if (q->cursor == 0) {
    return 1;
  } else {
    return 0;
  }
}

void* adequeue(aqueue* q) {
  if (!aempty(q)) {
    void* ptr = q->array[q->cursor - 1];
    q->cursor--;
    return ptr;
  } else {
    return NULL;
  }
}
