#include "../inc/lib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define DEF_LOWER_MARGIN (1.0f / 4)
#define DEF_UPPER_MARGIN (3.0f / 4)

struct Vec* vec_new_heap() {
  struct Vec* new = malloc(sizeof(struct Vec));
  new->size = 0;
  new->capacity = 16;
  new->arr = (int*)malloc(new->capacity * sizeof(int));
  return new;
}

struct Vec vec_new_stack() {
  struct Vec new;
  new.size = 0;
  new.capacity = 128;
  new.arr = (int*)malloc(new.capacity * sizeof(int));
  return new;
}

size_t vec_delete(struct Vec* vec) {
  int capacity = vec->capacity;
  free(vec->arr);
  free(vec);
  return (capacity + (2 * sizeof(size_t)));
}

size_t resize_down(struct Vec* vec) {
  vec->capacity = vec->capacity / 2;
  int* old_arr = vec->arr;
  int* new_arr = (int*)malloc(vec->capacity * sizeof(int));
  memcpy(new_arr, old_arr, vec->size * sizeof(int));
  vec->arr = new_arr;
  free(old_arr);
  return vec->capacity;
}

size_t resize_up(struct Vec* vec) {
  vec->capacity = vec->capacity * 2;
  int* old_arr = vec->arr;
  int* new_arr = (int*)malloc(vec->capacity * sizeof(int));
  memcpy(new_arr, old_arr, vec->size * sizeof(int));
  vec->arr = new_arr;
  free(old_arr);
  return vec->capacity;
}

size_t resize_on_bounds(struct Vec* vec, size_t lower, size_t upper) {
  if (lower >= upper) {
    return 0;
  }
  if (vec->size < lower) {
    return resize_down(vec);
  }
  if (vec->size > upper) {
    return resize_up(vec);
  }
  return 0;
}

size_t size(struct Vec* vec) { return vec->size; }
size_t capacity(struct Vec* vec) { return vec->capacity; }
int is_empty(struct Vec* vec) { return (vec->capacity == 0); }

int at(struct Vec* vec, size_t index) {
  if (index < vec->size) {
    return *(vec->arr + index);
  }
}

int find(struct Vec* vec, int item) {
  int* cursor = vec->arr;
  int counter = 0;
  while (*cursor != item) {
    if (counter >= vec->size) {
      return -1;
    }
    cursor += 1;
    counter += 1;
  }
  return counter;
}

size_t push(struct Vec* vec, int item) {
  if (vec->size < vec->capacity) {
    resize_on_bounds(vec, vec->capacity * DEF_LOWER_MARGIN, vec->capacity * DEF_UPPER_MARGIN);
  } else {
    resize_up(vec);
  }
  int offset = vec->size;
  *(vec->arr + offset) = item;
  vec->size++;
  return offset;
}

size_t insert(struct Vec* vec, size_t index, int item) {
  // if index is greater than size, push to last place;
  if (index >= vec->size) {
    return push(vec, item);
  } else {
    vec->size++;
    memmove(vec->arr + index + 1, vec->arr + index, (vec->size - index + 1) * sizeof(int));
    *(vec->arr + index) = item;
    resize_on_bounds(vec, vec->capacity * DEF_LOWER_MARGIN, vec->capacity * DEF_UPPER_MARGIN);
    return index;
  }
}

size_t preappend(struct Vec* vec, int item) { return insert(vec, 0, item); }

int pop(struct Vec* vec) {
  vec->size--;
  int item = *(vec->arr + vec->size);
  resize_on_bounds(vec, vec->capacity * DEF_LOWER_MARGIN, vec->capacity * DEF_UPPER_MARGIN);
  return item;
}

int deleete(struct Vec* vec, size_t index) {
  // if index is greater than size, push to last place;
  if (index >= vec->size) {
    return pop(vec);
  } else {
    int item = *(vec->arr + index);
    memmove(vec->arr + index, vec->arr + index + 1, (vec->size - index) * sizeof(int));
    vec->size--;
    resize_on_bounds(vec, vec->capacity * DEF_LOWER_MARGIN, vec->capacity * DEF_UPPER_MARGIN);
    return item;
  }
}

int remove_item(struct Vec* vec, int item) { return deleete(vec, find(vec, item)); }
