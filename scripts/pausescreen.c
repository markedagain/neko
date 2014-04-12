/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "pausescreen.h"
#include "pausescreenlogic.h"
#include "transform.h"

void arch_pauseScreen(ENTITY *entity) {
  entity->id = ARCH_PAUSESCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_pauseScreenLogic);
}
