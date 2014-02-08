/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "UI_student.h"
#include "UI_studentLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"

void arch_uistudent(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_UISTUDENT;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_UI_studentLogic);
  sprite->source = "backgrounds/white_box";
}