/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "genericsprite.h"
#include "transform.h"
#include "sprite.h"

void arch_genericsprite(ENTITY *entity) {
  entity->id = ARCH_GENERICSPRITE;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_sprite);
}