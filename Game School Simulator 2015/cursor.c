/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cursor.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/spritetext.h"
#include "cursorlogic.h"

void arch_cursor(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  CDATA_SPRITETEXT *spriteText;

  entity->id = ARCH_CURSOR;

  entity_connect(entity, comp_transform);

  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "cursor";

  spriteText = (CDATA_SPRITETEXT *)entity_connect(entity, comp_spriteText);
  strcpy(spriteText->text, "Hey hi hello");
  spriteText->color.r = 1;
  spriteText->color.g = 1;
  spriteText->color.b = 1;
  spriteText->color.a = 1;

  entity_connect(entity, comp_cursorLogic);
}