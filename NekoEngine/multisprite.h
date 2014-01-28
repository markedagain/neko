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

NEKO_API void comp_multiSprite(COMPONENT *);

#endif
