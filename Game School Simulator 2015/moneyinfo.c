/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "moneyinfo.h"
#include "moneyinfologic.h"
#include "transform.h"
#include "mousebox.h"
#include "sprite.h"
#include "component.h"

void arch_moneyInfo(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  CDATA_TRANSFORM *trans;
  entity->id = ARCH_MONEYINFO;

  trans = (CDATA_TRANSFORM *)entity_connect(entity, comp_transform);
  vec3_set(&trans->translation, 220, 120, 0); 
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "rooms/lobby";
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_moneyInfoLogic);
}
