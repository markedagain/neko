/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "inspectionscreenlogic.h"

void comp_inspectionScreenLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_inspectionScreenLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_INSPECTIONSCREENLOGIC);
  self->events.logicUpdate = comp_inspectionScreenLogic_logicUpdate;
}
