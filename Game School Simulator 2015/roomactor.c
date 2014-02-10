/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "roomactor.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"
#include "roomactorlogic.h"

void arch_roomActor(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  entity->id = ARCH_ROOMACTOR;

  //Connect components to the entity
  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_roomActorLogic);
  sprite->source = "rooms/template";
}
