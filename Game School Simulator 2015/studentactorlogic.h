/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __STUDENTACTORLOGIC__
#define __STUDENTACTORLOGIC__

#include "entity.h"
#include "hash.h"

#define ARCH_STUDENTACTORLOGIC HASH("ARCH_STUDENTACTORLOGIC")
void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event);
void comp_studentActorLogic(COMPONENT *self);

#endif
