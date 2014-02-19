/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "background.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "mousebox.h"
#include "backgroundlogic.h"

void arch_background(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_BACKGROUND;

  entity_connect(entity, comp_transform);

  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "backgrounds/basic";

  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_backgroundLogic);
}