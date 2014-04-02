/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_CREDITSSCREENLOGIC__
#define __COMP_CREDITSSCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_CREDITSSCREENLOGIC HASH("COMP_CREDITSSCREENLOGIC")
void comp_creditsScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_creditsScreenLogic(COMPONENT *self);
void comp_creditsScreenLogic_initialize(COMPONENT *self, void *event);

#endif
