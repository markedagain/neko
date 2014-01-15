/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "gamemanager.h"
#include "../NekoEngine/component.h"
#include "schoollogic.h"
#include "timemanager.h"

void arch_gameManager(ENTITY *entity) {
  entity->id = ARCH_GAMEMANAGER;

  entity_connect(entity, comp_schoolLogic);
  entity_connect(entity, comp_timeManager);
}