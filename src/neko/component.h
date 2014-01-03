/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "entity.h"

typedef struct entity_t ENTITY;

typedef struct component_t {
  void *data;
  ENTITY *owner;
  void (* update)(struct component_t *, float, float);
  void (* create)(struct component_t *);
  void (* destroy)(struct component_t *);
  
} COMPONENT;

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
