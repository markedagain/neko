/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "managescreen.h"
#include "managescreenlogic.h"
#include "transform.h"

void arch_manageScreen(ENTITY *entity) {
  entity->id = ARCH_MANAGESCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_manageScreenLogic);
}
