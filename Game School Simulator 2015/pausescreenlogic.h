/******************************************************************************
Filename: pausescreenlogic.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/

#ifndef __COMP_PAUSESCREENLOGIC__
#define __COMP_PAUSESCREENLOGIC__

#include "entity.h"
#include "hash.h"
#include "playerlogic.h"

#define COMP_PAUSESCREENLOGIC HASH("COMP_PAUSESCREENLOGIC")

typedef struct {
  bool textCreated;
  ENTITY *masterText;
  char masterBuffer[10];
  ENTITY *soundText;
  char soundBuffer[10];
  ENTITY *musicText;
  char musicBuffer[10];
  ENTITY *ambientText;
  char ambientBuffer[10];
} CDATA_PAUSESCREEN;

void comp_pauseScreenLogic_frameUpdate(COMPONENT *self, void *event);
void comp_pauseScreenLogic(COMPONENT *self);
void comp_pauseScreenLogic_makeMenu(COMPONENT *self);

#endif
