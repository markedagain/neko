/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_POPTEXTLOGIC__
#define __COMP_POPTEXTLOGIC__

#include "entity.h"
#include "hash.h"

typedef struct {
  float timer;
  float alpha;
} CDATA_POPTEXT;

#define COMP_POPTEXTLOGIC HASH("COMP_POPTEXTLOGIC")
void comp_popTextLogic_logicUpdate(COMPONENT *self, void *event);
void comp_popTextLogic(COMPONENT *self);

#endif
