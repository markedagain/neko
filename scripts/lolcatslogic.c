#include "lolcatslogic.h"

void comp_lolCatsLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_lolCatsLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_LOLCATSLOGIC);
  self->events.logicUpdate = comp_lolCatsLogic_logicUpdate;
}
