/******************************************************************************
Filename: component.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <stdlib.h>
#include "neko.h"
#include "event.h"
#include "entity.h"

#define MAX_DEPENDS 8
#define COMPONENT_INIT(self, id, data) component_initialize(self, id, &data, sizeof(data))
#define COMPONENT_INIT_NULL(self, id) component_initialize(self, id, NULL, sizeof(void *))

typedef struct entity_t ENTITY;

typedef struct component_t {
  void *data;
  unsigned int id;
  ENTITY *owner;
  unsigned int depends[MAX_DEPENDS];
  EVENTCONTAINER events;
} COMPONENT;

NEKO_API void component_initialize(COMPONENT *, unsigned int, void *, size_t);
NEKO_API void component_depend(COMPONENT *, unsigned int);
NEKO_API void component_doEvent(COMPONENT *, EVENT_TYPE, void *);

#endif
