/******************************************************************************
Filename: moneyinfo.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content � 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "moneyinfo.h"
#include "moneyinfologic.h"
#include "transform.h"
#include "mousebox.h"
#include "component.h"
#include "sprite.h"

void arch_moneyInfo(ENTITY *entity) {
  CDATA_TRANSFORM *trans;
  CDATA_SPRITE *sprite;
  entity->id = ARCH_MONEYINFO;

  trans = (CDATA_TRANSFORM *)entity_connect(entity, comp_transform);
  vec3_set(&trans->translation, 260, 250, 0);
  sprite = (CDATA_SPRITE *)entity_connect(entity, comp_sprite);
  sprite->source = "ui/money_hover";
  entity_connect(entity, comp_mouseBox);
  entity_connect(entity, comp_moneyInfoLogic);
}
