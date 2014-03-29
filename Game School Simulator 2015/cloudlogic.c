/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cloudLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"

// fix all mboxes to handle things
void comp_cloudLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_CLOUDLOGIC *comData = (CDATA_CLOUDLOGIC *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);

  vec3_set(&trans->translation, (float)(trans->translation.x + comData->speed * self->owner->space->game->systems.time.dt), trans->translation.y, trans->translation.z);
}


void comp_cloudLogic(COMPONENT *self) {
  CDATA_CLOUDLOGIC data = { 0 };
  data.speed = 10;

  COMPONENT_INIT(self, COMP_CLOUDLOGIC, data);
  self->events.logicUpdate = comp_cloudLogic_logicUpdate;
}
