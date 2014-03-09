/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_STUDENTACTORLOGIC__
#define __COMP_STUDENTACTORLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_STUDENTACTORLOGIC HASH("COMP_STUDENTACTORLOGIC")
void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event);
void comp_studentActorLogic(COMPONENT *self);
void comp_studentActorLogic_initialize(COMPONENT *self, void *event);
void comp_studentActorLogic_flipSprite(COMPONENT *self);

typedef struct {
  float timer;
  float timer2;
  float lifetime;
  bool setSprite;
  float velocity;
  float roomSize;
  float origin;
  bool fadeIn;
  bool fadeOut;
  ENTITY *studentPtr;
  char legs[30];
  char head[30];
  char face[30];
  char body[30];
  char hair[30];
} CDATA_STUDENTACTOR;

#endif
