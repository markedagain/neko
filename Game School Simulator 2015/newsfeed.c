/******************************************************************************
Filename: newsfeed.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "newsfeed.h"
#include "newsfeedlogic.h"
#include "mousebox.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"

void arch_newsFeed(ENTITY *entity) {
  CDATA_SPRITE *sprite;
  CDATA_TRANSFORM *trans;
  entity->id = ARCH_NEWSFEED;

  //Connect components to the entity
  trans = (CDATA_TRANSFORM *)entity_connect(entity, comp_transform);
  vec3_set(&trans->translation, 0, 110, 0); 
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "empty";
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_newsfeedlogic);

}
