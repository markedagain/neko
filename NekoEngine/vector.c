/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "vector.h"

/* initialize a vector with the default size */
void vector_init(VECTOR *v) {
  v->used = 0;
  v->capacity = VECTOR_DEFAULTCAPACITY;
  v->data = (void **)calloc(sizeof(void *), v->capacity);
}

/* initialize a vector with a defined size */
void vector_init_size(VECTOR *v, size_t capacity) {
  v->used = 0;
  v->capacity = capacity;
  v->data = (void **)calloc(sizeof(void *), v->capacity);
}

/* free a vector */
void vector_free(VECTOR *v) {
  free(v->data);
}

void vector_destroy(VECTOR *v) {
  size_t i;
  for (i = 0; i < v->used; ++i) {
    free(vector_get(v, i));
  }
  free(v->data);
}

void vector_clear(VECTOR *v) {
  size_t i;
  for (i = 0; i < v->used; ++i) {
    free(vector_get(v, i));
  }
  free(v->data);
  vector_init(v);
}

/* returns the number of used entries of the vector */
size_t vector_size(VECTOR *v) {
  return v->used;
}

/* returns the capacity of the vector (mostly used for debugging) */
size_t vector_capacity(VECTOR *v) {
  return v->capacity;
}

/* double the capacity of a vector until it has room to fit the desired size */
void vector_grow(VECTOR *v, size_t new_size) {
  while (v->capacity < new_size)
    v->capacity *= 2;
  v->data = (void **)realloc(v->data, sizeof(void *) * v->capacity);
  assert(v->data);
}

/* append a new entry to the end of a vector */
void vector_append(VECTOR *v, void *e) {
  if (v->used >= v->capacity) {
    vector_grow(v, v->capacity + 1);
  }
  v->data[v->used] = e;
  v->used++;
}

/* ??? set the value of a specific entry in a vector */
void vector_set(VECTOR *v, size_t index, void *e) {
  if (index > v->capacity) {
    vector_grow(v, index);
    return; /* needed?? */
  }
  v->data[index] = e;
}

/* get the value of a specific entry in a vector */
void *vector_get(VECTOR *v, size_t index) {
  if (index >= v->used)
    return NULL;

  return v->data[index];
}

/* pop an entry out of the vector and reorder the rest of the entries (WARNING: SLOW) */
void *vector_pop(VECTOR *v, size_t index) {
  void *ret;
  size_t i, j;
  void /* zackeree 'remscarf' */ **new_arr;
  if (index >= v->used)
    return NULL;

  ret = v->data[index];
  new_arr = (void **)malloc(sizeof(void *) * v->capacity);
  for (i = 0, j = 0; i < v->used; ++i) {
    if (i == index)
      continue;
    new_arr[j++] = v->data[i];
  }
  free(v->data);
  v->data = new_arr;
  v->used--;
  return ret;
}

/* get the index of the given void pointer in the vector (returns -1 if not in the vector) */
int vector_index(VECTOR *v, void *e) {
  unsigned int i;
  for (i = 0; i < vector_size(v); ++i)
    if (vector_get(v, i) == e)
      return i;
  return -1;
}

/* remove a specific entry from a vector, if it is indeed in the vector */
void vector_remove(VECTOR *v, void *e) {
  int i = vector_index(v, e);
  if (i == -1)
    return;
  vector_pop(v, i);
}
