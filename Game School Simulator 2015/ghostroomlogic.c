#include "ghostroomlogic.h"
#include "mousebox.h"
#include "../NekoEngine/component.h"

void comp_ghostRoomLogic_logicUpdate(COMPONENT *self, void *event) {
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *cursor = space_getEntity(uiSpace, "cursor");
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_TRANSFORM *cursorTrans = (CDATA_TRANSFORM *)entity_getComponentData(cursor, COMP_TRANSFORM);
  
  trans->translation.x = cursorTrans->translation.x;
  trans->translation.y = cursorTrans->translation.y;
}

void comp_ghostRoomLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_GHOSTROOMLOGIC);
  self->events.logicUpdate = comp_ghostRoomLogic_logicUpdate;
}