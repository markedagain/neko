/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "poptext.h"
#include "poptextlogic.h"
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

ENTITY *popText_create(SPACE *space, VEC3 *position, char *name, char *font, char *text, VEC4 *color) {
  ENTITY *entity = space_addEntity(space, arch_popText, name);
  CDATA_TRANSFORM *transData = ((CDATA_TRANSFORM *)entity_getComponentData(entity, COMP_TRANSFORM));
  CDATA_SPRITETEXT *textData = ((CDATA_SPRITETEXT *)entity_getComponentData(entity, COMP_SPRITETEXT));
  COMPONENT *comText = entity_getComponent(entity, COMP_SPRITETEXT);
  vec3_copy(&transData->translation, position);
  textData->font = font;
  textData->alignment.x = TEXTALIGN_CENTER;
  textData->alignment.y = TEXTALIGN_BOTTOM;
  vec4_copy(&textData->color, color);
  comp_spriteText_setText(comText, text);
  return entity;
}