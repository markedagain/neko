/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "namescreen.h"
#include "namescreenlogic.h"
#include "transform.h"

void arch_nameScreen(ENTITY *entity) {
  entity->id = ARCH_NAMESCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_nameScreenLogic);
}
