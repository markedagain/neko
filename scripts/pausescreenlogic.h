/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_PAUSESCREENLOGIC__
#define __COMP_PAUSESCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_PAUSESCREENLOGIC HASH("COMP_PAUSESCREENLOGIC")
void comp_pauseScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_pauseScreenLogic(COMPONENT *self);

#endif
