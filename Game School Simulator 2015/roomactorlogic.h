/******************************************************************************
Filename: roomactorlogic.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_ROOMACTORLOGIC__
#define __COMP_ROOMACTORLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "roomlogic.h"
#include "actionlist.h"

#define COMP_ROOMACTORLOGIC HASH("COMP_ROOMACTORLOGIC")

typedef struct cdata_actorLogic_t {
  ROOM_TYPE type;
  bool triggered;
  BOOL zoomedOut;
  int posX;
  int posY;
  float startY;
  float targetY;
  ALIST actions;
} CDATA_ACTORLOGIC;

void comp_roomActorLogic_logicUpdate(COMPONENT *self, void *event);
void comp_roomActorLogic(COMPONENT *self);
void comp_roomActorLogic_initialize(COMPONENT *self, void *event);

#endif
