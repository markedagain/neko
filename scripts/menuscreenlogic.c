/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "menuscreenlogic.h"

void comp_menuScreenLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_menuScreenLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_MENUSCREENLOGIC);
  self->events.logicUpdate = comp_menuScreenLogic_logicUpdate;
}
