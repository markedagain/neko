/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_CURSORLOGIC__
#define __COMP_CURSORLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_CURSORLOGIC HASH("COMP_CURSORLOGIC")

void comp_cursorLogic_logicUpdate(COMPONENT *, void *);
void comp_cursorLogic(COMPONENT *);
void snap_sprite(COMPONENT *self);
LIST_NODE *add_snap(COMPONENT *self, float left, float top, float right, float bot);
void remove_snap(COMPONENT *self, LIST_NODE *remove);
void comp_cursorLogic_destroy(COMPONENT *self, void *event);

typedef struct {
  LIST *snaps;
} CDATA_CURSORLOGIC;

#endif