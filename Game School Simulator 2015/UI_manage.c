/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "UI_manage.h"
#include "management.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"

void arch_uimanage(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_UIMANAGE;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_management);
  sprite->source = "backgrounds/white_box";
}