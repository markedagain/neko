#ifndef __LIST_H__
#define __LIST_H__

typedef struct {
  /* private */
  void** data;
  size_t used_entries;
  size_t capacity;
} Vector;

void vector_init(Vector *);
void vector_init_size(Vector *, size_t);
void vector_free(Vector *);
size_t vector_size(Vector *);
size_t vector_capacity(Vector *);
void vector_grow(Vector *, size_t);
void vector_append(Vector *, void *);
void vector_set(Vector *, size_t, void *);
void *vector_get(Vector *, size_t);
void *vector_pop(Vector *, size_t);
int vector_index(Vector *, void *);
void vector_remove(Vector *, void *);

#endif
