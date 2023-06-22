#include "../inc/lib.h"
#include "../inc/llist.h"
#include <stdlib.h>

llqueue* queue_init(void) {
  llqueue* p = malloc(sizeof(llqueue));
  llqueque np;
}
}

int llenqueue(llqueue* q, void* value);  //- adds value at position at tail
void* lldequeue(llqueue* q);             //- returns value and removes least recently added element (front)
int llempty(llqueue* q);

// Implement using fixed-sized array:
int aenqueue(aqueue* q, void* value);  //- adds item at end of available storage
void* adequeue(aqueue* q);             //- returns value and removes least recently added element
int aempty(aqueue* q);
int full(aqueue* q);
