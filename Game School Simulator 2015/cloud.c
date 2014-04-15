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
#include "random.h"

void arch_cloud(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  CDATA_TRANSFORM *trans;
  float scaleMult = 0;
  entity->id = ARCH_CLOUD;


  //Connect components to the entity
  trans = (CDATA_TRANSFORM *)entity_connect(entity, comp_transform);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  entity_connect(entity, comp_cloudLogic);
  sprite->source = "backgrounds/cloud1";
  scaleMult = randomFloatRange(0.6f, 1.2f);
  vec3_set(&trans->scale, scaleMult, scaleMult, 0);
}
