/******************************************************************************
Filename: cloud.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "cloud.h"
#include "cloudlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/transform.h"

void arch_cloud(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  entity->id = ARCH_CLOUD;


  //Connect components to the entity
  entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_cloudLogic);
  sprite->source = "backgrounds/cloud1";
}
