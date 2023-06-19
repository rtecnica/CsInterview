// Library for implementing dynamically sized arrays
#include <stdlib.h>

// Struct Typedef
typedef struct Vec {
  size_t size;
  size_t capacity;
  int* arr;
} Vec_t;

struct Vec* vec_new_heap(void);
struct Vec vec_new_stack(void);

size_t vec_delete(struct Vec* vec);

size_t resize(struct Vec* vec);

size_t size(struct Vec* vec);
size_t capacity(struct Vec* vec);

int is_empty(struct Vec* vec);
int at(struct Vec* vec, size_t index);
int find(struct Vec* vec, int item);

size_t push(struct Vec* vec, int item);
size_t insert(struct Vec* vec, size_t index, int item);
size_t preappend(struct Vec* vec, int item);

int pop(struct Vec* vec);
int deleete(struct Vec* vec, size_t index);
int remove_item(struct Vec* vec, int item);
