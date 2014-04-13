/******************************************************************************
Filename: room.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "room.h"
#include "../NekoEngine/component.h"
#include "roomlogic.h"

void arch_room(ENTITY *entity) {
  entity->id = ARCH_ROOM;

  //Connect components to the entity
  entity_connect(entity, comp_roomLogic);
}