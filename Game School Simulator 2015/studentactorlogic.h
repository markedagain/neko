/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_STUDENTACTORLOGIC__
#define __COMP_STUDENTACTORLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_STUDENTACTORLOGIC HASH("COMP_STUDENTACTORLOGIC")
void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event);
void comp_studentActorLogic(COMPONENT *self);

typedef struct {
  float timer;
  float lifetime;
  bool setSprite;
} CDATA_STUDENTACTOR;

#endif
