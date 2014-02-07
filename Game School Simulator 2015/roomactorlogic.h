/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_ROOMACTORLOGIC__
#define __COMP_ROOMACTORLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_ROOMACTORLOGIC HASH("COMP_CURSORLOGIC")

void comp_roomActorLogic_logicUpdate(COMPONENT *self, void *event);
void comp_roomActorLogic(COMPONENT *self);

#endif
