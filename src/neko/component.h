/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <stdlib.h>
#include "entity.h"
#include "event.h"

#define MAX_DEPENDS 8
#define COMPONENT_INIT(a, b, c) component_initialize(a, b, &c, sizeof(c))

typedef struct entity_t ENTITY;

typedef struct component_t {
  void *data;
  unsigned int id;
  ENTITY *owner;
  unsigned int depends[MAX_DEPENDS];
  EVENTCONTAINER events;
} COMPONENT;

void component_initialize(COMPONENT *, unsigned int, void *, size_t);
void component_depend(COMPONENT *, unsigned int);

#endif
