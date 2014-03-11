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
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  ENTITY *inspectionScreen = space_getEntity(uiSpace, "inspection_screen");
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(inspectionScreen, COMP_INSPECTIONSCREENLOGIC); 
  CDATA_ACTORLOGIC *comData = (CDATA_ACTORLOGIC *)self->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);

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

  // CHANGE SPRITE TO EXTERIOR IF ZOOMED OUT
  if(fg->systems.camera.transform.scale.x <= 0.65f && comData->zoomedOut == FALSE) {
    switch (comData->type) {
    case ROOMTYPE_LOBBY:
        sprite->source = "rooms/frontdoor";
        break;
    case ROOMTYPE_CLASS:
      sprite->source = "rooms/exterior";
      break;
    case ROOMTYPE_LIBRARY:
      sprite->source = "rooms/exterior2";
      break;
    case ROOMTYPE_TEAMSPACE:
      sprite->source = "rooms/exterior3";
      break;
    case ROOMTYPE_CAFETERIA:
      sprite->source = "rooms/exterior3";
      break;
    case ROOMTYPE_STORE:
      sprite->source = "rooms/exterior";
      break;
    case ROOMTYPE_OFFICES:
      sprite->source = "rooms/exterior";
      break;
    case ROOMTYPE_AUDITORIUM:
      sprite->source = "rooms/exterior3";
      break;
    case ROOMTYPE_TUTORING:
      sprite->source = "rooms/exterior";
      break;
    case ROOMTYPE_WIFI:
      sprite->source = "rooms/exterior";
      break;
    case ROOMTYPE_RECREATION:
      sprite->source = "rooms/exterior2";
      break;
    case ROOMTYPE_FIGURE:
      sprite->source = "rooms/exterior2";
      break;
    case ROOMTYPE_POTTERY:
      sprite->source = "rooms/exterior2";
      break;
    }
    comData->zoomedOut = TRUE;
  }

  // CHANGE SPRITE BACK TO INTERERIOR UPON ZOOM IN
  if(fg->systems.camera.transform.scale.x > 0.65f && comData->zoomedOut == TRUE) {
     switch (comData->type) {
    case ROOMTYPE_LOBBY:
        sprite->source = "rooms/lobby";
        break;
    case ROOMTYPE_CLASS:
      sprite->source = "rooms/class";
      break;
    case ROOMTYPE_LIBRARY:
      sprite->source = "rooms/library";
      break;
    case ROOMTYPE_TEAMSPACE:
      sprite->source = "rooms/teamspace";
      break;
    case ROOMTYPE_CAFETERIA:
      sprite->source = "rooms/cafeteria";
      break;
    case ROOMTYPE_STORE:
      sprite->source = "rooms/store";
      break;
    case ROOMTYPE_OFFICES:
      sprite->source = "rooms/offices";
      break;
    case ROOMTYPE_AUDITORIUM:
      sprite->source = "rooms/auditorium";
      break;
    case ROOMTYPE_TUTORING:
      sprite->source = "rooms/tutoring";
      break;
    case ROOMTYPE_WIFI:
      sprite->source = "rooms/wifi";
      break;
    case ROOMTYPE_RECREATION:
      sprite->source = "rooms/recreation";
      break;
    case ROOMTYPE_FIGURE:
      sprite->source = "rooms/figure";
      break;
    case ROOMTYPE_POTTERY:
      sprite->source = "rooms/library";
      break;
    }
    comData->zoomedOut = FALSE;
  }
}

void comp_roomActorLogic(COMPONENT *self) {
  CDATA_ACTORLOGIC data = { 0 };
  data.triggered = false;
  data.zoomedOut = FALSE;
  COMPONENT_INIT(self, COMP_ROOMACTORLOGIC, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_roomActorLogic_logicUpdate;
}