/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "pausescreen.h"
#include "pausescreenlogic.h"
#include "transform.h"
#include "mousebox.h"

void arch_pauseScreen(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_PAUSESCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_pauseScreenLogic);
  entity_connect(entity, comp_mouseBox);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);

  sprite->source = "ui/pauseBackground";
  sprite->color.a = 0.65f;
}
