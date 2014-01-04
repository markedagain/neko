/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "../component.h"
#include "../entity.h"

#ifndef __COMP_SPRITE__
#define __COMP_SPRITE__
int COMP_SPRITE = __COUNTER__;
#endif

void comp_sprite(COMPONENT *self) {
  CDATA_SPRITE initData = {};
  self->data = malloc(sizeof(CDATA_SPRITE));
  memcpy(self->data, &initData, sizeof(CDATA_SPRITE));
  strcpy(self->name, "sprite");
}
