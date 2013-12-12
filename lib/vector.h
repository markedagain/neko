#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct vector_t {
  void **data;
  size_t used_entries;
  size_t capacity;
} VECTOR;

void vector_init(VECTOR *);
void vector_init_size(VECTOR *, size_t);
void vector_free(VECTOR *);
size_t vector_size(VECTOR *);
size_t vector_capacity(VECTOR *);
void vector_grow(VECTOR *, size_t);
void vector_append(VECTOR *, void *);
void vector_set(VECTOR *, size_t, void *);
void *vector_get(VECTOR *, size_t);
void *vector_pop(VECTOR *, size_t);
int vector_index(VECTOR *, void *);
void vector_remove(VECTOR *, void *);

#endif
