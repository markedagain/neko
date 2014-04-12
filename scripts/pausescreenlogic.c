/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "pausescreenlogic.h"

void comp_pauseScreenLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_pauseScreenLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_PAUSESCREENLOGIC);
  self->events.logicUpdate = comp_pauseScreenLogic_logicUpdate;
}
