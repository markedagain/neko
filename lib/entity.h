/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ENTITY_H__
#define __ENTITY_H__

typedef struct entity_t {
  unsigned int id;
  unsigned int type;
  ENTITY *owner;
  SPACE *space;
  char[80] name;
  VECTOR tags;
  VECTOR components;
  VECTOR children;
  unsigned char shouldDestroy;
} ENTITY;

#endif
