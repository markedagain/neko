/******************************************************************************
Filename: menuscreen.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "menuscreen.h"
#include "menuscreenlogic.h"
#include "transform.h"

void arch_menuScreen(ENTITY *entity) {
  entity->id = ARCH_MENUSCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_menuScreenLogic);
}
