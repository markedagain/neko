#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "list.h"

/* initialize a list with the default size */
void list_init(List *v) {
  v->used_entries = 0;
  v->capacity = 8;
  v->data = calloc(sizeof(void *), v->capacity);
}

/* initialize a list with a defined size */
void list_init_size(List *v, size_t capacity) {
  v->used_entries = 0;
  v->capacity = capacity;
  v->data = calloc(sizeof(void *), v->capacity);
}

/* free a list */
void list_free(List *v) {
  free(v->data);
}

/* returns the number of used entries of the list */
size_t list_size(List *v) {
  return v->used_entries;
}

/* returns the capacity of the list (mostly used for debugging) */
size_t list_capacity(List *v) {
  return v->capacity;
}

/* double the capacity of a list until it has room to fit the desired size */
void list_grow(List *v, size_t new_size) {
  while (v->capacity < new_size)
    v->capacity *= 2;
  v->data = realloc(v->data, sizeof(void *) * v->capacity);
  assert(v->data);
}

/* append a new entry to the end of a list */
void list_append(List *v, void *e) {
  if (v->used_entries >= v->capacity) {
    list_grow(v, v->capacity + 1);
  }
  v->data[v->used_entries] = e;
  v->used_entries++;
}

/* ??? set the value of a specific entry in a list */
void list_set(List *v, size_t index, void *e) {
  if (index > v->capacity) {
    list_grow(v, index);
    return; /* needed?? */
  }
  v->data[index] = e;
}

/* get the value of a specific entry in a list */
void *list_get(List *v, size_t index) {
  if (index >= v->used_entries)
    return NULL;

  return v->data[index];
}

/* pop an entry out of the list and reorder the rest of the entries (WARNING: SLOW) */
void *list_pop(List *v, size_t index) {
  void *ret;
  size_t i, j;
  void /* zackeree 'remscarf' */ **new_arr;
  if (index >= v->used_entries)
    return NULL;

  ret = v->data[index];
  new_arr = (void **)malloc(sizeof(void *) * v->capacity);
  for (i = 0, j = 0; i < v->used_entries; ++i) {
    if (i == index)
      continue;
    new_arr[j] = v->data[i];
  }
  free(v->data);
  v->data = new_arr;
  v->used_entries--;
  return ret;
}

/* get the index of the given void pointer in the list (returns -1 if not in the list) */
int list_index(List *v, void *e) {
  int i;
  for (i = 0; i < list_size(v); ++i)
    if (list_get(v, i) == e)
      return i;
  return -1;
}

/* remove a specific entry from a list, if it is indeed in the list */
void list_remove(List *v, void *e) {
  int i = list_index(v, e);
  printf("%i\n", i);
  if (i == -1)
    return;
  list_pop(v, i);
}
