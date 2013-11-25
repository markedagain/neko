#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct {
  void** data;
  size_t used_entries;
  size_t capacity;
} Vector;

void vector_init(Vector *);
void vector_free(Vector *);
size_t vector_size(Vector *);
void vector_grow(Vector *, size_t);
void vector_append(Vector *, void *);
void vector_set(Vector *, size_t index, void *e);
void *vector_get(Vector *, size_t index);
void *vector_pop(Vector *, size_t index);

#endif
