/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "poptextlogic.h"

void comp_popTextLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_popTextLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_POPTEXTLOGIC);
  self->events.logicUpdate = comp_popTextLogic_logicUpdate;
}
