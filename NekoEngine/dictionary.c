/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "dictionary.h"
#include "util.h"

void dict_init(DICT *dict) {
  vector_init(&dict->keys);
  vector_init(&dict->values);
  vector_init(&dict->empties);
  dict->count = 0;
}

void sdict_set(DICT *dict, char *key, void *value) {

  if (vector_size(&dict->empties) > 0) {
    // TODO: HANDLE EMPTIES
  }
  
}
void *sdict_get(DICT *dict, char *key) {
  int i;
  bool found = false;
  for (i = 0; i < vector_size(&dict->keys); ++i) {
  }
  return NULL;
}
void sdict_remove(DICT *dict, char *key) {
}
void sdict_free(DICT *dict) {
}