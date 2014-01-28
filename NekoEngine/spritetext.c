/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "spritetext.h"
#include "entity.h"
#include "transform.h"
#include "vectormath.h"
#include "genericsprite.h"
#include "sprite.h"

void comp_spriteText_initialize(COMPONENT *self, void *event) {
  CDATA_SPRITETEXT *data = (CDATA_SPRITETEXT *)self->data;
  int i;
  vector_init(&data->characters);
  for (i = 0; i < SPRITETEXT_MAXLENGTH; ++i) {
    ENTITY *ent = space_addEntity(self->owner->space, arch_genericSprite, NULL);
    CDATA_SPRITE *entData = (CDATA_SPRITE *)entity_getComponentData(ent, COMP_SPRITE);
    entData->source = data->font;

  }
}

void comp_spriteText_draw(COMPONENT *self, void *event) {
  CDATA_SPRITETEXT *data = (CDATA_SPRITETEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
}

void comp_spriteText(COMPONENT *self) {
  CDATA_SPRITETEXT data = { 0 };
  data.font = "fonts/8x8";
  data.color.r = 1;
  data.color.g = 1;
  data.color.b = 1;
  data.color.a = 1;
  COMPONENT_INIT(self, COMP_SPRITETEXT, data);
  component_depend(self, COMP_TRANSFORM);
  self->events.initialize = comp_spriteText_initialize;
  self->events.draw = comp_spriteText_draw;
}