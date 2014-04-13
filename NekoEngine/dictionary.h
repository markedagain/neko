/******************************************************************************
Filename: dictionary.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <string.h>
#include <stdlib.h>
#include "neko.h"
#include "hash.h"

#define DICT_DEFAULTCAPACITY 8

typedef struct dict_t {
  unsigned int *keys;
  void **values;
  size_t used;
  size_t capacity;
} DICT;

NEKO_API void dict_init(DICT *dictionary);
NEKO_API void dict_init_size(DICT *dictionary, size_t size);
NEKO_API void dict_set(DICT *dictionary, const char *key, void *value);
NEKO_API void *dict_get(DICT *dictionary, const char *key);
NEKO_API void dict_remove(DICT *dictionary, const char *key);
NEKO_API void dict_free(DICT *dictionary);

NEKO_API void dict_destroy(DICT *dict);

void dict_grow(DICT *dictionary, size_t size);

#endif