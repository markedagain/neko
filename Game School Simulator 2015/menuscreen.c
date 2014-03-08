/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "menuscreen.h"
#include "menuscreenlogic.h"
#include "transform.h"

void arch_menuScreen(ENTITY *entity) {
  entity->id = ARCH_MENUSCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_menuScreenLogic);
}
