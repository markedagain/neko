/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "test.h"
#include "../../neko/entity.h"
#include "../../neko/component.h"
#include "../../neko/components/transform.h"
#include "../../neko/components/sprite.h"
#include "../components/playerLogic.h"

void arch_test(ENTITY *entity) {
  CDATA_TRANSFORM *transform;
  CDATA_SPRITE *sprite;

  entity->id = ARCH_TEST;

  transform = (CDATA_TRANSFORM *)entity_connect(entity, comp_transform);
  transform->translation.x = 100.0f;
  transform->translation.y = -60.0f;

  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "data/textures/PlanetTexture.png";

  entity_connect(entity, comp_playerLogic);
}
