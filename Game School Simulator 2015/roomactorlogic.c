#include "roomactorlogic.h"
#include "mousebox.h"
#include "../NekoEngine/component.h"
#include "inspectionscreen.h"


void comp_roomActorLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_ACTORLOGIC *comData = (CDATA_ACTORLOGIC *)self->data;
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  VEC3 position = { -100.0f, 100.0f, 0 };

  if (mbox->left.pressed) {
    space_addEntityAtPosition(ui, arch_inspectionScreen, "inspection_screen", &position);
  }

}

void comp_roomActorLogic(COMPONENT *self) {
  CDATA_ACTORLOGIC data;

  COMPONENT_INIT(self, COMP_ROOMACTORLOGIC, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_roomActorLogic_logicUpdate;
}