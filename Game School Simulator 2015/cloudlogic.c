/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cloudLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "weathermanager.h"

// fix all mboxes to handle things
void comp_cloudLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_CLOUDLOGIC *comData = (CDATA_CLOUDLOGIC *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_WEATHERMANAGER *weatherData = (CDATA_WEATHERMANAGER *)entity_getComponentData(space_getEntity(self->owner->space, "backdrop"), COMP_WEATHERMANGER);

  vec3_set(&trans->translation, (float)(trans->translation.x + comData->speed * 0.025f), trans->translation.y, trans->translation.z);
  if(trans->translation.x > 1000) {
    --weatherData->clouds;
    entity_destroy(self->owner);
  }
}


void comp_cloudLogic(COMPONENT *self) {
  CDATA_CLOUDLOGIC data = { 0 };
  data.speed = 10;

  COMPONENT_INIT(self, COMP_CLOUDLOGIC, data);
  self->events.logicUpdate = comp_cloudLogic_logicUpdate;
}
