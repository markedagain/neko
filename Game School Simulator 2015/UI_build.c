/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "UI_build.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"

void arch_uibuild(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_UIBUILD;

  entity_connect(entity, comp_transform);

  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  //sprite->source = "backgrounds/basic";
}