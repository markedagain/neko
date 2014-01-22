/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_CURSORLOGIC__
#define __COMP_CURSORLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_CURSORLOGIC HASH("COMP_CURSORLOGIC")

static VEC3 snaps[] = {{100, 100}, {-100, -100}};

void snap_sprite(COMPONENT *self, VEC3 *snaps, int size, float distance);
void comp_cursorLogic_logicUpdate(COMPONENT *, void *);
void comp_cursorLogic(COMPONENT *);

typedef struct {
  LIST *snapEntities;
} CDATA_CURSORLOGIC;

#endif