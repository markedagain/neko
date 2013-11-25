#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

void vector_init(Vector *v) {
  v->used_entries = 0;
  v->capacity = 8;
  v->data = calloc(sizeof(void *), v->capacity);
}

void vector_init_size(Vector *v, size_t capacity) {
  v->used_entries = 0;
  v->capacity = capacity;
  v->data = calloc(sizeof(void *), v->capacity);
}

int vector_count(Vector *v) {
  return v->used_entries;
}

void vector_free(Vector *v) {
  free(v->data);
}

size_t vector_size(Vector *v) {
  return v->used_entries;
}

void vector_grow(Vector *v, size_t new_size) {
  while (v->capacity < new_size)
    v->capacity *= 2;
  v->data = realloc(v->data, sizeof(void *) * v->capacity);
  assert(v->data);
}

void vector_append(Vector *v, void *e) {
  if (v->used_entries >= v->capacity) {
    vector_grow(v, v->capacity * 2);
  }
  v->data[v->used_entries] = e;
  v->used_entries++;
}

void vector_set(Vector *v, size_t index, void *e) {
  if (index > v->capacity) {
    vector_grow(v, index);
    return; /* needed?? */
  }
  v->data[index] = e;
}

void *vector_get(Vector *v, size_t index) {
  if (index >= v->used_entries)
    return NULL;

  return v->data[index];
}

void *vector_pop(Vector *v, size_t index) {
  void *ret;
  size_t i, j;
  void **newarr;

  if (index >= v->used_entries)
    return NULL;

  ret = v->data[index];
  newarr = (void **)malloc(sizeof(void *) * v->capacity);
  for (i = 0, j = 0; i < v->used_entries; ++i) {
    if (i == index)
      continue;
    newarr[j] = v->data[i];
  }
  free(v->data);
  v->data = newarr;
  v->used_entries--;
  return ret;
}
