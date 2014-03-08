/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_INSPECTIONSCREENLOGIC__
#define __COMP_INSPECTIONSCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_INSPECTIONSCREENLOGIC HASH("COMP_INSPECTIONSCREENLOGIC")
void comp_inspectionScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_inspectionScreenLogic(COMPONENT *self);

#endif
