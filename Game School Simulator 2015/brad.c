/******************************************************************************
Filename: brad.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/

#include "brad.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"

void arch_brad(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_BRAD;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "brad";
}
