#include "studentactorlogic.h"

void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event) {
}

void comp_studentActorLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_STUDENTACTORLOGIC);
  self->events.logicUpdate = comp_studentActorLogic_logicUpdate;
}
