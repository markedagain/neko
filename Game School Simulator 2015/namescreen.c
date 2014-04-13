/******************************************************************************
Filename: namescreen.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "namescreen.h"
#include "namescreenlogic.h"
#include "transform.h"

void arch_nameScreen(ENTITY *entity) {
  entity->id = ARCH_NAMESCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_nameScreenLogic);
}
