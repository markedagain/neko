/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "managescreenlogic.h"

void comp_manageScreenLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_manageScreenLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_MANAGESCREENLOGIC);
  self->events.logicUpdate = comp_manageScreenLogic_logicUpdate;
}
