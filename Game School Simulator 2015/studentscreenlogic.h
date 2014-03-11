/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_STUDENTSCREENLOGIC__
#define __COMP_STUDENTSCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_STUDENTSCREENLOGIC HASH("COMP_STUDENTSCREENLOGIC")

typedef struct{
  ENTITY *studentTxt;
} CDATA_STUDENTSCREEN;

void comp_studentScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_studentScreenLogic(COMPONENT *self);

#endif
