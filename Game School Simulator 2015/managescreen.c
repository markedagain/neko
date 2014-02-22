/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "managescreen.h"
#include "managescreenlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"

void arch_manageScreen(ENTITY *entity) {
  CDATA_SPRITE *sprite;  
  
  entity->id = ARCH_MANAGESCREEN;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_manageScreenLogic);
  sprite->source = "backgrounds/manage_screen_box";

}
