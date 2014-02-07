/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "UI_base.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"
#include "UI_logic.h"

void arch_uibase(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_UIBASE;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_UI_logic);
  sprite->source = "backgrounds/test_ui";
}