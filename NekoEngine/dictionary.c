/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "dictionary.h"
#include "util.h"

void dict_init(DICT *dict) {
  dict->used = 0;
  dict->capacity = DICT_DEFAULTCAPACITY;
  dict->keys = (unsigned int *)calloc(sizeof(unsigned int), dict->capacity);
  dict->values = (void **)calloc(sizeof(void *), dict->capacity);
}

void dict_init_size(DICT *dict, size_t size) {
  dict->used = 0;
  dict->capacity = size;
  dict->keys = (unsigned int *)calloc(sizeof(unsigned int), dict->capacity);
  dict->values = (void **)calloc(sizeof(void *), dict->capacity);
}

void dict_free(DICT *dict) {
  free(dict->keys);
  free(dict->values);
}

void dict_grow(DICT *dict, size_t size) {
  while (dict->capacity < size)
    dict->capacity *= 2;
  dict->keys = (unsigned int *)realloc(dict->keys, sizeof(unsigned int) * dict->capacity);
  dict->values = (void **)realloc(dict->values, sizeof(void *) * dict->capacity);
}

void dict_set(DICT *dict, const char *key, void *value) {
  if (dict->used >= dict->capacity)
    dict_grow(dict, dict->capacity + 1);
  dict->keys[dict->used] = hash_string(key);
  dict->values[dict->used] = value;
  dict->used++;
}
void *dict_get(DICT *dict, const char *key) {
  unsigned int i;
  unsigned int hash;
  hash = hash_string(key);
  for (i = 0; i < dict->used; ++i) {
    if (hash == dict->keys[i])
      return dict->values[i];
  }
  return NULL;
}
void dict_remove(DICT *dict, const char *key) {
  // THIS SPACE INTENTIONALLY LEFT BLANK
}
void dict_free(DICT *dict) {
}