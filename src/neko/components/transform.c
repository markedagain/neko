/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "transform.h"
#include "../component.h"
#include "../entity.h"

void comp_transform(COMPONENT *self) {
  self->id = COMP_TRANSFORM;
  CDATA_TRANSFORM initData = { { 0, 0, 0 }, { 1, 1, 1 }, 0 };
  self->data = malloc(sizeof(CDATA_TRANSFORM));
  memcpy(self->data, &initData, sizeof(CDATA_TRANSFORM));
}
