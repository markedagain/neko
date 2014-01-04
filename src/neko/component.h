/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <stdlib.h>
#include "entity.h"

#define MAX_DEPENDS 8
#define COMPONENT_INIT(a, b, c) component_initialize(a, b, &c, sizeof(c))

typedef struct entity_t ENTITY;

typedef struct component_t {
  void *data;
  unsigned int id;
  ENTITY *owner;
  unsigned int depends[MAX_DEPENDS];
  /*
  void (* update)(struct component_t *, float, float);
  void (* create)(struct component_t *);
  void (* destroy)(struct component_t *);
  */
} COMPONENT;

void component_initialize(COMPONENT *, unsigned int, void *, size_t);
void component_depend(COMPONENT *, unsigned int);

#endif

/*

typedef struct com_sprite_t {
  char[80] spriteSource;
  unsigned char currentFrame;
  unsigned char isVisible;
} COM_SPRITE;

function com_sprite_update(COMPONENT *self, float dt, float elapsedTime) {
  ((COM_SPRITE *)(*self))->currentFrame++;
  self->owner->shouldDestroy = 1;
}

*/
