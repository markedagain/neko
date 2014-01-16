/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "room.h"
#include "../NekoEngine/component.h"
#include "roomlogic.h"

void arch_room(ENTITY *entity) {
  entity->id = ARCH_ROOM;

  //Connect components to the entity
  entity_connect(entity, comp_roomLogic);
}