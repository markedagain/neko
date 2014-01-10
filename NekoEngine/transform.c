/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "transform.h"
#include "component.h"
#include "entity.h"
#include "event.h"
#include "util.h"

void comp_transform_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *comData = (CDATA_TRANSFORM *)self->data;
  comData->rotation = (float)fmod(comData->rotation, 2.0f * (float)M_PI);
  if (comData->rotation < 0)
    comData->rotation += 2.0f * (float)M_PI;
}

void comp_transform_destroy(COMPONENT *self, void *event) {
}

void comp_transform(COMPONENT *self) {
  CDATA_TRANSFORM initData = { { 0, 0, 0 }, { 1, 1, 1 }, 0 };
  COMPONENT_INIT(self, COMP_TRANSFORM, initData);
  self->events.logicUpdate = comp_transform_logicUpdate;
}
