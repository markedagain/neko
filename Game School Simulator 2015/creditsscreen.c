/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "creditsscreen.h"
#include "creditsscreenlogic.h"
#include "transform.h"
#include "sprite.h"
#include "mousebox.h"

void arch_creditsScreen(ENTITY *entity) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity->id = ARCH_CREDITSSCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_creditsScreenLogic);
  entity_connect(entity, comp_mouseBox);
  sprite->source = "backgrounds/credits";
}
