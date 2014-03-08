/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "inspectionscreen.h"
#include "inspectionscreenlogic.h"
#include "transform.h"
#include "sprite.h"

void arch_inspectionScreen(ENTITY *entity) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity->id = ARCH_INSPECTIONSCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_inspectionScreenLogic);
  sprite->source = "backgrounds/manage_screen_box";
}