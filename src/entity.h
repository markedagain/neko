/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "vector.h"
#include "space.h"

typedef struct entity_t {
  unsigned int id;
  unsigned int type;
  struct entity_t *owner;
  SPACE *space;
  char[80] name;
  VECTOR tags;
  VECTOR components;
  VECTOR children;
  unsigned char shouldDestroy;
} ENTITY;

#endif
