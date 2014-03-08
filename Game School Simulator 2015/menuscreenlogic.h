/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MENUSCREENLOGIC__
#define __COMP_MENUSCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_MENUSCREENLOGIC HASH("COMP_MENUSCREENLOGIC")
void comp_menuScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_menuScreenLogic(COMPONENT *self);
void comp_menuScreenLogic_initialize(COMPONENT *self, void *event);

#endif
