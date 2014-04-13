/******************************************************************************
Filename: generictext.c

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "generictext.h"
#include "transform.h"
#include "multisprite.h"
#include "spritetext.h"

void arch_genericText(ENTITY *entity) {
  entity->id = ARCH_GENERICTEXT;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_multiSprite);
  entity_connect(entity, comp_spriteText);
}

ENTITY *genericText_create(SPACE *space, VEC3 *position, char *name, char *font, char *text, VEC4 *color, TEXTALIGN xAlign, TEXTALIGN yAlign) {
  ENTITY *entity = space_addEntity(space, arch_genericText, name);
  CDATA_TRANSFORM *transData = ((CDATA_TRANSFORM *)entity_getComponentData(entity, COMP_TRANSFORM));
  CDATA_SPRITETEXT *textData = ((CDATA_SPRITETEXT *)entity_getComponentData(entity, COMP_SPRITETEXT));
  textData->font = font;
  textData->alignment.x = xAlign;
  textData->alignment.y = yAlign;
  vec4_copy(&textData->color, color);
  
  vec3_copy(&transData->translation, position);
  
  genericText_setText(entity, text);
  return entity;
}

void genericText_setText(ENTITY *entity, char *text) {
  COMPONENT *comText = entity_getComponent(entity, COMP_SPRITETEXT);
  CDATA_MULTISPRITE *multi = (CDATA_MULTISPRITE *)entity_getComponentData(entity, COMP_MULTISPRITE);
  LIST_NODE *node;
  comp_spriteText_setText(comText, text);
  node = multi->entities->first;
  while (node) {
    comp_transform_frameUpdate(entity_getComponent((ENTITY *)node->data, COMP_TRANSFORM), NULL);
    node = node->next;
  }

}