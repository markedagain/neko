/******************************************************************************
Filename: creditsscreenlogic.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_CREDITSSCREENLOGIC__
#define __COMP_CREDITSSCREENLOGIC__

#include "entity.h"
#include "hash.h"
#include "actionlist.h"

#define COMP_CREDITSSCREENLOGIC HASH("COMP_CREDITSSCREENLOGIC")

typedef struct {
  bool finishedFading;
  ALIST actions;
} CDATA_CREDITS;

void comp_creditsScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_creditsScreenLogic(COMPONENT *self);
void comp_creditsScreenLogic_initialize(COMPONENT *self, void *event);

#endif
