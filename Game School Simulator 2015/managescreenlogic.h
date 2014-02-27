/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MANAGESCREENLOGIC__
#define __COMP_MANAGESCREENLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_MANAGESCREENLOGIC HASH("COMP_MANAGESCREENLOGIC")

typedef struct{
  char gpaBuffer[40];
  char tuitionBuffer[40];
  char costsBuffer[40];
  char studentPopBuffer[40];
  char studentIncBuffer[40];
  int currStudentInc;
  int currUpkeep;
  int currStudentPop;
  float currMinGpa;
  ENTITY *gpa;
  ENTITY *tuition;
  ENTITY *manageWindow;
  ENTITY *titleText;
  ENTITY *currMoney;
  ENTITY *currCosts;
  ENTITY *studentPop;
  ENTITY *studentInc;
  bool updateTriggered;
} CDATA_MANAGESCREEN;

void comp_manageScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_manageScreenLogic(COMPONENT *self);

#endif
