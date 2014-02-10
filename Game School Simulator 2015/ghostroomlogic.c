#include "ghostroomlogic.h"
#include "mousebox.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "playerlogic.h"
#include "cursorlogic.h"

void comp_ghostRoomLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  
  

  if (mbox->over) {
    sprite->color.a = 0.9f;
  }
  else
    sprite->color.a = 0.75f;

  if (mbox->left.pressed) {
    SPACE *ui = game_getSpace(self->owner->space->game, "ui");
    ENTITY *cursor = space_getEntity(ui, "cursor");
    ENTITY *player = space_getEntity(ui, "player");
    CDATA_PLAYERLOGIC *playerData = entity_getComponentData(player, COMP_PLAYERLOGIC);
    CDATA_CURSORLOGIC *cursorData = entity_getComponentData(player, COMP_CURSORLOGIC);

    playerData->gameMode = DEFAULT;
    cursorData->gameMode = DEFAULT;

    sprite->color.a = 1.0f;

  }
}

void comp_ghostRoomLogic_initialize(COMPONENT *self, void *event) {
  CDATA_GHOSTROOMLOGIC *data = (CDATA_GHOSTROOMLOGIC *)self->data;
  data->constructed = false;
}

void comp_ghostRoomLogic(COMPONENT *self) {
  CDATA_GHOSTROOMLOGIC data = { 0 };
  COMPONENT_INIT(self, COMP_GHOSTROOMLOGIC, data);
  self->events.logicUpdate = comp_ghostRoomLogic_logicUpdate;
  self->events.initialize = comp_ghostRoomLogic_initialize;
}