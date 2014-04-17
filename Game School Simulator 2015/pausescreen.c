/******************************************************************************
Filename: pausescreen.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/
#include "pausescreen.h"
#include "pausescreenlogic.h"
#include "transform.h"
#include "mousebox.h"

void arch_pauseScreen(ENTITY *entity) {
  CDATA_SPRITE *sprite;

  entity->id = ARCH_PAUSESCREEN;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_pauseScreenLogic);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  sprite->source = "ui/pauseBackground";
  sprite->color.a = 0.65f;
}
