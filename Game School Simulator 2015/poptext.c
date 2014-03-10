/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "poptext.h"
#include "transform.h"
#include "spritetext.h"
#include "multisprite.h"

void arch_popText(ENTITY *entity) {
  entity->id = ARCH_POPTEXT;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_multiSprite);
  entity_connect(entity, comp_spriteText);
  entity_connect(entity, comp_popTextLogic);
}

ENTITY *popText_create(SPACE *space, VEC3 *position, char *name, char *font, char *text, VEC4 *color, POPTYPE popType, float duration) {
  ENTITY *entity = space_addEntity(space, arch_popText, name);
  CDATA_TRANSFORM *transData = (CDATA_TRANSFORM *)entity_getComponentData(entity, COMP_TRANSFORM);
  CDATA_SPRITETEXT *textData = (CDATA_SPRITETEXT *)entity_getComponentData(entity, COMP_SPRITETEXT);
  CDATA_POPTEXT *popTextData = (CDATA_POPTEXT *)entity_getComponentData(entity, COMP_POPTEXTLOGIC);
  COMPONENT *comText = entity_getComponent(entity, COMP_SPRITETEXT);
  vec3_copy(&transData->translation, position);
  textData->font = font;
  textData->alignment.x = TEXTALIGN_CENTER;
  textData->alignment.y = TEXTALIGN_BOTTOM;
  popTextData->type = popType;
  popTextData->duration = duration;
  vec4_copy(&textData->color, color);
  comp_spriteText_setText(comText, text);
  return entity;
}