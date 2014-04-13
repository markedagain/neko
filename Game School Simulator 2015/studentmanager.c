/******************************************************************************
Filename: studentmanager.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "studentmanager.h"
#include "studentmanagerlogic.h"

void arch_studentManager(ENTITY *entity) {
  entity->id = ARCH_STUDENTMANAGER;
  entity_connect(entity, comp_studentManagerLogic);
}
