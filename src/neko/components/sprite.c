/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "../component.h"
#include "../entity.h"

void comp_sprite(COMPONENT *self) {
  self->id = COMP_SPRITE;
  CDATA_SPRITE initData = {};
  self->data = malloc(sizeof(CDATA_SPRITE));
  memcpy(self->data, &initData, sizeof(CDATA_SPRITE));
}
