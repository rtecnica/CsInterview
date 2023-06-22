// Implement using linked-list, with tail pointer:

#include "llist.h"

typedef llist llqueue;

llqueue* queue_init(void);

int llenqueue(llqueue* q, void* value);  //- adds value at position at tail
void* lldequeue(llqueue* q);             //- returns value and removes least recently added element (front)
int llempty(llqueue* q);

// Implement using fixed-sized array:

typedef struct ArrayQueue {
  int size;
  int item_size;
  void** array;
} aqueue;

int aenqueue(aqueue* q, void* value);  //- adds item at end of available storage
void* adequeue(aqueue* q);             //- returns value and removes least recently added element
int aempty(aqueue* q);
int full(aqueue* q);
