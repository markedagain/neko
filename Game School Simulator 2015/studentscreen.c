/******************************************************************************
Filename: studentscreen.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "studentscreen.h"
#include "studentscreenlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"

void arch_studentScreen(ENTITY *entity) {
  CDATA_SPRITE *sprite;  
  
  entity->id = ARCH_STUDENTSCREEN;

  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_studentScreenLogic);
  sprite->source = "backgrounds/student_screen_box";

}
