/******************************************************************************
Filename: homework.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "homework.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"
#include "mousebox.h"
#include "homeworklogic.h"

void arch_homework(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  entity->id = ARCH_HOMEWORK;

  //Connect components to the entity
  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_homeworkLogic);
  sprite->source = "student/homework";
}
