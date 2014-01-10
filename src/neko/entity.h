/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "vector.h"
#include "space.h"
#include "component.h"
#include "linkedlist.h"

typedef struct component_t COMPONENT;

typedef struct entity_t {
  unsigned int id;
  struct entity_t *parent;
  SPACE *space;
  char name[80];
  VECTOR components;
  VECTOR children;
  LIST_NODE *node;
  unsigned char destroying;
} ENTITY;

typedef void (*entity_callback)(ENTITY *);
typedef void (*component_callback)(COMPONENT *);

ENTITY *entity_create(entity_callback, char *);
void entity_attach(ENTITY *, ENTITY *);
void *entity_connect(ENTITY *, component_callback);
COMPONENT *entity_getComponent(ENTITY *, unsigned int);
void *entity_getComponentData(ENTITY *, unsigned int);
void entity_destroy(ENTITY *);
void __entity_destroy(ENTITY *);

#endif
