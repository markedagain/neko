/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_PAUSESCREENLOGIC__
#define __COMP_PAUSESCREENLOGIC__

#include "entity.h"
#include "hash.h"
#include "playerlogic.h"

#define COMP_PAUSESCREENLOGIC HASH("COMP_PAUSESCREENLOGIC")

typedef struct {
  bool textCreated;
  GMODE lastMode;
} CDATA_PAUSESCREEN;

void comp_pauseScreenLogic_frameUpdate(COMPONENT *self, void *event);
void comp_pauseScreenLogic(COMPONENT *self);

#endif
