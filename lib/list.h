#ifndef __LIST_H__
#define __LIST_H__

typedef struct {
  /* private */
  void** data;
  size_t used_entries;
  size_t capacity;
} List;

void list_init(List *);
void list_init_size(List *, size_t);
void list_free(List *);
size_t list_size(List *);
size_t list_capacity(List *);
void list_grow(List *, size_t);
void list_append(List *, void *);
void list_set(List *, size_t, void *);
void *list_get(List *, size_t);
void *list_pop(List *, size_t);
int list_index(List *, void *);
void list_remove(List *, void *);

#endif
