/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "vector.h"

typedef struct dict_t {
  VECTOR keys;
  VECTOR values;
  VECTOR empties;
  int count;
} DICT;

void dict_init(DICT *);
void sdict_set(DICT *, char *, void *);
void *sdict_get(DICT *, char *);
void sdict_remove(DICT *, char *);
void sdict_free(DICT *);

#endif