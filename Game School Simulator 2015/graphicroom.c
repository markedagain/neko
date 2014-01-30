/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "graphicroom.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"

void arch_graphicRoom(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  entity->id = ARCH_GRAPHICROOM;

  //Connect components to the entity
  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  sprite->source = "rooms/template2";
}
