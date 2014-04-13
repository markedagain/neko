/******************************************************************************
Filename: UI_build.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "UI_build.h"
#include "UI_button.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"

void arch_uibuild(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_UIBUILD;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_UI_button);
  sprite->source = "ui/individualRoomsButton";
}
