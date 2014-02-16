/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MULTISPRITE_H__
#define __COMP_MULTISPRITE_H__

#include "neko.h"
#include "component.h"
#include "hash.h"
#include "linkedlist.h"
#include "sprite.h"
#include "transform.h"

#define COMP_MULTISPRITE HASH("COMP_MULTISPRITE")

typedef struct {
  LIST *entities;
} CDATA_MULTISPRITE;

void comp_multiSprite_destroy(COMPONENT *self, void *event);

NEKO_API void comp_multiSprite(COMPONENT *self);

NEKO_API void multiSprite_addSprite(COMPONENT *self, ENTITY *sprite);
NEKO_API void multiSprite_removeSprite(COMPONENT *self, size_t index);

#endif
