/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "neko.h"
#include "vector.h"
#include "space.h"
#include "game.h"
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
  bool handled[EV_LAST];
} ENTITY;

typedef void (*entity_callback)(ENTITY *);
typedef void (*component_callback)(COMPONENT *);

ENTITY *entity_create(entity_callback, char *);
NEKO_API void entity_attach(ENTITY *, ENTITY *);
NEKO_API void *entity_connect(ENTITY *, component_callback);
NEKO_API COMPONENT *entity_getComponent(ENTITY *, unsigned int);
NEKO_API void *entity_getComponentData(ENTITY *, unsigned int);
void entity_invokeEvent(ENTITY *entity, EVENT_TYPE event, void *data);
NEKO_API void entity_destroy(ENTITY *);
void __entity_destroy(ENTITY *);

#endif
