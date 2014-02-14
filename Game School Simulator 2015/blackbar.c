/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "blackbar.h"
#include "transform.h"
#include "sprite.h"
#include "blackbarlogic.h"

void arch_blackbar(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_BLACKBAR;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "blank";
  sprite->visible = false;
  vec4_set(&sprite->color, 0.0f, 0.0f, 0.0f, 1.0f);

  entity_connect(entity, comp_blackBarLogic);
}