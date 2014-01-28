/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

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

ENTITY *genericText_create(SPACE *space, VEC3 *position, char *name, char *font, char *text, VEC4 *color) {
  ENTITY *entity = space_addEntity(space, arch_genericText, name);
  CDATA_TRANSFORM *transData = ((CDATA_TRANSFORM *)entity_getComponentData(entity, COMP_TRANSFORM));
  CDATA_SPRITETEXT *textData = ((CDATA_SPRITETEXT *)entity_getComponentData(entity, COMP_SPRITETEXT));
  vec3_copy(&transData->translation, position);
  textData->font = font;
  strcpy(textData->text, text);
  vec4_copy(&textData->color, color);
  comp_spriteText_initialize(entity_getComponent(entity, COMP_SPRITETEXT), NULL);
  return entity;
}

void genericText_setText(ENTITY *entity, char *text) {
  COMPONENT *comText = entity_getComponent(entity, COMP_SPRITETEXT);
  comp_spriteText_setText(comText, text);
}