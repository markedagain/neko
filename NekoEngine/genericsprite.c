/******************************************************************************
Filename: genericsprite.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "genericsprite.h"
#include "transform.h"
#include "sprite.h"

void arch_genericSprite(ENTITY *entity) {
  entity->id = ARCH_GENERICSPRITE;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_sprite);
}

ENTITY *genericSprite_create(SPACE *space, VEC3 *position, char *name, char *source) {
  ENTITY *entity = space_addEntity(space, arch_genericSprite, name);
  CDATA_TRANSFORM *transData = ((CDATA_TRANSFORM *)entity_getComponentData(entity, COMP_TRANSFORM));
  CDATA_SPRITE *spriteData = ((CDATA_SPRITE *)entity_getComponentData(entity, COMP_SPRITE));
  vec3_copy(&transData->translation, position);
  spriteData->source = source;
  return entity;
}

ENTITY *genericSprite_createBlank(SPACE *space, VEC3 *position, VEC2 *dimensions, VEC4 *color, char *name) {
  ENTITY *entity = genericSprite_create(space, position, name, "blank");
  CDATA_SPRITE *spriteData = ((CDATA_SPRITE *)entity_getComponentData(entity, COMP_SPRITE));
  vec2_copy(&spriteData->size, dimensions);
  vec4_copy(&spriteData->color, color);
  return entity;
}