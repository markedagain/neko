/******************************************************************************
Filename: inspectionscreenlogic.h

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_INSPECTIONSCREENLOGIC__
#define __COMP_INSPECTIONSCREENLOGIC__

#include "entity.h"
#include "hash.h"
#include "roomlogic.h"

#define COMP_INSPECTIONSCREENLOGIC HASH("COMP_INSPECTIONSCREENLOGIC")

typedef struct cdata_inspectionScreen_t {
  bool active;
  bool posActive;
  bool studentActive;
  bool triggered;

  // STUDENT INSPECTION
  char nameBuffer[30];
  char GPA[16];
  char expectedGraduationYear[30];
  char major[16];
  char motivation[16];
  ENTITY *studentName;
  ENTITY *studentMajor;
  ENTITY *studentGPA;
  ENTITY *studentGraduation;
  ENTITY *studentMotivation;

  // ROOM INSPECTION
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
  int posX;
  int posY;
  } CDATA_INSPECTIONSCREEN;

void room_inspection_clear(COMPONENT *self);
void student_inspection_clear(COMPONENT *self);
void comp_inspectionScreenLogic_logicUpdate(COMPONENT *self, void *event);
void comp_inspectionScreenLogic(COMPONENT *self);
void comp_inspectionScreenLogic_initialize(COMPONENT *self, void *event);

#endif
