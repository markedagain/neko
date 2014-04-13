/******************************************************************************
Filename: UI_studentLogic.h

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_UI_STUDENTLOGIC__
#define __COMP_UI_STUDENTLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_UI_STUDENTLOGIC HASH("COMP_UI_STUDENTLOGIC")

typedef struct{
  ENTITY *ent1;
  ENTITY *ent2;
  ENTITY *ent3;
} CDATA_UI_STUDENTLOGIC;

void comp_UI_studentLogicUpdate(COMPONENT *self, void *event);
void comp_UI_studentLogic(COMPONENT *self);

#endif
