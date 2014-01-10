/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "transform.h"
#include "component.h"
#include "entity.h"
#include "event.h"

void comp_transform_logicUpdate(COMPONENT *self, void *data) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)data;
  CDATA_TRANSFORM *comData = (CDATA_TRANSFORM *)self->data;
  comData->rotation = (float)fmod(comData->rotation, 2.0f * (float)PI);
  if (comData->rotation < 0)
    comData->rotation += 2.0f * (float)PI;
}

void comp_transform_destroy(COMPONENT *self, void *data) {
}

void comp_transform(COMPONENT *self) {
  CDATA_TRANSFORM initData = { { 0, 0, 0 }, { 1, 1, 1 }, 0 };
  COMPONENT_INIT(self, COMP_TRANSFORM, initData);
  self->events.logicUpdate = comp_transform_logicUpdate;
}
