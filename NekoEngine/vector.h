/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include "neko.h"

typedef struct vector_t {
  void **data;
  size_t used_entries;
  size_t capacity;
} VECTOR;

NEKO_API void vector_init(VECTOR *);
NEKO_API void vector_init_size(VECTOR *, size_t);
NEKO_API void vector_free(VECTOR *);
NEKO_API size_t vector_size(VECTOR *);
NEKO_API size_t vector_capacity(VECTOR *);
NEKO_API void vector_grow(VECTOR *, size_t);
NEKO_API void vector_append(VECTOR *, void *);
NEKO_API void vector_set(VECTOR *, size_t, void *);
NEKO_API void *vector_get(VECTOR *, size_t);
NEKO_API void *vector_pop(VECTOR *, size_t);
NEKO_API int vector_index(VECTOR *, void *);
NEKO_API void vector_remove(VECTOR *, void *);

#endif
