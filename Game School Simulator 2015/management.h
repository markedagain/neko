/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_MANAGEMENT__
#define __COMP_MANAGEMENT__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_MANAGEMENT HASH("COMP_MANAGEMENT")

typedef struct{
  ENTITY *gpa;
  ENTITY *tuition;
  ENTITY *manageWindow;
  ENTITY *titleText;
  ENTITY *currMoney;
  ENTITY *currCosts;
  ENTITY *currStudents;
  ENTITY *studentMax;
  ENTITY *incomingStudents;
  bool triggered;
} CDATA_MANAGEMENT;

void comp_managementUpdate(COMPONENT *self, void *event);
void comp_management(COMPONENT *self);

#endif
