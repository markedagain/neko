/******************************************************************************
Filename: cursor.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "cursor.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "cursorlogic.h"

void arch_cursor(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_CURSOR;

  entity_connect(entity, comp_transform);

  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "cursor/default";
  sprite->visible = false;

  entity_connect(entity, comp_cursorLogic);
}