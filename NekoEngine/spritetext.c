/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "spritetext.h"
#include "entity.h"
#include "transform.h"
#include "vectormath.h"

void comp_spriteText_draw(COMPONENT *self, void *event) {
  CDATA_SPRITETEXT *data = (CDATA_SPRITETEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);

}

void comp_spriteText(COMPONENT *self) {
  CDATA_SPRITETEXT data = { 0 };
  data.color.r = 1;
  data.color.g = 1;
  data.color.b = 1;
  data.color.a = 1;
  COMPONENT_INIT(self, COMP_SPRITETEXT, data);
  component_depend(self, COMP_TRANSFORM);
}