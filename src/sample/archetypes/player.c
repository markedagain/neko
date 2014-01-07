/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ARCH_PLAYER_H__
#define __ARCH_PLAYER_H__

#include "player.h"
#include "../../neko/entity.h"
#include "../../neko/component.h"
#include "../../neko/hash.h"
#include "../../neko/components/transform.h"
#include "../../neko/components/sprite.h"

#define ARCH_PLAYER HASH("ARCH_PLAYER")

void arch_player(ENTITY *entity) {
  CDATA_TRANSFORM *transform;
  CDATA_SPRITE *sprite;

  entity->id = ARCH_PLAYER;

  transform = (CDATA_TRANSFORM *)entity_connect(entity, comp_transform);
  transform->translation.x = 10;

  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "something_or_whatever.png";
}

#endif