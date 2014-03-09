#include "roomactorlogic.h"
#include "mousebox.h"
#include "roomlogic.h"
#include "schoollogic.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include "inspectionscreen.h"
#include "inspectionscreenlogic.h"


void comp_roomActorLogic_logicUpdate(COMPONENT *self, void *event) {
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  ENTITY *inspectionScreen = space_getEntity(uiSpace, "inspection_screen");
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(inspectionScreen, COMP_INSPECTIONSCREENLOGIC); 
  CDATA_ACTORLOGIC *comData = (CDATA_ACTORLOGIC *)self->data;

  if (mbox->left.pressed && !inspectData->active && !comData->triggered) {
    inspectData->posActive = true;
    inspectData->posX = comData->posX;
    inspectData->posY = comData->posY;
    comData->triggered = true;
    inspectData->active = true;
  }
  else if (mbox->left.pressed && inspectData->active && (inspectData->posX != comData->posX 
    || inspectData->posY != comData->posY) && !comData->triggered) {
      inspectData->posX = comData->posX;
      inspectData->posY = comData->posY;
      inspectData->triggered = true;
  } 
  else if (mbox->left.pressed && inspectData->active && inspectData->posX == comData->posX 
    && inspectData->posY == comData->posY && !comData->triggered) {
    comData->triggered = true;
    inspectData->active = false;
  }
  else if (!mbox->left.pressed)
    comData->triggered = false;
}

void comp_roomActorLogic(COMPONENT *self) {
  CDATA_ACTORLOGIC data = { 0 };
  data.triggered = false;
  COMPONENT_INIT(self, COMP_ROOMACTORLOGIC, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_roomActorLogic_logicUpdate;
}