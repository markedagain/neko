/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MANAGESCREENLOGIC__
#define __COMP_MANAGESCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_MANAGESCREENLOGIC HASH("COMP_MANAGESCREENLOGIC")
void comp_manageScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_manageScreenLogic(COMPONENT *self);

#endif
