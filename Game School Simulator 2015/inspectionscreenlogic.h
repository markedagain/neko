/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_INSPECTIONSCREENLOGIC__
#define __COMP_INSPECTIONSCREENLOGIC__

#include "entity.h"
#include "hash.h"
#include "roomlogic.h"

#define COMP_INSPECTIONSCREENLOGIC HASH("COMP_INSPECTIONSCREENLOGIC")

typedef struct cdata_inspectionScreen_t {
  bool active;
  bool posActive;
  ROOM_TYPE type;
  char roomTypeBuffer[20];
  char bonusBuffer[128];
  char upkeepBuffer[20];
  char upgradeCostBuffer[20];
  char upgradeMessageBuffer[64];
  char levelBuffer[20];
  ENTITY *bonusText;
  ENTITY *upgradeCost;
  ENTITY *roomType;
  ENTITY *bonuses;
  ENTITY *upkeep;
  ENTITY *upgradeButton;
  ENTITY *level;
  bool triggered;
  int posX;
  int posY;
  int bonusSum;
  } CDATA_INSPECTIONSCREEN;

void comp_inspectionScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_inspectionScreenLogic(COMPONENT *self);
void comp_inspectionScreenLogic_initialize(COMPONENT *self, void *event);

#endif
