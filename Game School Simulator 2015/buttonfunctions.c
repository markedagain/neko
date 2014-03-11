/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "buttonfunctions.h"

void custom_onHover(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  sprite->color.r = 1.0f;
}

void custom_onExit(COMPONENT *self) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

  sprite->color.r = 0.5f;
}
